#ifdef __BORLANDC__
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#endif

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.00.15 */
/* at Thu Jun 13 20:25:13 1996
 */
/* Compiler settings for datapath.idl:
    Oi, W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __datapath_h__
#define __datapath_h__

#ifdef __cplusplus
extern "C"{
#endif

/* Forward Declarations */

#ifndef __IObjectWithSite_FWD_DEFINED__
#define __IObjectWithSite_FWD_DEFINED__
typedef interface IObjectWithSite IObjectWithSite;
#endif 	/* __IObjectWithSite_FWD_DEFINED__ */


#ifndef __IDataPathBrowser_FWD_DEFINED__
#define __IDataPathBrowser_FWD_DEFINED__
typedef interface IDataPathBrowser IDataPathBrowser;
#endif 	/* __IDataPathBrowser_FWD_DEFINED__ */


#ifndef __IProvideClassInfo3_FWD_DEFINED__
#define __IProvideClassInfo3_FWD_DEFINED__
typedef interface IProvideClassInfo3 IProvideClassInfo3;
#endif 	/* __IProvideClassInfo3_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "oleidl.h"
#include "oaidl.h"
#include "olectl.h"
#include "urlmon.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * );

/****************************************
 * Generated header for interface: __MIDL__intf_0000
 * at Thu Jun 13 20:25:13 1996
 * using MIDL 3.00.15
 ****************************************/
/* [local] */


//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright 1995 - 1996 Microsoft Corporation. All Rights Reserved.
//
//  File: datapath.h

#pragma comment(lib,"uuid3.lib")
//
//--------------------------------------------------------------------------


#include "idispids.h"
typedef BSTR OLE_DATAPATH;
#define SID_SDataPathBrowser IID_IDataPathBrowser

#if 0
////////////////////////////////////////////////////////////////////////////
//  State values for the DISPID_READYSTATE property

enum __MIDL___MIDL__intf_0000_0001
    {	READYSTATE_UNINITIALIZED	= 1,
	READYSTATE_LOADING	= 0,
	READYSTATE_LOADED	= 2,
	READYSTATE_INTERACTIVE	= 3,
	READYSTATE_COMPLETE	= 4
    };
#endif
////////////////////////////////////////////////////////////////////////////
//  DataPath GUIDs (link to uuid3.lib)
EXTERN_C const GUID OLE_DATAPATH_BMP;
EXTERN_C const GUID OLE_DATAPATH_DIB;
EXTERN_C const GUID OLE_DATAPATH_WMF;
EXTERN_C const GUID OLE_DATAPATH_ENHMF;
EXTERN_C const GUID OLE_DATAPATH_GIF;
EXTERN_C const GUID OLE_DATAPATH_JPEG;
EXTERN_C const GUID OLE_DATAPATH_TIFF;
EXTERN_C const GUID OLE_DATAPATH_XBM;
EXTERN_C const GUID OLE_DATAPATH_PCX;
EXTERN_C const GUID OLE_DATAPATH_PICT;
EXTERN_C const GUID OLE_DATAPATH_CGM;
EXTERN_C const GUID OLE_DATAPATH_EPS;
EXTERN_C const GUID OLE_DATAPATH_COMMONIMAGE;
EXTERN_C const GUID OLE_DATAPATH_ALLIMAGE;
EXTERN_C const GUID OLE_DATAPATH_AVI;
EXTERN_C const GUID OLE_DATAPATH_MPEG;
EXTERN_C const GUID OLE_DATAPATH_QUICKTIME;
EXTERN_C const GUID OLE_DATAPATH_BASICAUDIO;
EXTERN_C const GUID OLE_DATAPATH_MIDI;
EXTERN_C const GUID OLE_DATAPATH_WAV;
EXTERN_C const GUID OLE_DATAPATH_RIFF;
EXTERN_C const GUID OLE_DATAPATH_SOUND;
EXTERN_C const GUID OLE_DATAPATH_VIDEO;
EXTERN_C const GUID OLE_DATAPATH_ALLMM;
EXTERN_C const GUID OLE_DATAPATH_ANSITEXT;
EXTERN_C const GUID OLE_DATAPATH_UNICODE;
EXTERN_C const GUID OLE_DATAPATH_RTF;
EXTERN_C const GUID OLE_DATAPATH_HTML;
EXTERN_C const GUID OLE_DATAPATH_POSTSCRIPT;
EXTERN_C const GUID OLE_DATAPATH_ALLTEXT;
EXTERN_C const GUID OLE_DATAPATH_DIF;
EXTERN_C const GUID OLE_DATAPATH_SYLK;
EXTERN_C const GUID OLE_DATAPATH_BIFF;
EXTERN_C const GUID OLE_DATAPATH_PALETTE;
EXTERN_C const GUID OLE_DATAPATH_PENDATA;
////////////////////////////////////////////////////////////////////////////

