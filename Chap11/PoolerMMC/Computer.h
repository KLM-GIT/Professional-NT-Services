// Computer.h : Declaration of the CComputer

#ifndef __COMPUTER_H_
#define __COMPUTER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CComputer
class CComputer : 
	public CDialogImpl<CComputer>
{
public:
	CComputer();
	~CComputer();
	WCHAR m_szComputer[25];

	enum { IDD = IDD_COMPUTER };

BEGIN_MSG_MAP(CComputer)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif //__COMPUTER_H_
