// ComponentData.cpp : Implementation of CComponentData
#include "stdafx.h"
#include "PoolerMMC.h"
#include "ComponentData.h"
#include "dataobject.h"
#include "component.h"
#include "ExtendContextMenu.h"
#include "entry.h"

/////////////////////////////////////////////////////////////////////////////
// CComponentData

STDMETHODIMP CComponentData::Initialize (LPUNKNOWN pUnknown)
{
	m_pRoot = new CEntry ();

	pUnknown->QueryInterface (IID_IConsoleNameSpace, (void**)(&m_pConsoleNameSpace));
	pUnknown->QueryInterface (IID_IContextMenuProvider, (void**)(&m_pContextMenuProvider));

	CComObject<CExtendContextMenu> *pExtendContextMenu;
	CComObject<CExtendContextMenu>::CreateInstance(&pExtendContextMenu);

	pExtendContextMenu->QueryInterface (IID_IExtendContextMenu, (void **) &m_pExtendContextMenu);

	IPoolerMMCExtendContextMenu *pMyExtendContextMenu;
	pExtendContextMenu->QueryInterface (IID_IPoolerMMCExtendContextMenu, (void **) &pMyExtendContextMenu);
	pMyExtendContextMenu->put_Console (pUnknown);
	pMyExtendContextMenu->Release ();

	LPCONSOLE lpConsole;
	pUnknown->QueryInterface (IID_IConsole, (void**)(&lpConsole));

	LPIMAGELIST lpImageScope;
	lpConsole->QueryScopeImageList (&lpImageScope);

	HINSTANCE hInst = _Module.GetModuleInstance();
	HBITMAP hBmp16 = LoadBitmap (hInst, MAKEINTRESOURCE (IDB_BITMAP1));
	HBITMAP hBmp32 = LoadBitmap (hInst, MAKEINTRESOURCE (IDB_BITMAP2));

	lpImageScope->ImageListSetStrip ((LONG *) hBmp16,
									 (LONG *) hBmp32, 0, RGB (0,255,0));

	lpConsole->Release(); //

	return S_OK;
}

STDMETHODIMP CComponentData::GetDisplayInfo (LPSCOPEDATAITEM pItem)
{
	LPENTRY lpEntry = (LPENTRY) pItem->lParam;
	pItem->displayname = lpEntry->GetName ();
	return S_OK;
}

STDMETHODIMP CComponentData::QueryDataObject (long cookie, DATA_OBJECT_TYPES type, LPDATAOBJECT * ppDataObject)
{
	CComObject<CDataObject>* pDataObject;
	CComObject<CDataObject>::CreateInstance(&pDataObject);

	IPoolerMMCDataObject *pPoolObject;
	pDataObject->QueryInterface (IID_IPoolerMMCDataObject, (void **) &pPoolObject);

	if (cookie)
		pPoolObject->put_Cookie (cookie);
	else
		pPoolObject->put_Cookie ((long) m_pRoot);

	*ppDataObject = pDataObject;

	if (m_pContextMenuProvider)
		m_pContextMenuProvider->AddPrimaryExtensionItems (m_pExtendContextMenu, pDataObject);

	return S_OK;
}

STDMETHODIMP CComponentData::Notify (LPDATAOBJECT lpDataObject, 
									 MMC_NOTIFY_TYPE event, long arg, long param)
{
	if (event != MMCN_EXPAND)
		return S_OK;

	SCOPEDATAITEM sdi;
	memset (&sdi, 0, sizeof (SCOPEDATAITEM));
	sdi.mask = SDI_STR|SDI_PARAM|SDI_IMAGE|SDI_OPENIMAGE|SDI_PARENT;
	sdi.relativeID = (HSCOPEITEM) param;
	sdi.displayname = MMC_CALLBACK;

	IPoolerMMCDataObject *pPoolObject;
	lpDataObject->QueryInterface (IID_IPoolerMMCDataObject, (void **) &pPoolObject);

	long cookie;
	pPoolObject->get_Cookie (&cookie);
	pPoolObject->Release ();

	LPENTRY lpEntry;

	if (cookie)
		lpEntry = (LPENTRY) cookie;
	else
		lpEntry = m_pRoot;

	lpEntry->SetScope((HSCOPEITEM) param);

	//Only add to scope pane at computer level, not connection level
	if( lpEntry->GetTier() == -1 )
	{
		int count = lpEntry->GetSubCount ();

		for (int pos = 0; pos < count; pos++)
		{
			LPENTRY lpSubItem = lpEntry->GetSubEntry (pos);
			sdi.lParam = (LPARAM) lpSubItem;
			sdi.nImage = 0;
			sdi.nOpenImage = 1;

			m_pConsoleNameSpace->InsertItem (&sdi);
		}
	}
	return S_OK;
}


STDMETHODIMP CComponentData::CreateComponent (LPCOMPONENT * ppComponent)
{
	CComObject<CComponent>* pComponent;
	CComObject<CComponent>::CreateInstance(&pComponent);

	*ppComponent = pComponent;

	return S_OK;
}

//Compulsory methods
STDMETHODIMP CComponentData::Destroy ()
{
	// Free interfaces   
	m_pContextMenuProvider->Release(); 
	m_pContextMenuProvider = NULL;    

	m_pConsoleNameSpace->Release(); 
	m_pConsoleNameSpace = NULL;    

	delete m_pRoot;

	return S_OK;
}

STDMETHODIMP CComponentData::CompareObjects (LPDATAOBJECT lpDataObjectA, LPDATAOBJECT lpDataObjectB)
{
	return E_NOTIMPL;
}

