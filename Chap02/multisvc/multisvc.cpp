#define _UNICODE
#define UNICODE

#include <windows.h>
#include <TCHAR.h>

void WINAPI ServiceMainA(DWORD argc, LPTSTR* argv);
void WINAPI HandlerA(DWORD dwControl);
void WINAPI ServiceMainB(DWORD argc, LPTSTR* argv);
void WINAPI HandlerB(DWORD dwControl);
int ErrorPrinter(const TCHAR* pszFcn, DWORD dwErr = GetLastError());
void LookupErrorMsg(TCHAR* pszMsg, int cch, DWORD dwError = GetLastError());
void PrintEvent(const TCHAR* psz);
void SendStatusA(DWORD dwCurrentStatus, 
				 DWORD dwCheckpoint = 0, DWORD dwWaitHint = 0,
				 DWORD dwControlsAccepted =
				 SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE,
				 DWORD dwExitCode = NO_ERROR);
void SendStatusB(DWORD dwCurrentStatus, 
				 DWORD dwCheckpoint = 0, DWORD dwWaitHint = 0,
				 DWORD dwControlsAccepted =
				 SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE,
				 DWORD dwExitCode = NO_ERROR);

const TCHAR* const g_ServiceNameA = _T("MyServiceA");
const TCHAR* const g_ServiceNameB = _T("MyServiceB");

SERVICE_STATUS_HANDLE g_hServiceStatusA;
SERVICE_STATUS_HANDLE g_hServiceStatusB;

const TCHAR* const g_pszStopEventA = _T("StopEventA");
const TCHAR* const g_pszPauseEventA = _T("PauseEventA");
const TCHAR* const g_pszContinueEventA = _T("ContinueEventA");
const TCHAR* const g_pszStopEventB = _T("StopEventB");
const TCHAR* const g_pszPauseEventB = _T("PauseEventB");
const TCHAR* const g_pszContinueEventB = _T("ContinueEventB");

DWORD g_stateA = 0;
DWORD g_statusA = 0;
DWORD g_stateB = 0;
DWORD g_statusB = 0;

int main()
{
	SERVICE_TABLE_ENTRY svcTable[] =
	{
		{ const_cast<TCHAR*>(g_ServiceNameA), ServiceMainA },
		{ const_cast<TCHAR*>(g_ServiceNameB), ServiceMainB },
		{ NULL, NULL }
	};

	if(!StartServiceCtrlDispatcher(svcTable))
		ErrorPrinter(_T("StartServiceCtrlDispatcher"));

	return 0;
}

void WINAPI ServiceMainA(DWORD argc, LPTSTR* argv)
{
	// Register the control handler
	g_hServiceStatusA =	RegisterServiceCtrlHandler(g_ServiceNameA, HandlerA);
	if(!g_hServiceStatusA)
		ErrorPrinter(_T("RegisterServiceCtrlHandler"));

	// Let the SCM know I'm working on starting
	SendStatusA(SERVICE_START_PENDING, 1, 5000, 0);

	// Do some initialization
	HANDLE hEvents[3];
	hEvents[0] = CreateEvent(NULL, FALSE, FALSE, g_pszStopEventA);
	hEvents[1] = CreateEvent(NULL, FALSE, FALSE, g_pszPauseEventA);
	hEvents[2] = CreateEvent(NULL, FALSE, FALSE, g_pszContinueEventA);
	bool bRun = true;

	// Notify the SCM I am running
	SendStatusA(SERVICE_RUNNING);

	// Put myself in a state to do my work
	DWORD dwWait;
	while(1)
	{
		if(bRun)
		{
			PrintEvent(_T("Service A - Doing my work - it takes 5 seconds"));		
			Sleep(5000);
		}

		// Wait for a signal to stop
		dwWait = WaitForMultipleObjects(3, hEvents, FALSE, 100);
		if(WAIT_OBJECT_0 == dwWait)
		{
			PrintEvent(_T("ServiceA Got the Stop Event"));
			break;
		}
		else if(1 == dwWait - WAIT_OBJECT_0)
		{
			PrintEvent(_T("ServiceA Got the Pause Event"));
			bRun = false;

			// Let the SCM know I am paused
			SendStatusA(SERVICE_PAUSED);
			ResetEvent(hEvents[1]);
		}
		else if(2 == dwWait - WAIT_OBJECT_0)
		{
			PrintEvent(_T("ServiceA Got the Continue Event"));
			bRun = true;

			// Let the SCM know I am running again
			SendStatusA(SERVICE_RUNNING);
			ResetEvent(hEvents[2]);
		}
	}
	
	// Let the SCM know I am stopping
	SendStatusA(SERVICE_STOP_PENDING, 1, 2000);

	// De-initialize resources - Do the steps necessary to stop
	for(int i = 0 ; i < 3 ; i++)
	{
		CloseHandle(hEvents[i]);
	}
	
	// Let the SCM know I have stopped
	SendStatusA(SERVICE_STOPPED);		
}

