#include "stdafx.h"

#define HANDLEALLOCCOST 1000 //remove to use

//----------------------------------------
//
// List Class members
//

#define SPINX 5000

CFreeList::CFreeList()
: m_pHead( NULL ), m_pTail( NULL ), m_Count(0)
{
	InitializeCriticalSectionAndSpinCount( &m_cs, SPINX );	
}

CFreeList::~CFreeList()
{
	RemoveAll();
	DeleteCriticalSection( &m_cs );
}

void CFreeList::AddTail( const RHANDLE* newHandle )
{
	NODE* pNew = new NODE(newHandle);

	EnterCriticalSection( &m_cs );
	if( m_pTail == NULL) //list is empty
	{		
		m_pHead = pNew;
	}
	else
	{		
		pNew->prev = m_pTail;
		m_pTail->next = pNew;
	}

	m_pTail = pNew;
	m_Count++;
	
	LeaveCriticalSection( &m_cs );
}

void CFreeList::RemoveAll( )
{
	NODE* pNext = 0;

	EnterCriticalSection( &m_cs );

	NODE* p = m_pHead;
	while( p != NULL )
	{
		pNext = p->next;
		delete p;
		p = pNext;
	}
	m_pHead = m_pTail = NULL;

	m_Count = 0;

	LeaveCriticalSection( &m_cs );
}

const RHANDLE* CFreeList::Pop( )
{
	const RHANDLE* rh = 0;
	EnterCriticalSection( &m_cs );

	NODE* p = m_pHead;
	if( p != NULL )
	{
		//obtain rhandle
		rh = p->pRH;

		if( p->next ) 
		{
			p->next->prev = NULL;
			m_pHead = p->next;
		}
		else
			m_pHead = m_pTail = NULL;

		delete p;
		m_Count--;
	}

	LeaveCriticalSection( &m_cs );

	return rh;
}

//---------------------------------------------------------------------------
// CResourceArray Class
//
//
//
CResourceArray::CResourceArray( long dwSize )
:m_size(dwSize), m_count(0), m_hEnv(NULL)
{
	InitializeCriticalSectionAndSpinCount( &m_cs, SPINX);

	m_pHandles = new RHANDLEHEADER* [dwSize];
	memset(m_pHandles, 0, sizeof(RHANDLEHEADER*) * dwSize);
}

void CResourceArray::Init( LPTSTR szServer, LPTSTR szLogin, LPTSTR szPassword)
{
	_tcscpy( m_szServer, szServer );
	_tcscpy( m_szLogin, szLogin );
	_tcscpy( m_szPassword, szPassword);
}

CResourceArray::~CResourceArray( )
{
	RemoveAll( );
	delete [] m_pHandles;
	m_size = 0;	
	m_pHandles = NULL;

    if (m_hEnv) SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);

	DeleteCriticalSection( &m_cs );
}

const RHANDLE* CResourceArray::Add(  )
{
	SQLHDBC hSession = 0;
	RHANDLE* chd = 0;

	EnterCriticalSection( &m_cs );
	if (m_count < m_size)
	{
		hSession = GetResourceHandle( );
		if ( hSession != 0 )
		{
			RHANDLEHEADER* pSH = new RHANDLEHEADER;
			chd = new RHANDLE;
			chd->handle = hSession;
			chd->pos = m_count; 

			pSH->pRH = chd;
			pSH->bFree = TRUE;
			pSH->dwTime = 0;

			m_pHandles[m_count] = pSH;
			m_count++ ; 
		}
		else 
		{
			//Event Log call
			CEventLog el(_Module.m_szServiceName);
			el.LogEvent( BUSOBJ_HANDLE_CONNECTION_FAILED, EVENTLOG_ERROR_TYPE);
		}
	}

	LeaveCriticalSection( &m_cs );

	return chd;
}

void CResourceArray::RemoveAll( )
{
	RHANDLEHEADER* pTemp = 0;

	EnterCriticalSection( &m_cs );
	
	for( int i=0; i<m_count; i++ )
	{
		pTemp = m_pHandles[i];
		if( pTemp )
		{
			const RHANDLE* pRHTemp = pTemp->pRH;
			if( pRHTemp )
			{
				ReleaseResourceHandle( pRHTemp->handle );
				delete (RHANDLE*)pRHTemp;
			}
			delete pTemp;
		}		
		m_pHandles[i] = NULL;
	}	
	m_count = 0;
	LeaveCriticalSection( &m_cs );
}

SQLHDBC CResourceArray::GetResourceHandle( )
{
	if (!m_hEnv)
		AllocateEnvironment();

	if(!m_hEnv)
		goto ErrorH;

	SQLHDBC hdbc;
	SQLRETURN rc;

	//Open connection
	rc = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &hdbc);
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		goto ErrorH;

    // Set login timeout to 5 seconds.
    SQLSetConnectAttr(hdbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
    
	// Connect to data source 
    rc = SQLConnect(hdbc,(SQLCHAR*) m_szServer, SQL_NTS,
                         (SQLCHAR*) m_szLogin, SQL_NTS,
                         (SQLCHAR*) m_szPassword, SQL_NTS);
    
	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		goto ErrorH;
	
	return hdbc;

ErrorH:
	CEventLog el(_Module.m_szServiceName);
	el.LogEvent(BUSOBJ_HANDLE_CONNECTION_FAILED, EVENTLOG_ERROR_TYPE);
	return NULL;
}

void CResourceArray::ReleaseResourceHandle( SQLHDBC hResHandle )
{
    if(hResHandle)
	{
		SQLDisconnect(hResHandle);
		SQLFreeHandle(SQL_HANDLE_DBC, hResHandle);
	}
}

void CResourceArray::AllocateEnvironment()
{
	SQLRETURN rc;
	rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv);
    rc = SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0); 
	return;
}


//---------------------------------------------------------------------------
//
// CQuartermaster Class
//
//

CQuartermaster* CQuartermaster::m_pThis = 0;

CQuartermaster::CQuartermaster( )
:m_dwNumCurrentResources(0), m_bStartAllocator(FALSE)
{
	m_pThis = this;
	InitializeCriticalSectionAndSpinCount( &m_cs, SPINX );
}

void CQuartermaster::Init( 	DWORD dwMaxResources,
				DWORD dwStartResources,
				DWORD dwWaitForHandleTime,
				DWORD dwHandleLifeTime,
				DWORD dwAllocationPoll,
				DWORD dwMinPoolSize, 
				DWORD dwResourceAllocSize, 
				DWORD dwDeadResourcePoll,
				LPTSTR szServer, 
				LPTSTR szLogin,
				LPTSTR szPassword )

{
	//Event to signal workers to stop
	m_hStopEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
	m_dwStartResources = dwStartResources;
	m_dwMaxResources = dwMaxResources;
	m_dwWaitForHandleTime = dwWaitForHandleTime;
	m_dwHandleLifeTime = dwHandleLifeTime;
	m_dwAllocationPoll = dwAllocationPoll;
	m_dwMinPoolSize = dwMinPoolSize;
	m_dwResourceAllocSize = dwResourceAllocSize;
	m_dwDeadResourcePoll =dwDeadResourcePoll;

	m_pResources = new CResourceArray( dwMaxResources );
	m_pFreeList = new CFreeList;

	//Initialize the Resource Array
	m_pResources->Init( szServer, szLogin, szPassword );

	//Initialize the Semaphore with max possible
	m_hSem = CreateSemaphore( NULL, 0, dwMaxResources, NULL );

	DWORD dwAid, dwPid;
	m_hAllocThread = (HANDLE)_beginthreadex( NULL, 0, 
		(PBEGINTHREADEX_TFUNC)CQuartermaster::AllocateMoreResourcesThread,
					0, 0, (PBEGINTHREADEX_TID)&dwAid );
	m_hRefreshThread = (HANDLE)_beginthreadex( NULL, 0, 
		(PBEGINTHREADEX_TFUNC)CQuartermaster::RefreshDeadResourcesThread,
					0, 0, (PBEGINTHREADEX_TID)&dwPid );

}

CQuartermaster::~CQuartermaster( )
{
	if (m_hAllocThread)
		CloseHandle(m_hAllocThread);
	if (m_hRefreshThread)
		CloseHandle(m_hRefreshThread);
	
	CloseHandle( m_hSem );

	delete m_pResources;
	m_pResources = NULL;
	
	delete m_pFreeList;
	m_pFreeList = NULL;

	DeleteCriticalSection( &m_cs );
}

DWORD CQuartermaster::GetFreeResource( const RHANDLE** poutHandle)
{
	//Function does NOT find a KNOWN valid handle. It is up to the 
	//object to check handle validity and retry if necessary.

	const RHANDLE* pHandle = 0;

	if ( _Module.m_bPaused || _Module.m_bStopped )
		return BUSOBJ_SERVICE_STOPPED_PAUSED;

	//Wait on the semaphore. I can block for a short time if no handles left.
	if( WaitForSingleObject( m_hSem, m_dwWaitForHandleTime ) 
		== WAIT_OBJECT_0 )
	{
		//Get the handle and give it out
		pHandle = m_pFreeList->Pop();

		if( pHandle )
		{
			//Mark time and busy
			m_pResources->SetBusy( pHandle->pos );
			*poutHandle = pHandle;
			return 0;
		}
	}

	*poutHandle = NULL;
	return BUSOBJ_NOSESSIONS_AVAILABLE;

}

