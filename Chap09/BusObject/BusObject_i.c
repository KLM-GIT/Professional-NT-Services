/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.01.75 */
/* at Mon Jun 29 09:45:17 1998
 */
/* Compiler settings for BusObject.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IAuthor = {0xD0B92D6B,0xF0DF,0x11D1,{0x84,0x66,0x00,0x20,0xAF,0x05,0xED,0x45}};


const IID LIBID_BUSOBJECTLib = {0xD285D162,0xED84,0x11D1,{0x84,0x66,0x00,0x20,0xAF,0x05,0xED,0x45}};


const CLSID CLSID_Author = {0xD0B92D6C,0xF0DF,0x11D1,{0x84,0x66,0x00,0x20,0xAF,0x05,0xED,0x45}};


#ifdef __cplusplus
}
#endif

