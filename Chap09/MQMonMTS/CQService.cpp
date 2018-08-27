
#include "precomp.h"
#include "cqservice.h"

#import "AgentMonMTSObject.dll" no_namespace //in project directory

#define AGENT_REQUEST_1 239
#define AGENT_REQUEST_2 240
#define TH_TYPE1 (WM_USER + 1020)
#define TH_TYPE2 (WM_USER + 1021)

IMPLEMENT_SERVICE( CQueueService, MQAgentMTS )

CQueueService::CQueueService( LPCTSTR szName, LPCTSTR szDisplay, DWORD dwType ) :
	  CService( szName, szDisplay, dwType ) 
{
	m_pThis = this;
	m_bStop  = FALSE;
	m_hQueue = NULL;
	m_bOpen = FALSE;
}

CQueueService::~CQueueService( )
{
}

//The main processing logic belongs in this overridable
//All start, running, and stop code here.
void CQueueService::Run( )
{
	SetStatus( SERVICE_RUNNING, 0, 0, SERVICE_ACCEPT_STOP );

	RetrieveMessage( ); //Loops until m_bStop is set

	//Tell the workers to quit
	for(int i=0; i<NUMWORKERS; i++ )
	{
		PostThreadMessage( m_dwWorkerID[i], WM_QUIT, 0, 0 );
	}

	WaitForMultipleObjects(NUMWORKERS, m_hWorkers, TRUE, 2000 ); 
	
	//Stopped, so exit
	SetStatus( SERVICE_STOP_PENDING, 2, 5000 );
}

void CQueueService::OnStop( )
{
	SetStatus( SERVICE_STOP_PENDING, 1, 20000 );

	//The ServiceMain thread could be reading this value!
	InterlockedExchange( (LPLONG) &m_bStop, (LONG) TRUE );
}

void CQueueService::Init( )
{
	SetStatus( SERVICE_START_PENDING, m_dwCheckpoint++, 2000 );

	//Initialize the Queue
	if (!OpenQueue( L".\\AgentMonitorQ", L"AgentMonitorQ" ))
		ErrorHandler( _TEXT( "Open Queue" ) );

	for( int i=0; i<NUMWORKERS; i++ )
	{
		m_hWorkers[i] = (HANDLE)_beginthreadex( NULL, 0, 
			(PBEGINTHREADEX_TFUNC)CQueueService::TFuncType, 
			0, 0, (PBEGINTHREADEX_TID)&m_dwWorkerID[i] );
		if( !m_hWorkers[i] )
			ErrorHandler( _TEXT( "Create Worker Thread") );
	}

	return;
}

void CQueueService::DeInit( )
{

	CloseQueue( );

	//Close worker threads
	for( int i=0; i<NUMWORKERS; i++ )
	{
		::CloseHandle( m_hWorkers[i] );
	}

	CService::DeInit( ); 
}

/////////////////////////////////////
HRESULT CQueueService::CreateQueue( )
{
	
	const DWORD cProps = 2;
	MQQUEUEPROPS qp;
    MQPROPVARIANT aVariant[cProps];
	QUEUEPROPID aPropId[cProps];

    DWORD cFN = MAX_QUEUE_PATH;
    TCHAR szFN[ MAX_QUEUE_PATH ];

    //Set the PROPID_Q_PATHNAME property.
    aPropId[0] = PROPID_Q_PATHNAME;    
	aVariant[0].vt = VT_LPWSTR;        
    aVariant[0].pwszVal = m_wszQueueName;         

	//Set the PROPID_Q_LABEL property.
    aPropId[1] = PROPID_Q_LABEL;    
    aVariant[1].vt = VT_LPWSTR;     
    aVariant[1].pwszVal = m_wszQueueLabel;         

	//Set the MQQUEUEPROPS structure.
    qp.cProp = cProps;           
    qp.aPropID = aPropId;             
    qp.aPropVar = aVariant;           
    qp.aStatus = NULL;                    

	HRESULT hr = MQCreateQueue(
         NULL,            
         &qp,                             
		 szFN,      
         &cFN );
		return hr;
}

