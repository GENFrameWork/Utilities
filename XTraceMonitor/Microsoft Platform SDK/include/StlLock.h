//***************************************************************************
//
//  Copyright © Microsoft Corporation.  All rights reserved.
//
//  stllock.h
//
//  Purpose: Critical section class
//
//***************************************************************************

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _STLLOCK_H_
#define _STLLOCK_H_

#ifdef __BORLANDC__
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#endif


class CCritSec : public CRITICAL_SECTION
{
public:
    CCritSec() 
    {
        InitializeCriticalSection(this);
    }
    ~CCritSec()
    {
        DeleteCriticalSection(this);
    }
    void Enter()
    {
        EnterCriticalSection(this);
    }
    void Leave()
    {
        LeaveCriticalSection(this);
    }
};

#ifdef __BORLANDC__
#pragma option pop /*P_O_Pop*/
#endif

#endif

