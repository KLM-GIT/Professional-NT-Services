#define _WIN32_WINNT 0x400
#define UNICODE 
#define _UNICODE

#include <windows.h>
#include <iostream>
using namespace std;

#ifdef UNICODE
	#define _tcout wcout
	#define _tostream wostream
#else
	#define _tcout cout
	#define _tostream ostream
#endif

#include <TCHAR.h>

void Install();
void Remove();
void Config(BOOL bAutostart);
void Display();
void GetConfig();
void Status();
void Dependencies();
void Start();
void Control(DWORD dwControl);

DWORD ErrorPrinter( const TCHAR* pszFcn, DWORD dwErr = GetLastError() );

const int MAX_SERVICE_NAME = 256;
LPCTSTR g_service = _T("MyService");
LPCTSTR g_display = _T("My Service Service");
LPCTSTR g_binary = _T("%SystemRoot%\\system32\\services\\simplesvc.exe");

int main()
{
	TCHAR* pszCmdLine = GetCommandLine();
	CharLowerBuff(pszCmdLine, lstrlen(pszCmdLine));

	if(_tcsstr(pszCmdLine, _T("-install")))
		Install();
	else if(_tcsstr(pszCmdLine, _T("-remove")))
		Remove();
	else if(_tcsstr(pszCmdLine, _T("-auto")))
		Config(TRUE);
	else if(_tcsstr(pszCmdLine, _T("-demand")))
		Config(FALSE);
	else if(_tcsstr(pszCmdLine, _T("-display")))
		Display();
	else if(_tcsstr(pszCmdLine, _T("-showconfig")))
		GetConfig();
	else if(_tcsstr(pszCmdLine, _T("-status")))
		Status();
	else if(_tcsstr(pszCmdLine, _T("-depends")))
		Dependencies();
	else if(_tcsstr(pszCmdLine, _T("-start")))
		Start();
	else if(_tcsstr(pszCmdLine, _T("-stop")))
		Control(SERVICE_CONTROL_STOP);
	else if(_tcsstr(pszCmdLine, _T("-pause")))
		Control(SERVICE_CONTROL_PAUSE);
	else if(_tcsstr(pszCmdLine, _T("-continue")))
		Control(SERVICE_CONTROL_CONTINUE);

	return 0;
}

void Install()
{
	SC_HANDLE hSCM = NULL;
	SC_HANDLE hService = NULL;

	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if(!hSCM)
	{
		ErrorPrinter(_T("OpenSCManager"));
		return;
	}

	hService = CreateService(hSCM,
                             g_service,
                             g_display,
                             GENERIC_READ,
                             SERVICE_WIN32_OWN_PROCESS,
                             SERVICE_DEMAND_START,
                             SERVICE_ERROR_NORMAL,
                             g_binary,
                             NULL,
                             NULL,
                             NULL,
                             NULL,
                             NULL);

	if(!hService)
	{
		ErrorPrinter(_T("CreateService"));
		CloseServiceHandle(hSCM);
		return;
	}
	else
	{
		_tprintf(_T("%s Created\n"), g_service);
		CloseServiceHandle(hService);
	}

	CloseServiceHandle( hSCM );
	return;
}

void Remove()
{
	SC_HANDLE hSCM = NULL;
	SC_HANDLE hService = NULL;
	BOOL bSuccess = FALSE;

	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
	if(!hSCM)
	{
		ErrorPrinter(_T("OpenSCManager"));
		return;
	}

	hService = OpenService(hSCM, g_service, DELETE);
	if(!hService)
	{
		ErrorPrinter(_T("OpenService"));
		CloseServiceHandle(hSCM);
		return;
	}
	
	bSuccess = DeleteService(hService);
	if(bSuccess)
		_tprintf(_T("%s Removed\n"), g_service); 
	else
		ErrorPrinter(_T("DeleteService"));

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCM);
	return;
}

