/**-------------------------------------------------------------------------------------------------------------------
*
* @file       #@[jig].h
*
* @class      #*[jig]
* @brief      #@[jig] Main Module
* @ingroup    #*[jig]
*
* @copyright  #=[jig]. All right reserved.
*
*---------------------------------------------------------------------------------------------------------------------*/

#ifndef _#*[jig]_H_
#define _#*[jig]_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFSMachine.h"
#include "XString.h"

#include "APPFlowConsole.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum #*[jig]XFSMEVENTS
{
  #*[jig]_XFSMEVENT_NONE                = 0 ,
  #*[jig]_XFSMEVENT_INI                     ,
  #*[jig]_XFSMEVENT_UPDATE                  ,
  #*[jig]_XFSMEVENT_END                     ,

  #*[jig]_LASTEVENT
};


enum #*[jig]XFSMSTATES
{
  #*[jig]_XFSMSTATE_NONE                = 0 ,
  #*[jig]_XFSMSTATE_INI                     ,
  #*[jig]_XFSMSTATE_UPDATE                  ,
  #*[jig]_XFSMSTATE_END                     ,

  #*[jig]_LASTSTATE
};


#define APPLICATION_VERSION                     0
#define APPLICATION_SUBVERSION                  1
#define APPLICATION_SUBVERSIONERR               0

#define APPLICATION_NAMEAPP                     __L("#@[jig]")
#define APPLICATION_ENTERPRISE                  __L("EndoraSoft")

#define APPLICATION_NAMEFILE                    __L("#![jig]")

#define APPLICATION_YEAROFCREATION              #%[jig]


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIMER;
class XMUTEX;

class #*[jig] : public APPFLOWCONSOLE, public XFSMACHINE
{
  public:
                                    #*[jig]                                 ();
    virtual                        ~#*[jig]                                 ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();

    bool                            KeyValidSecuences                       (int key);

    bool                            Show_Line                               (XSTRING& string, XSTRING& string2, int tab = 3, bool linefeed = true);
    bool                            Show_Header                             (bool separator);
    bool                            Show_AppStatus                          ();
    bool                            Show_AllStatus                          ();

  private:

    void                            Clean                                   ();

    void                            HandleEvent                             (XEVENT* xevent);

    XTIMER*                         xtimerupdateconsole;    
    XMUTEX*                         xmutexshowallstatus;
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif

