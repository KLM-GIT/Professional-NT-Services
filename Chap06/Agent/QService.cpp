#include "precomp.h"
#include "qservice.h"

const int AGENT_REQUEST_1 = 239;
const int AGENT_REQUEST_2 = 240;

IMPLEMENT_SERVICE(CQueueService, MQAgent)

CQueueService::CQueueService(LPCTSTR szName, LPCTSTR szDisplay, DWORD dwType) : CService(szName, szDisplay, dwType)
{
   m_pThis = this;
   m_bOpen = false;
   m_bStop  = false;
   m_hQueue = NULL;
}

// The main processing logic belongs in this overridable
// All start, running, and stop code here
void CQueueService::Run()
{
   SetStatus(SERVICE_RUNNING, 0, 0, SERVICE_ACCEPT_STOP);

   RetrieveMessage();                            // Loops until m_bStop is set

   // Stopped, so exit
   SetStatus(SERVICE_STOP_PENDING, 2, 5000);
}

void CQueueService::OnStop()
{
   SetStatus(SERVICE_STOP_PENDING, 1, 15000);

   // The ServiceMain thread could be reading this value!
   InterlockedExchange((LPLONG)&m_bStop, (LONG)TRUE);
}

void CQueueService::Init()
{
   SetStatus(SERVICE_START_PENDING, m_dwCheckpoint++, 2000);

   // Initialize the Queue
   if(!OpenQueue(_T(".\\AgentMonitorQ"), _T("AgentMonitorQ")))
      ErrorHandler(_T("Open Queue"));

   return;
}

void CQueueService::DeInit()
{
   if(m_hQueue)
      MQCloseQueue(m_hQueue);

   m_bOpen = false;
   CService::DeInit();
}

// Queue Specific Implementation
HRESULT CQueueService::CreateQueue()
{
   const DWORD cProps = 2;
   MQQUEUEPROPS qp;
   MQPROPVARIANT aVariant[cProps];
   QUEUEPROPID aPropId[cProps];

   DWORD cFN = MAX_QUEUE_PATH;
   TCHAR szFN[MAX_QUEUE_PATH];

   // Set the PROPID_Q_PATHNAME property
   aPropId[0] = PROPID_Q_PATHNAME;
   aVariant[0].vt = VT_LPWSTR;
   aVariant[0].pwszVal = m_wszQueueName;

   // Set the PROPID_Q_LABEL property
   aPropId[1] = PROPID_Q_LABEL;
   aVariant[1].vt = VT_LPWSTR;
   aVariant[1].pwszVal = m_wszQueueLabel;

   // Set the MQQUEUEPROPS structure
   qp.cProp = cProps;
   qp.aPropID = aPropId;
   qp.aPropVar = aVariant;
   qp.aStatus = NULL;

   HRESULT hr = MQCreateQueue(NULL, &qp, szFN, &cFN);
   return hr;
}

bool CQueueService::OpenQueue(LPWSTR wszName, LPWSTR wszLabel)
{
   DWORD cFN = MAX_QUEUE_PATH;
   TCHAR szFN[MAX_QUEUE_PATH];
   HRESULT hr;

   _tcscpy(m_wszQueueName, wszName);
   _tcscpy(m_wszQueueLabel, wszLabel);

   hr = CreateQueue();

   if(FAILED(hr) && hr != MQ_ERROR_QUEUE_EXISTS)
   {
      return false;
   }
   else
   {
      // Open the queue to get its handle
      hr = MQPathNameToFormatName(m_wszQueueName, szFN, &cFN);
      if(FAILED(hr))
         return false;

      hr = MQOpenQueue(szFN, MQ_RECEIVE_ACCESS, 0, &m_hQueue);
      if(FAILED(hr))
         return false;

      _tcscpy(m_wszFormatName, szFN);
      m_bOpen = true;
      return true;
   }
}