void Config(BOOL bAutostart)
{
	SC_HANDLE hSCM = 0;
	SC_HANDLE hService = 0;
	SC_LOCK hLock = 0; 
	DWORD dwStartType = 0;
	BOOL bRet = FALSE;

	hSCM = OpenSCManager(NULL, NULL, GENERIC_READ | GENERIC_EXECUTE);
	if(!hSCM)
	{
		ErrorPrinter(_T("OpenSCManager"));
		return;
	}
	
	hLock = LockServiceDatabase(hSCM);
	if(!hLock)
	{
		_tprintf(_T("Service Configuration could not be changed\n"));
		CloseServiceHandle(hSCM);
		return;
	}	
	
	hService = OpenService(hSCM, g_service, SERVICE_CHANGE_CONFIG);
	if(!hService)
	{
		ErrorPrinter(_T("OpenService"));
		UnlockServiceDatabase(hLock);
		CloseServiceHandle(hSCM);
		return;
	}

	dwStartType = (bAutostart) ? SERVICE_AUTO_START : SERVICE_DEMAND_START;
	bRet = ChangeServiceConfig(hService,
                               SERVICE_NO_CHANGE,
                               dwStartType,
                               SERVICE_NO_CHANGE,
                               NULL,
                               NULL,
                               NULL,
                               NULL,
                               NULL,
                               NULL,
                               NULL);
	
	if(bRet)
		_tprintf(_T("Changed Service Configuration Successfully\n"));
	else
		ErrorPrinter(_T("ChangeServiceConfig"));

	CloseServiceHandle(hService);
	UnlockServiceDatabase(hLock);
	CloseServiceHandle(hSCM);
	return;
}

void Display()
{
	SC_HANDLE hSCM = 0;
	BOOL bRet = FALSE;

	TCHAR lpBuf[MAX_SERVICE_NAME + 1]; //Display name can't be longer than this!
	DWORD cchBuffer = MAX_SERVICE_NAME + 1; 

	hSCM = OpenSCManager(NULL, NULL, GENERIC_READ);
	if(!hSCM)
	{
		ErrorPrinter(_T("OpenSCManager"));
		return;
	}

	
	bRet = GetServiceDisplayName(hSCM, g_service, lpBuf, &cchBuffer);
	if(bRet)
		_tprintf(_T("The display name is: %s\n"), lpBuf); 
	else
		ErrorPrinter(_T("GetServiceDisplayName"));

	CloseServiceHandle(hSCM);
	return;
}

void GetConfig()
{
	SC_HANDLE hSCM = 0;
	SC_HANDLE hService = 0 ;
	BOOL bRet = FALSE;

	LPQUERY_SERVICE_CONFIG pqscBuf = {0};
	DWORD dwBytesNeeded = 0;
	
	hSCM = OpenSCManager(NULL, NULL, GENERIC_READ);
	if(!hSCM)
	{
		ErrorPrinter(_T("OpenSCManager"));
		return;
	}

	hService = OpenService(hSCM, g_service, SERVICE_QUERY_CONFIG);
	if(!hService)
	{
		ErrorPrinter(_T("OpenService"));
		CloseServiceHandle(hSCM);
		return;
	}

	// Obtain the number of bytes needed
	bRet = QueryServiceConfig(hService, 0, 0, &dwBytesNeeded);

	// Allocate the proper size
	pqscBuf = (LPQUERY_SERVICE_CONFIG)LocalAlloc(LPTR, dwBytesNeeded);
	if(!pqscBuf)
	{
		ErrorPrinter(_T("LocalAlloc"), TRUE);
		CloseServiceHandle(hService);
		CloseServiceHandle(hSCM);
		return;
	}
	
	// Call with the right amount
	bRet = QueryServiceConfig(hService, pqscBuf, dwBytesNeeded, &dwBytesNeeded);
	if(bRet)
	{
		_tcout << _T("Service Configuration for ") << g_service << endl;
		_tcout << _T("Display Name: ") << pqscBuf->lpDisplayName << endl;
		_tcout << _T("Type: 0x") << pqscBuf->dwServiceType << endl;
		_tcout << _T("Start Type: 0x") << pqscBuf->dwStartType << endl;
		_tcout << _T("Error Level: 0x") << pqscBuf->dwErrorControl << endl;
		_tcout << _T("Binary path: ") << pqscBuf->lpBinaryPathName << endl;
		_tcout << _T("Load Order Group: ") << pqscBuf->lpLoadOrderGroup << endl;
		_tcout << _T("Tag ID: ") << pqscBuf->dwTagId << endl;
		_tcout << _T("Dependencies: ") << endl;

		if(pqscBuf->lpDependencies)
		{
			TCHAR* pszDepend = 0;
			int i = 0;
			pszDepend = &pqscBuf->lpDependencies[i];
			while(*pszDepend != 0) 
			{
				_tcout << pszDepend << endl;
				i += _tcslen(pszDepend) + 1;
				pszDepend = &pqscBuf->lpDependencies[i];
			}
		}
		_tcout << _T("Login Under: ") << pqscBuf->lpServiceStartName << endl;
	}
	else
		ErrorPrinter(_T("QueryServiceConfig"));

	LocalFree(pqscBuf);
	CloseServiceHandle(hService);
	CloseServiceHandle(hSCM);
	return;
}

