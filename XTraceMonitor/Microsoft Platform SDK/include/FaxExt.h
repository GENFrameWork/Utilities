/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

Module Name:

    faxext.h

Abstract:

    Declarations of fax extension configuration and notification functions.

--*/


#ifndef _FAX_EXT_H_
#define _FAX_EXT_H_

#ifdef __BORLANDC__
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#endif

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/************************************
*                                   *
*   Extension configuration data    *
*                                   *
************************************/

typedef enum
{
    DEV_ID_SRC_FAX,         // Device id is generated by the fax server
    DEV_ID_SRC_TAPI         // Device id is generated by a TAPI TSP (of FSP).
}   FAX_ENUM_DEVICE_ID_SOURCE;

//
// Prototype of FaxExtGetData 
// 
DWORD
FaxExtGetData (
    DWORD                       dwDeviceId,     // Device id (0 = No device)
    FAX_ENUM_DEVICE_ID_SOURCE   DevIdSrc,       // The source of the device id
    LPCWSTR                     lpcwstrDataGUID,// GUID of data
    LPBYTE                     *ppData,         // (Out) Pointer to allocated data
    LPDWORD                     lpdwDataSize    // (Out) Pointer to data size
);
typedef DWORD (CALLBACK *PFAX_EXT_GET_DATA) (DWORD, FAX_ENUM_DEVICE_ID_SOURCE, LPCWSTR, LPBYTE *, LPDWORD);

//
// Prototype of FaxExtSetData 
// 
DWORD
FaxExtSetData (
    HINSTANCE                   hInst,          // Instance of calling extension
    DWORD                       dwDeviceId,     // Device id (0 = No device)
    FAX_ENUM_DEVICE_ID_SOURCE   DevIdSrc,       // The source of the device id
    LPCWSTR                     lpcwstrDataGUID,// GUID of data
    LPBYTE                      pData,          // Pointer to  data
    DWORD                       dwDataSize      // Data size
);
typedef DWORD (CALLBACK *PFAX_EXT_SET_DATA) (HINSTANCE, DWORD, FAX_ENUM_DEVICE_ID_SOURCE, LPCWSTR, LPBYTE, DWORD);

HRESULT
FaxExtConfigChange (
    DWORD       dwDeviceId,         // The device for which configuration has changed
    LPCWSTR     lpcwstrDataGUID,    // Configuration name
    LPBYTE      lpData,             // New configuration data
    DWORD       dwDataSize          // Size of new configuration data
);
typedef HRESULT (WINAPI *PFAX_EXT_CONFIG_CHANGE) (DWORD, LPCWSTR, LPBYTE, DWORD);

//
// Prototype of FaxExtRegisterForEvents 
//
HANDLE
FaxExtRegisterForEvents (
    HINSTANCE                   hInst,          // Instance of calling extension
    DWORD                       dwDeviceId,     // Device id (0 = No device)
    FAX_ENUM_DEVICE_ID_SOURCE   DevIdSrc,       // The source of the device id
    LPCWSTR                     lpcwstrDataGUID,// GUID of data
    PFAX_EXT_CONFIG_CHANGE      lpConfigChangeCallback
);
typedef HANDLE (CALLBACK *PFAX_EXT_REGISTER_FOR_EVENTS) (HINSTANCE, DWORD, FAX_ENUM_DEVICE_ID_SOURCE, LPCWSTR, PFAX_EXT_CONFIG_CHANGE);

//
// Prototype of FaxExtUnregisterForEvents 
//
DWORD
FaxExtUnregisterForEvents (
    HANDLE      hNotification
);
typedef DWORD (CALLBACK *PFAX_EXT_UNREGISTER_FOR_EVENTS) (HANDLE);

//
// Prototype of FaxExtFreeBuffer
//
VOID
FaxExtFreeBuffer (
    LPVOID lpvBuffer
);
typedef VOID (CALLBACK *PFAX_EXT_FREE_BUFFER) (LPVOID);

//
// The extension should implement and export the following function:
//
HRESULT 
FaxExtInitializeConfig (
    PFAX_EXT_GET_DATA,              // Pointer to FaxExtGetExtensionData in service
    PFAX_EXT_SET_DATA,              // Pointer to FaxExtSetExtensionData in service
    PFAX_EXT_REGISTER_FOR_EVENTS,   // Pointer to FaxExtRegisterForExtensionEvents in service
    PFAX_EXT_UNREGISTER_FOR_EVENTS, // Pointer to FaxExtUnregisterForExtensionEvents in service
    PFAX_EXT_FREE_BUFFER            // Pointer to FaxExtFreeBuffer in service
);
typedef HRESULT (WINAPI *PFAX_EXT_INITIALIZE_CONFIG) (PFAX_EXT_GET_DATA, PFAX_EXT_SET_DATA, PFAX_EXT_REGISTER_FOR_EVENTS, PFAX_EXT_UNREGISTER_FOR_EVENTS, PFAX_EXT_FREE_BUFFER);

#ifdef __cplusplus
}
#endif

#ifdef __BORLANDC__
#pragma option pop /*P_O_Pop*/
#endif

#endif // _FAX_EXT_H_
