#if !defined(AFX_PROPPAGE1_H__19D5D5FF_D934_11D1_A200_0004ACB58CFB__INCLUDED_)
#define AFX_PROPPAGE1_H__19D5D5FF_D934_11D1_A200_0004ACB58CFB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropPage1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPage1 dialog

class CPropPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropPage1)

// Construction
public:
	CPropPage1();
	~CPropPage1();

// Dialog Data
	//{{AFX_DATA(CPropPage1)
	enum { IDD = IDD_PAGE_SERVER };
	CString	m_szPassword;
	CString	m_szServer;
	CString	m_szUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropPage1)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	BOOL OnInitDialog();
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropPage1)
	afx_msg void OnChangeEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void ReadRegistry();
private:
	void SendControlMessage();
	void UpdateRegistry();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGE1_H__19D5D5FF_D934_11D1_A200_0004ACB58CFB__INCLUDED_)
