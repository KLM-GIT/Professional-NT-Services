// BusObjCpl.h : main header file for the BUSOBJCPL DLL
//

#if !defined(AFX_BUSOBJCPL_H__B152D428_F94C_11D1_846B_0020AF05ED45__INCLUDED_)
#define AFX_BUSOBJCPL_H__B152D428_F94C_11D1_846B_0020AF05ED45__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "cpanel.h"
/////////////////////////////////////////////////////////////////////////////
// CBusObjCplApp
// See BusObjCpl.cpp for the implementation of this class
//

class CBusObjCplApp : public CWinApp
{
public:
	CBusObjCplApp();
	CControlPanel m_panel;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBusObjCplApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CBusObjCplApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUSOBJCPL_H__B152D428_F94C_11D1_846B_0020AF05ED45__INCLUDED_)
