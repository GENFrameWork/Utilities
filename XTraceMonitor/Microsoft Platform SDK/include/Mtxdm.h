//  Copyright (C) 1995-1999 Microsoft Corporation.  All rights reserved.

#ifndef __MTXDM_H__
#define __MTXDM_H__

#ifdef __BORLANDC__
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#endif
// mtxdm.h
// Defines legacy mtxdm startup interface, remove asap, when all dispensers stop doing this.
// New stuff is in ccpublic.idl and dispman.idl

#include "comsvcs.h"

#ifdef __cplusplus
extern "C"{
#endif 

//
// GetDispenserManager
// A Dispenser calls this API to get a reference to DispenserManager.
//
__declspec(dllimport) HRESULT __cdecl GetDispenserManager(IDispenserManager**);


#ifdef __cplusplus
}
#endif

#ifdef __BORLANDC__
#pragma option pop /*P_O_Pop*/
#endif

#endif