BOOL CQueueService::OpenQueue( LPWSTR wszName, LPWSTR wszLabel )
{
    DWORD cFN = MAX_QUEUE_PATH;
    TCHAR szFN[ MAX_QUEUE_PATH ];
	HRESULT hr;

	_tcscpy( m_wszQueueName, wszName );
	_tcscpy( m_wszQueueLabel, wszLabel );
	
	hr = CreateQueue();

	if (FAILED(hr) && hr != MQ_ERROR_QUEUE_EXISTS )
	{
		return FALSE;
	}
	else
	{
		//Open the queue to get its handle
		hr = MQPathNameToFormatName(  m_wszQueueName, szFN, &cFN );
		if(FAILED(hr))
			return FALSE;

		hr = MQOpenQueue( szFN, MQ_RECEIVE_ACCESS, 0, &m_hQueue );
		if (FAILED(hr))
			return FALSE;
		
		_tcscpy( m_wszFormatName, szFN ); 
		m_bOpen = TRUE;
		return TRUE;
	}
}

void CQueueService::CloseQueue( )
{
	if (m_hQueue)
	{
		MQCloseQueue( m_hQueue );
		m_bOpen = FALSE;	
	}
}

void CQueueService::RetrieveMessage( )
{
	int count = 0;
	
	//Get the message type- asynch
	MQMSGPROPS*  pMsgp;
	pMsgp = new MQMSGPROPS;
	
	MQPROPVARIANT* paVar;
	paVar = new MQPROPVARIANT[4];

	MSGPROPID* paPropid;
	paPropid = new MSGPROPID[4];

	paPropid[0] = PROPID_M_APPSPECIFIC;
	paVar[0].vt = VT_UI4 ;
	paVar[0].ulVal  = 0;

	const long BODY_LEN = 50; //Hardcoded
	paPropid[1] = PROPID_M_BODY;
	paVar[1].vt = VT_VECTOR|VT_UI1;         
	paVar[1].caub.cElems = BODY_LEN ;    
	paVar[1].caub.pElems = new unsigned char[ BODY_LEN ]; 

	paPropid[2] = PROPID_M_RESP_QUEUE_LEN;
	paVar[2].vt = VT_UI4;
	paVar[2].ulVal = MAX_QUEUE_PATH;

	paPropid[3] = PROPID_M_RESP_QUEUE;
	paVar[3].vt = VT_LPWSTR;
	paVar[3].pwszVal = new TCHAR[MAX_QUEUE_PATH];

	pMsgp->cProp = 4;
	pMsgp->aPropID = paPropid;
	pMsgp->aPropVar = paVar;
	pMsgp->aStatus  = NULL;  

	OVERLAPPED* pov = new OVERLAPPED ;
	pov->hEvent = CreateEvent(0, TRUE, TRUE, 0);
	while( m_bStop == FALSE )
	{
		HRESULT hr = MQReceiveMessage( m_hQueue, 10000, 
										MQ_ACTION_RECEIVE, 
										pMsgp, pov, NULL, NULL, NULL );

		if( SUCCEEDED( hr ) )
		{
			if( hr==MQ_INFORMATION_OPERATION_PENDING )
				WaitForSingleObject( pov->hEvent, INFINITE );
			
			if( paVar[0].ulVal == AGENT_REQUEST_1 || paVar[0].ulVal == AGENT_REQUEST_2)
			{
				count++;
				//Get hold of thread and give it new work to do.
				LPVOID mem = ::CoTaskMemAlloc( 256 );
				_tcscpy( (LPTSTR)mem, paVar[3].pwszVal );
				
				TCHAR szTemp[BODY_LEN] = {0};
				memcpy (szTemp, paVar[1].caub.pElems, paVar[1].caub.cElems);

				UINT threshold = _ttoi(szTemp);

				DWORD type = (paVar[0].ulVal == AGENT_REQUEST_1) ? TH_TYPE1 : TH_TYPE2 ;
				PostThreadMessage ( m_dwWorkerID[count % NUMWORKERS], type, 
								(WPARAM)mem, (LPARAM)threshold);

				paVar[0].ulVal = 0; //Clear Type
				//Must clear out buffer for next read. MQ won't clear it.
				memset( paVar[1].caub.pElems, 0, paVar[1].caub.cElems ); 
			}
		}
		else
		{
			ErrorHandler( _TEXT( "MQReceiveMessage" ) );
			break;
		}
	}

	CloseHandle(pov->hEvent);

	delete[] paVar;  
	delete[] paPropid;
	delete pMsgp;
	delete pov;
}	


