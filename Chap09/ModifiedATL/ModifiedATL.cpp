// ModifiedATL.cpp : Implementation of WinMain


// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f ModifiedATLps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "ModifiedATL.h"

#include "ModifiedATL_i.c"


#include <stdio.h>

CServiceModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()


LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
	while (*p1 != NULL)
	{
		LPCTSTR p = p2;
		while (*p != NULL)
		{
			if (*p1 == *p++)
				return p1+1;
		}
		p1++;
	}
	return NULL;
}

// Although some of these functions are big they are declared inline since they are only used once

inline HRESULT CServiceModule::RegisterServer(BOOL bRegTypeLib, BOOL bService)
{
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
		return hr;

	// Remove any previous service since it may point to
	// the incorrect file
	Uninstall();

	// Add service entries
	UpdateRegistryFromResource(IDR_ModifiedATL, TRUE);

	// Adjust the AppID for Local Server or Service
	CRegKey keyAppID;
	LONG lRes = keyAppID.Open(HKEY_CLASSES_ROOT, _T("AppID"));
	if (lRes != ERROR_SUCCESS)
		return lRes;

	CRegKey key;
	lRes = key.Open(keyAppID, _T("{D285D154-ED84-11D1-8466-0020AF05ED45}"));
	if (lRes != ERROR_SUCCESS)
		return lRes;
	key.DeleteValue(_T("LocalService"));
	
	if (bService)
	{
		key.SetValue(_T("ModifiedATL"), _T("LocalService"));
		key.SetValue(_T("-Service"), _T("ServiceParameters"));
		// Create service
		Install();
		UpdateRegistryFromResource(IDR_ServiceParams, TRUE);
		UpdateRegistryFromResource(IDR_EVENTLOG, TRUE);

	}

	// Add object entries
	hr = CComModule::RegisterServer(bRegTypeLib);

	CoUninitialize();
	return hr;
}

inline HRESULT CServiceModule::UnregisterServer()
{
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
		return hr;

	// Remove service entries
	UpdateRegistryFromResource(IDR_ModifiedATL, FALSE);
	// Remove service
	Uninstall();
	// Remove object entries
	CComModule::UnregisterServer();

	CoUninitialize();
	return S_OK;
}

inline long CServiceModule::ReadParameters()
{
	//Assemble key name
	TCHAR szKey[100] = {0};
	DWORD slen = 25;
	TCHAR psz[100] = {0};
	
	wsprintf( szKey, _T("SYSTEM\\CurrentControlSet\\Services\\%s\\Parameters\0") ,
			_Module.m_szServiceName);
	CRegKey keyAppID;
	LONG lres = keyAppID.Open(HKEY_LOCAL_MACHINE, szKey);
	if( lres != ERROR_SUCCESS )
		goto RegistryError;

	_tcscpy(psz, _T("Server"));
	lres = keyAppID.QueryValue( m_szServer, psz, &slen );
	if( lres != ERROR_SUCCESS )
		goto RegistryError;

	_tcscpy(psz, _T("MaxTimeout"));
	lres = keyAppID.QueryValue( m_dwMaxTimeout, psz );
	if( lres != ERROR_SUCCESS )
		goto RegistryError;

	//Close key
	lres = keyAppID.Close( );
	
	return ERROR_SUCCESS;

RegistryError:
	CEventLog el(m_szServiceName);
	el.LogEvent( MODATL_CONFIGURATION_DATA_MISSING, psz );
	return lres;
}


inline void CServiceModule::Init(_ATL_OBJMAP_ENTRY* p, HINSTANCE h, UINT nServiceNameID)
{
	CComModule::Init(p, h);

	m_bService = TRUE;

	LoadString(h, nServiceNameID, m_szServiceName, sizeof(m_szServiceName) / sizeof(TCHAR));
	LoadString(h, IDS_DISPLAYNAME, m_szDisplayName, sizeof(m_szDisplayName) / sizeof(TCHAR));

    // set up the initial service status 
    m_hServiceStatus = NULL;
    m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    m_status.dwCurrentState = SERVICE_STOPPED;
    m_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    m_status.dwWin32ExitCode = 0;
    m_status.dwServiceSpecificExitCode = 0;
    m_status.dwCheckPoint = 0;
    m_status.dwWaitHint = 0;
}

LONG CServiceModule::Unlock()
{
	LONG l = CComModule::Unlock();
	if (l == 0 && !m_bService)
		SetEvent( m_hStopEvent );
	return l;
}

BOOL CServiceModule::IsInstalled()
{
    BOOL bResult = FALSE;

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

    if (hSCM != NULL)
	{
        SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_QUERY_CONFIG);
        if (hService != NULL)
		{
            bResult = TRUE;
            ::CloseServiceHandle(hService);
        }
        ::CloseServiceHandle(hSCM);
    }
    return bResult;
}