void CQueueService::RetrieveMessage()
{
   // Get the message type - asynch
   MQMSGPROPS* pMsgp;
   pMsgp = new MQMSGPROPS;

   MQPROPVARIANT* paVar;
   paVar = new MQPROPVARIANT[4];

   MSGPROPID* paPropid;
   paPropid = new MSGPROPID[4];

   paPropid[0] = PROPID_M_APPSPECIFIC;
   paVar[0].vt = VT_UI4;
   paVar[0].ulVal = 0;

   const long BODY_LEN = 1024;                   // Hardcoded
   paPropid[1] = PROPID_M_BODY;
   paVar[1].vt = VT_VECTOR | VT_UI1;
   paVar[1].caub.cElems = BODY_LEN;
   paVar[1].caub.pElems = new unsigned char[BODY_LEN];

   paPropid[2] = PROPID_M_RESP_QUEUE_LEN;
   paVar[2].vt = VT_UI4;
   paVar[2].ulVal = MAX_QUEUE_PATH;

   paPropid[3] = PROPID_M_RESP_QUEUE;
   paVar[3].vt = VT_LPWSTR;
   paVar[3].pwszVal = new TCHAR[MAX_QUEUE_PATH];

   pMsgp->cProp = 4;
   pMsgp->aPropID = paPropid;
   pMsgp->aPropVar = paVar;
   pMsgp->aStatus = NULL;

   OVERLAPPED* pov = new OVERLAPPED;
   pov->hEvent = CreateEvent(0, TRUE, TRUE, 0);

   while(m_bStop == false)
   {
      HRESULT hr = MQReceiveMessage(m_hQueue, 10000, MQ_ACTION_RECEIVE,
                                                pMsgp, pov, NULL, NULL, NULL);

      if(SUCCEEDED(hr))
      {
         if(hr == MQ_INFORMATION_OPERATION_PENDING)
            WaitForSingleObject(pov->hEvent, INFINITE);

         if(paVar[0].ulVal == AGENT_REQUEST_1)
         {
            // Do work of type...
            TCHAR szMsg[25] = _T("Results of Request 1");
            SendMessage(paVar[3].pwszVal, _T("Type 1 Response"), szMsg);
            paVar[0].ulVal = 0;
         }
         else if(paVar[0].ulVal == AGENT_REQUEST_2)
         {
            TCHAR szMsg[25] = _T("Results of Request 2");
            SendMessage(paVar[3].pwszVal, _T("Type 2 Response"), szMsg);
            paVar[0].ulVal = 0;
         }
      }
      else
      {
         ErrorHandler(_T("MQReceiveMessage"));
         break;
      }
   }

   CloseHandle(pov->hEvent);
   delete pov;
   delete paVar[3].pwszVal;
   delete paVar[1].caub.pElems;
   delete [] paPropid;
   delete [] paVar;
   delete pMsgp;

/* 
   delete [] paVar;
   delete [] paPropid;
   delete pMsgp;
   delete pov;
*/
}

bool CQueueService::SendMessage(LPTSTR szFNQueue, TCHAR* szLabel, TCHAR* szMsg)
{
   // Note that message has been processed to Resp queue
   QUEUEHANDLE hQueue;
   HRESULT hr;

   hr = MQOpenQueue(szFNQueue, MQ_SEND_ACCESS, 0, &hQueue);
   if(FAILED(hr))
      return false;

   MQMSGPROPS msg;
   MQPROPVARIANT aVar[2];
   MSGPROPID aPropid[2];

   aPropid[0] = PROPID_M_LABEL;
   aVar[0].vt = VT_LPWSTR;
   aVar[0].pwszVal = szLabel;

   aPropid[1] = PROPID_M_BODY;
   aVar[1].vt = VT_VECTOR | VT_UI1;
   aVar[1].caub.pElems = (UCHAR*)szMsg;
   aVar[1].caub.cElems = (_tcslen(szMsg) + _tcslen(_T("\0"))) * sizeof TCHAR;

   msg.cProp = 2;
   msg.aPropID = aPropid;
   msg.aPropVar = aVar;
   msg.aStatus = 0;

   hr = MQSendMessage(hQueue, &msg, NULL);
   if(FAILED(hr))
   {
      MQCloseQueue(hQueue);
      return false;
   }

   MQCloseQueue(hQueue);
   return true;
}