EXTERN_C const GUID FLAGID_Internet;
EXTERN_C const GUID GUID_PathProperty;
EXTERN_C const GUID GUID_HasPathProperties;

////////////////////////////////////////////////////////////////////////////
//  ARRAYID GUIDs (link to uuid3.lib)
EXTERN_C const GUID ARRAYID_PathProperties;

////////////////////////////////////////////////////////////////////////////
//  Interface Definitions
#ifndef _LPOBJECTWITHSITE_DEFINED
#define _LPOBJECTWITHSITE_DEFINED


extern RPC_IF_HANDLE __MIDL__intf_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0000_v0_0_s_ifspec;

#ifndef __IObjectWithSite_INTERFACE_DEFINED__
#define __IObjectWithSite_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IObjectWithSite
 * at Thu Jun 13 20:25:13 1996
 * using MIDL 3.00.15
 ****************************************/
/* [unique][object][uuid] */


typedef /* [unique] */ IObjectWithSite __RPC_FAR *LPOBJECTWITHSITE;


EXTERN_C const IID IID_IObjectWithSite;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface IObjectWithSite : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetSite(
            /* [in] */ IUnknown __RPC_FAR *pUnkSite) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetSite(
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvSite) = 0;

    };

#else 	/* C style interface */

    typedef struct IObjectWithSiteVtbl
    {
        BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
            IObjectWithSite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
            IObjectWithSite __RPC_FAR * This);

        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
            IObjectWithSite __RPC_FAR * This);

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSite )(
            IObjectWithSite __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkSite);

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSite )(
            IObjectWithSite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvSite);

        END_INTERFACE
    } IObjectWithSiteVtbl;

    interface IObjectWithSite
    {
        CONST_VTBL struct IObjectWithSiteVtbl __RPC_FAR *lpVtbl;
    };



#ifdef COBJMACROS


#define IObjectWithSite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IObjectWithSite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IObjectWithSite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IObjectWithSite_SetSite(This,pUnkSite)	\
    (This)->lpVtbl -> SetSite(This,pUnkSite)

#define IObjectWithSite_GetSite(This,riid,ppvSite)	\
    (This)->lpVtbl -> GetSite(This,riid,ppvSite)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IObjectWithSite_SetSite_Proxy(
    IObjectWithSite __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkSite);


void __RPC_STUB IObjectWithSite_SetSite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IObjectWithSite_GetSite_Proxy(
    IObjectWithSite __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvSite);


void __RPC_STUB IObjectWithSite_GetSite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IObjectWithSite_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL__intf_0119
 * at Thu Jun 13 20:25:13 1996
 * using MIDL 3.00.15
 ****************************************/
/* [local] */


#endif
#ifndef _LPDATAPATHBROWSER_DEFINED
#define _LPDATAPATHBROWSER_DEFINED


extern RPC_IF_HANDLE __MIDL__intf_0119_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0119_v0_0_s_ifspec;

