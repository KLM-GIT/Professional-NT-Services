// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__D285D166_ED84_11D1_8466_0020AF05ED45__INCLUDED_)
#define AFX_STDAFX_H__D285D166_ED84_11D1_8466_0020AF05ED45__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT


#define _WIN32_WINNT 0x0500
#define _ATL_FREE_THREADED


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
#define STATE_NO_CHANGE 12345
#include <sqlext.h>
#include "BusObjMsg.h"
#include "CEventLog.h"
#include "CQuartermaster.h"

class CServiceModule : public CComModule
{
public:
	~CServiceModule()
	{ 
		CComModule::~CComModule();
		//delete the event log object in CServiceModule
		delete m_pEl;
	}

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
	long ReadParameters();


//Implementation
private:
	DWORD m_dwRequestedControl;
	static void WINAPI _ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
    static void WINAPI _Handler(DWORD dwOpcode);

	typedef CComMultiThreadModel::AutoCriticalSection _CritSec;
	_CritSec m_cs;

// data members
public:
	BOOL m_Stopped;
	BOOL m_Paused;
	HANDLE m_hStopEvent;
    TCHAR m_szServiceName[256];
	TCHAR m_szDisplayName[256];
    SERVICE_STATUS_HANDLE m_hServiceStatus;
    SERVICE_STATUS m_status;
	DWORD dwThreadID;
	BOOL m_bService;

	// The resource pooler
	CQuartermaster* m_pQM;

	// CEventLog Object
	CEventLog* m_pEl;

	//Registry defaults
	TCHAR m_szServer[25] ;
	TCHAR m_szUser[25] ;
	TCHAR m_szPassword[25] ;

	DWORD m_dwMaxResources; 
	DWORD m_dwStartResources;
	DWORD m_dwMaxWaitForHandleTime; //How long will thread wait for a handle?
	DWORD m_dwHandleLifeTime; 
	DWORD m_dwAllocationPoll; 
	DWORD m_dwMinPoolSize;
	DWORD m_dwResourceAllocSize;
	DWORD m_dwDeadResourcePoll;

	DWORD m_dwWaitForClientsBeforeClosing;

};

extern CServiceModule _Module;

#include <atlcom.h>

#include <process.h>
typedef unsigned (WINAPI *PBEGINTHREADEX_TFUNC) 
(
	LPVOID lpThreadParameter
);

typedef unsigned* PBEGINTHREADEX_TID;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D285D166_ED84_11D1_8466_0020AF05ED45__INCLUDED)
