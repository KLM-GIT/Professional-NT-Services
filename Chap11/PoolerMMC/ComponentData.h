// ComponentData.h : Declaration of the CComponentData

#ifndef __COMPONENTDATA_H_
#define __COMPONENTDATA_H_

#include "resource.h"       // main symbols

class CEntry;
/////////////////////////////////////////////////////////////////////////////
// CComponentData
class ATL_NO_VTABLE CComponentData : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CComponentData, &CLSID_ComponentData>,
	public IComponentData
{
public:
	CComponentData()
	{
		m_pConsoleNameSpace = NULL;
		m_pContextMenuProvider = NULL;
		m_pExtendContextMenu = NULL;
		m_pRoot = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMPONENTDATA)

BEGIN_COM_MAP(CComponentData)
	COM_INTERFACE_ENTRY(IComponentData)
END_COM_MAP()

// IComponentData
public:
	STDMETHOD(CompareObjects)(LPDATAOBJECT lpDataObjectA, LPDATAOBJECT lpDataObjectB);
	STDMETHOD(GetDisplayInfo)(LPSCOPEDATAITEM pItem);
	STDMETHOD(QueryDataObject)(long cookie, DATA_OBJECT_TYPES type, LPDATAOBJECT * ppDataObject);
	STDMETHOD(Notify)(LPDATAOBJECT lpDataObject, MMC_NOTIFY_TYPE event, long arg, long param);
	STDMETHOD(CreateComponent)(LPCOMPONENT * ppComponent);
	STDMETHOD(Initialize)(LPUNKNOWN pUnknown);
	STDMETHOD(Destroy)();

private:
	IConsoleNameSpace* m_pConsoleNameSpace;
	IContextMenuProvider* m_pContextMenuProvider;
	IExtendContextMenu* m_pExtendContextMenu;
	CEntry* m_pRoot;
};

#endif //__COMPONENTDATA_H_
