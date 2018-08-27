// PoolAdminData.h : Declaration of the CPoolAdminData

#ifndef __POOLADMINDATA_H_
#define __POOLADMINDATA_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPoolAdminData
class ATL_NO_VTABLE CPoolAdminData : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CPoolAdminData, &CLSID_PoolAdminData>,
	public IDispatchImpl<IPoolAdminData, &IID_IPoolAdminData, &LIBID_BUSOBJECTLib>
{
public:
	CPoolAdminData()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_POOLADMINDATA)

BEGIN_COM_MAP(CPoolAdminData)
	COM_INTERFACE_ENTRY(IPoolAdminData)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IPoolAdminData
public:
	STDMETHOD(GetUsageStats)(/*[out]*/ long* pConnections, /*[out]*/ long* pRemaining);
	STDMETHOD(GetPoolInfo)(/*[out, retval]*/ VARIANT* paVariant);
};

#endif //__POOLADMINDATA_H_
