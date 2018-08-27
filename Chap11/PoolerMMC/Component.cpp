// Component.cpp : Implementation of CComponent
#include "stdafx.h"
#include "PoolerMMC.h"
#include "Component.h"
#include "entry.h"


/////////////////////////////////////////////////////////////////////////////
// CComponent

STDMETHODIMP CComponent::Initialize (LPCONSOLE lpConsole)
{
	lpConsole->QueryInterface (IID_IHeaderCtrl,
							   (void **) &m_pHeaderCtrl);

	m_pConsole = lpConsole;
	lpConsole->SetHeader (m_pHeaderCtrl);

	lpConsole->QueryInterface (IID_IResultData,
							   (void **) &m_pResultData);

	lpConsole->QueryConsoleVerb (&m_pConsoleVerb);
	lpConsole->QueryResultImageList (&m_pImageResult);

	HINSTANCE hInst = _Module.GetModuleInstance();
	m_hBmp16 = LoadBitmap (hInst, MAKEINTRESOURCE (IDB_BITMAP1));
	m_hBmp32 = LoadBitmap (hInst, MAKEINTRESOURCE (IDB_BITMAP2));

	return S_OK;
}

STDMETHODIMP CComponent::Notify (LPDATAOBJECT lpDataObject, MMC_NOTIFY_TYPE event, long arg, long param)
{
	switch (event)
	{
		case MMCN_ACTIVATE:
			break;
		case MMCN_DBLCLICK:
			break;
		case MMCN_COLUMN_CLICK:
			break;

		case MMCN_ADD_IMAGES:
			AddImages (lpDataObject);
			break;

		case MMCN_SELECT:
			Select (lpDataObject, arg);
			break;

		case MMCN_REFRESH:
			Refresh( lpDataObject );
			Show( lpDataObject );
			break;
		case MMCN_SHOW:
			Show (lpDataObject);
			break;
	}

	return S_OK;
}

STDMETHODIMP CComponent::GetResultViewType (long cookie,  LPOLESTR* ppViewType, long* pViewOptions)
{
	*pViewOptions = MMC_VIEW_OPTIONS_NONE;
	return S_FALSE;
}

STDMETHODIMP CComponent::GetDisplayInfo (RESULTDATAITEM*  pResultDataItem)
{
	LPENTRY lpEntry = (LPENTRY) pResultDataItem->lParam;

	if (!lpEntry)
		return E_FAIL;

	if (pResultDataItem->str)
		delete[] pResultDataItem->str;

	int nTier = lpEntry->GetTier ();

	switch (nTier)
	{
		//For computer level
		case 0:
			switch (pResultDataItem->nCol)
			{
				case 0:
					pResultDataItem->str = lpEntry->GetName ();
					pResultDataItem->nImage = 0;
					break;
				case 1:
					pResultDataItem->str = lpEntry->GetConnections();
					break;
				case 2:
					pResultDataItem->str = lpEntry->GetRemaining();
					break;
			}
			break;

		//For Connections
		case 1:
			switch (pResultDataItem->nCol)
			{
				case 0:
					pResultDataItem->str = lpEntry->GetName ();
					pResultDataItem->nImage = 2;
					break;

				case 1:
					pResultDataItem->str = lpEntry->GetPos ();
					break;

				case 2:
					pResultDataItem->str = lpEntry->GetHandle ();
					break;

				case 3:
					pResultDataItem->str = lpEntry->GetState ();
					break;
			}
			break;

		}

	return S_OK;
}

void CComponent::Select (LPDATAOBJECT lpDataObject, long arg)
{
	BOOL bScope = LOWORD (arg);
	BOOL bSelect  = HIWORD (arg);

	if (!bScope || !bSelect)
		return;

	IPoolerMMCDataObject *pPoolObject;
	lpDataObject->QueryInterface (IID_IPoolerMMCDataObject, (void **) &pPoolObject);

	long cookie;
	pPoolObject->get_Cookie (&cookie);
	pPoolObject->Release ();

	//Enable the refresh verb on all scope pane components
	if (cookie)
		m_pConsoleVerb->SetVerbState (MMC_VERB_REFRESH, ENABLED, TRUE);
}

void CComponent::Show (LPDATAOBJECT lpDataObject)
{
	long cookie;
	IPoolerMMCDataObject *pPoolObject;
	lpDataObject->QueryInterface (IID_IPoolerMMCDataObject, (void **) &pPoolObject);
	pPoolObject->get_Cookie (&cookie);
	pPoolObject->Release ();

	LPENTRY lpEntry = (LPENTRY) cookie;

	if (!lpEntry)
		return;

	int tier = lpEntry->GetTier ();

	switch (tier)
	{
		case -1:
			m_pHeaderCtrl->InsertColumn (0, L"Name", 0, 100);
			m_pHeaderCtrl->InsertColumn (1, L"Total Connections", 0, 100);
			m_pHeaderCtrl->InsertColumn (2, L"Remaining Connections", 0, 100);

			break;

		case 0:
			m_pHeaderCtrl->InsertColumn (0, L"Name", 0, 100);
			m_pHeaderCtrl->InsertColumn (1, L"Position", 0, 60);
			m_pHeaderCtrl->InsertColumn (2, L"Handle", 0, 100);
			m_pHeaderCtrl->InsertColumn (3, L"State", 0, 75);


			m_pResultData->DeleteAllRsltItems ();

			RESULTDATAITEM rdi;
			memset (&rdi, 0, sizeof (RESULTDATAITEM));

			rdi.mask =  RDI_STR | RDI_IMAGE | RDI_PARAM;
			rdi.nImage = 2;
			rdi.str = MMC_CALLBACK;

			int nSub = lpEntry->GetSubCount ();

			for (int sub = 0; sub < nSub; sub++)
			{
				LPENTRY lpSubItem = lpEntry->GetSubEntry (sub);
				rdi.lParam = (LPARAM) lpSubItem;

				m_pResultData->InsertItem (&rdi);
			}

			break;
	}
}

void CComponent::Refresh(LPDATAOBJECT lpDataObject)
{
	long cookie;
	IPoolerMMCDataObject *pPoolObject;
	lpDataObject->QueryInterface (IID_IPoolerMMCDataObject, (void **) &pPoolObject);
	pPoolObject->get_Cookie (&cookie);
	pPoolObject->Release ();

	LPENTRY lpEntry = (LPENTRY) cookie;

	lpEntry->RefreshSubEntries();
}

void CComponent::AddImages (LPDATAOBJECT lpDataObject)
{
	m_pImageResult->ImageListSetStrip ((LONG *) m_hBmp16,
									   (LONG *) m_hBmp32, 0, RGB (0,255,0));

}

STDMETHODIMP CComponent::Destroy (long cookie)
{
	m_pResultData->Release();
	m_pHeaderCtrl->Release();

	return S_OK;
}

///
//NOT IMPLS
//

STDMETHODIMP CComponent::CompareObjects (LPDATAOBJECT lpDataObjectA, LPDATAOBJECT lpDataObjectB)
{
	return E_NOTIMPL;
}

STDMETHODIMP CComponent::QueryDataObject (long cookie, DATA_OBJECT_TYPES type, LPDATAOBJECT* ppDataObject)
{
	return E_NOTIMPL;
}

