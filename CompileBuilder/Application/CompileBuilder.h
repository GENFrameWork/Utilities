/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CompileBuilder.h
* 
* @class      COMPILEBUILDER
* @brief      Compile Builder Utility
* @ingroup    APPLICATION
* 
* @copyright  GEN Group. All rights reserved.
* 
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
* 
* --------------------------------------------------------------------------------------------------------------------*/

#ifndef _COMPILEBUILDER_H_
#define _COMPILEBUILDER_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XDateTime.h"
#include "XFSMachine.h"
#include "XString.h"
#include "XScheduler.h"

#include "DIOStream.h"
#include "DIOURL.h"

#include "Script_XEvent.h"
#include "Script_Lib_Console.h"
#include "Script_Lib_Log.h"
#include "Script_Lib_System.h"
#include "Script_Lib_Math.h"
#include "Script_Lib_Path.h"
#include "Script_Lib_Rand.h"
#include "Script_Lib_String.h"
#include "Script_Lib_Timer.h"
#include "Script_Lib_Process.h"
#include "Script_Lib_Dir.h"

#include "APPConsole.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum CBUILDERXFSMEVENTS
{
  CBUILDER_XFSMEVENT_NONE                = 0 ,
  CBUILDER_XFSMEVENT_INI                     ,
  CBUILDER_XFSMEVENT_UPDATE                  ,
  CBUILDER_XFSMEVENT_END                     ,

  CBUILDER_LASTEVENT
};


enum CBUILDERXFSMSTATES
{
  CBUILDER_XFSMSTATE_NONE                = 0 ,
  CBUILDER_XFSMSTATE_INI                     ,
  CBUILDER_XFSMSTATE_UPDATE                  ,
  CBUILDER_XFSMSTATE_END                     ,

  CBUILDER_LASTSTATE
};


enum CBUILDERTASKID
{
  CBUILDERTASKID_UNKNOWN                 = 0 ,
  CBUILDERTASKID_CHECKMEMORYSTATUS           ,
};


#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       __L("CompileBuilder")
#define APPLICATION_NAMEFILE                      __L("compilebuilder")

#define APPLICATION_OWNER                         __L("GEN Group")

#define APPLICATION_YEAROFCREATION                2023

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XTIME;
class XTIMER;
class XRAND;
class XTHREAD;
class XDIR;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class DIOCHECKTCPIPCONNECTIONS;
class DIOCHECKINTERNETCONNECTION;
class DIOSCRAPERWEBPUBLICIP;
class DIOSCRAPERWEBGEOLOCATIONIP;
class DIOSCRAPERWEBUSERAGENTID;
class GRPBITMAPSECUENCE;
class GRPXEVENT;
class CBUILDER_CFG;
class SCRIPT;


class CBUILDER : public APPCONSOLE, public XFSMACHINE
{
  public:
                                    CBUILDER                                ();
    virtual                        ~CBUILDER                                ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();

    bool                            LoadScriptAndRun                        ();

    bool                            Show_AppStatus                          ();    
    bool                            Show_AllStatus                          ();

  private:

    void                            Clean                                   ();

    static void                     AdjustLibraries                         (SCRIPT* script);

    void                            HandleEvent_Script                      (SCRIPT_XEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);

    XTIMER*                         xtimerupdateconsole;
    XTIMER*                         xtimerscriptrun;

    XMUTEX*                         xmutexshowallstatus;

    SCRIPT*                         script;

};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif
