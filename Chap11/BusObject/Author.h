// Author.h : Declaration of the CAuthor

#ifndef __AUTHOR_H_
#define __AUTHOR_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAuthor
class ATL_NO_VTABLE CAuthor : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CAuthor, &CLSID_Author>,
	public IDispatchImpl<IAuthor, &IID_IAuthor, &LIBID_BUSOBJECTLib>
{
public:
	CAuthor()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_AUTHOR)

BEGIN_COM_MAP(CAuthor)
	COM_INTERFACE_ENTRY(IAuthor)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IAuthor
public:
	STDMETHOD(GetAuthorList)(/*[in]*/ long nContract, /*[out, retval]*/ VARIANT* pDataArray);
};

#endif //__AUTHOR_H_