inline BOOL CServiceModule::Install()
{
	if (IsInstalled())
		return TRUE;

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
	{
		MessageBox(NULL, _T("Couldn't open service manager"), m_szServiceName, MB_OK);
        return FALSE;
	}

    // Get the executable file path
    TCHAR szFilePath[_MAX_PATH];
    ::GetModuleFileName(NULL, szFilePath, _MAX_PATH);

    SC_HANDLE hService = ::CreateService(
		hSCM, m_szServiceName, m_szDisplayName,
		SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
		SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
        szFilePath, NULL, NULL, _T("RPCSS\0"), NULL, NULL);

    if (hService == NULL)
	{
        ::CloseServiceHandle(hSCM);
		MessageBox(NULL, _T("Couldn't create service"), m_szServiceName, MB_OK);
		return FALSE;
    }

    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);
	return TRUE;
}

inline BOOL CServiceModule::Uninstall()
{
	if (!IsInstalled())
		return TRUE;

	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (hSCM == NULL)
	{
		MessageBox(NULL, _T("Couldn't open service manager"), m_szServiceName, MB_OK);
		return FALSE;
	}

	SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_STOP | DELETE);

	if (hService == NULL)
	{
		::CloseServiceHandle(hSCM);
		MessageBox(NULL, _T("Couldn't open service"), m_szServiceName, MB_OK);
		return FALSE;
	}
	SERVICE_STATUS status;
	::ControlService(hService, SERVICE_CONTROL_STOP, &status);

	BOOL bDelete = ::DeleteService(hService);
	::CloseServiceHandle(hService);
	::CloseServiceHandle(hSCM);

	if (bDelete)
		return TRUE;

	MessageBox(NULL, _T("Service could not be deleted"), m_szServiceName, MB_OK);
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Service startup and registration
inline void CServiceModule::Start()
{
    SERVICE_TABLE_ENTRY st[] =
	{
        { m_szServiceName, _ServiceMain },
        { NULL, NULL }
    };
    if (m_bService && !::StartServiceCtrlDispatcher(st))
	{
		m_bService = FALSE;
	}
	if (m_bService == FALSE)
		Run();
}

inline void CServiceModule::ServiceMain(DWORD /* dwArgc */, LPTSTR* /* lpszArgv */)
{
    // Register the control request handler
    m_status.dwCurrentState = SERVICE_START_PENDING;
    m_hServiceStatus = RegisterServiceCtrlHandler(m_szServiceName, _Handler);
    if (m_hServiceStatus == NULL)
	{
        CEventLog el(m_szServiceName);
		el.LogWin32Error(MODATL_WIN32_ERROR, _T("Handler not installed"));
        return;
    }
    SetServiceStatus(SERVICE_START_PENDING, 1, 2000);

	ReadParameters();

    // When the Run function returns, the service has stopped.
    Run();

    //Do this before because the thread terminates.
	CEventLog el(m_szServiceName);
	el.LogEvent(MODATL_STOPPED, EVENTLOG_INFORMATION_TYPE );
	
    SetServiceStatus(SERVICE_STOPPED);
}

inline void CServiceModule::Handler(DWORD dwOpcode)
{
	if (m_dwRequestedControl == dwOpcode)
		return;

	switch (dwOpcode)
	{
	case SERVICE_CONTROL_STOP:
		SetServiceStatus(SERVICE_STOP_PENDING, 1, 5000);

		SetEvent( m_hStopEvent );

		break;
	case SERVICE_CONTROL_PAUSE:
		break;
	case SERVICE_CONTROL_CONTINUE:
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		break;
	default:
        CEventLog el(m_szServiceName);		
		el.LogEvent(MODATL_GENERIC_ERROR, _T("Bad service request"));
		return;
	}
	m_dwRequestedControl = dwOpcode;
}

void WINAPI CServiceModule::_ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
	_Module.ServiceMain(dwArgc, lpszArgv);
}
void WINAPI CServiceModule::_Handler(DWORD dwOpcode)
{
	_Module.Handler(dwOpcode); 
}

