// ExtendContextMenu.h : Declaration of the CExtendContextMenu

#ifndef __EXTENDCONTEXTMENU_H_
#define __EXTENDCONTEXTMENU_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExtendContextMenu
class ATL_NO_VTABLE CExtendContextMenu : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExtendContextMenu, &CLSID_ExtendContextMenu>,
	public IExtendContextMenu,
	public IPoolerMMCExtendContextMenu
{
private:
	IConsoleNameSpace *m_pConsoleNameSpace;
	void DoTheNew (LPDATAOBJECT pDataObject);

public:
	CExtendContextMenu()
	{
		m_pConsoleNameSpace = NULL;
	}
	~CExtendContextMenu();

DECLARE_REGISTRY_RESOURCEID(IDR_EXTENDCONTEXTMENU)

BEGIN_COM_MAP(CExtendContextMenu)
	COM_INTERFACE_ENTRY(IExtendContextMenu)
	COM_INTERFACE_ENTRY(IPoolerMMCExtendContextMenu)
END_COM_MAP()

// IExtendContextMenu
public:
	STDMETHOD(AddMenuItems)(LPDATAOBJECT pDataObject, LPCONTEXTMENUCALLBACK piCallback, long * pInsertionAllowed);
	STDMETHOD(Command)(long lCommandID, LPDATAOBJECT pDataObject);

public:
	STDMETHOD(put_Console)(/*[in]*/ LPUNKNOWN  pi);

};

#endif //__EXTENDCONTEXTMENU_H_
