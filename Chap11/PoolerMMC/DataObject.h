// DataObject.h : Declaration of the CDataObject

#ifndef __DATAOBJECT_H_
#define __DATAOBJECT_H_

#include "resource.h"       // main symbols

// {A2AF0D5A-F7E6-11d1-846A-0020AF05ED45}
static const UUID UUIDRootNode = 
{ 0xa2af0d5a, 0xf7e6, 0x11d1, { 0x84, 0x6a, 0x0, 0x20, 0xaf, 0x5, 0xed, 0x45 } };

// {A2AF0D5B-F7E6-11d1-846A-0020AF05ED45}
static const UUID UUIDCompNode = 
{ 0xa2af0d5b, 0xf7e6, 0x11d1, { 0x84, 0x6a, 0x0, 0x20, 0xaf, 0x5, 0xed, 0x45 } };

// {A2AF0D5C-F7E6-11d1-846A-0020AF05ED45}
static const UUID UUIDArrayNode = 
{ 0xa2af0d5c, 0xf7e6, 0x11d1, { 0x84, 0x6a, 0x0, 0x20, 0xaf, 0x5, 0xed, 0x45 } };

/////////////////////////////////////////////////////////////////////////////
// CDataObject
class ATL_NO_VTABLE CDataObject : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDataObject, &CLSID_DataObject>,
	public IDataObject,
	public IPoolerMMCDataObject
{

public:
	CDataObject()
	{
		s_DisplayName = RegisterClipboardFormat(CCF_DISPLAY_NAME);
		s_NodeType = RegisterClipboardFormat(CCF_NODETYPE);
		s_SnapinClsid = RegisterClipboardFormat(CCF_SNAPIN_CLASSID);
		m_cookie = 0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DATAOBJECT)

BEGIN_COM_MAP(CDataObject)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IPoolerMMCDataObject)
END_COM_MAP()

// IDataObject
private:
	static UINT s_DisplayName;
	static UINT s_NodeType;
	static UINT s_SnapinClsid;

	long m_cookie;

public:
	STDMETHOD(GetDataHere)(FORMATETC *pformatetc, STGMEDIUM *pmedium);
	STDMETHOD(GetData)(LPFORMATETC lpFormatetcIn, LPSTGMEDIUM lpMedium);
	STDMETHOD(EnumFormatEtc)(DWORD dwDirection, LPENUMFORMATETC* ppEnumFormatEtc);
	STDMETHOD(QueryGetData)(LPFORMATETC lpFormatetc);
	STDMETHOD(GetCanonicalFormatEtc)(LPFORMATETC lpFormatetcIn, LPFORMATETC lpFormatetcOut);
	STDMETHOD(SetData)(LPFORMATETC lpFormatetc, LPSTGMEDIUM lpMedium, BOOL bRelease);
	STDMETHOD(DAdvise)(LPFORMATETC lpFormatetc, DWORD advf, LPADVISESINK pAdvSink, LPDWORD pdwConnection);
	STDMETHOD(DUnadvise)(DWORD dwConnection);
	STDMETHOD(EnumDAdvise)(LPENUMSTATDATA* ppEnumAdvise);

public:
	STDMETHOD(get_Cookie)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Cookie)(/*[in]*/ long newval);

};

#endif //__DATAOBJECT_H_
