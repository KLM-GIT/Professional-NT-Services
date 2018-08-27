// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__D285D157_ED84_11D1_8466_0020AF05ED45__INCLUDED_)
#define AFX_STDAFX_H__D285D157_ED84_11D1_8466_0020AF05ED45__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT


#define _WIN32_WINNT 0x0400
#define _ATL_FREE_THREADED


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
#define STATE_NO_CHANGE 12345
#include "ModATLMsg.h"
#include "CEventLog.h"

class CServiceModule : public CComModule
{
public:
	HRESULT RegisterServer(BOOL bRegTypeLib, BOOL bService);
	HRESULT UnregisterServer();
	void Init(_ATL_OBJMAP_ENTRY* p, HINSTANCE h, UINT nServiceNameID);
    void Start();
	void ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
    void Handler(DWORD dwOpcode);
    void Run();
    BOOL IsInstalled();
    BOOL Install();
    BOOL Uninstall();
	LONG Unlock();
	void SetServiceStatus(
			DWORD dwNewState, 
			DWORD dwNewCheckpoint = STATE_NO_CHANGE,
			DWORD dwNewHint = STATE_NO_CHANGE,
			DWORD dwNewControls = STATE_NO_CHANGE,
			DWORD dwExitCode = S_OK,
			DWORD dwSpecificExit = 0 );

//Implementation
private:
	HANDLE m_hStopEvent;
	DWORD m_dwRequestedControl;
	long ReadParameters();
	static void WINAPI _ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
    static void WINAPI _Handler(DWORD dwOpcode);

	typedef CComMultiThreadModel::AutoCriticalSection _CritSec;
	_CritSec m_cs;

// data members
public:
	DWORD m_dwMaxTimeout;
	TCHAR m_szServer[25];
    TCHAR m_szServiceName[256];
	TCHAR m_szDisplayName[256];
    SERVICE_STATUS_HANDLE m_hServiceStatus;
    SERVICE_STATUS m_status;
	DWORD dwThreadID;
	BOOL m_bService;
};

extern CServiceModule _Module;
#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D285D157_ED84_11D1_8466_0020AF05ED45__INCLUDED)