BOOL CQueueService::SendMessage( LPTSTR szFNQueue, TCHAR* szLabel, TCHAR* szMsg )
{
	//Note that message has been processed to Resp queue
	QUEUEHANDLE hQueue;
	HRESULT hr;

	hr = MQOpenQueue( szFNQueue, MQ_SEND_ACCESS, 0, &hQueue );
	if (FAILED(hr))
		return FALSE;

	MQMSGPROPS msg;
	MQPROPVARIANT aVar[2];
	MSGPROPID aPropid[2];

	aPropid[0] = PROPID_M_LABEL;
	aVar[0].vt = VT_LPWSTR;
	aVar[0].pwszVal = szLabel;

	aPropid[1] = PROPID_M_BODY;
	aVar[1].vt = VT_VECTOR|VT_UI1;
	aVar[1].caub.pElems = (UCHAR*)szMsg;
	aVar[1].caub.cElems = (_tcslen(szMsg) + _tcslen(_T("\0"))) * sizeof TCHAR;

    msg.cProp = 2;
    msg.aPropID =  aPropid;
    msg.aPropVar = aVar;
    msg.aStatus =  0;

	hr = MQSendMessage( hQueue, &msg, NULL );
	if (FAILED(hr))
	{
		MQCloseQueue( hQueue );
		return FALSE;
	}

	MQCloseQueue( hQueue );
	return TRUE;
}

DWORD CQueueService::TFuncType ( LPVOID lpParameter )
{
	CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );
	
	MSG msg;
	LPVOID mem = 0;
	LPTSTR szFN = 0;
	TCHAR szLabel[40] = {0};
	TCHAR szMsg[75] = {0};
	int storeid = 0;
	while( GetMessage( &msg, NULL, 0, 0 ) > 0 )
	{

		//Crack the message params
		if (msg.message == TH_TYPE1)
		{
			_Type1Ptr pT1(__uuidof(Type1));
			_tcscpy( szLabel, _T("Least Sales Over Threshold"));

			mem = (LPVOID)msg.wParam;
			szFN = (LPTSTR)mem;

			storeid = pT1->GetLowestSales( msg.lParam );
			
			pT1 = NULL;

			wsprintf(szMsg, _T("The store with the least sales above the threshold of %lu is store# %d"),
					msg.lParam, storeid);			
		}
		else if (msg.message == TH_TYPE2)
		{
			_Type2Ptr pT2(__uuidof(Type2));
			_tcscpy( szLabel, _T("Highest Sales Under Threshold"));

			mem = (LPVOID)msg.wParam;
			szFN = (LPTSTR)mem;

			storeid = pT2->GetHighestSales( msg.lParam );
			
			pT2 = NULL;

			wsprintf(szMsg, _T("The store with the highest sales below the threshold of %lu is store# %d"),
					msg.lParam, storeid);			
		}

		m_pThis->SendMessage( szFN, szLabel, szMsg);
		
		//Free the memory allocated to pass the RespQ format name.
		::CoTaskMemFree( mem );

	}

	CoUninitialize( );
	return 0;

}

