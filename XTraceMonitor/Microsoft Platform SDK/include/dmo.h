//------------------------------------------------------------------------------
// File: DMO.h
//
// Desc: Headers needed by almost all DMOs.
//
// Copyright (c) 1999 - 2001, Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#ifndef __DMO_H__
#define __DMO_H__

#ifdef __BORLANDC__
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#endif

#include "mediaerr.h"

// When using ATL we get collisions on Lock, so in this case rename
// IMediaObject::Lock to IMediaObject::DMOLock

#ifdef FIX_LOCK_NAME
#define Lock DMOLock
#endif
#include "mediaobj.h"
#ifdef FIX_LOCK_NAME
#undef Lock
#endif
#include "dmoreg.h"
#include "dmort.h"

#ifdef __BORLANDC__
#pragma option pop /*P_O_Pop*/
#endif

#endif //__DMO_H__
