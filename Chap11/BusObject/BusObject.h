/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Tue Jun 30 05:48:16 1998
 */
/* Compiler settings for BusObject.idl:
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

#ifndef __BusObject_h__
#define __BusObject_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAuthor_FWD_DEFINED__
#define __IAuthor_FWD_DEFINED__
typedef interface IAuthor IAuthor;
#endif 	/* __IAuthor_FWD_DEFINED__ */


#ifndef __IPoolAdminData_FWD_DEFINED__
#define __IPoolAdminData_FWD_DEFINED__
typedef interface IPoolAdminData IPoolAdminData;
#endif 	/* __IPoolAdminData_FWD_DEFINED__ */


#ifndef __Author_FWD_DEFINED__
#define __Author_FWD_DEFINED__

#ifdef __cplusplus
typedef class Author Author;
#else
typedef struct Author Author;
#endif /* __cplusplus */

#endif 	/* __Author_FWD_DEFINED__ */


#ifndef __PoolAdminData_FWD_DEFINED__
#define __PoolAdminData_FWD_DEFINED__

#ifdef __cplusplus
typedef class PoolAdminData PoolAdminData;
#else
typedef struct PoolAdminData PoolAdminData;
#endif /* __cplusplus */

#endif 	/* __PoolAdminData_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IAuthor_INTERFACE_DEFINED__
#define __IAuthor_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAuthor
 * at Tue Jun 30 05:48:16 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAuthor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("D0B92D6B-F0DF-11D1-8466-0020AF05ED45")
    IAuthor : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAuthorList( 
            /* [in] */ long nContract,
            /* [retval][out] */ VARIANT __RPC_FAR *pDataArray) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAuthorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAuthor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAuthor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAuthor __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAuthor __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAuthor __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAuthor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAuthor __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAuthorList )( 
            IAuthor __RPC_FAR * This,
            /* [in] */ long nContract,
            /* [retval][out] */ VARIANT __RPC_FAR *pDataArray);
        
        END_INTERFACE
    } IAuthorVtbl;

    interface IAuthor
    {
        CONST_VTBL struct IAuthorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAuthor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAuthor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAuthor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAuthor_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAuthor_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAuthor_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAuthor_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAuthor_GetAuthorList(This,nContract,pDataArray)	\
    (This)->lpVtbl -> GetAuthorList(This,nContract,pDataArray)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuthor_GetAuthorList_Proxy( 
    IAuthor __RPC_FAR * This,
    /* [in] */ long nContract,
    /* [retval][out] */ VARIANT __RPC_FAR *pDataArray);


void __RPC_STUB IAuthor_GetAuthorList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAuthor_INTERFACE_DEFINED__ */


#ifndef __IPoolAdminData_INTERFACE_DEFINED__
#define __IPoolAdminData_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPoolAdminData
 * at Tue Jun 30 05:48:16 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IPoolAdminData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("91606953-0FD2-11D2-928B-0080C767BC99")
    IPoolAdminData : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPoolInfo( 
            /* [retval][out] */ VARIANT __RPC_FAR *paVariant) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUsageStats( 
            /* [out] */ long __RPC_FAR *pConnections,
            /* [out] */ long __RPC_FAR *pRemaining) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPoolAdminDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPoolAdminData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPoolAdminData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPoolAdminData __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPoolAdminData __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPoolAdminData __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPoolAdminData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPoolAdminData __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPoolInfo )( 
            IPoolAdminData __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *paVariant);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUsageStats )( 
            IPoolAdminData __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pConnections,
            /* [out] */ long __RPC_FAR *pRemaining);
        
        END_INTERFACE
    } IPoolAdminDataVtbl;

    interface IPoolAdminData
    {
        CONST_VTBL struct IPoolAdminDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoolAdminData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPoolAdminData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPoolAdminData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPoolAdminData_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPoolAdminData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPoolAdminData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPoolAdminData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPoolAdminData_GetPoolInfo(This,paVariant)	\
    (This)->lpVtbl -> GetPoolInfo(This,paVariant)

#define IPoolAdminData_GetUsageStats(This,pConnections,pRemaining)	\
    (This)->lpVtbl -> GetUsageStats(This,pConnections,pRemaining)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPoolAdminData_GetPoolInfo_Proxy( 
    IPoolAdminData __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *paVariant);


void __RPC_STUB IPoolAdminData_GetPoolInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPoolAdminData_GetUsageStats_Proxy( 
    IPoolAdminData __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pConnections,
    /* [out] */ long __RPC_FAR *pRemaining);


void __RPC_STUB IPoolAdminData_GetUsageStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPoolAdminData_INTERFACE_DEFINED__ */



#ifndef __BUSOBJECTLib_LIBRARY_DEFINED__
#define __BUSOBJECTLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: BUSOBJECTLib
 * at Tue Jun 30 05:48:16 1998
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_BUSOBJECTLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Author;

class DECLSPEC_UUID("D0B92D6C-F0DF-11D1-8466-0020AF05ED45")
Author;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_PoolAdminData;

class DECLSPEC_UUID("D2EA07E4-F887-11D1-846A-0020AF05ED45")
PoolAdminData;
#endif
#endif /* __BUSOBJECTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
