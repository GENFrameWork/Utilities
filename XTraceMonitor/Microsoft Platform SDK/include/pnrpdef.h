/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

Module Name:

    pnrpdef.h

Abstract:

    Common PNRP related types

--*/

#ifndef __PNRPDEF__
#define __PNRPDEF__
#ifdef __BORLANDC__
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#endif

#pragma once

#define PNRP_MAX_ENDPOINT_ADDRESSES   (4)

//
// Scope
//
#define     WSZ_SCOPE_GLOBAL            L"GLOBAL"
#define     WSZ_SCOPE_SITELOCAL         L"SITELOCAL"
#define     WSZ_SCOPE_LINKLOCAL         L"LINKLOCAL"

typedef enum _PNRP_SCOPE 
{
    PNRP_SCOPE_ANY                  = 0,    //  Any
    PNRP_GLOBAL_SCOPE               = 1,    //  global
    PNRP_SITE_LOCAL_SCOPE           = 2,    //  site local
    PNRP_LINK_LOCAL_SCOPE           = 3     //  link local
} PNRP_SCOPE, *PPNRP_SCOPE;


//
// Cloud state
//

typedef enum _PNRP_CLOUD_STATE 
{
    PNRP_CLOUD_STATE_VIRTUAL       = 0,    //  Not initialized
    PNRP_CLOUD_STATE_SYNCHRONISING = 1,    //  The cache is initializing
    PNRP_CLOUD_STATE_ACTIVE        = 2,    //  Cloud is active
    PNRP_CLOUD_STATE_DEAD          = 3,    //  Initialized but has had a problem
    PNRP_CLOUD_STATE_DISABLED      = 4,    //  Cloud is not disbaled in registery
    PNRP_CLOUD_STATE_NO_NET        = 5,    //  Was active, but now has lost access to net
    PNRP_CLOUD_STATE_ALONE         = 6     //  Cloud is in standalone mode
} PNRP_CLOUD_STATE;

//
// Cloud Flags values
//  These should be powers of 2 so they can be ORed together
//

typedef enum _PNRP_CLOUD_FLAGS
{
    PNRP_CLOUD_NO_FLAGS            = 0,    //  
    PNRP_CLOUD_NAME_LOCAL          = 1,    //  Name not valid on other computers
} PNRP_CLOUD_FLAGS;

//
// Registered name state
//

typedef enum _PNRP_REGISTERED_ID_STATE
{
    PNRP_REGISTERED_ID_STATE_OK      = 1,    //  Id is active in cloud
    PNRP_REGISTERED_ID_STATE_PROBLEM = 2     //  Id is no longer registered in cloud

} PNRP_REGISTERED_ID_STATE;

//
// Resolve criteria
//

typedef enum _PNRP_RESOLVE_CRITERIA
{
    PNRP_RESOLVE_CRITERIA_DEFAULT           = 0,            // Default = PNRP_RESOLVE_CRITERIA_NON_CURRENT_PROCESS_PEER_NAME

    PNRP_RESOLVE_CRITERIA_REMOTE_PEER_NAME  = 1,            // match first 128 bits (remote node)

    PNRP_RESOLVE_CRITERIA_NEAREST_REMOTE_PEER_NAME = 2,     // match first 128 bits, and close to top 64 bits
                                                            // of the second 128 bits (remote node)

    PNRP_RESOLVE_CRITERIA_NON_CURRENT_PROCESS_PEER_NAME = 3,//  match first 128 bits (not in the current process) 

    PNRP_RESOLVE_CRITERIA_NEAREST_NON_CURRENT_PROCESS_PEER_NAME = 4, // match first 128 bits, and close to top 64 bits
                                                            // of the second 128 bits (not in the current process)   

    PNRP_RESOLVE_CRITERIA_ANY_PEER_NAME     = 5,            // match first 128 bits (any node)

    PNRP_RESOLVE_CRITERIA_NEAREST_PEER_NAME = 6             // match first 128 bits, and close to top 64 bits
                                                            // of the second 128 bits (any node)   


} PNRP_RESOLVE_CRITERIA;

//
// PNRP Cloud identification
//

typedef struct _PNRP_CLOUD_ID 
{
    INT         AddressFamily;          // should be AF_INET6
    PNRP_SCOPE  Scope;                  // Global, site, or link
    ULONG       ScopeId;                // specifies interface
} PNRP_CLOUD_ID, *PPNRP_CLOUD_ID;

#ifdef __BORLANDC__
#pragma option pop /*P_O_Pop*/
#endif

#endif //__PNRPDEF__
