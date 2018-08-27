#define _UNICODE
#define UNICODE

#include <windows.h>
#include <TCHAR.h>

void WINAPI ServiceMain(DWORD argc, LPTSTR* argv);
void WINAPI Handler(DWORD dwControl);
int ErrorPrinter(const TCHAR* pszFcn, DWORD dwErr = GetLastError());
void LookupErrorMsg(TCHAR* pszMsg, int cch, DWORD dwError = GetLastError());
void PrintEvent(const TCHAR* psz);
void SendStatus(DWORD dwCurrentStatus, 
				DWORD dwCheckpoint = 0, DWORD dwWaitHint = 0,
				DWORD dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE,
				DWORD dwExitCode = NO_ERROR);

const TCHAR* const g_ServiceName = _T("MyService");
SERVICE_STATUS_HANDLE g_hServiceStatus;

HANDLE g_hEvents[3];
DWORD g_state = 0;
DWORD g_status = 0;

int main()
{
	SERVICE_TABLE_ENTRY svcTable[] =
	{
		{ const_cast<TCHAR*>(g_ServiceName), ServiceMain },
		{ NULL, NULL }
	};

	if(!StartServiceCtrlDispatcher(svcTable))
		ErrorPrinter(_T("StartServiceCtrlDispatcher"));

	return 0;
}

void WINAPI ServiceMain(DWORD argc, LPTSTR* argv)
{
	// Register the control handler
	g_hServiceStatus = RegisterServiceCtrlHandler(g_ServiceName, Handler);
	
	if(!g_hServiceStatus)
		ErrorPrinter(_T("RegisterServiceCtrlHandler"));

	// Let the SCM know I'm working on starting
	SendStatus(SERVICE_START_PENDING, 1, 5000, 0);

	// Do some initialization
	g_hEvents[0] = CreateEvent(NULL, FALSE, FALSE, _T("StopEvent"));
	g_hEvents[1] = CreateEvent(NULL, FALSE, FALSE, _T("PauseEvent"));
	g_hEvents[2] = CreateEvent(NULL, FALSE, FALSE, _T("ContinueEvent"));
	bool bRun = true;

	// Notify the SCM I am running
	SendStatus(SERVICE_RUNNING);

	// Put myself in a state to do my work
	DWORD dwWait;
	while(1)
	{
		if(bRun)
		{
			PrintEvent(_T("Doing my work - it takes 2 seconds"));		
			Sleep(2000);
		}

		// Wait for a signal to stop
		dwWait = WaitForMultipleObjects(3, g_hEvents, FALSE, 0);
		if(WAIT_OBJECT_0 == dwWait)
		{
			PrintEvent(_T("Got the Stop Event"));
			break;
		}
		else if(1 == dwWait - WAIT_OBJECT_0)
		{
			PrintEvent(_T("Got the Pause Event"));
			bRun = false;

			// Let the SCM know I am paused
			SendStatus(SERVICE_PAUSED);
			ResetEvent(g_hEvents[1]);
		}

		else if(2 == dwWait - WAIT_OBJECT_0)
		{
			PrintEvent(_T("Got the Continue Event"));
			bRun = true;

			// Let the SCM know I am running again
			SendStatus(SERVICE_RUNNING);
			ResetEvent(g_hEvents[2]);
		}
	}
	
	// Let the SCM know I am stopping
	SendStatus(SERVICE_STOP_PENDING, 1, 2000);

	// De-initialize resources - do the steps necessary to stop
	for(int i = 0 ; i < 3 ; i++)
	{
		CloseHandle(g_hEvents[i]);
	}
	
	// Let the SCM know I have stopped
	SendStatus(SERVICE_STOPPED);		
}

void WINAPI Handler(DWORD dwControl)
{
	// Keep an additional control request from coming in when you're
	// already handling it.
	if(g_state == dwControl)
		return;

	switch(dwControl)
	{
	case SERVICE_CONTROL_STOP:
		g_state = dwControl;
		
		// Notify the main thread you want to stop...
		SetEvent(g_hEvents[0]);
		break;
	
	case SERVICE_CONTROL_PAUSE:
		g_state = dwControl;
		
		// Notify the main thread you want to pause...
		SetEvent(g_hEvents[1]);
		break;

	case SERVICE_CONTROL_CONTINUE:
		g_state = dwControl;
		
		// Notify the main thread you want to continue...
		SetEvent(g_hEvents[2]);
		break;

	default:
		// Return current status on interrogation
		SendStatus(g_status);
	}
}

void SendStatus(DWORD dwCurrentStatus, 
				DWORD dwCheckpoint, DWORD dwWaitHint,
				DWORD dwControlsAccepted,
				DWORD dwExitCode)
{
	g_status = dwCurrentStatus;
	SERVICE_STATUS ss = { SERVICE_WIN32_OWN_PROCESS,
						  g_status, dwControlsAccepted,
						  dwExitCode, 0, dwCheckpoint, dwWaitHint };
	
	SetServiceStatus(g_hServiceStatus, &ss);
}

int ErrorPrinter(const TCHAR* psz, DWORD dwErr)
{
	TCHAR szMsg[512];
	LookupErrorMsg(szMsg, sizeof szMsg / sizeof *szMsg, dwErr);

	TCHAR sz[512];
	const TCHAR* rgsz[] = { sz };
	wsprintf(sz, _T( "%s failed: %s" ), psz, szMsg);

	HANDLE hes = RegisterEventSource(0, _T("My Service"));
	if(hes)
	{
		ReportEvent(hes, EVENTLOG_ERROR_TYPE, 0, 0, 0, 1, 0, rgsz, 0);
		DeregisterEventSource(hes);
	}
	return dwErr;
}

void LookupErrorMsg(TCHAR* pszMsg, int cch, DWORD dwError)
{
    if(!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, dwError, 0, pszMsg, cch, 0))
        wsprintf(pszMsg, _T("Unknown: %x"), dwError);
}

void PrintEvent(const TCHAR* psz)
{
	const TCHAR* rgsz[] = { psz };

	HANDLE hes = RegisterEventSource(0, _T("My Service"));
	if(hes)
	{
		ReportEvent(hes, EVENTLOG_INFORMATION_TYPE, 0, 0, 0, 1, 0, rgsz, 0);
		DeregisterEventSource(hes);
	}
}