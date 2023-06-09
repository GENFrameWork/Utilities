/******************************************************************************

Copyright (c) Microsoft Corporation.  All rights reserved.

Module Name:
    errorrep.h

Abstract:
    contains functions used to report errors to Microsoft

******************************************************************************/	

#ifndef __ERRORREP_H__
#define __ERRORREP_H__

#ifdef __BORLANDC__
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#endif

typedef enum tagEFaultRepRetVal
{
    frrvOk = 0,
    frrvOkManifest,
    frrvOkQueued,
    frrvErr,
    frrvErrNoDW,
    frrvErrTimeout,
    frrvLaunchDebugger,
    frrvOkHeadless
} EFaultRepRetVal;

EFaultRepRetVal APIENTRY ReportFault(LPEXCEPTION_POINTERS pep, DWORD dwOpt);

BOOL            APIENTRY AddERExcludedApplicationA(LPCSTR szApplication);
BOOL            APIENTRY AddERExcludedApplicationW(LPCWSTR wszApplication);


typedef EFaultRepRetVal (APIENTRY *pfn_REPORTFAULT)(LPEXCEPTION_POINTERS, DWORD);
typedef EFaultRepRetVal (APIENTRY *pfn_ADDEREXCLUDEDAPPLICATIONA)(LPCSTR);
typedef EFaultRepRetVal (APIENTRY *pfn_ADDEREXCLUDEDAPPLICATIONW)(LPCWSTR);

#ifdef UNICODE
#define AddERExcludedApplication AddERExcludedApplicationW
#define pfn_ADDEREXCLUDEDAPPLICATION pfn_ADDEREXCLUDEDAPPLICATIONW
#else
#define AddERExcludedApplication AddERExcludedApplicationA
#define pfn_ADDEREXCLUDEDAPPLICATION pfn_ADDEREXCLUDEDAPPLICATIONA
#endif

#ifdef __BORLANDC__
#pragma option pop /*P_O_Pop*/
#endif

#endif
