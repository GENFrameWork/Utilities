/****************************************************************************
*
*  (C) COPYRIGHT 1998-2000, MICROSOFT CORP.
*
*  FILE:        wiadevd.h
*
*  VERSION:     1.0
*
*  DATE:        7/5/1999
*
*  DESCRIPTION:
*    Device Dialog and UI extensibility declarations.
*
*****************************************************************************/

#ifndef _WIADEVD_H_INCLUDED
#define _WIADEVD_H_INCLUDED

#ifdef __BORLANDC__
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#endif

#include "wia.h"

#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack8.h>

typedef struct tagDEVICEDIALOGDATA
{
    DWORD            cbSize;           // Size of the structure in bytes
    HWND             hwndParent;       // Parent window
    IWiaItem         *pIWiaItemRoot;   // Valid root item
    DWORD            dwFlags;          // Flags
    LONG             lIntent;          // Intent flags
    LONG             lItemCount;       // Number of items in ppWiaItems array.  Filled on return.
    IWiaItem         **ppWiaItems;     // Array of IWiaItem interface pointers.  Array must
                                       // be allocated using LocalAlloc, all interface pointers must be AddRef'ed
} DEVICEDIALOGDATA, *LPDEVICEDIALOGDATA, *PDEVICEDIALOGDATA;

HRESULT WINAPI DeviceDialog( PDEVICEDIALOGDATA pDeviceDialogData );

// IWiaUIExtension provides a means to replace a device's image acquisition dialog
// and to provide custom icons and logo bitmaps to appear on the standard dialog
#undef  INTERFACE
#define INTERFACE IWiaUIExtension
DECLARE_INTERFACE_(IWiaUIExtension, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS) PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    // *** IWiaUIExtension methods ***
    STDMETHOD(DeviceDialog)( THIS_ PDEVICEDIALOGDATA pDeviceDialogData ) PURE;
    STDMETHOD(GetDeviceIcon)(THIS_ BSTR bstrDeviceId, HICON *phIcon, ULONG nSize ) PURE;
    STDMETHOD(GetDeviceBitmapLogo)(THIS_ BSTR bstrDeviceId, HBITMAP *phBitmap, ULONG nMaxWidth, ULONG nMaxHeight ) PURE;
};

// {da319113-50ee-4c80-b460-57d005d44a2c}
DEFINE_GUID(IID_IWiaUIExtension, 0xDA319113, 0x50EE, 0x4C80, 0xB4, 0x60, 0x57, 0xD0, 0x05, 0xD4, 0x4A, 0x2C);

typedef HRESULT (WINAPI *DeviceDialogFunction)(PDEVICEDIALOGDATA);

#define SHELLEX_WIAUIEXTENSION_NAME TEXT("WiaDialogExtensionHandlers")

// Define clipboard format names for retrieving data from an IDataObject
#define CFSTR_WIAITEMNAMES TEXT("WIAItemNames")
#define CFSTR_WIAITEMPTR   TEXT("WIAItemPointer")

#include <poppack.h>

#if defined(__cplusplus)
};
#endif

#ifdef __BORLANDC__
#pragma option pop /*P_O_Pop*/
#endif

#endif // !_WIADEVD_H_INCLUDED

