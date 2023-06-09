/**************************************************************************
*
* Copyright (c) 2000 Microsoft Corporation
*
* Module Name:
*
*   CachedBitmap class definition
*
* Abstract:
*
*   GDI+ CachedBitmap is a representation of an accelerated drawing
*   that has restrictions on what operations are allowed in order
*   to accelerate the drawing to the destination.
*
*   Look for class definition in GdiplusHeaders.h
*
**************************************************************************/

#ifndef _GDIPLUSCACHEDBITMAP_H
#define _GDIPLUSCACHEDBITMAP_H

#ifdef __BORLANDC__
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#endif

inline 
CachedBitmap::CachedBitmap(
    IN Bitmap *bitmap, 
    IN Graphics *graphics)
{
    nativeCachedBitmap = NULL;    

    lastResult = DllExports::GdipCreateCachedBitmap(
        (GpBitmap *)bitmap->nativeImage,
        graphics->nativeGraphics,
        &nativeCachedBitmap
    );
}

inline 
CachedBitmap::~CachedBitmap()
{
    DllExports::GdipDeleteCachedBitmap(nativeCachedBitmap);
}

inline Status 
CachedBitmap::GetLastStatus() const 
{
    Status lastStatus = lastResult;
    lastResult = Ok;    
    return (lastStatus);
}

#ifdef __BORLANDC__
#pragma option pop /*P_O_Pop*/
#endif

#endif

