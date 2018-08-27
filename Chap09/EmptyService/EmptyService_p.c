/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 3.01.75 */
/* at Mon May 18 09:32:17 1998
 */
/* Compiler settings for EmptyService.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY

#include "rpcproxy.h"
#include "EmptyService.h"

#define TYPE_FORMAT_STRING_SIZE   1                                 
#define PROC_FORMAT_STRING_SIZE   1                                 

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDoSomething, ver. 0.0,
   GUID={0xD285D14E,0xED84,0x11D1,{0x84,0x66,0x00,0x20,0xAF,0x05,0xED,0x45}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")
CINTERFACE_PROXY_VTABLE(7) _IDoSomethingProxyVtbl = 
{
    0,
    &IID_IDoSomething,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IDoSomething_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IDoSomethingStubVtbl =
{
    &IID_IDoSomething,
    0,
    7,
    &IDoSomething_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IDoNothing, ver. 0.0,
   GUID={0xD285D151,0xED84,0x11D1,{0x84,0x66,0x00,0x20,0xAF,0x05,0xED,0x45}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    0, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x301004b, /* MIDL Version 3.1.75 */
    0,
    0,
    0,  /* Reserved1 */
    0,  /* Reserved2 */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

CINTERFACE_PROXY_VTABLE(7) _IDoNothingProxyVtbl = 
{
    0,
    &IID_IDoNothing,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IDoNothing_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IDoNothingStubVtbl =
{
    &IID_IDoNothing,
    0,
    7,
    &IDoNothing_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

#pragma data_seg(".rdata")

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {

			0x0
        }
    };

const CInterfaceProxyVtbl * _EmptyService_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IDoSomethingProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IDoNothingProxyVtbl,
    0
};

const CInterfaceStubVtbl * _EmptyService_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IDoSomethingStubVtbl,
    ( CInterfaceStubVtbl *) &_IDoNothingStubVtbl,
    0
};

PCInterfaceName const _EmptyService_InterfaceNamesList[] = 
{
    "IDoSomething",
    "IDoNothing",
    0
};

const IID *  _EmptyService_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _EmptyService_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _EmptyService, pIID, n)

int __stdcall _EmptyService_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _EmptyService, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _EmptyService, 2, *pIndex )
    
}

const ExtendedProxyFileInfo EmptyService_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _EmptyService_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _EmptyService_StubVtblList,
    (const PCInterfaceName * ) & _EmptyService_InterfaceNamesList,
    (const IID ** ) & _EmptyService_BaseIIDList,
    & _EmptyService_IID_Lookup, 
    2,
    2
};
