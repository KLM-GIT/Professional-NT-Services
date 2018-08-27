// DataObject.cpp : Implementation of CDataObject
#include "stdafx.h"
#include "PoolerMMC.h"
#include "DataObject.h"
#include "entry.h"


/////////////////////////////////////////////////////////////////////////////
// CDataObject

UINT CDataObject::s_DisplayName = 0;
UINT CDataObject::s_NodeType = 0;
UINT CDataObject::s_SnapinClsid = 0;

//Extra interface methods
STDMETHODIMP CDataObject::get_Cookie(long * pVal)
{
	*pVal = m_cookie;

	return S_OK;
}

STDMETHODIMP CDataObject::put_Cookie(long newval)
{
	m_cookie = newval;

	return S_OK;
}

STDMETHODIMP CDataObject::GetDataHere (LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpMedium)
{
	IStream *pStream;
	CreateStreamOnHGlobal (lpMedium->hGlobal, FALSE, &pStream);

	CLIPFORMAT cf = lpFormatEtc->cfFormat;

	if (cf == s_DisplayName)
		pStream->Write (L"Pooler SnapIn", sizeof (L"Pooler SnapIn"), NULL);
	else if (cf == s_NodeType)
	{
		LPENTRY lpEntry = (LPENTRY) m_cookie;
		int tier = lpEntry->GetTier ();
		switch (tier)
		{
		case -1:
			pStream->Write (&UUIDRootNode, sizeof (UUID), NULL);
			break;

		case 0:
			pStream->Write (&UUIDCompNode, sizeof (UUID), NULL);
			break;

		case 1:
			pStream->Write (&UUIDArrayNode, sizeof (UUID), NULL);
			break;
		}
	}

	else if (cf == s_SnapinClsid)
		pStream->Write (&CLSID_ComponentData, sizeof(CLSID_ComponentData), NULL);

	pStream->Release ();

	return S_OK;
}


//All the NOTIMPLs
STDMETHODIMP CDataObject::GetData (LPFORMATETC lpFormatetcIn, LPSTGMEDIUM lpMedium)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDataObject::EnumFormatEtc (DWORD dwDirection, LPENUMFORMATETC* ppEnumFormatEtc)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDataObject::QueryGetData (LPFORMATETC lpFormatetc) 
{
	return E_NOTIMPL;
}

STDMETHODIMP CDataObject::GetCanonicalFormatEtc (LPFORMATETC lpFormatetcIn, LPFORMATETC lpFormatetcOut)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDataObject::SetData (LPFORMATETC lpFormatetc, LPSTGMEDIUM lpMedium, BOOL bRelease)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDataObject::DAdvise (LPFORMATETC lpFormatetc, DWORD advf, LPADVISESINK pAdvSink, LPDWORD pdwConnection)
{
	return E_NOTIMPL;
}
    
STDMETHODIMP CDataObject::DUnadvise (DWORD dwConnection)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDataObject::EnumDAdvise (LPENUMSTATDATA* ppEnumAdvise)
{
	return E_NOTIMPL;
}

