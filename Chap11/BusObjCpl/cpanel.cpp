// Source for CControlPanel
#include "stdafx.h"
#include "BusObjCpl.h"
#include "cpanel.h"
#include "cplpropsheet.h"
#include "proppage1.h"
#include "proppage2.h"

// static data
CControlPanel* CControlPanel::m_pThis = NULL;

CControlPanel::CControlPanel()
{
    m_pThis = this;
}

CControlPanel::~CControlPanel()
{
}

//////////////////////////////////////////////////////////////////////////////              
// Callback function

// static member functions (callbacks)
LONG APIENTRY CControlPanel::CPlApplet(HWND hwndCPl, UINT  uMsg,
                                       LONG lParam1, LONG lParam2)
{
	//Avoids state problems in MFC extensions using shared MFC libs.
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

    CControlPanel* pCtrl = m_pThis;
    ASSERT(pCtrl);

    switch (uMsg) {
    case CPL_DBLCLK:
        return pCtrl->OnDblclk(hwndCPl, lParam1, lParam2);

    case CPL_EXIT:
        return pCtrl->OnExit();

    case CPL_GETCOUNT:
        return pCtrl->OnGetCount();

    case CPL_INIT:
        return pCtrl->OnInit();

    case CPL_NEWINQUIRE:
        return pCtrl->OnNewInquire(lParam1, (NEWCPLINFO*)lParam2);

    case CPL_INQUIRE:
		return pCtrl->OnInquire( lParam1, (CPLINFO*)lParam2 );

    case CPL_SELECT:
        return 1; //Message no longer used

    case CPL_STOP:
        return pCtrl->OnStop(lParam1, lParam2);

	case CPL_STARTWPARMS:
		return pCtrl->OnDblclk(hwndCPl, lParam1, lParam2);

    default:
        break;
    }

    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Default command handlers

LONG CControlPanel::OnNewInquire(UINT uAppNum, NEWCPLINFO* pInfo) 
{
    // Fill in the data
    pInfo->dwSize = sizeof(NEWCPLINFO); // important
    pInfo->dwFlags = 0;
    pInfo->dwHelpContext = 0;
    pInfo->lData = 0;

	HINSTANCE h = AfxGetResourceHandle();
    pInfo->hIcon = ::LoadIcon(h, MAKEINTRESOURCE(IDI_ICON));
	LoadString(h, IDS_CPLNAME, pInfo->szName, sizeof(pInfo->szName) / sizeof(TCHAR));
	LoadString(h, IDS_CPLINFOSTRING, pInfo->szInfo, sizeof(pInfo->szInfo) / sizeof(TCHAR));

    strcpy(pInfo->szHelpFile, "");
    return 0;
}

LONG CControlPanel::OnInquire(UINT uAppNum, CPLINFO* pInfo)
{
	pInfo->idIcon = IDI_ICON;
	pInfo->idName = IDS_CPLNAME;
	pInfo->idInfo = IDS_CPLINFOSTRING;
	pInfo->lData = 0;

	return 0;
}

LONG CControlPanel::OnDblclk(HWND hwndCPl, UINT uAppNum, LONG lData)
{
	CPropPage1 page1;
	CPropPage2 page2;
	
	CCplPropSheet sheet( IDS_PSHEETTITLE );

	sheet.AddPage( &page1 );
	sheet.AddPage( &page2 );
	
	sheet.DoModal( );

	return 0;
}

LONG CControlPanel::OnExit()
{
    return 0; // OK
}

LONG CControlPanel::OnGetCount()
{
    return 1; // only one applet
}

LONG CControlPanel::OnInit()
{
    return 1; // OK
}

LONG CControlPanel::OnStop(UINT uAppNum, LONG lData) 
{
    return 1; // not handled
}



