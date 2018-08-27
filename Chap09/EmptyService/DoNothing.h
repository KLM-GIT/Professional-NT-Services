// DoNothing.h : Declaration of the CDoNothing

#ifndef __DONOTHING_H_
#define __DONOTHING_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDoNothing
class ATL_NO_VTABLE CDoNothing : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CDoNothing, &CLSID_DoNothing>,
	public IDispatchImpl<IDoNothing, &IID_IDoNothing, &LIBID_EMPTYSERVICELib>
{
public:
	CDoNothing()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DONOTHING)

BEGIN_COM_MAP(CDoNothing)
	COM_INTERFACE_ENTRY(IDoNothing)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IDoNothing
public:
};

#endif //__DONOTHING_H_