void CQuartermaster::ReleaseResource( const RHANDLE* handle )
{
	//Make sure handle hasn't been released twice by client accidentally
	if (handle)
	{
		if( m_pResources->IsFree( handle->pos ) == FALSE )
		{
			long lPrev;
			m_pResources->SetFree( handle->pos );
			m_pFreeList->AddTail( handle );
			ReleaseSemaphore( m_hSem, 1, &lPrev );
		}
	}
}

DWORD CQuartermaster::AllocateResources( DWORD dwNumAdd )
{
	DWORD count = 0;
	const RHANDLE* pRH = 0;
	DWORD newRes = 0;
	
	DWORD dwNumRes = GetNumResources();

	if ( dwNumAdd + dwNumRes > m_dwMaxResources )
		newRes = m_dwMaxResources - dwNumRes;
	else
		newRes = dwNumAdd;

	//Connect the sessions
	for( DWORD i=0; i<newRes; i++ )
	{
		pRH = m_pResources->Add( );
		if( pRH )
		{
			m_pFreeList->AddTail( pRH );
			count++;
		}
	}

	InterlockedExchangeAdd((long*)&m_dwNumCurrentResources, count);

	//ReleaseSemaphore count number of times
	if( count > 0 )
	{
		long dwPrev;
		ReleaseSemaphore( m_hSem, (long)count ,&dwPrev );
	}

	//Write to event log that x new handles were allocated
	TCHAR sz1[5], sz2[5];
	wsprintf(sz1,_T("%lu"), count );
	wsprintf(sz2,_T("%lu"), dwNumRes );
	const TCHAR* rgsz[2] = { sz1, sz2 };
	
	CEventLog el(_Module.m_szServiceName);
	el.LogEvent( BUSOBJ_MORESESSIONS_ALLOCATED, rgsz, 2, EVENTLOG_INFORMATION_TYPE );

	//Also write if maximum session limit was reached.
	if ( GetNumResources() >= m_dwMaxResources )
	{
		el.LogEvent( BUSOBJ_MAXIMUM_SESSIONS_ALLOCATED, EVENTLOG_INFORMATION_TYPE );
	}

	//Allow the allocator thread to start, if it hasn't before
	if(!m_bStartAllocator)
		InterlockedExchange( (long*)&m_bStartAllocator, true);

	//Return
	return count;
}

void CQuartermaster::DeallocateResources( )
{
	EnterCriticalSection( &m_cs );

	//Stop the worker threads
	SetStop(); 

	m_dwNumCurrentResources = 0;
	m_pResources->RemoveAll( );
	m_pFreeList->RemoveAll( );

	LeaveCriticalSection( &m_cs );
}

//Will be called on a schedule by another thread
void CQuartermaster::ReleaseDeadResources( )
{
	//Walk the list and see if any bFrees are FALSE with 
	//now - timestamp > m_dwHandleLifetime
	//If so, bFree = TRUE
	//and add back to free list.

	CRITICAL_SECTION cs;
	InitializeCriticalSection( &cs );

	DWORD now = ::GetTickCount();
	
	RHANDLEHEADER* pTemp = 0;
	DWORD stamp = 0;


	long count = m_pResources->GetCount();
	for( long i=0; i<count; i++ )
	{
		pTemp = m_pResources->m_pHandles[i];
		if( pTemp )
		{

			EnterCriticalSection( &cs );
			if( m_pResources->IsFree(i) == FALSE )
			{
				stamp = pTemp->dwTime;
				if( now - stamp > m_dwHandleLifeTime )
				{
					if( pTemp->pRH )
					{
						m_pResources->SetFree(i);
						m_pFreeList->AddTail( pTemp->pRH );
					}		
				}
			}
			LeaveCriticalSection( &cs );
		}
	}
	DeleteCriticalSection( &cs );
}

/////////
//Background task threads
/////////

DWORD WINAPI CQuartermaster::AllocateMoreResourcesThread( LPVOID lpParameter )
{
	while (WaitForSingleObject( m_pThis->m_hStopEvent, m_pThis->m_dwAllocationPoll ) == WAIT_TIMEOUT )
	{
		if( m_pThis->FreeResourcesLeft() <= m_pThis->m_dwMinPoolSize 
			&& m_pThis->m_bStartAllocator)
		{
			m_pThis->AllocateResources( m_pThis->m_dwResourceAllocSize ); 
			Sleep( HANDLEALLOCCOST ); //**Simulation** of amount of time it takes 
		}
	}
	return 0;
}


DWORD WINAPI CQuartermaster::RefreshDeadResourcesThread( LPVOID lpParameter )
{
	while (WaitForSingleObject( m_pThis->m_hStopEvent, m_pThis->m_dwDeadResourcePoll ) == WAIT_TIMEOUT )
	{
		m_pThis->ReleaseDeadResources( );
	}
	return 0;
}
