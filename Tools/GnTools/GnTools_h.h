

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon May 23 09:04:11 2011
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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __GnTools_h_h__
#define __GnTools_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IGnTools_FWD_DEFINED__
#define __IGnTools_FWD_DEFINED__
typedef interface IGnTools IGnTools;
#endif 	/* __IGnTools_FWD_DEFINED__ */


#ifndef __CGnToolsDoc_FWD_DEFINED__
#define __CGnToolsDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CGnToolsDoc CGnToolsDoc;
#else
typedef struct CGnToolsDoc CGnToolsDoc;
#endif /* __cplusplus */

#endif 	/* __CGnToolsDoc_FWD_DEFINED__ */


#ifndef __IGtFloatSpinButtonCtrl_FWD_DEFINED__
#define __IGtFloatSpinButtonCtrl_FWD_DEFINED__
typedef interface IGtFloatSpinButtonCtrl IGtFloatSpinButtonCtrl;
#endif 	/* __IGtFloatSpinButtonCtrl_FWD_DEFINED__ */


#ifndef __GtFloatSpinButtonCtrl_FWD_DEFINED__
#define __GtFloatSpinButtonCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class GtFloatSpinButtonCtrl GtFloatSpinButtonCtrl;
#else
typedef struct GtFloatSpinButtonCtrl GtFloatSpinButtonCtrl;
#endif /* __cplusplus */

#endif 	/* __GtFloatSpinButtonCtrl_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __GnTools_LIBRARY_DEFINED__
#define __GnTools_LIBRARY_DEFINED__

/* library GnTools */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_GnTools;

#ifndef __IGnTools_DISPINTERFACE_DEFINED__
#define __IGnTools_DISPINTERFACE_DEFINED__

/* dispinterface IGnTools */
/* [uuid] */ 


EXTERN_C const IID DIID_IGnTools;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("825D5E62-11AB-4FC9-AF78-13E954238533")
    IGnTools : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IGnToolsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGnTools * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGnTools * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGnTools * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGnTools * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGnTools * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGnTools * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGnTools * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IGnToolsVtbl;

    interface IGnTools
    {
        CONST_VTBL struct IGnToolsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGnTools_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGnTools_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGnTools_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGnTools_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGnTools_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGnTools_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGnTools_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IGnTools_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CGnToolsDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("40AEC219-DA5A-42B0-81C1-7F7BD24BC0B2")
CGnToolsDoc;
#endif

#ifndef __IGtFloatSpinButtonCtrl_DISPINTERFACE_DEFINED__
#define __IGtFloatSpinButtonCtrl_DISPINTERFACE_DEFINED__

/* dispinterface IGtFloatSpinButtonCtrl */
/* [uuid] */ 


EXTERN_C const IID DIID_IGtFloatSpinButtonCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CC38B162-DEED-411B-AA0A-6D2D44AF24F2")
    IGtFloatSpinButtonCtrl : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IGtFloatSpinButtonCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGtFloatSpinButtonCtrl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGtFloatSpinButtonCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGtFloatSpinButtonCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGtFloatSpinButtonCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGtFloatSpinButtonCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGtFloatSpinButtonCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGtFloatSpinButtonCtrl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IGtFloatSpinButtonCtrlVtbl;

    interface IGtFloatSpinButtonCtrl
    {
        CONST_VTBL struct IGtFloatSpinButtonCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGtFloatSpinButtonCtrl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGtFloatSpinButtonCtrl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGtFloatSpinButtonCtrl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGtFloatSpinButtonCtrl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGtFloatSpinButtonCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGtFloatSpinButtonCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGtFloatSpinButtonCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IGtFloatSpinButtonCtrl_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_GtFloatSpinButtonCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("8C4187D0-1070-4C85-BFE6-0A7634DF7EF4")
GtFloatSpinButtonCtrl;
#endif
#endif /* __GnTools_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


