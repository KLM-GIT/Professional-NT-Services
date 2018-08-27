
class CServiceInstall
{
public:
	CServiceInstall( LPCTSTR szServiceName, LPCTSTR szDisplay );
	~CServiceInstall( ) { }

	DWORD Install(	DWORD dwType = SERVICE_WIN32_OWN_PROCESS,
					DWORD dwStart = SERVICE_DEMAND_START,
					LPCTSTR lpDepends = NULL, 
					LPCTSTR lpName = NULL,
					LPCTSTR lpPassword = NULL
					);
	DWORD Remove( BOOL bForce = FALSE );

	BOOL IsInstalled( );

private:
	LPCTSTR m_service;
	LPCTSTR m_display;

};