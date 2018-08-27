#if !defined(AFX_PROPPAGE2_H__B152D433_F94C_11D1_846B_0020AF05ED45__INCLUDED_)
#define AFX_PROPPAGE2_H__B152D433_F94C_11D1_846B_0020AF05ED45__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropPage2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPage2 dialog

class CPropPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropPage2)

// Construction
public:
	void ReadRegistry( );
	CPropPage2();
	~CPropPage2();
	BOOL CPropPage2::OnInitDialog();

// Dialog Data
	//{{AFX_DATA(CPropPage2)
	enum { IDD = IDD_PAGE_PARAMS };
	DWORD	m_dwDeadPoll;
	DWORD	m_dwHandleLife;
	DWORD	m_dwInitSessions;
	DWORD	m_dwMaxSessions;
	DWORD	m_dwMaxWait;
	DWORD	m_dwReallocMin;
	DWORD	m_dwReallocPoll;
	DWORD	m_dwReallocSize;
	DWORD	m_dwWaitToClose;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropPage2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGE2_H__B152D433_F94C_11D1_846B_0020AF05ED45__INCLUDED_)
