/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Scripts.h
*
* @class      SCRIPTS
* @brief      Main class
* @ingroup    TEMPLATE
*
* @copyright  GEN Group. All right reserved.
*
*---------------------------------------------------------------------------------------------------------------------*/

#ifndef _SCRIPTS_H_
#define _SCRIPTS_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFSMachine.h"
#include "XString.h"

#include "APPConsole.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum SCRIPTSXFSMEVENTS
{
  SCRIPTS_XFSMEVENT_NONE                = 0 ,
  SCRIPTS_XFSMEVENT_INI                     ,
  SCRIPTS_XFSMEVENT_UPDATE                  ,
  SCRIPTS_XFSMEVENT_END                     ,

  SCRIPTS_LASTEVENT
};


enum SCRIPTSXFSMSTATES
{
  SCRIPTS_XFSMSTATE_NONE                = 0 ,
  SCRIPTS_XFSMSTATE_INI                     ,
  SCRIPTS_XFSMSTATE_UPDATE                  ,
  SCRIPTS_XFSMSTATE_END                     ,

  SCRIPTS_LASTSTATE
};


#define APPLICATION_VERSION                     0
#define APPLICATION_SUBVERSION                  1
#define APPLICATION_SUBVERSIONERR               0

#define APPLICATION_NAMEAPP                     __L("Scripts")
#define APPLICATION_ENTERPRISE                  __L("GEN Group")

#define APPLICATION_NAMEFILE                    __L("scripts")

#define APPLICATION_YEAROFCREATION              2022


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIMER;
class XMUTEX;

class SCRIPTS : public APPCONSOLE, public XFSMACHINE
{
  public:
                                    SCRIPTS                                 ();
    virtual                        ~SCRIPTS                                 ();

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

