/**************************************************************************\
*
* Copyright (c) 1998-2001, Microsoft Corp.  All Rights Reserved.
*
* Module Name:
*
*   GdiplusBase.h
*
* Abstract:
*
*   GDI+ base memory allocation class
*
\**************************************************************************/

#ifndef _GDIPLUSBASE_H
#define _GDIPLUSBASE_H

#ifdef __BORLANDC__
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#endif

class GdiplusBase
{
public:
    void (operator delete)(void* in_pVoid)
    {
       DllExports::GdipFree(in_pVoid);
    }
    void* (operator new)(size_t in_size)
    {
       return DllExports::GdipAlloc(in_size);
    }
    void (operator delete[])(void* in_pVoid)
    {
       DllExports::GdipFree(in_pVoid);
    }
    void* (operator new[])(size_t in_size)
    {
       return DllExports::GdipAlloc(in_size);
    }
};

#ifdef __BORLANDC__
#pragma option pop /*P_O_Pop*/
#endif

#endif 