void WINAPI ServiceMainB(DWORD argc, LPTSTR* argv)
{
	// Register the control handler
	g_hServiceStatusB =	RegisterServiceCtrlHandler(g_ServiceNameB, HandlerB);
	if(!g_hServiceStatusB)
		ErrorPrinter(_T("RegisterServiceCtrlHandler"));

	// Let the SCM know I'm working on starting
	SendStatusB(SERVICE_START_PENDING, 1, 5000, 0);

	// Do some initialization
	HANDLE hEvents[3];
	hEvents[0] = CreateEvent(NULL, FALSE, FALSE, g_pszStopEventB);
	hEvents[1] = CreateEvent(NULL, FALSE, FALSE, g_pszPauseEventB);
	hEvents[2] = CreateEvent(NULL, FALSE, FALSE, g_pszContinueEventB);
	bool bRun = true;

	// Notify the SCM I am running
	SendStatusB(SERVICE_RUNNING);

	// Put myself in a state to do my work
	DWORD dwWait;
	while(1)
	{
		if(bRun)
		{
			PrintEvent(_T("Service B - Doing my work - it takes 5 seconds"));		
			Sleep(5000);
		}

		// Wait for a signal to stop
		dwWait = WaitForMultipleObjects(3, hEvents, FALSE, 100);
		if(WAIT_OBJECT_0 == dwWait)
		{
			PrintEvent(_T("ServiceB Got the Stop Event"));
			break;
		}
		else if(1 == dwWait - WAIT_OBJECT_0)
		{
			PrintEvent(_T("ServiceB Got the Pause Event"));
			bRun = false;

			// Let the SCM know I am paused
			SendStatusB(SERVICE_PAUSED);
			ResetEvent( hEvents[1] );
		}
		else if(2 == dwWait - WAIT_OBJECT_0)
		{
			PrintEvent(_T("ServiceB Got the Continue Event"));
			bRun = true;

			// Let the SCM know I am running again
			SendStatusB(SERVICE_RUNNING);
			ResetEvent(hEvents[2]);
		}
	}

	// Let the SCM know I am stopping
	SendStatusB(SERVICE_STOP_PENDING, 1, 2000);

	// De-initialize resources -- Do the steps necessary to stop
	for(int i = 0 ; i < 3 ; i++)
	{
		CloseHandle(hEvents[i]);
	}
	
	// Let the SCM know I have stopped
	SendStatusB(SERVICE_STOPPED);		
}

void WINAPI HandlerA(DWORD dwControl)
{
	// Keep an additional control request from coming in when you're
	// already handling it.
	if(g_stateA == dwControl)
		return;

	HANDLE hEvent;
	switch(dwControl)
	{
	case SERVICE_CONTROL_STOP:
		g_stateA = dwControl;
		
		// Notify the main thread you want to stop...
		hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, g_pszStopEventA);
		SetEvent(hEvent);
		break;
	
	case SERVICE_CONTROL_PAUSE:
		g_stateA = dwControl;
		
		// Notify the main thread you want to pause...
		hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, g_pszPauseEventA);
		SetEvent(hEvent);
		break;

	case SERVICE_CONTROL_CONTINUE:
		g_stateA = dwControl;
		
		// Notify the main thread you want to continue...
		hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, g_pszContinueEventA);
		SetEvent(hEvent);
		break;

	default:
		// Return current status on interrogation
		SendStatusA(g_statusA);
	}
}

void WINAPI HandlerB(DWORD dwControl)
{
	// Keep an additional control request from coming in when you're
	// already handling it.
	if(g_stateB == dwControl)
		return;

	HANDLE hEvent;
	switch(dwControl)
	{
	case SERVICE_CONTROL_STOP:
		g_stateB = dwControl;
		
		// Notify the main thread you want to stop...
		hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, g_pszStopEventB);
		SetEvent(hEvent);
		break;
	
	case SERVICE_CONTROL_PAUSE:
		g_stateB = dwControl;
		
		// Notify the main thread you want to pause...
		hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, g_pszPauseEventB);
		SetEvent(hEvent);
		break;

	case SERVICE_CONTROL_CONTINUE:
		g_stateB = dwControl;
		
		// Notify the main thread you want to continue...
		hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, g_pszContinueEventB);
		SetEvent(hEvent);
		break;

	default:
		// Return current status on interrogation
		SendStatusB(g_statusB);
	}
}

void SendStatusA(DWORD dwCurrentStatus, 
				 DWORD dwCheckpoint, DWORD dwWaitHint,
				 DWORD dwControlsAccepted,
				 DWORD dwExitCode)
{
	g_statusA = dwCurrentStatus;
	SERVICE_STATUS ss = { SERVICE_WIN32_SHARE_PROCESS,
						  g_statusA, dwControlsAccepted,
						  dwExitCode, 0, dwCheckpoint, dwWaitHint };
	
	SetServiceStatus(g_hServiceStatusA, &ss);
}

void SendStatusB(DWORD dwCurrentStatus, 
				 DWORD dwCheckpoint, DWORD dwWaitHint,
				 DWORD dwControlsAccepted,
				 DWORD dwExitCode)
{
	g_statusB = dwCurrentStatus;
	SERVICE_STATUS ss = { SERVICE_WIN32_SHARE_PROCESS,
						  g_statusB, dwControlsAccepted,
						  dwExitCode, 0, dwCheckpoint, dwWaitHint };
	
	SetServiceStatus(g_hServiceStatusB, &ss);
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
		wsprintf(pszMsg, _T( "Unknown: %x" ), dwError);
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