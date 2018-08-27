#if !defined(AFX_CPLPROPSHEET_H__19D5D600_D934_11D1_A200_0004ACB58CFB__INCLUDED_)
#define AFX_CPLPROPSHEET_H__19D5D600_D934_11D1_A200_0004ACB58CFB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CplPropSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCplPropSheet

class CCplPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CCplPropSheet)

// Construction
public:
	CCplPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCplPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCplPropSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCplPropSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCplPropSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPLPROPSHEET_H__19D5D600_D934_11D1_A200_0004ACB58CFB__INCLUDED_)
