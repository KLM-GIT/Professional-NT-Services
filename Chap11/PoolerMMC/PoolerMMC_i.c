/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.01.75 */
/* at Tue Jun 30 06:08:13 1998
 */
/* Compiler settings for PoolerMMC.idl:
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

const IID IID_IPoolerMMCDataObject = {0xA2AF0D58,0xF7E6,0x11d1,{0x84,0x6A,0x00,0x20,0xAF,0x05,0xED,0x45}};


const IID IID_IPoolerMMCExtendContextMenu = {0xA2AF0D59,0xF7E6,0x11d1,{0x84,0x6A,0x00,0x20,0xAF,0x05,0xED,0x45}};


const IID LIBID_POOLERMMCLib = {0xC8FF6D09,0xF7C9,0x11D1,{0x84,0x6A,0x00,0x20,0xAF,0x05,0xED,0x45}};


const CLSID CLSID_Component = {0xC8FF6D19,0xF7C9,0x11D1,{0x84,0x6A,0x00,0x20,0xAF,0x05,0xED,0x45}};


const CLSID CLSID_ComponentData = {0xC8FF6D1B,0xF7C9,0x11D1,{0x84,0x6A,0x00,0x20,0xAF,0x05,0xED,0x45}};


const CLSID CLSID_DataObject = {0xC8FF6D1D,0xF7C9,0x11D1,{0x84,0x6A,0x00,0x20,0xAF,0x05,0xED,0x45}};


const CLSID CLSID_ExtendContextMenu = {0xC8FF6D1F,0xF7C9,0x11D1,{0x84,0x6A,0x00,0x20,0xAF,0x05,0xED,0x45}};


#ifdef __cplusplus
}
#endif

