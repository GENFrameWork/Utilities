/*++

  Copyright (c) Microsoft Corporation. All rights reserved.
  Copyright (c) 1996-1999 Highground Systems

  Module Name:

        NtmsMli.h

  Abstract:

        This header contains the definitions of the 
        MediaLabelInfo structure. Media label libraries use
        this structure to pass information to RSM to use to
        identify media. 

        The name of this file reflects it's history.  RSM 
        began its life as NTMS.


--*/

#ifndef _INCL_NTMSMLI_H_
#define _INCL_NTMSMLI_H_

#ifdef __BORLANDC__
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#endif

#if _MSC_VER > 1000
#pragma once
#endif

#define NTMSMLI_MAXTYPE     64
#define NTMSMLI_MAXIDSIZE   256
#define NTMSMLI_MAXAPPDESCR 256

#ifndef NTMS_NOREDEF

typedef struct
{
        WCHAR   LabelType[NTMSMLI_MAXTYPE];
        DWORD   LabelIDSize;
        BYTE    LabelID[NTMSMLI_MAXIDSIZE];
        WCHAR   LabelAppDescr[NTMSMLI_MAXAPPDESCR];
} MediaLabelInfo, *pMediaLabelInfo;

#endif  // NTMS_NOREDEF

typedef DWORD ( WINAPI *MAXMEDIALABEL) (DWORD * const pMaxSize);
typedef DWORD ( WINAPI *CLAIMMEDIALABEL) (const BYTE * const pBuffer, const DWORD nBufferSize,
                                  MediaLabelInfo * const pLabelInfo);
typedef DWORD ( WINAPI *CLAIMMEDIALABELEX) (const BYTE * const pBuffer, const DWORD nBufferSize,
                                  MediaLabelInfo * const pLabelInfo, GUID * LabelGuid);

#ifdef __BORLANDC__
#pragma option pop /*P_O_Pop*/
#endif

#endif
