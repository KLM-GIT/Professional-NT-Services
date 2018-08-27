/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Mon May 18 09:32:17 1998
 */
/* Compiler settings for EmptyService.idl:
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

#ifndef __EmptyService_h__
#define __EmptyService_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDoSomething_FWD_DEFINED__
#define __IDoSomething_FWD_DEFINED__
typedef interface IDoSomething IDoSomething;
#endif 	/* __IDoSomething_FWD_DEFINED__ */


#ifndef __IDoNothing_FWD_DEFINED__
#define __IDoNothing_FWD_DEFINED__
typedef interface IDoNothing IDoNothing;
#endif 	/* __IDoNothing_FWD_DEFINED__ */


#ifndef __DoSomething_FWD_DEFINED__
#define __DoSomething_FWD_DEFINED__

#ifdef __cplusplus
typedef class DoSomething DoSomething;
#else
typedef struct DoSomething DoSomething;
#endif /* __cplusplus */

#endif 	/* __DoSomething_FWD_DEFINED__ */


#ifndef __DoNothing_FWD_DEFINED__
#define __DoNothing_FWD_DEFINED__

#ifdef __cplusplus
typedef class DoNothing DoNothing;
#else
typedef struct DoNothing DoNothing;
#endif /* __cplusplus */

#endif 	/* __DoNothing_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IDoSomething_INTERFACE_DEFINED__
#define __IDoSomething_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDoSomething
 * at Mon May 18 09:32:17 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IDoSomething;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("D285D14E-ED84-11D1-8466-0020AF05ED45")
    IDoSomething : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IDoSomethingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDoSomething __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDoSomething __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDoSomething __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDoSomething __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDoSomething __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDoSomething __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDoSomething __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IDoSomethingVtbl;

    interface IDoSomething
    {
        CONST_VTBL struct IDoSomethingVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDoSomething_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDoSomething_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDoSomething_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDoSomething_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDoSomething_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDoSomething_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDoSomething_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDoSomething_INTERFACE_DEFINED__ */


#ifndef __IDoNothing_INTERFACE_DEFINED__
#define __IDoNothing_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDoNothing
 * at Mon May 18 09:32:17 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IDoNothing;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("D285D151-ED84-11D1-8466-0020AF05ED45")
    IDoNothing : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IDoNothingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDoNothing __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDoNothing __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDoNothing __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDoNothing __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDoNothing __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDoNothing __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDoNothing __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IDoNothingVtbl;

    interface IDoNothing
    {
        CONST_VTBL struct IDoNothingVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDoNothing_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDoNothing_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDoNothing_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDoNothing_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDoNothing_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDoNothing_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDoNothing_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDoNothing_INTERFACE_DEFINED__ */



#ifndef __EMPTYSERVICELib_LIBRARY_DEFINED__
#define __EMPTYSERVICELib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: EMPTYSERVICELib
 * at Mon May 18 09:32:17 1998
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_EMPTYSERVICELib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_DoSomething;

class DECLSPEC_UUID("D285D14F-ED84-11D1-8466-0020AF05ED45")
DoSomething;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_DoNothing;

class DECLSPEC_UUID("D285D152-ED84-11D1-8466-0020AF05ED45")
DoNothing;
#endif
#endif /* __EMPTYSERVICELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
