// PropPage1.cpp : implementation file
//

#include "stdafx.h"
#include "BusObjCpl.h"
#include "PropPage1.h"
#include "winsvc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPage1 property page

IMPLEMENT_DYNCREATE(CPropPage1, CPropertyPage)

CPropPage1::CPropPage1() : CPropertyPage(CPropPage1::IDD)
{
	//{{AFX_DATA_INIT(CPropPage1)
	m_szPassword = _T("");
	m_szServer = _T("");
	m_szUserName = _T("");
	//}}AFX_DATA_INIT
}

CPropPage1::~CPropPage1()
{
}

void CPropPage1::DoDataExchange(CDataExchange* pDX)
{
	
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPage1)
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_szPassword);
	DDV_MaxChars(pDX, m_szPassword, 25);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_szServer);
	DDV_MaxChars(pDX, m_szServer, 25);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_szUserName);
	DDV_MaxChars(pDX, m_szUserName, 25);
	//}}AFX_DATA_MAP

	if( pDX->m_bSaveAndValidate == TRUE )
	{
		UpdateRegistry();
		SendControlMessage(); //Sends a custom message to the handler for the service
	}
}

BOOL CPropPage1::OnInitDialog()
{
	ReadRegistry();
	return CDialog::OnInitDialog();
}



BEGIN_MESSAGE_MAP(CPropPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPage1)
	ON_EN_CHANGE(IDC_EDIT_PASSWORD, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_SERVERNAME, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_USERNAME, OnChangeEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPage1 message handlers

void CPropPage1::ReadRegistry()
{
    HKEY hkey;
	CHAR szKey[256];
	CHAR psz[100] = {0};
	CHAR psz2[100] = {0};

	strcpy(szKey, "SOFTWARE\\WroxBook\\BusObject\\Parameters\0");
    long lres = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                     szKey, 0, KEY_ALL_ACCESS,
                     &hkey);
	if ( lres != ERROR_SUCCESS)
	{
		//Generate message - service not installed
		AfxMessageBox("Registry Open Failed. The service is not installed properly.");
		return;
	}

	DWORD dwSize = 0;
	DWORD dwType = 0;
	CHAR sz[25] = {0};

	//Read each value
	dwSize = 25;
	strcpy(psz, "Password");
	lres = RegQueryValueEx( hkey, psz, NULL, &dwType, (BYTE*)sz, &dwSize );
	if( lres != ERROR_SUCCESS )
		goto RegReadError;
	m_szPassword = sz;

	//Server
	dwSize = 25;
	strcpy(psz, "Server");
	lres = RegQueryValueEx( hkey, psz, NULL, &dwType, (BYTE*)sz, &dwSize );
	if( lres != ERROR_SUCCESS )
		goto RegReadError;
	m_szServer = sz;
    
	//User
	dwSize = 25;
	strcpy(psz, "User");
	lres = RegQueryValueEx( hkey, psz, NULL, &dwType, (BYTE*)sz, &dwSize );
	if( lres != ERROR_SUCCESS )
		goto RegReadError;
	m_szUserName = sz;

	// Finished with key
    RegCloseKey(hkey);
	return;

RegReadError:
	wsprintf(psz2, "Value query on '%s' failed with code %lu", psz, lres);
	AfxMessageBox(psz2);
    RegCloseKey(hkey);
}

void CPropPage1::UpdateRegistry()
{
    HKEY hkey;
	char szKey[256];
	CHAR psz[100] = {0};
	CHAR psz2[100] = {0};

	strcpy(szKey, "SOFTWARE\\WroxBook\\BusObject\\Parameters\0");
    long lres = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                     szKey, 0, KEY_ALL_ACCESS,
                     &hkey);
	if ( lres != ERROR_SUCCESS)
	{
		//Generate message - service not installed
		AfxMessageBox("Registry Open Failed. The service is not installed properly.");
		return;
	}

	DWORD dwSize = 0;
	DWORD dwType = REG_SZ;
	char sz[25] = {0};

	//Write each value
	dwSize = 25;
	strcpy(psz, "Password");
	strcpy(sz, m_szPassword.GetBuffer(25) );
	lres = RegSetValueEx( hkey, psz, NULL, dwType, (BYTE*)sz, dwSize );
	if( lres != ERROR_SUCCESS )
		goto RegReadError;

	strcpy(psz, "Server");
	strcpy(sz, m_szServer.GetBuffer(25) );
	lres = RegSetValueEx( hkey, psz, NULL, dwType, (BYTE*)sz, dwSize );
	if( lres != ERROR_SUCCESS )
		goto RegReadError;

	strcpy(psz, "User");
	strcpy(sz, m_szUserName.GetBuffer(25) );
	lres = RegSetValueEx( hkey, psz, NULL, dwType, (BYTE*)sz, dwSize );
	if( lres != ERROR_SUCCESS )
		goto RegReadError;

	// Finished with key
    RegCloseKey(hkey);
	return;

RegReadError:
	wsprintf(psz2, "Value write on '%s' failed with code %lu", psz, lres);
	AfxMessageBox(psz2);
    RegCloseKey(hkey);

}

void CPropPage1::OnChangeEdit() 
{
	SetModified(TRUE);	
}

void CPropPage1::SendControlMessage()
{
	SERVICE_STATUS ss;
	const DWORD SERVICE_CONTROL_UPDATEFROMREGISTRY=129;
	
	char szService[10] = "BusObject";

	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT | SC_MANAGER_QUERY_LOCK_STATUS );

	if (hSCM == NULL)
	{
		AfxMessageBox("Couldn't open service manager");
		return;
	}

	SC_HANDLE hService = ::OpenService(hSCM, szService, SERVICE_USER_DEFINED_CONTROL);

	if (hService == NULL)
	{
		::CloseServiceHandle(hSCM);
		AfxMessageBox("Couldn't open service to notify of registry changes");
		return;
	}

	::ControlService( hService, SERVICE_CONTROL_UPDATEFROMREGISTRY, &ss );

	::CloseServiceHandle(hService);
	::CloseServiceHandle(hSCM);

}

