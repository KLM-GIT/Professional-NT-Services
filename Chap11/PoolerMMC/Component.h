// Component.h : Declaration of the CComponent

#ifndef __COMPONENT_H_
#define __COMPONENT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CComponent
class ATL_NO_VTABLE CComponent : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CComponent, &CLSID_Component>,
	public IComponent
{
private:
	IConsole* m_pConsole;
	void Refresh( LPDATAOBJECT lpDataObject );
	LPRESULTDATA m_pResultData;
	LPCONSOLEVERB m_pConsoleVerb;
	LPHEADERCTRL m_pHeaderCtrl;
	LPIMAGELIST m_pImageResult;
	HBITMAP m_hBmp16;
	HBITMAP m_hBmp32;

	void Show (LPDATAOBJECT lpDataObject);
	void AddImages (LPDATAOBJECT lpDataObject);
	void Select (LPDATAOBJECT lpDataObject, long arg);

public:
	CComponent()
	{
		m_pResultData = NULL;
		m_pConsoleVerb = NULL;
		m_pHeaderCtrl = NULL;
		m_pImageResult = NULL;
		m_hBmp16 = NULL;
		m_hBmp32 = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMPONENT)

BEGIN_COM_MAP(CComponent)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IComponent
public:
	STDMETHOD(Initialize)(LPCONSOLE lpConsole);
	STDMETHOD(Notify)(LPDATAOBJECT lpDataObject, MMC_NOTIFY_TYPE event, long arg, long param);
	STDMETHOD(Destroy)(long cookie);
	STDMETHOD(GetResultViewType)(long cookie,  LPOLESTR* ppViewType, long* pViewOptions);
	STDMETHOD(QueryDataObject)(long cookie, DATA_OBJECT_TYPES type, LPDATAOBJECT* ppDataObject);
	STDMETHOD(GetDisplayInfo)(RESULTDATAITEM*  pResultDataItem);
	STDMETHOD(CompareObjects)(LPDATAOBJECT lpDataObjectA, LPDATAOBJECT lpDataObjectB);

};

#endif //__COMPONENT_H_