#ifndef __IDataPathBrowser_INTERFACE_DEFINED__
#define __IDataPathBrowser_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDataPathBrowser
 * at Thu Jun 13 20:25:13 1996
 * using MIDL 3.00.15
 ****************************************/
/* [unique][object][local][uuid] */



EXTERN_C const IID IID_IDataPathBrowser;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface IDataPathBrowser : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE BrowseType(
            /* [in] */ REFGUID rguidPathType,
            /* [in] */ LPOLESTR pszDefaultPath,
            /* [in] */ ULONG cchPath,
            /* [size_is][out] */ LPOLESTR pszPath,
            /* [in] */ HWND hWnd) = 0;

    };

#else 	/* C style interface */

    typedef struct IDataPathBrowserVtbl
    {
        BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
            IDataPathBrowser __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
            IDataPathBrowser __RPC_FAR * This);

        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
            IDataPathBrowser __RPC_FAR * This);

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BrowseType )(
            IDataPathBrowser __RPC_FAR * This,
            /* [in] */ REFGUID rguidPathType,
            /* [in] */ LPOLESTR pszDefaultPath,
            /* [in] */ ULONG cchPath,
            /* [size_is][out] */ LPOLESTR pszPath,
            /* [in] */ HWND hWnd);

        END_INTERFACE
    } IDataPathBrowserVtbl;

    interface IDataPathBrowser
    {
        CONST_VTBL struct IDataPathBrowserVtbl __RPC_FAR *lpVtbl;
    };



#ifdef COBJMACROS


#define IDataPathBrowser_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDataPathBrowser_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDataPathBrowser_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDataPathBrowser_BrowseType(This,rguidPathType,pszDefaultPath,cchPath,pszPath,hWnd)	\
    (This)->lpVtbl -> BrowseType(This,rguidPathType,pszDefaultPath,cchPath,pszPath,hWnd)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDataPathBrowser_BrowseType_Proxy(
    IDataPathBrowser __RPC_FAR * This,
    /* [in] */ REFGUID rguidPathType,
    /* [in] */ LPOLESTR pszDefaultPath,
    /* [in] */ ULONG cchPath,
    /* [size_is][out] */ LPOLESTR pszPath,
    /* [in] */ HWND hWnd);


void __RPC_STUB IDataPathBrowser_BrowseType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDataPathBrowser_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL__intf_0120
 * at Thu Jun 13 20:25:13 1996
 * using MIDL 3.00.15
 ****************************************/
/* [local] */


#endif
#ifndef _LPPROVIDECLASSINFO3_DEFINED
#define _LPPROVIDECLASSINFO3_DEFINED


extern RPC_IF_HANDLE __MIDL__intf_0120_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0120_v0_0_s_ifspec;

#ifndef __IProvideClassInfo3_INTERFACE_DEFINED__
#define __IProvideClassInfo3_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IProvideClassInfo3
 * at Thu Jun 13 20:25:13 1996
 * using MIDL 3.00.15
 ****************************************/
/* [unique][uuid][object] */


typedef /* [unique] */ IProvideClassInfo3 __RPC_FAR *LPPROVIDECLASSINFO3;


enum __MIDL_IProvideClassInfo3_0001
    {	INTERNETFLAG_USESDATAPATHS	= 0x1
    };

EXTERN_C const IID IID_IProvideClassInfo3;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface IProvideClassInfo3 : public IProvideClassInfo2
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetGUIDDwordArrays(
            /* [in] */ REFGUID rguidArray,
            /* [out][in] */ CAUUID __RPC_FAR *pcaUUID,
            /* [out][in] */ CADWORD __RPC_FAR *pcadw) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetClassInfoLocale(
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppITypeInfo,
            /* [in] */ LCID lcid) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetFlags(
            /* [in] */ REFGUID guidGroup,
            /* [out] */ DWORD __RPC_FAR *pdwFlags) = 0;

    };

