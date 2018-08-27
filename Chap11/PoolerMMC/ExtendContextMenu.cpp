// ExtendContextMenu.cpp : Implementation of CExtendContextMenu
#include "stdafx.h"
#include "PoolerMMC.h"
#include "ExtendContextMenu.h"
#include "entry.h"
#include "computer.h"


/////////////////////////////////////////////////////////////////////////////
// CExtendContextMenu

CExtendContextMenu::~CExtendContextMenu()
{
	m_pConsoleNameSpace->Release();
}

STDMETHODIMP CExtendContextMenu::AddMenuItems (LPDATAOBJECT pDataObject, LPCONTEXTMENUCALLBACK pCallback, long * pInsertionAllowed)
{
	IPoolerMMCDataObject *pPoolObject;
	pDataObject->QueryInterface (IID_IPoolerMMCDataObject, (void **) &pPoolObject);

	long cookie;
	pPoolObject->get_Cookie (&cookie);
	pPoolObject->Release ();

	LPENTRY lpEntry = (LPENTRY) cookie;

	if (!lpEntry)
		return S_OK;

	int tier = lpEntry->GetTier ();

	CONTEXTMENUITEM cmi;
	memset (&cmi, 0, sizeof (CONTEXTMENUITEM));

	if ((*pInsertionAllowed & CCM_INSERTIONALLOWED_NEW) && (tier == -1))
	{
		cmi.strName = L"Computer";
		cmi.lCommandID = 0x1;
		cmi.lInsertionPointID = CCM_INSERTIONPOINTID_PRIMARY_NEW;

		pCallback->AddItem (&cmi);
	}

	return S_OK;
}

STDMETHODIMP CExtendContextMenu::Command (long lCommandID, LPDATAOBJECT pDataObject)
{
	switch (lCommandID)
	{
	case 0x01:
		DoTheNew (pDataObject);
		break;
	}

	return S_OK;
}

void CExtendContextMenu::DoTheNew (LPDATAOBJECT pDataObject)
{
	if (!m_pConsoleNameSpace)
		return;

	CComputer dlg;
	if (dlg.DoModal () == IDCANCEL)
		return;

	long cookie;
	IPoolerMMCDataObject *pPoolObject;
	pDataObject->QueryInterface (IID_IPoolerMMCDataObject, (void **) &pPoolObject);
	pPoolObject->get_Cookie (&cookie);
	pPoolObject->Release ();


	LPENTRY lpEntry = (LPENTRY) cookie;
	LPENTRY lpSubEntry = lpEntry->AddSubEntry( dlg.m_szComputer );

	SCOPEDATAITEM sdi;

	memset (&sdi, 0, sizeof (SCOPEDATAITEM));

	sdi.mask = SDI_STR|SDI_PARAM|SDI_IMAGE|SDI_OPENIMAGE|SDI_PARENT;
	sdi.lParam = (LPARAM) lpSubEntry;
	sdi.relativeID = lpEntry->GetScope();
	sdi.displayname = MMC_CALLBACK;

	sdi.nImage = 0;
	sdi.nOpenImage = 1;

	m_pConsoleNameSpace->InsertItem (&sdi);

	lpSubEntry->SetScope (sdi.ID);
}

STDMETHODIMP CExtendContextMenu::put_Console(LPUNKNOWN  pi)
{
	pi->QueryInterface (IID_IConsoleNameSpace, (void **) &m_pConsoleNameSpace);

	return S_OK;
}

