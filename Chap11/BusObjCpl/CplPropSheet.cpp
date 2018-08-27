// CplPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "BusObjCpl.h"
#include "CplPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCplPropSheet

IMPLEMENT_DYNAMIC(CCplPropSheet, CPropertySheet)

CCplPropSheet::CCplPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CCplPropSheet::CCplPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CCplPropSheet::~CCplPropSheet()
{
}


BEGIN_MESSAGE_MAP(CCplPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CCplPropSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCplPropSheet message handlers