void Status()
{
	SC_HANDLE hSCM = 0;
	SC_HANDLE hService = 0 ;
	BOOL bRet = FALSE;
	
	SERVICE_STATUS ss;
	
	hSCM = OpenSCManager(NULL, NULL, GENERIC_READ);
	if(!hSCM)
	{
		ErrorPrinter(_T("OpenSCManager"));
		return;
	}

	hService = OpenService(hSCM, g_service, SERVICE_QUERY_STATUS);
	if(!hService) 
	{
		ErrorPrinter(_T("OpenService"));
		CloseServiceHandle(hSCM);
		return;
	}

	bRet = QueryServiceStatus(hService, &ss);
	if(bRet)
	{
		_tcout << _T("Service Status for ") << g_service << endl;
		_tcout << _T("Type: 0x") << ss.dwServiceType << endl;
		_tcout << _T("Current State: 0x") << ss.dwCurrentState << endl;
		_tcout << _T("Controls Accepted: ") << ss.dwControlsAccepted << endl;
		_tcout << _T("Win32 Exit: ") << ss.dwWin32ExitCode << endl;
		_tcout << _T("Service Exit: ") << ss.dwServiceSpecificExitCode << endl;
		_tcout << _T("Checkpoint: 0x") << ss.dwCheckPoint << endl;
		_tcout << _T("WaitHint: 0x") << ss.dwWaitHint << endl;
	}
	else
		ErrorPrinter( _T("QueryServiceStatus"));

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCM);
	return;
}

void Dependencies()
{
	SC_HANDLE hSCM = 0;
	SC_HANDLE hService = 0;
	BOOL bRet = 0;
	
	DWORD dwBytesNeeded = 0;
	DWORD dwServicesReturned = 0;
	LPENUM_SERVICE_STATUS pessBuf = {0};

	hSCM = OpenSCManager(NULL, NULL, GENERIC_READ);
	if(!hSCM)
	{
		ErrorPrinter(_T("OpenSCManager"));
		return;
	}

	hService = OpenService(hSCM, g_service, SERVICE_ENUMERATE_DEPENDENTS);
	if(!hService)
	{
		ErrorPrinter(_T("OpenService"));
		CloseServiceHandle(hSCM);
		return;
	}

	// Find out how much to allocate
	bRet = EnumDependentServices(hService,
                                 SERVICE_STATE_ALL,
                                 0,
                                 0,
                                 &dwBytesNeeded,
                                 &dwServicesReturned);

	if(dwBytesNeeded == 0)
	{
		_tprintf(_T("%s has no dependencies\n"), g_service);
		CloseServiceHandle(hService);
		CloseServiceHandle(hSCM);
		return;
	}

	// Allocate the proper size
	pessBuf = (LPENUM_SERVICE_STATUS)LocalAlloc(LPTR, dwBytesNeeded);
	if(!pessBuf)
	{
		ErrorPrinter(_T("LocalAlloc"), TRUE);
		CloseServiceHandle(hService);
		CloseServiceHandle(hSCM);
		return;
	}

	bRet = EnumDependentServices(hService,
                                 SERVICE_STATE_ALL,
                                 pessBuf,
                                 dwBytesNeeded,
                                 &dwBytesNeeded,
                                 &dwServicesReturned);
	
	if(bRet)
	{
		LPENUM_SERVICE_STATUS pess = 0;
		_tcout << _T( "Services dependent on ") << g_service << endl;
		for(int i = 0 ; i < dwServicesReturned ; i++)
		{
			pess = &pessBuf[i];
			_tcout << pess->lpDisplayName << endl;
			_tcout << _T("  Current State: 0x");
			_tcout << pess->ServiceStatus.dwCurrentState << endl;
		}
	}
	else
		ErrorPrinter(_T("EnumDependentServices"));
	
	// Clean up
	LocalFree(pessBuf);
	CloseServiceHandle(hService);
	CloseServiceHandle(hSCM);
	return;
}