#else 	/* C style interface */

    typedef struct IProvideClassInfo3Vtbl
    {
        BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
            IProvideClassInfo3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
            IProvideClassInfo3 __RPC_FAR * This);

        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
            IProvideClassInfo3 __RPC_FAR * This);

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClassInfo )(
            IProvideClassInfo3 __RPC_FAR * This,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTI);

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGUID )(
            IProvideClassInfo3 __RPC_FAR * This,
            /* [in] */ DWORD dwGuidKind,
            /* [out] */ GUID __RPC_FAR *pGUID);

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGUIDDwordArrays )(
            IProvideClassInfo3 __RPC_FAR * This,
            /* [in] */ REFGUID rguidArray,
            /* [out][in] */ CAUUID __RPC_FAR *pcaUUID,
            /* [out][in] */ CADWORD __RPC_FAR *pcadw);

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClassInfoLocale )(
            IProvideClassInfo3 __RPC_FAR * This,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppITypeInfo,
            /* [in] */ LCID lcid);

        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlags )(
            IProvideClassInfo3 __RPC_FAR * This,
            /* [in] */ REFGUID guidGroup,
            /* [out] */ DWORD __RPC_FAR *pdwFlags);

        END_INTERFACE
    } IProvideClassInfo3Vtbl;

    interface IProvideClassInfo3
    {
        CONST_VTBL struct IProvideClassInfo3Vtbl __RPC_FAR *lpVtbl;
    };



#ifdef COBJMACROS


#define IProvideClassInfo3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IProvideClassInfo3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IProvideClassInfo3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IProvideClassInfo3_GetClassInfo(This,ppTI)	\
    (This)->lpVtbl -> GetClassInfo(This,ppTI)


#define IProvideClassInfo3_GetGUID(This,dwGuidKind,pGUID)	\
    (This)->lpVtbl -> GetGUID(This,dwGuidKind,pGUID)


#define IProvideClassInfo3_GetGUIDDwordArrays(This,rguidArray,pcaUUID,pcadw)	\
    (This)->lpVtbl -> GetGUIDDwordArrays(This,rguidArray,pcaUUID,pcadw)

#define IProvideClassInfo3_GetClassInfoLocale(This,ppITypeInfo,lcid)	\
    (This)->lpVtbl -> GetClassInfoLocale(This,ppITypeInfo,lcid)

#define IProvideClassInfo3_GetFlags(This,guidGroup,pdwFlags)	\
    (This)->lpVtbl -> GetFlags(This,guidGroup,pdwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IProvideClassInfo3_GetGUIDDwordArrays_Proxy(
    IProvideClassInfo3 __RPC_FAR * This,
    /* [in] */ REFGUID rguidArray,
    /* [out][in] */ CAUUID __RPC_FAR *pcaUUID,
    /* [out][in] */ CADWORD __RPC_FAR *pcadw);


void __RPC_STUB IProvideClassInfo3_GetGUIDDwordArrays_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IProvideClassInfo3_GetClassInfoLocale_Proxy(
    IProvideClassInfo3 __RPC_FAR * This,
    /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppITypeInfo,
    /* [in] */ LCID lcid);


void __RPC_STUB IProvideClassInfo3_GetClassInfoLocale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IProvideClassInfo3_GetFlags_Proxy(
    IProvideClassInfo3 __RPC_FAR * This,
    /* [in] */ REFGUID guidGroup,
    /* [out] */ DWORD __RPC_FAR *pdwFlags);


void __RPC_STUB IProvideClassInfo3_GetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IProvideClassInfo3_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL__intf_0121
 * at Thu Jun 13 20:25:13 1996
 * using MIDL 3.00.15
 ****************************************/
/* [local] */


#endif


extern RPC_IF_HANDLE __MIDL__intf_0121_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0121_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

#ifdef __BORLANDC__
#pragma option pop /*P_O_Pop*/
#endif
