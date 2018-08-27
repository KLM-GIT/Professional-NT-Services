#include "precomp.h"
#include "CServiceInstall.h"

CServiceInstall::CServiceInstall( LPCTSTR szServiceName, LPCTSTR szDisplay )
{
	m_service = szServiceName;
	m_display = szDisplay;
}

DWORD CServiceInstall::Install(DWORD dwType, DWORD dwStart,
							   LPCTSTR lpDepends, LPCTSTR lpName,
							   LPCTSTR lpPassword )
{
	if( IsInstalled() == TRUE )
		return TRUE;
	
	SC_HANDLE hSCM = OpenSCManager( NULL,
									NULL,
									SC_MANAGER_CREATE_SERVICE );
	if ( !hSCM )
		return ::GetLastError();

    TCHAR szFilePath[_MAX_PATH];
    ::GetModuleFileName(NULL, szFilePath, _MAX_PATH);

	SC_HANDLE hService = CreateService( 
		hSCM,
		m_service,
		m_display,
		SERVICE_ALL_ACCESS,
		dwType,
		dwStart,
		SERVICE_ERROR_NORMAL,
		szFilePath,
		NULL,
		NULL,
		lpDepends,
		lpName,
		lpPassword );

	if ( !hService ) 
		return ::GetLastError();
	else
	{
		_tcout << m_service << _TEXT(" Created") << endl;
		CloseServiceHandle( hService );
	}

	CloseServiceHandle( hSCM );
	return 0;
}

DWORD CServiceInstall::Remove( BOOL bForce )
{
	SC_HANDLE hSCM = ::OpenSCManager( NULL,
									  NULL,
									  SC_MANAGER_CONNECT );
	if ( !hSCM )
		return ::GetLastError();
	
	SC_HANDLE hService = ::OpenService(
		hSCM,
		m_service,
		DELETE );						
	if ( !hService ) 
		return ::GetLastError();
	
	//Force the service to stop so it is deleted NOW
		//rather than marked for deletion
	if( bForce == TRUE ) 
	{
		SERVICE_STATUS status;
		::ControlService(hService, SERVICE_CONTROL_STOP, &status);
		_tcout << m_service << _TEXT(" stopped") << endl;
	}

	BOOL bSuccess = ::DeleteService( hService );

	if (!bSuccess)
		return ::GetLastError();

	_tcout << m_service << _TEXT(" removed") << endl;
	::CloseServiceHandle( hService );
	::CloseServiceHandle( hSCM );

	return 0;
}

BOOL CServiceInstall::IsInstalled( )
{
    BOOL bRes = FALSE;

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);

    if (hSCM != NULL)
	{
        SC_HANDLE hService = ::OpenService(hSCM, m_service, SERVICE_QUERY_CONFIG);
        if (hService != NULL)
		{
            bRes = TRUE;
            ::CloseServiceHandle(hService);
        }
        ::CloseServiceHandle(hSCM);
    }
    return bRes;
}