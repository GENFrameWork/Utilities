/*-------------------------------------------------------*\
 *
 *	Copyright (c) 1999 Microsoft Corporation
 *
 *	Module Name:
 *
 *		wptypes.h
 *
 *	Abstract:
 *
 *		Data types for the Microsoft Web Publishing API.
 *
\*-------------------------------------------------------*/


#ifndef __WPTYPES_H__
#define __WPTYPES_H__

#ifdef __BORLANDC__
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#endif

#ifdef __cplusplus
extern "C" {
#endif


//
//	Site info structures
//

typedef struct tagWPSITEINFOA {

	DWORD dwSize;
	DWORD dwFlags;
	LPSTR lpszSiteName;
	LPSTR lpszSiteURL;

} WPSITEINFOA, *LPWPSITEINFOA;

typedef struct tagWPSITEINFOW {

	DWORD dwSize;
	DWORD dwFlags;
	LPWSTR lpszSiteName;
	LPWSTR lpszSiteURL;

} WPSITEINFOW, *LPWPSITEINFOW;


//
//	Provider info structures
//

typedef struct tagWPPROVINFOA {

	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwPriority;
	LPSTR lpszProviderName;
	LPSTR lpszProviderCLSID;
	LPSTR lpszDllPath;

} WPPROVINFOA, *LPWPPROVINFOA;

typedef struct tagWPPROVINFOW {

	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwPriority;
	LPWSTR lpszProviderName;
	LPWSTR lpszProviderCLSID;
	LPWSTR lpszDllPath;

} WPPROVINFOW, *LPWPPROVINFOW;


#ifdef UNICODE

#define WPSITEINFO				WPSITEINFOW
#define LPWPSITEINFO			LPWPSITEINFOW
#define WPPROVINFO				WPPROVINFOW
#define LPWPPROVINFO			LPWPPROVINFOW

#else

#define WPSITEINFO				WPSITEINFOA
#define LPWPSITEINFO			LPWPSITEINFOA
#define WPPROVINFO				WPPROVINFOA
#define LPWPPROVINFO			LPWPPROVINFOA

#endif


#ifdef __cplusplus
}
#endif


#ifdef __BORLANDC__
#pragma option pop /*P_O_Pop*/
#endif

#endif  // __WPTYPES_H__