void CServiceModule::Run()
{
	
	HRESULT hr;
	_Module.dwThreadID = GetCurrentThreadId();

	//Initialize Event
	m_hStopEvent = ::CreateEvent( NULL, TRUE, FALSE, NULL );
	
	HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	_ASSERTE(SUCCEEDED(hr));

	// This provides a NULL DACL which will allow access to everyone.
	CSecurityDescriptor sd;
	sd.InitializeFromThreadToken();
	hr = CoInitializeSecurity(sd, -1, NULL, NULL,
		RPC_C_AUTHN_LEVEL_PKT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	_ASSERTE(SUCCEEDED(hr));

	hr = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER, 
			REGCLS_MULTIPLEUSE | REGCLS_SUSPENDED );
	_ASSERTE(SUCCEEDED(hr));

	hr = CoResumeClassObjects();
	_ASSERTE(SUCCEEDED(hr));

    CEventLog el(m_szServiceName);
	el.LogEvent(MODATL_STARTED, EVENTLOG_INFORMATION_TYPE);
    SetServiceStatus(SERVICE_RUNNING);

	//Waits here till STOP request
	WaitForSingleObject(m_hStopEvent, INFINITE);

	CoSuspendClassObjects();

	_Module.RevokeClassObjects();

	CoUninitialize();

	::CloseHandle( m_hStopEvent );

}

/////////////////////////////////////////////////////////////////////////////
//
extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, 
	HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int /*nShowCmd*/)
{
	lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
	_Module.Init(ObjectMap, hInstance, IDS_SERVICENAME);
	_Module.m_bService = TRUE;

	TCHAR szTokens[] = _T("-/");

	LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
	while (lpszToken != NULL)
	{
		if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
			return _Module.UnregisterServer();

		// Register as Local Server
		if (lstrcmpi(lpszToken, _T("RegServer"))==0)
			return _Module.RegisterServer(TRUE, FALSE);
		
		// Register as Service
		if (lstrcmpi(lpszToken, _T("Service"))==0)
			return _Module.RegisterServer(TRUE, TRUE);
		
		lpszToken = FindOneOf(lpszToken, szTokens);
	}

	// Are we Service or Local Server
	CRegKey keyAppID;
	LONG lRes = keyAppID.Open(HKEY_CLASSES_ROOT, _T("AppID"));
	if (lRes != ERROR_SUCCESS)
		return lRes;

	CRegKey key;
	lRes = key.Open(keyAppID, _T("{D285D154-ED84-11D1-8466-0020AF05ED45}"));
	if (lRes != ERROR_SUCCESS)
		return lRes;

	TCHAR szValue[_MAX_PATH];
	DWORD dwLen = _MAX_PATH;
	lRes = key.QueryValue(szValue, _T("LocalService"), &dwLen);

	_Module.m_bService = FALSE;
	if (lRes == ERROR_SUCCESS)
		_Module.m_bService = TRUE;

	_Module.Start();

    // When we get here, the service has been stopped
    return _Module.m_status.dwWin32ExitCode;
}



void CServiceModule::SetServiceStatus( DWORD dwNewState, DWORD dwNewCheckpoint,
 						DWORD dwNewHint, DWORD dwNewControls,
						DWORD dwExitCode, DWORD dwSpecificExit )
{		
	//The only state which can set Exit Codes is STOPPED
	if(	dwNewState != SERVICE_STOPPED )
	{
		dwExitCode = S_OK;
		dwSpecificExit = 0;
	}

	//Only pending states can set checkpoints or wait hints
	//and pending states must set wait hints
	if( dwNewState == SERVICE_STOPPED || dwNewState == SERVICE_PAUSED ||
		dwNewState == SERVICE_RUNNING )
	{		
		//Requires hint and checkpoint == 0
		//Fix it so that NO_CHANGE from previous state does not cause nonzero in this
		dwNewHint = 0;
		dwNewCheckpoint = 0;
	}
	else
	{

		//Requires hint and checkpoint != 0 
		if (dwNewHint <= 0 || dwNewCheckpoint <=0)
		{
			CEventLog el(m_szServiceName);
			el.LogEvent( MODATL_GENERIC_ERROR, 
				_T( "SetServiceStatus: Pending statuses require a hint and checkpoint" ) ); 
		}
	}

	m_cs.Lock();
	
	m_status.dwCurrentState = dwNewState;
	if( dwNewCheckpoint != STATE_NO_CHANGE )
		m_status.dwCheckPoint = dwNewCheckpoint;
	if( dwNewHint != STATE_NO_CHANGE )
		m_status.dwWaitHint = dwNewHint;
	if( dwNewControls != STATE_NO_CHANGE )
		m_status.dwControlsAccepted = dwNewControls;

	m_status.dwWin32ExitCode = dwExitCode;
	m_status.dwServiceSpecificExitCode = dwSpecificExit;
	
	m_cs.Unlock();
	
	if( !::SetServiceStatus( m_hServiceStatus, &m_status ))
	{
		CEventLog el(m_szServiceName);
		el.LogWin32Error( MODATL_WIN32_ERROR, _T( "SetServiceStatus" ) ); 
	}
}