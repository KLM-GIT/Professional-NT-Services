// DoSomething.h : Declaration of the CDoSomething

#ifndef __DOSOMETHING_H_
#define __DOSOMETHING_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDoSomething
class ATL_NO_VTABLE CDoSomething : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDoSomething, &CLSID_DoSomething>,
	public IDispatchImpl<IDoSomething, &IID_IDoSomething, &LIBID_EMPTYSERVICELib>
{
public:
	CDoSomething()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DOSOMETHING)

BEGIN_COM_MAP(CDoSomething)
	COM_INTERFACE_ENTRY(IDoSomething)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IDoSomething
public:
};

#endif //__DOSOMETHING_H_
