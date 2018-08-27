#include "precomp.h"
#include "cmonitor.h"
#include <winsock2.h>

IMPLEMENT_SERVICE(CMonitor, Monitor)

CMonitor::CMonitor(LPTSTR szName, LPTSTR szDisplay, DWORD dwType) : CService(szName, szDisplay, dwType)
{
   m_pThis = this;

   m_bPause = false;
   m_bStop  = false;

   m_hPauseNotifyEvent = NULL;

   m_nCycleTime = 0;
   m_nPort = 0;
}

// The main processing logic belongs in this overridable
// All start, running, and stop code here
void CMonitor::Run()
{
   SetStatus(SERVICE_RUNNING, 0, 0, SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE);

   bool bPauseSent = false;
   DWORD dwErr = NO_ERROR;

   while(true)
   {
      // I'm not stopped or paused
      while(!m_bStop)
      {
         // Do some work
         Sleep(m_nCycleTime);
         if(m_bPause && !bPauseSent)
         {
            // Pausing; SetEvent message received
            SetEvent(m_hPauseNotifyEvent);
            bPauseSent = true;
         }
         else if(!m_bPause && bPauseSent)
         {
            // Continuing; SetEvent message received
            SetEvent(m_hPauseNotifyEvent);
            bPauseSent = false;
         }
         else if(!m_bPause)                      // (!m_bPause && !bPauseSent)
         {
            // I'm running as usual, so ping
            dwErr = Ping();
            if(dwErr != NO_ERROR)
               break;

            PrintEvent(_T("Successful Ping"), FALSE);
         }
      }

      // Stopped, so exit
      SetStatus(SERVICE_STOP_PENDING, 2, 5000);
      break;
   }
}

void CMonitor::OnPause()
{
   DWORD dwCheckPt = 1;
   SetStatus(SERVICE_PAUSE_PENDING, dwCheckPt, 6000);

   // Remember, this function is called by the thread watching for handler
   //  notifications. The ServiceMain thread (Run) could be reading this value
   InterlockedExchange((LPLONG)&m_bPause, (LONG)true);

   // Wait for the Run loop to signal that it has received the pause request
   while(WaitForSingleObject(m_hPauseNotifyEvent, 5000) == WAIT_TIMEOUT)
   {
      dwCheckPt++;
      SetStatus(SERVICE_PAUSE_PENDING, dwCheckPt, 6000);
   }
   SetStatus(SERVICE_PAUSED);
   ResetEvent(m_hPauseNotifyEvent);
}

void CMonitor::OnContinue()
{
   DWORD dwCheckPt = 1;
   SetStatus(SERVICE_CONTINUE_PENDING, dwCheckPt, 6000);

   // The ServiceMain thread could be reading this value
   InterlockedExchange((LPLONG)&m_bPause, (LONG)false);

   // Wait for the Run loop to signal it has received the continue request
   while(WaitForSingleObject(m_hPauseNotifyEvent, 5000) == WAIT_TIMEOUT)
   {
      dwCheckPt++;
      SetStatus(SERVICE_CONTINUE_PENDING, dwCheckPt, 6000);
   }
   SetStatus(SERVICE_RUNNING);
   ResetEvent(m_hPauseNotifyEvent);
}

void CMonitor::OnStop()
{
   SetStatus(SERVICE_STOP_PENDING, 1, m_nCycleTime);

   // The ServiceMain thread could be reading this value
   InterlockedExchange((LPLONG)&m_bStop, (LONG)true);
}

void CMonitor::Init()
{
   // Set up event that lets handlers know a ctrl request has been processed
   m_hPauseNotifyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
   if(!m_hPauseNotifyEvent)
      ErrorHandler(_T("CreateEvent"));

   // Initialize Sockets library
   WSADATA wsaData;
   if(WSAStartup(MAKEWORD(2, 2), &wsaData) == SOCKET_ERROR)
      ErrorHandler(_T("WSAStartup"));
}

void CMonitor::DeInit()
{
   CService::DeInit();

   if(m_hPauseNotifyEvent)
      CloseHandle(m_hPauseNotifyEvent);

   WSACleanup();
}

void CMonitor::ParseArgs(DWORD argc, LPTSTR* argv)
{
   if(argc > 1)
   {
      // For the first argument, convert it to a regular LPSTR so it can be
      //  used inside the sockets calls
      long lconv = (lstrlenW(argv[1]) + 1) * 2;
      char lpa[25] = "";
      WideCharToMultiByte(CP_ACP, 0, argv[1], -1, lpa, lconv, NULL, NULL);
      memcpy(m_pingAddress, lpa, lconv);

      // Get the cycle time and convert to milliseconds - default of 5000
      m_nCycleTime = (argc > 2) ? (DWORD)((_ttol(argv[2]) * 1000)) : (DWORD) 5000;

      // Set the port to 21 (FTP) if no port given
      m_nPort = (argc > 3) ? (_ttol(argv[3])) : 21;
   }
   else
   {
      ErrorHandler(_T("Invalid IP address as argument to StartService: Service Stopping"), TRUE, TRUE, 0);
   }
}

DWORD CMonitor::Ping()
{
   // Set up socket structures and try to connect
   DWORD dwErr = NO_ERROR;

   SOCKADDR_IN saDestAddr = {0};
   SOCKET sSocket;
   unsigned long destaddr;

   destaddr = inet_addr(m_pingAddress);
   memcpy(&saDestAddr.sin_addr, &destaddr, sizeof(destaddr));
   saDestAddr.sin_port = htons(m_nPort);
   saDestAddr.sin_family = AF_INET;

   sSocket = socket(AF_INET, SOCK_STREAM, 0);
   if(INVALID_SOCKET == sSocket)
      return ErrorHandler(_T("socket"), TRUE, TRUE, WSAGetLastError());

   if(connect(sSocket, (LPSOCKADDR)&saDestAddr, sizeof(saDestAddr)) == SOCKET_ERROR)
   {
      dwErr = ErrorHandler(_T("socket connect"), TRUE, FALSE, WSAGetLastError());
   }

   if(closesocket(sSocket) == SOCKET_ERROR)
      return ErrorHandler(_T("closesocket"), TRUE, TRUE, WSAGetLastError());

   return dwErr;
}
