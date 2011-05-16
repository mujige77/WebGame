

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon May 16 00:09:33 2011
 */
/* Compiler settings for GnTools.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

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

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_GnTools,0x1648CA1B,0x1D6E,0x43DB,0x8E,0x3B,0xDF,0xB5,0xC4,0xFB,0xED,0x64);


MIDL_DEFINE_GUID(IID, DIID_IGnTools,0x825D5E62,0x11AB,0x4FC9,0xAF,0x78,0x13,0xE9,0x54,0x23,0x85,0x33);


MIDL_DEFINE_GUID(CLSID, CLSID_CGnToolsDoc,0x40AEC219,0xDA5A,0x42B0,0x81,0xC1,0x7F,0x7B,0xD2,0x4B,0xC0,0xB2);


MIDL_DEFINE_GUID(IID, DIID_IGtFloatSpinButtonCtrl,0xCC38B162,0xDEED,0x411B,0xAA,0x0A,0x6D,0x2D,0x44,0xAF,0x24,0xF2);


MIDL_DEFINE_GUID(CLSID, CLSID_GtFloatSpinButtonCtrl,0x8C4187D0,0x1070,0x4C85,0xBF,0xE6,0x0A,0x76,0x34,0xDF,0x7E,0xF4);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



