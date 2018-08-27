// Computer.cpp : Implementation of CComputer
#include "stdafx.h"
#include "Computer.h"

/////////////////////////////////////////////////////////////////////////////
// CComputer

CComputer::CComputer()
{
}

CComputer::~CComputer()
{
}

LRESULT CComputer::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 1;  // Let the system set the focus
}

LRESULT CComputer::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	*(WORD *) m_szComputer = sizeof (m_szComputer) - 1;

	WORD cbText = (WORD) SendDlgItemMessage (IDC_COMPNAME, EM_GETLINE, 
					0, (LPARAM) m_szComputer);

	m_szComputer[cbText] = 0;
	EndDialog(wID);
	return 0;
}

LRESULT CComputer::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

