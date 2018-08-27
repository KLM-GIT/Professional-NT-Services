/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 3.01.75 */
/* at Tue Jun 30 05:48:16 1998
 */
/* Compiler settings for BusObject.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY

#include "rpcproxy.h"
#include "BusObject.h"

#define TYPE_FORMAT_STRING_SIZE   995                               
#define PROC_FORMAT_STRING_SIZE   85                                

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


/* Object interface: IAuthor, ver. 0.0,
   GUID={0xD0B92D6B,0xF0DF,0x11D1,{0x84,0x66,0x00,0x20,0xAF,0x05,0xED,0x45}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAuthor_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short IAuthor_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_SERVER_INFO IAuthor_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IAuthor_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IAuthor_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IAuthor_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(8) _IAuthorProxyVtbl = 
{
    &IAuthor_ProxyInfo,
    &IID_IAuthor,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* IAuthor::GetAuthorList */
};


static const PRPC_STUB_FUNCTION IAuthor_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _IAuthorStubVtbl =
{
    &IID_IAuthor,
    &IAuthor_ServerInfo,
    8,
    &IAuthor_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IPoolAdminData, ver. 0.0,
   GUID={0x91606953,0x0FD2,0x11D2,{0x92,0x8B,0x00,0x80,0xC7,0x67,0xBC,0x99}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IPoolAdminData_ServerInfo;

#pragma code_seg(".orpc")
extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[1];

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
    UserMarshalRoutines,
    0,  /* Reserved1 */
    0,  /* Reserved2 */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static const unsigned short IPoolAdminData_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    30,
    54
    };

static const MIDL_SERVER_INFO IPoolAdminData_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IPoolAdminData_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IPoolAdminData_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IPoolAdminData_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(9) _IPoolAdminDataProxyVtbl = 
{
    &IPoolAdminData_ProxyInfo,
    &IID_IPoolAdminData,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* IPoolAdminData::GetPoolInfo */ ,
    (void *)-1 /* IPoolAdminData::GetUsageStats */
};


static const PRPC_STUB_FUNCTION IPoolAdminData_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IPoolAdminDataStubVtbl =
{
    &IID_IPoolAdminData,
    &IPoolAdminData_ServerInfo,
    9,
    &IPoolAdminData_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[1] = 
        {
            
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure GetAuthorList */

			0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/*  2 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/*  4 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/*  6 */	NdrFcShort( 0x8 ),	/* 8 */
/*  8 */	NdrFcShort( 0x8 ),	/* 8 */
/* 10 */	0x5,		/* 5 */
			0x3,		/* 3 */

	/* Parameter nContract */

/* 12 */	NdrFcShort( 0x48 ),	/* 72 */
#ifndef _ALPHA_
/* 14 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 16 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pDataArray */

/* 18 */	NdrFcShort( 0x4113 ),	/* 16659 */
#ifndef _ALPHA_
/* 20 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 22 */	NdrFcShort( 0x3c6 ),	/* Type Offset=966 */

	/* Return value */

/* 24 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 26 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 28 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetPoolInfo */

/* 30 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 32 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/* 34 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 36 */	NdrFcShort( 0x0 ),	/* 0 */
/* 38 */	NdrFcShort( 0x8 ),	/* 8 */
/* 40 */	0x5,		/* 5 */
			0x2,		/* 2 */

	/* Parameter paVariant */

/* 42 */	NdrFcShort( 0x4113 ),	/* 16659 */
#ifndef _ALPHA_
/* 44 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 46 */	NdrFcShort( 0x3d4 ),	/* Type Offset=980 */

	/* Return value */

/* 48 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 50 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 52 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetUsageStats */

/* 54 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 56 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 58 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x18 ),	/* 24 */
/* 64 */	0x4,		/* 4 */
			0x3,		/* 3 */

	/* Parameter pConnections */

/* 66 */	NdrFcShort( 0x2150 ),	/* 8528 */
#ifndef _ALPHA_
/* 68 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 70 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pRemaining */

/* 72 */	NdrFcShort( 0x2150 ),	/* 8528 */
#ifndef _ALPHA_
/* 74 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 76 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 78 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 80 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 82 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  2 */	NdrFcShort( 0x3c4 ),	/* Offset= 964 (966) */
/*  4 */	
			0x13, 0x0,	/* FC_OP */
/*  6 */	NdrFcShort( 0x3ac ),	/* Offset= 940 (946) */
/*  8 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x8,		/* FC_LONG */
/* 10 */	0x6,		/* 6 */
			0x0,		/*  */
/* 12 */	NdrFcShort( 0xfffffff8 ),	/* -8 */
/* 14 */	NdrFcShort( 0x2 ),	/* Offset= 2 (16) */
/* 16 */	NdrFcShort( 0x10 ),	/* 16 */
/* 18 */	NdrFcShort( 0x2b ),	/* 43 */
/* 20 */	NdrFcLong( 0x3 ),	/* 3 */
/* 24 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32736) */
/* 26 */	NdrFcLong( 0x11 ),	/* 17 */
/* 30 */	NdrFcShort( 0xffff8002 ),	/* Offset= -32766 (-32736) */
/* 32 */	NdrFcLong( 0x2 ),	/* 2 */
/* 36 */	NdrFcShort( 0xffff8006 ),	/* Offset= -32762 (-32726) */
/* 38 */	NdrFcLong( 0x4 ),	/* 4 */
/* 42 */	NdrFcShort( 0xffff800a ),	/* Offset= -32758 (-32716) */
/* 44 */	NdrFcLong( 0x5 ),	/* 5 */
/* 48 */	NdrFcShort( 0xffff800c ),	/* Offset= -32756 (-32708) */
/* 50 */	NdrFcLong( 0xb ),	/* 11 */
/* 54 */	NdrFcShort( 0xffff8006 ),	/* Offset= -32762 (-32708) */
/* 56 */	NdrFcLong( 0xa ),	/* 10 */
/* 60 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32700) */
/* 62 */	NdrFcLong( 0x6 ),	/* 6 */
/* 66 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (280) */
/* 68 */	NdrFcLong( 0x7 ),	/* 7 */
/* 72 */	NdrFcShort( 0xffff800c ),	/* Offset= -32756 (-32684) */
/* 74 */	NdrFcLong( 0x8 ),	/* 8 */
/* 78 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (286) */
/* 80 */	NdrFcLong( 0xd ),	/* 13 */
/* 84 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (310) */
/* 86 */	NdrFcLong( 0x9 ),	/* 9 */
/* 90 */	NdrFcShort( 0xee ),	/* Offset= 238 (328) */
/* 92 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 96 */	NdrFcShort( 0xfa ),	/* Offset= 250 (346) */
/* 98 */	NdrFcLong( 0x24 ),	/* 36 */
/* 102 */	NdrFcShort( 0x308 ),	/* Offset= 776 (878) */
/* 104 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 108 */	NdrFcShort( 0x302 ),	/* Offset= 770 (878) */
/* 110 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 114 */	NdrFcShort( 0x300 ),	/* Offset= 768 (882) */
/* 116 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 120 */	NdrFcShort( 0x2fe ),	/* Offset= 766 (886) */
/* 122 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 126 */	NdrFcShort( 0x2fc ),	/* Offset= 764 (890) */
/* 128 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 132 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (894) */
/* 134 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 138 */	NdrFcShort( 0x2f8 ),	/* Offset= 760 (898) */
/* 140 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 144 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (886) */
/* 146 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 150 */	NdrFcShort( 0x2e4 ),	/* Offset= 740 (890) */
/* 152 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 156 */	NdrFcShort( 0x2ea ),	/* Offset= 746 (902) */
/* 158 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 162 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (898) */
/* 164 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 168 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (906) */
/* 170 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 174 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (910) */
/* 176 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 180 */	NdrFcShort( 0x2de ),	/* Offset= 734 (914) */
/* 182 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 186 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (918) */
/* 188 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 192 */	NdrFcShort( 0x2da ),	/* Offset= 730 (922) */
/* 194 */	NdrFcLong( 0x10 ),	/* 16 */
/* 198 */	NdrFcShort( 0xffff8002 ),	/* Offset= -32766 (-32568) */
/* 200 */	NdrFcLong( 0x12 ),	/* 18 */
/* 204 */	NdrFcShort( 0xffff8006 ),	/* Offset= -32762 (-32558) */
/* 206 */	NdrFcLong( 0x13 ),	/* 19 */
/* 210 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32550) */
/* 212 */	NdrFcLong( 0x16 ),	/* 22 */
/* 216 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32544) */
/* 218 */	NdrFcLong( 0x17 ),	/* 23 */
/* 222 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32538) */
/* 224 */	NdrFcLong( 0xe ),	/* 14 */
/* 228 */	NdrFcShort( 0x2be ),	/* Offset= 702 (930) */
/* 230 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 234 */	NdrFcShort( 0x2c4 ),	/* Offset= 708 (942) */
/* 236 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 240 */	NdrFcShort( 0x282 ),	/* Offset= 642 (882) */
/* 242 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 246 */	NdrFcShort( 0x280 ),	/* Offset= 640 (886) */
/* 248 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 252 */	NdrFcShort( 0x27e ),	/* Offset= 638 (890) */
/* 254 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 258 */	NdrFcShort( 0x278 ),	/* Offset= 632 (890) */
/* 260 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 264 */	NdrFcShort( 0x272 ),	/* Offset= 626 (890) */
/* 266 */	NdrFcLong( 0x0 ),	/* 0 */
/* 270 */	NdrFcShort( 0x0 ),	/* Offset= 0 (270) */
/* 272 */	NdrFcLong( 0x1 ),	/* 1 */
/* 276 */	NdrFcShort( 0x0 ),	/* Offset= 0 (276) */
/* 278 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (277) */
/* 280 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 282 */	NdrFcShort( 0x8 ),	/* 8 */
/* 284 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 286 */	
			0x13, 0x0,	/* FC_OP */
/* 288 */	NdrFcShort( 0xc ),	/* Offset= 12 (300) */
/* 290 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 292 */	NdrFcShort( 0x2 ),	/* 2 */
/* 294 */	0x9,		/* 9 */
			0x0,		/*  */
/* 296 */	NdrFcShort( 0xfffffffc ),	/* -4 */
/* 298 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 300 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 302 */	NdrFcShort( 0x8 ),	/* 8 */
/* 304 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (290) */
/* 306 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 308 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 310 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 312 */	NdrFcLong( 0x0 ),	/* 0 */
/* 316 */	NdrFcShort( 0x0 ),	/* 0 */
/* 318 */	NdrFcShort( 0x0 ),	/* 0 */
/* 320 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 322 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 324 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 326 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 328 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 330 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 334 */	NdrFcShort( 0x0 ),	/* 0 */
/* 336 */	NdrFcShort( 0x0 ),	/* 0 */
/* 338 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 340 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 342 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 344 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 346 */	
			0x13, 0x0,	/* FC_OP */
/* 348 */	NdrFcShort( 0x200 ),	/* Offset= 512 (860) */
/* 350 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x48,		/* 72 */
/* 352 */	NdrFcShort( 0x18 ),	/* 24 */
/* 354 */	NdrFcShort( 0xa ),	/* 10 */
/* 356 */	NdrFcLong( 0x8 ),	/* 8 */
/* 360 */	NdrFcShort( 0x58 ),	/* Offset= 88 (448) */
/* 362 */	NdrFcLong( 0xd ),	/* 13 */
/* 366 */	NdrFcShort( 0x78 ),	/* Offset= 120 (486) */
/* 368 */	NdrFcLong( 0x9 ),	/* 9 */
/* 372 */	NdrFcShort( 0x94 ),	/* Offset= 148 (520) */
/* 374 */	NdrFcLong( 0xc ),	/* 12 */
/* 378 */	NdrFcShort( 0xbc ),	/* Offset= 188 (566) */
/* 380 */	NdrFcLong( 0x24 ),	/* 36 */
/* 384 */	NdrFcShort( 0x118 ),	/* Offset= 280 (664) */
/* 386 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 390 */	NdrFcShort( 0x134 ),	/* Offset= 308 (698) */
/* 392 */	NdrFcLong( 0x10 ),	/* 16 */
/* 396 */	NdrFcShort( 0x14c ),	/* Offset= 332 (728) */
/* 398 */	NdrFcLong( 0x2 ),	/* 2 */
/* 402 */	NdrFcShort( 0x164 ),	/* Offset= 356 (758) */
/* 404 */	NdrFcLong( 0x3 ),	/* 3 */
/* 408 */	NdrFcShort( 0x17c ),	/* Offset= 380 (788) */
/* 410 */	NdrFcLong( 0x14 ),	/* 20 */
/* 414 */	NdrFcShort( 0x194 ),	/* Offset= 404 (818) */
/* 416 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (415) */
/* 418 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 420 */	NdrFcShort( 0x4 ),	/* 4 */
/* 422 */	0x18,		/* 24 */
			0x0,		/*  */
/* 424 */	NdrFcShort( 0x0 ),	/* 0 */
/* 426 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 428 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 430 */	NdrFcShort( 0x4 ),	/* 4 */
/* 432 */	NdrFcShort( 0x0 ),	/* 0 */
/* 434 */	NdrFcShort( 0x1 ),	/* 1 */
/* 436 */	NdrFcShort( 0x0 ),	/* 0 */
/* 438 */	NdrFcShort( 0x0 ),	/* 0 */
/* 440 */	0x13, 0x0,	/* FC_OP */
/* 442 */	NdrFcShort( 0xffffff72 ),	/* Offset= -142 (300) */
/* 444 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 446 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 448 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 450 */	NdrFcShort( 0x8 ),	/* 8 */
/* 452 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 454 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 456 */	NdrFcShort( 0x4 ),	/* 4 */
/* 458 */	NdrFcShort( 0x4 ),	/* 4 */
/* 460 */	0x11, 0x0,	/* FC_RP */
/* 462 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (418) */
/* 464 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 466 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 468 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 470 */	NdrFcShort( 0x0 ),	/* 0 */
/* 472 */	0x18,		/* 24 */
			0x0,		/*  */
/* 474 */	NdrFcShort( 0x0 ),	/* 0 */
/* 476 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 480 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 482 */	NdrFcShort( 0xffffff54 ),	/* Offset= -172 (310) */
/* 484 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 486 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 488 */	NdrFcShort( 0x8 ),	/* 8 */
/* 490 */	NdrFcShort( 0x0 ),	/* 0 */
/* 492 */	NdrFcShort( 0x6 ),	/* Offset= 6 (498) */
/* 494 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 496 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 498 */	
			0x11, 0x0,	/* FC_RP */
/* 500 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (468) */
/* 502 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 506 */	0x18,		/* 24 */
			0x0,		/*  */
/* 508 */	NdrFcShort( 0x0 ),	/* 0 */
/* 510 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 514 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 516 */	NdrFcShort( 0xffffff44 ),	/* Offset= -188 (328) */
/* 518 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 520 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 522 */	NdrFcShort( 0x8 ),	/* 8 */
/* 524 */	NdrFcShort( 0x0 ),	/* 0 */
/* 526 */	NdrFcShort( 0x6 ),	/* Offset= 6 (532) */
/* 528 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 530 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 532 */	
			0x11, 0x0,	/* FC_RP */
/* 534 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (502) */
/* 536 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 538 */	NdrFcShort( 0x4 ),	/* 4 */
/* 540 */	0x18,		/* 24 */
			0x0,		/*  */
/* 542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 544 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 546 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 548 */	NdrFcShort( 0x4 ),	/* 4 */
/* 550 */	NdrFcShort( 0x0 ),	/* 0 */
/* 552 */	NdrFcShort( 0x1 ),	/* 1 */
/* 554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 558 */	0x13, 0x0,	/* FC_OP */
/* 560 */	NdrFcShort( 0x182 ),	/* Offset= 386 (946) */
/* 562 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 564 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 566 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 568 */	NdrFcShort( 0x8 ),	/* 8 */
/* 570 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 572 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 574 */	NdrFcShort( 0x4 ),	/* 4 */
/* 576 */	NdrFcShort( 0x4 ),	/* 4 */
/* 578 */	0x11, 0x0,	/* FC_RP */
/* 580 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (536) */
/* 582 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 584 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 586 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 588 */	NdrFcLong( 0x2f ),	/* 47 */
/* 592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 596 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 598 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 600 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 602 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 604 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 606 */	NdrFcShort( 0x1 ),	/* 1 */
/* 608 */	0x18,		/* 24 */
			0x0,		/*  */
/* 610 */	NdrFcShort( 0x4 ),	/* 4 */
/* 612 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 614 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 616 */	NdrFcShort( 0x10 ),	/* 16 */
/* 618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 620 */	NdrFcShort( 0xa ),	/* Offset= 10 (630) */
/* 622 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 624 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 626 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (586) */
/* 628 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 630 */	
			0x13, 0x0,	/* FC_OP */
/* 632 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (604) */
/* 634 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 636 */	NdrFcShort( 0x4 ),	/* 4 */
/* 638 */	0x18,		/* 24 */
			0x0,		/*  */
/* 640 */	NdrFcShort( 0x0 ),	/* 0 */
/* 642 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 644 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 646 */	NdrFcShort( 0x4 ),	/* 4 */
/* 648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 650 */	NdrFcShort( 0x1 ),	/* 1 */
/* 652 */	NdrFcShort( 0x0 ),	/* 0 */
/* 654 */	NdrFcShort( 0x0 ),	/* 0 */
/* 656 */	0x13, 0x0,	/* FC_OP */
/* 658 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (614) */
/* 660 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 662 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 664 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 666 */	NdrFcShort( 0x8 ),	/* 8 */
/* 668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 670 */	NdrFcShort( 0x6 ),	/* Offset= 6 (676) */
/* 672 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 674 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 676 */	
			0x11, 0x0,	/* FC_RP */
/* 678 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (634) */
/* 680 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 682 */	NdrFcShort( 0x8 ),	/* 8 */
/* 684 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 686 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 688 */	NdrFcShort( 0x10 ),	/* 16 */
/* 690 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 692 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 694 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (680) */
			0x5b,		/* FC_END */
/* 698 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 700 */	NdrFcShort( 0x18 ),	/* 24 */
/* 702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 704 */	NdrFcShort( 0xa ),	/* Offset= 10 (714) */
/* 706 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 708 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 710 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (686) */
/* 712 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 714 */	
			0x11, 0x0,	/* FC_RP */
/* 716 */	NdrFcShort( 0xffffff08 ),	/* Offset= -248 (468) */
/* 718 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 720 */	NdrFcShort( 0x1 ),	/* 1 */
/* 722 */	0x19,		/* 25 */
			0x0,		/*  */
/* 724 */	NdrFcShort( 0x0 ),	/* 0 */
/* 726 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 728 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 730 */	NdrFcShort( 0x8 ),	/* 8 */
/* 732 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 734 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 736 */	NdrFcShort( 0x4 ),	/* 4 */
/* 738 */	NdrFcShort( 0x4 ),	/* 4 */
/* 740 */	0x13, 0x0,	/* FC_OP */
/* 742 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (718) */
/* 744 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 746 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 748 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 750 */	NdrFcShort( 0x2 ),	/* 2 */
/* 752 */	0x19,		/* 25 */
			0x0,		/*  */
/* 754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 756 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 758 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 760 */	NdrFcShort( 0x8 ),	/* 8 */
/* 762 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 764 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 766 */	NdrFcShort( 0x4 ),	/* 4 */
/* 768 */	NdrFcShort( 0x4 ),	/* 4 */
/* 770 */	0x13, 0x0,	/* FC_OP */
/* 772 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (748) */
/* 774 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 776 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 778 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 780 */	NdrFcShort( 0x4 ),	/* 4 */
/* 782 */	0x19,		/* 25 */
			0x0,		/*  */
/* 784 */	NdrFcShort( 0x0 ),	/* 0 */
/* 786 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 788 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 790 */	NdrFcShort( 0x8 ),	/* 8 */
/* 792 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 794 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 796 */	NdrFcShort( 0x4 ),	/* 4 */
/* 798 */	NdrFcShort( 0x4 ),	/* 4 */
/* 800 */	0x13, 0x0,	/* FC_OP */
/* 802 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (778) */
/* 804 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 806 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 808 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 810 */	NdrFcShort( 0x8 ),	/* 8 */
/* 812 */	0x19,		/* 25 */
			0x0,		/*  */
/* 814 */	NdrFcShort( 0x0 ),	/* 0 */
/* 816 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 818 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 820 */	NdrFcShort( 0x8 ),	/* 8 */
/* 822 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 824 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 826 */	NdrFcShort( 0x4 ),	/* 4 */
/* 828 */	NdrFcShort( 0x4 ),	/* 4 */
/* 830 */	0x13, 0x0,	/* FC_OP */
/* 832 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (808) */
/* 834 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 836 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 838 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 840 */	NdrFcShort( 0x8 ),	/* 8 */
/* 842 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 844 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 846 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 848 */	NdrFcShort( 0x8 ),	/* 8 */
/* 850 */	0x6,		/* 6 */
			0x0,		/*  */
/* 852 */	NdrFcShort( 0xffffffd8 ),	/* -40 */
/* 854 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 856 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (838) */
/* 858 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 860 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 862 */	NdrFcShort( 0x28 ),	/* 40 */
/* 864 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (846) */
/* 866 */	NdrFcShort( 0x0 ),	/* Offset= 0 (866) */
/* 868 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 870 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 872 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 874 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffdf3 ),	/* Offset= -525 (350) */
			0x5b,		/* FC_END */
/* 878 */	
			0x13, 0x0,	/* FC_OP */
/* 880 */	NdrFcShort( 0xfffffef6 ),	/* Offset= -266 (614) */
/* 882 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 884 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 886 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 888 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 890 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 892 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 894 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 896 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 898 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 900 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 902 */	
			0x13, 0x0,	/* FC_OP */
/* 904 */	NdrFcShort( 0xfffffd90 ),	/* Offset= -624 (280) */
/* 906 */	
			0x13, 0x10,	/* FC_OP */
/* 908 */	NdrFcShort( 0xfffffd92 ),	/* Offset= -622 (286) */
/* 910 */	
			0x13, 0x10,	/* FC_OP */
/* 912 */	NdrFcShort( 0xfffffda6 ),	/* Offset= -602 (310) */
/* 914 */	
			0x13, 0x10,	/* FC_OP */
/* 916 */	NdrFcShort( 0xfffffdb4 ),	/* Offset= -588 (328) */
/* 918 */	
			0x13, 0x10,	/* FC_OP */
/* 920 */	NdrFcShort( 0xfffffdc2 ),	/* Offset= -574 (346) */
/* 922 */	
			0x13, 0x10,	/* FC_OP */
/* 924 */	NdrFcShort( 0x2 ),	/* Offset= 2 (926) */
/* 926 */	
			0x13, 0x0,	/* FC_OP */
/* 928 */	NdrFcShort( 0xfffffc60 ),	/* Offset= -928 (0) */
/* 930 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 932 */	NdrFcShort( 0x10 ),	/* 16 */
/* 934 */	0x6,		/* FC_SHORT */
			0x2,		/* FC_CHAR */
/* 936 */	0x2,		/* FC_CHAR */
			0x38,		/* FC_ALIGNM4 */
/* 938 */	0x8,		/* FC_LONG */
			0x39,		/* FC_ALIGNM8 */
/* 940 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 942 */	
			0x13, 0x0,	/* FC_OP */
/* 944 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (930) */
/* 946 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 948 */	NdrFcShort( 0x20 ),	/* 32 */
/* 950 */	NdrFcShort( 0x0 ),	/* 0 */
/* 952 */	NdrFcShort( 0x0 ),	/* Offset= 0 (952) */
/* 954 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 956 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 958 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 960 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 962 */	NdrFcShort( 0xfffffc46 ),	/* Offset= -954 (8) */
/* 964 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 966 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 968 */	NdrFcShort( 0x0 ),	/* 0 */
/* 970 */	NdrFcShort( 0x10 ),	/* 16 */
/* 972 */	NdrFcShort( 0x0 ),	/* 0 */
/* 974 */	NdrFcShort( 0xfffffc36 ),	/* Offset= -970 (4) */
/* 976 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 978 */	NdrFcShort( 0x2 ),	/* Offset= 2 (980) */
/* 980 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 982 */	NdrFcShort( 0x0 ),	/* 0 */
/* 984 */	NdrFcShort( 0x10 ),	/* 16 */
/* 986 */	NdrFcShort( 0x0 ),	/* 0 */
/* 988 */	NdrFcShort( 0xfffffc28 ),	/* Offset= -984 (4) */
/* 990 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 992 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

const CInterfaceProxyVtbl * _BusObject_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IPoolAdminDataProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAuthorProxyVtbl,
    0
};

const CInterfaceStubVtbl * _BusObject_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IPoolAdminDataStubVtbl,
    ( CInterfaceStubVtbl *) &_IAuthorStubVtbl,
    0
};

PCInterfaceName const _BusObject_InterfaceNamesList[] = 
{
    "IPoolAdminData",
    "IAuthor",
    0
};

const IID *  _BusObject_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _BusObject_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _BusObject, pIID, n)

int __stdcall _BusObject_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _BusObject, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _BusObject, 2, *pIndex )
    
}

const ExtendedProxyFileInfo BusObject_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _BusObject_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _BusObject_StubVtblList,
    (const PCInterfaceName * ) & _BusObject_InterfaceNamesList,
    (const IID ** ) & _BusObject_BaseIIDList,
    & _BusObject_IID_Lookup, 
    2,
    2
};
