// Class CServiceConfig
const int MAX_SERVICE_NAME = 256;

class CServiceConfig
{
public:
	CServiceConfig(LPTSTR szServiceName, LPTSTR szDisplay);
	~CServiceConfig() {}

	LPTSTR GetServiceName() {return m_service;}
	LPTSTR GetDisplayName() {return m_display;}

	void Install(DWORD dwType = SERVICE_WIN32_OWN_PROCESS,
				 DWORD dwStart = SERVICE_DEMAND_START,
				 LPCTSTR lpDepends = NULL, 
				 LPCTSTR lpName = NULL,
				 LPCTSTR lpPassword = NULL);

	void Remove(BOOL bForce = FALSE);
	BOOL IsInstalled();

	void ChangeStartType(BOOL bAutostart);
	void GetConfig();
	
	void Status();
	void Dependencies();

	void Start();
	void Control(DWORD dwControl);

	SC_LOCK LockDatabase(SC_HANDLE hSCM);
	DWORD ErrorPrinter(const TCHAR* pszFcn, DWORD dwErr = GetLastError());

private:
	TCHAR m_service[257];
	TCHAR m_display[257];
};