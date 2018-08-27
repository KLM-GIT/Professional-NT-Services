// PropPage2.cpp : implementation file
//

#include "stdafx.h"
#include "BusObjCpl.h"
#include "PropPage2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPage2 property page

IMPLEMENT_DYNCREATE(CPropPage2, CPropertyPage)

CPropPage2::CPropPage2() : CPropertyPage(CPropPage2::IDD)
{
	//{{AFX_DATA_INIT(CPropPage2)
	m_dwDeadPoll = 0;
	m_dwHandleLife = 0;
	m_dwInitSessions = 0;
	m_dwMaxSessions = 0;
	m_dwMaxWait = 0;
	m_dwReallocMin = 0;
	m_dwReallocPoll = 0;
	m_dwReallocSize = 0;
	m_dwWaitToClose = 0;
	//}}AFX_DATA_INIT
}

CPropPage2::~CPropPage2()
{
}

void CPropPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPage2)
	DDX_Text(pDX, IDC_DEADPOLL, m_dwDeadPoll);
	DDX_Text(pDX, IDC_HANDLELIFE, m_dwHandleLife);
	DDX_Text(pDX, IDC_INITSESSIONS, m_dwInitSessions);
	DDV_MinMaxDWord(pDX, m_dwInitSessions, 0, 5000);
	DDX_Text(pDX, IDC_MAXSESSIONS, m_dwMaxSessions);
	DDV_MinMaxDWord(pDX, m_dwMaxSessions, 0, 5000);
	DDX_Text(pDX, IDC_MAXWAIT, m_dwMaxWait);
	DDV_MinMaxDWord(pDX, m_dwMaxWait, 0, 20000);
	DDX_Text(pDX, IDC_REALLOCMIN, m_dwReallocMin);
	DDV_MinMaxDWord(pDX, m_dwReallocMin, 0, 50);
	DDX_Text(pDX, IDC_REALLOCPOLL, m_dwReallocPoll);
	DDX_Text(pDX, IDC_REALLOCSIZE, m_dwReallocSize);
	DDV_MinMaxDWord(pDX, m_dwReallocSize, 0, 50);
	DDX_Text(pDX, IDC_WAITTOCLOSE, m_dwWaitToClose);
	DDV_MinMaxDWord(pDX, m_dwWaitToClose, 0, 120);
	//}}AFX_DATA_MAP
}

BOOL CPropPage2::OnInitDialog()
{
	ReadRegistry();
	return CDialog::OnInitDialog();
}


BEGIN_MESSAGE_MAP(CPropPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPage2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPage2 message handlers

void CPropPage2::ReadRegistry()
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
	DWORD dw;

	//Start Pool
	dwSize = 4;
	strcpy(psz, "ResourceStartPool");
	lres = RegQueryValueEx( hkey, psz, NULL, &dwType, (BYTE*)&dw, &dwSize );
	if( lres != ERROR_SUCCESS )
		goto RegReadError;
	m_dwInitSessions = dw;

	//ResourceMaxPool
	dwSize = 4;
	strcpy(psz, "ResourceMaxPool");
	lres = RegQueryValueEx( hkey, psz, NULL, &dwType, (BYTE*)&dw, &dwSize );
	if( lres != ERROR_SUCCESS )
		goto RegReadError;
	m_dwMaxSessions = dw;

	//ResourceAllocationSize
	dwSize = 4;
	strcpy(psz, "ResourceAllocationSize");
	lres = RegQueryValueEx( hkey, psz, NULL, &dwType, (BYTE*)&dw, &dwSize );
	if( lres != ERROR_SUCCESS )
		goto RegReadError;
	m_dwReallocSize = dw;

	//DeadResourcePollTime
	dwSize = 4;
	strcpy(psz, "DeadResourcePollTime");
	lres = RegQueryValueEx( hkey, psz, NULL, &dwType, (BYTE*)&dw, &dwSize );
	if( lres != ERROR_SUCCESS )
		goto RegReadError;
	m_dwDeadPoll = dw;

	//AllocPollTime
	dwSize = 4;
	strcpy(psz, "AllocPollTime");
	lres = RegQueryValueEx( hkey, psz, NULL, &dwType, (BYTE*)&dw, &dwSize );
	if( lres != ERROR_SUCCESS )
		goto RegReadError;
	m_dwReallocPoll = dw;
	
	//MaxWaitForResourceTime
	dwSize = 4;
	strcpy(psz, "MaxWaitForResourceTime");
	lres = RegQueryValueEx( hkey, psz, NULL, &dwType, (BYTE*)&dw, &dwSize );
	if( lres != ERROR_SUCCESS )
		goto RegReadError;
	m_dwMaxWait = dw;

	//HandleLifeTime
	dwSize = 4;
	strcpy(psz, "HandleLifeTime");
	lres = RegQueryValueEx( hkey, psz, NULL, &dwType, (BYTE*)&dw, &dwSize );
	if( lres != ERROR_SUCCESS )
		goto RegReadError;
	m_dwHandleLife = dw;

	//MinPoolSize
	dwSize = 4;
	strcpy(psz, "MinPoolSize");
	lres = RegQueryValueEx( hkey, psz, NULL, &dwType, (BYTE*)&dw, &dwSize );
	if( lres != ERROR_SUCCESS )
		goto RegReadError;
	m_dwReallocMin = dw;
	
	//WaitForClientsBeforeClosing
	dwSize = 4;
	strcpy(psz, "WaitForClientsBeforeClosing");
	lres = RegQueryValueEx( hkey, psz, NULL, &dwType, (BYTE*)&dw, &dwSize );
	if( lres != ERROR_SUCCESS )
		goto RegReadError;
	m_dwWaitToClose = dw;

	// Finished with key
    RegCloseKey(hkey);
	return;

RegReadError:
	wsprintf(psz2, "Value query on '%s' failed with code %lu", psz, lres);
	AfxMessageBox(psz);
    RegCloseKey(hkey);

}
