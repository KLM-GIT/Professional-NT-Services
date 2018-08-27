/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Tue Jun 30 06:08:13 1998
 */
/* Compiler settings for PoolerMMC.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __PoolerMMC_h__
#define __PoolerMMC_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPoolerMMCDataObject_FWD_DEFINED__
#define __IPoolerMMCDataObject_FWD_DEFINED__
typedef interface IPoolerMMCDataObject IPoolerMMCDataObject;
#endif 	/* __IPoolerMMCDataObject_FWD_DEFINED__ */


#ifndef __IPoolerMMCExtendContextMenu_FWD_DEFINED__
#define __IPoolerMMCExtendContextMenu_FWD_DEFINED__
typedef interface IPoolerMMCExtendContextMenu IPoolerMMCExtendContextMenu;
#endif 	/* __IPoolerMMCExtendContextMenu_FWD_DEFINED__ */


#ifndef __Component_FWD_DEFINED__
#define __Component_FWD_DEFINED__

#ifdef __cplusplus
typedef class Component Component;
#else
typedef struct Component Component;
#endif /* __cplusplus */

#endif 	/* __Component_FWD_DEFINED__ */


#ifndef __ComponentData_FWD_DEFINED__
#define __ComponentData_FWD_DEFINED__

#ifdef __cplusplus
typedef class ComponentData ComponentData;
#else
typedef struct ComponentData ComponentData;
#endif /* __cplusplus */

#endif 	/* __ComponentData_FWD_DEFINED__ */


#ifndef __DataObject_FWD_DEFINED__
#define __DataObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class DataObject DataObject;
#else
typedef struct DataObject DataObject;
#endif /* __cplusplus */

#endif 	/* __DataObject_FWD_DEFINED__ */


#ifndef __ExtendContextMenu_FWD_DEFINED__
#define __ExtendContextMenu_FWD_DEFINED__

#ifdef __cplusplus
typedef class ExtendContextMenu ExtendContextMenu;
#else
typedef struct ExtendContextMenu ExtendContextMenu;
#endif /* __cplusplus */

#endif 	/* __ExtendContextMenu_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "mmc.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IPoolerMMCDataObject_INTERFACE_DEFINED__
#define __IPoolerMMCDataObject_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPoolerMMCDataObject
 * at Tue Jun 30 06:08:13 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IPoolerMMCDataObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("A2AF0D58-F7E6-11d1-846A-0020AF05ED45")
    IPoolerMMCDataObject : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Cookie( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Cookie( 
            /* [in] */ long newval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPoolerMMCDataObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPoolerMMCDataObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPoolerMMCDataObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPoolerMMCDataObject __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cookie )( 
            IPoolerMMCDataObject __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Cookie )( 
            IPoolerMMCDataObject __RPC_FAR * This,
            /* [in] */ long newval);
        
        END_INTERFACE
    } IPoolerMMCDataObjectVtbl;

    interface IPoolerMMCDataObject
    {
        CONST_VTBL struct IPoolerMMCDataObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoolerMMCDataObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPoolerMMCDataObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPoolerMMCDataObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPoolerMMCDataObject_get_Cookie(This,pVal)	\
    (This)->lpVtbl -> get_Cookie(This,pVal)

#define IPoolerMMCDataObject_put_Cookie(This,newval)	\
    (This)->lpVtbl -> put_Cookie(This,newval)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPoolerMMCDataObject_get_Cookie_Proxy( 
    IPoolerMMCDataObject __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPoolerMMCDataObject_get_Cookie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPoolerMMCDataObject_put_Cookie_Proxy( 
    IPoolerMMCDataObject __RPC_FAR * This,
    /* [in] */ long newval);


void __RPC_STUB IPoolerMMCDataObject_put_Cookie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPoolerMMCDataObject_INTERFACE_DEFINED__ */


#ifndef __IPoolerMMCExtendContextMenu_INTERFACE_DEFINED__
#define __IPoolerMMCExtendContextMenu_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPoolerMMCExtendContextMenu
 * at Tue Jun 30 06:08:13 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IPoolerMMCExtendContextMenu;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("A2AF0D59-F7E6-11d1-846A-0020AF05ED45")
    IPoolerMMCExtendContextMenu : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Console( 
            /* [in] */ LPUNKNOWN pi) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPoolerMMCExtendContextMenuVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPoolerMMCExtendContextMenu __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPoolerMMCExtendContextMenu __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPoolerMMCExtendContextMenu __RPC_FAR * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Console )( 
            IPoolerMMCExtendContextMenu __RPC_FAR * This,
            /* [in] */ LPUNKNOWN pi);
        
        END_INTERFACE
    } IPoolerMMCExtendContextMenuVtbl;

    interface IPoolerMMCExtendContextMenu
    {
        CONST_VTBL struct IPoolerMMCExtendContextMenuVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoolerMMCExtendContextMenu_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPoolerMMCExtendContextMenu_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPoolerMMCExtendContextMenu_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPoolerMMCExtendContextMenu_put_Console(This,pi)	\
    (This)->lpVtbl -> put_Console(This,pi)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IPoolerMMCExtendContextMenu_put_Console_Proxy( 
    IPoolerMMCExtendContextMenu __RPC_FAR * This,
    /* [in] */ LPUNKNOWN pi);


void __RPC_STUB IPoolerMMCExtendContextMenu_put_Console_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPoolerMMCExtendContextMenu_INTERFACE_DEFINED__ */



#ifndef __POOLERMMCLib_LIBRARY_DEFINED__
#define __POOLERMMCLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: POOLERMMCLib
 * at Tue Jun 30 06:08:13 1998
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_POOLERMMCLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Component;

class DECLSPEC_UUID("C8FF6D19-F7C9-11D1-846A-0020AF05ED45")
Component;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_ComponentData;

class DECLSPEC_UUID("C8FF6D1B-F7C9-11D1-846A-0020AF05ED45")
ComponentData;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_DataObject;

class DECLSPEC_UUID("C8FF6D1D-F7C9-11D1-846A-0020AF05ED45")
DataObject;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_ExtendContextMenu;

class DECLSPEC_UUID("C8FF6D1F-F7C9-11D1-846A-0020AF05ED45")
ExtendContextMenu;
#endif
#endif /* __POOLERMMCLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