void Start()
{
	SC_HANDLE hSCM = 0;
	SC_HANDLE hService = 0 ;
	BOOL bRet = 0;
	DWORD dwOldCheck = 0;
	
	SERVICE_STATUS ss;

	hSCM = OpenSCManager(NULL, NULL, GENERIC_READ);
	if(!hSCM)
	{
		ErrorPrinter(_T("OpenSCManager"));
		return;
	}

	hService = OpenService(hSCM, g_service, SERVICE_START | SERVICE_QUERY_STATUS);
	if(!hService)
	{
		ErrorPrinter(_T("OpenService"));
		CloseServiceHandle(hSCM);
		return;
	}

	if(!StartService(hService, 0, NULL))
	{
		ErrorPrinter(_T("StartService"));
		CloseServiceHandle(hService);
		CloseServiceHandle(hSCM);
		return;
	}
	
	// Optionally, make sure service is running before continuing...
	bRet = QueryServiceStatus(hService, &ss);
	if(!bRet)
	{
		ErrorPrinter(_T("QueryServiceStatus"), TRUE);
		CloseServiceHandle(hService);
		CloseServiceHandle(hSCM);
		return;
	}

	while(SERVICE_RUNNING != ss.dwCurrentState)
	{
		dwOldCheck = ss.dwCheckPoint;
		Sleep(ss.dwWaitHint);
		
		bRet = QueryServiceStatus(hService, &ss);
		if(!bRet)
		{
			ErrorPrinter(_T("QueryServiceStatus"), TRUE);
			CloseServiceHandle(hService);
			CloseServiceHandle(hSCM);
			return;
		}

		// Service changed state or did not increment in time, so break
		if(dwOldCheck >= ss.dwCheckPoint)
			break;
	}

	if(SERVICE_RUNNING == ss.dwCurrentState)
		_tcout << g_service << _T(" started successfully.") << endl;
	else
	{
		_tcout << g_service << _T(" start unsuccessful: ") << endl;
		_tcout << _T("Current State: 0x") << ss.dwCurrentState << endl;
		_tcout << _T("Win32 Exit: ") << ss.dwWin32ExitCode << endl;
		_tcout << _T("Service Exit: ") << ss.dwServiceSpecificExitCode << endl;
		_tcout << _T("Checkpoint: 0x") << ss.dwCheckPoint << endl;
		_tcout << _T("WaitHint: 0x") << ss.dwWaitHint << endl;
	}

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCM);
	return;
}

void Control(DWORD dwControl)
{
	SC_HANDLE hSCM = 0;
	SC_HANDLE hService = 0 ;
	BOOL bRet = 0;
	
	SERVICE_STATUS ss;

	hSCM = OpenSCManager(NULL, NULL, GENERIC_READ);
	if(!hSCM)
	{
		ErrorPrinter(_T("OpenSCManager"));
		return;
	}

	hService = OpenService(hSCM, g_service, GENERIC_EXECUTE);
	if(!hService)
	{
		ErrorPrinter(_T("OpenService"));
		CloseServiceHandle(hSCM);
		return;
	}

	bRet = ControlService(hService, dwControl, &ss);
	if(bRet)
	{
		_tcout << _T("Service Status for ") << g_service << endl;
		_tcout << _T("Type: 0x") << ss.dwServiceType << endl;
		_tcout << _T("Current State: 0x") << ss.dwCurrentState << endl;
		_tcout << _T("Controls Accepted: ") << ss.dwControlsAccepted << endl;
		_tcout << _T("Win32 Exit: ") << ss.dwWin32ExitCode << endl;
		_tcout << _T("Service Exit: ") << ss.dwServiceSpecificExitCode << endl;
		_tcout << _T("Checkpoint: 0x") << ss.dwCheckPoint << endl;
		_tcout << _T("WaitHint: 0x") << ss.dwWaitHint << endl;		
	}
	else
		ErrorPrinter(_T("ControlService"));

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCM);
	return;
}

DWORD ErrorPrinter(const TCHAR* psz, DWORD dwErr)
{
	LPVOID lpvMsgBuf;
    if(!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, 0, dwErr, 0, (LPTSTR)&lpvMsgBuf, 0, 0))
	{
		_tprintf(_T("%s failed: Unknown error %x\n"), psz, dwErr);
	}
	else
		_tprintf(_T("%s failed: %s\n"), psz, (LPTSTR)lpvMsgBuf);

	LocalFree(lpvMsgBuf);
	return dwErr;
}