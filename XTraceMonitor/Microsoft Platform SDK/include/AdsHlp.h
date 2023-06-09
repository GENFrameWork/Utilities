//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1996-1999
//
//  File:       oleds.h
//
//  Contents:   Public header file for all oleds client code
//
//----------------------------------------------------------------------------

#ifndef _ADSHLP_
#define _ADSHLP_

#ifdef __BORLANDC__
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#endif

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

HRESULT WINAPI
ADsGetObject(
    LPCWSTR lpszPathName,
    REFIID riid,
    VOID * * ppObject
    );


HRESULT WINAPI
ADsBuildEnumerator(
    IADsContainer *pADsContainer,
    IEnumVARIANT   **ppEnumVariant
    );

HRESULT WINAPI
ADsFreeEnumerator(
    IEnumVARIANT *pEnumVariant
    );

HRESULT WINAPI
ADsEnumerateNext(
    IEnumVARIANT *pEnumVariant,
    ULONG         cElements,
    VARIANT FAR  *pvar,
    ULONG FAR    *pcElementsFetched
    );

HRESULT WINAPI
ADsBuildVarArrayStr(
    LPWSTR * lppPathNames,
    DWORD  dwPathNames,
    VARIANT * pVar
    );

HRESULT WINAPI
ADsBuildVarArrayInt(
    LPDWORD    lpdwObjectTypes,
    DWORD      dwObjectTypes,
    VARIANT * pVar
    );


HRESULT WINAPI
ADsOpenObject(
    LPCWSTR lpszPathName,
    LPCWSTR lpszUserName,
    LPCWSTR lpszPassword,
    DWORD  dwReserved,
    REFIID riid,
    void FAR * FAR * ppObject
    );

//
// Helper functions for extended error support
//

HRESULT WINAPI
ADsGetLastError(
    OUT     LPDWORD lpError,
    OUT     LPWSTR  lpErrorBuf,
    IN      DWORD   dwErrorBufLen,
    OUT     LPWSTR  lpNameBuf,
    IN      DWORD   dwNameBufLen
    );

VOID WINAPI
ADsSetLastError(
    IN  DWORD   dwErr,
    IN  LPCWSTR  pszError,
    IN  LPCWSTR  pszProvider
    );


VOID WINAPI
ADsFreeAllErrorRecords(
    VOID);

LPVOID WINAPI
AllocADsMem(
    DWORD cb
);

BOOL WINAPI
FreeADsMem(
   LPVOID pMem
);

LPVOID WINAPI
ReallocADsMem(
   LPVOID pOldMem,
   DWORD cbOld,
   DWORD cbNew
);

LPWSTR WINAPI
AllocADsStr(
    LPCWSTR pStr
);

BOOL WINAPI
FreeADsStr(
   LPWSTR pStr
);


BOOL WINAPI
ReallocADsStr(
   LPWSTR *ppStr,
   LPWSTR pStr
);


HRESULT WINAPI
ADsEncodeBinaryData (
   PBYTE   pbSrcData,
   DWORD   dwSrcLen,
   LPWSTR  * ppszDestData
   );

HRESULT WINAPI
ADsDecodeBinaryData (
   LPCWSTR szSrcData,
   PBYTE  *ppbDestData,
   ULONG  *pdwDestLen
   );

HRESULT WINAPI
PropVariantToAdsType(
    VARIANT * pVariant,
    DWORD dwNumVariant,
    PADSVALUE *ppAdsValues,
    PDWORD pdwNumValues
    );

HRESULT WINAPI
AdsTypeToPropVariant(
    PADSVALUE pAdsValues,
    DWORD dwNumValues,
    VARIANT * pVariant
    );

void WINAPI
AdsFreeAdsValues(
    PADSVALUE pAdsValues,
    DWORD dwNumValues
    );

//
// Helper routines to convert IADsSecurityDescriptor to a binary
// security descriptor and also to convert a binary SD to 
// IADsSecurityDescriptor.
//
HRESULT WINAPI
BinarySDToSecurityDescriptor(
    PSECURITY_DESCRIPTOR  pSecurityDescriptor,
    VARIANT *pVarsec, 
    LPCWSTR pszServerName,
    LPCWSTR userName,
    LPCWSTR passWord,
    DWORD dwFlags
    );

HRESULT WINAPI
SecurityDescriptorToBinarySD(
    VARIANT vVarSecDes,
    PSECURITY_DESCRIPTOR * ppSecurityDescriptor,
    PDWORD pdwSDLength,
    LPCWSTR pszServerName,
    LPCWSTR userName,
    LPCWSTR passWord,
    DWORD dwFlags
    );

#if DBG

extern LIST_ENTRY ADsMemList ;

extern CRITICAL_SECTION ADsMemCritSect ;

VOID InitADsMem(
    VOID
    ) ;

VOID AssertADsMemLeaks(
    VOID
    ) ;


VOID
DumpMemoryTracker();


#else

#define InitADsMem()
#define AssertADsMemLeaks()

#define DumpMemoryTracker()



#endif


#ifdef __cplusplus
}
#endif

#ifdef __BORLANDC__
#pragma option pop /*P_O_Pop*/
#endif

#endif // _ADSHLP_

