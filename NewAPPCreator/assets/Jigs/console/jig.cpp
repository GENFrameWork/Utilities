/**-------------------------------------------------------------------------------------------------------------------
*
* @file       #@[jig].cpp
*
* @class      #*[jig]
* @brief      #@[jig] Main Module
* @ingroup    #*[jig]
*
* @copyright  #=[jig]. All right reserved.
*
*---------------------------------------------------------------------------------------------------------------------*/


/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "XPath.h"
#include "XDateTime.h"
#include "XTimer.h"
#include "XFactory.h"
#include "XRand.h"
#include "XDir.h"
#include "XString.h"
#include "XSystem.h"
#include "XLog.h"
#include "XConsole.h"
#include "XFileTXT.h"
#include "XFileCSV.h"
#include "XFileXML.h"
#include "XTranslation.h"
#include "XScheduler.h"
#include "XScheduler_XEvent.h"
#include "XConsole.h"
#include "XThread.h"
#include "XTrace.h"
#include "XObserver.h"

#include "HashMD5.h"

#include "DIOFactory.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamIPLocalEnumDevices.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamTCPIP.h"

#include "DIOWebClient_XEvent.h"
#include "DIOWebClient.h"

#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"

#include "DIOScraperWeb.h"
#include "DIOScraperWebPublicIP.h"
#include "DIOScraperWebGeolocationIP.h"
#include "DIOScraperWebUserAgentID.h"

#include "APPFlowLog.h"

#include "#@[jig]_CFG.h"

#include "#@[jig].h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

 APPLICATIONCREATEINSTANCE(#*[jig], #![jig])

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         #*[jig]::#*[jig]
* @brief      Constructor
* @ingroup    [#*[jig]]
*
* @param
* @return
*
*---------------------------------------------------------------------------------------------------------------------*/
#*[jig]::#*[jig]() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         #*[jig]::~#*[jig]
* @brief      Destructor
* @ingroup    [#*[jig]]
*
* @param
* @return
*
*---------------------------------------------------------------------------------------------------------------------*/
#*[jig]::~#*[jig]()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         #*[jig]::InitFSMachine
* @brief      Init FS Machine
* @ingroup    [#*[jig]]  
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool #*[jig]::InitFSMachine()
{
  if(!AddState( #*[jig]_XFSMSTATE_NONE            ,
                #*[jig]_XFSMEVENT_INI             , #*[jig]_XFSMSTATE_INI       ,
                #*[jig]_XFSMEVENT_END             , #*[jig]_XFSMSTATE_END       ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( #*[jig]_XFSMSTATE_INI             ,
                #*[jig]_XFSMEVENT_NONE            , #*[jig]_XFSMSTATE_NONE      ,
                #*[jig]_XFSMEVENT_UPDATE          , #*[jig]_XFSMSTATE_UPDATE    ,
                #*[jig]_XFSMEVENT_END             , #*[jig]_XFSMSTATE_END       ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  if(!AddState( #*[jig]_XFSMSTATE_UPDATE          ,
                #*[jig]_XFSMEVENT_NONE            , #*[jig]_XFSMSTATE_NONE      ,
                #*[jig]_XFSMEVENT_END             , #*[jig]_XFSMSTATE_END       ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( #*[jig]_XFSMSTATE_END             ,
                #*[jig]_XFSMEVENT_NONE            , #*[jig]_XFSMSTATE_NONE      ,
                #*[jig]_XFSMEVENT_INI             , #*[jig]_XFSMSTATE_INI       ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         #*[jig]::AppProc_Ini
* @brief      Ini Application
* @ingroup    [#*[jig]]
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool #*[jig]::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  XPATH   xpathsection;
  XPATH   xpath;
  bool    status;

  //-------------------------------------------------------------------------------------------------

  Application_GetName()->Set(APPLICATION_NAMEAPP);

  //--------------------------------------------------------------------------------------------------

  ACTIVATEXTHREADGROUP(XTHREADGROUPID_SCHEDULER);
  ACTIVATEXTHREADGROUP(XTHREADGROUPID_DIOSTREAM);

  //--------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME((*Application_GetName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  //--------------------------------------------------------------------------------------------------

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPFLOW_DEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_#*[jig], APPFLOW_DEFAULT_DIRECTORY_#*[jig]);

  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------

  xmutexshowallstatus = GEN_XFACTORY.Create_Mutex();
  if(!xmutexshowallstatus) return false;

  //--------------------------------------------------------------------------------------

  APPFLOW_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Application ROOT path: %s"),  GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT)->xpath->Get());

  //--------------------------------------------------------------------------------------

  /*
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), APPLICATION_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }
  */

  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA);

  //--------------------------------------------------------------------------------------

  //console->Clear();
  Show_Header(true);

  //--------------------------------------------------------------------------------------

  if(APPFLOW_CFG.Log_IsActive())
    {
      string.Format(APPFLOWCONSOLE_DEFAULT_MESSAGEMASK, __L("Activating LOG system"));
      console->PrintMessage(string.Get(), 1, true, false);

      status = APPFLOW_LOG.Ini(&APPFLOW_CFG , APPLICATION_NAMEFILE 
                                            , APPLICATION_VERSION
                                            , APPLICATION_SUBVERSION
                                            , APPLICATION_SUBVERSIONERR);

      stringresult.Format((status)?__L("Ok."):__L("ERROR!"));
      console->PrintMessage(stringresult.Get(), 0, false, true);
    }

  //--------------------------------------------------------------------------------------

  SetEvent(#*[jig]_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         #*[jig]::AppProc_FirstUpdate
* @brief      First Update
* @ingroup    [#*[jig]]
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool #*[jig]::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  xtimerupdateconsole = GEN_XFACTORY.CreateTimer();
  if(!xtimerupdateconsole) return false;
  
  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         #*[jig]::AppProc_Update
* @brief      Update Application
* @ingroup    [#*[jig]]
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool #*[jig]::AppProc_Update()
{
  if(GetEvent()==#*[jig]_XFSMEVENT_NONE) // Not new event
    {
      switch(GetCurrentState())
        {
          case #*[jig]_XFSMSTATE_NONE       : break;

          case #*[jig]_XFSMSTATE_INI        : SetEvent(#*[jig]_XFSMEVENT_UPDATE);
                                              break;

          case #*[jig]_XFSMSTATE_UPDATE     : if(GetExitType() == APPFLOWBASE_EXITTYPE_UNKNOWN)
                                                {
                                                  if(xtimerupdateconsole)
                                                    {
                                                      if(xtimerupdateconsole->GetMeasureSeconds() >= 1)
                                                        {
                                                          Show_AllStatus();
                                                          xtimerupdateconsole->Reset();
                                                        }


                                                      if(console->KBHit())
                                                        {
                                                          int key = console->GetChar();
                                                          KeyValidSecuences(key);
                                                        }
                                                    }
                                                }
                                              break;

          case #*[jig]_XFSMSTATE_END        : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<#*[jig]_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case #*[jig]_XFSMSTATE_NONE   : break;

              case #*[jig]_XFSMSTATE_INI    : break;

              case #*[jig]_XFSMSTATE_UPDATE : break;

              case #*[jig]_XFSMSTATE_END    : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         #*[jig]::AppProc_End
* @brief      End Application
* @ingroup    [#*[jig]]  
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool #*[jig]::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetEvent(#*[jig]_XFSMEVENT_END);

  //--------------------------------------------------------------------------------------

  if(xmutexshowallstatus)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexshowallstatus);
      xmutexshowallstatus = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(xtimerupdateconsole)
    {
      GEN_XFACTORY.DeleteTimer(xtimerupdateconsole);
      xtimerupdateconsole = NULL;
    }

  //--------------------------------------------------------------------------------------

  APPFLOW_LOG.DelInstance();

  //--------------------------------------------------------------------------------------

  APPFLOW_CFG.DelInstance();

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool #*[jig]::KeyValidSecuences(int key)
* @brief      KeyValidSecuences
* @ingroup    [#*[jig]]
*
* @param[in]  key :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool #*[jig]::KeyValidSecuences(int key)
{
  XCHAR character = (XCHAR)key;

  if((character<32) || (character>127)) character = __C('?');
  APPFLOW_LOG_ENTRY(XLOGLEVEL_WARNING, APPFLOW_CFG_LOG_SECTIONID_STATUSAPP, false, __L("Key pressed: 0x%02X [%c]"), key, character);

  console->Printf(__L("\r    \r"));

  switch(key)
    {
      case 0x1B : // ESC Exit application
                  SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                  break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool #*[jig]::Show_Line(XSTRING& string, XSTRING& string2, int tab, bool linefeed)
* @brief      Show_Line
* @ingroup    [#*[jig]]
*
* @param[in]  string :
* @param[in]  string2 :
* @param[in]  tab :
* @param[in]  linefeed :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool #*[jig]::Show_Line(XSTRING& string, XSTRING& string2, int tab, bool linefeed)
{
  XSTRING line1;
  XSTRING line2;

  console->Format_Message(string.Get(), tab , false, false, line1);
  if(tab)
    {
      int _tab = tab;

      if(_tab<37) _tab = 37;
      line1.AdjustSize(_tab, false, __L(" "));
    }

  console->Format_Message(string2.Get(), 0 , false, linefeed, line2);

  console->Print(line1.Get());
  console->Print(line2.Get());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::Show_Header(bool separator)
* @brief      Show_Header
* @ingroup    [#*[jig]]
*
* @param[in]  separator :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool #*[jig]::Show_Header(bool separator)
{
  XSTRING header;

  if(!console->TipicalHeader_Create(APPLICATION_YEAROFCREATION, APPLICATION_NAMEAPP, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_ENTERPRISE,header)) return false;

  console->Printf(header.Get());
  console->Printf(__L("\n"));
  if(separator) console->Printf(__L("\n"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::Show_AppStatus()
* @brief      Show_AppStatus
* @ingroup    [#*[jig]]
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool #*[jig]::Show_AppStatus()
{
  XSTRING string;
  XSTRING string2;

  XDWORD  total;
  XDWORD  free;

  GEN_XSYSTEM.GetMemoryInfo(total,free);

  string  = __L("Total memory");
  string2.Format(__L("%d Kb, Free %d Kb (el %d%%%%)"), total, free, GEN_XSYSTEM.GetFreeMemoryPercent());
  Show_Line(string, string2);


  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  if(datetime)
    {
      datetime->Read();

      string  = __L("Fecha ");
      datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_TEXTMONTH | XDATETIME_FORMAT_ADDDAYOFWEEK, string2);
      Show_Line(string, string2);

      GEN_XFACTORY.DeleteDateTime(datetime);
    }


  if(xtimerglobal)
    {
      string  = __L("Operating time");
      xtimerglobal->GetMeasureString(string2, true);
      Show_Line(string, string2);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool #*[jig]::Show_AllStatus()
* @brief      Show_AllStatus
* @ingroup    [#*[jig]]
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool #*[jig]::Show_AllStatus()
{
  console->Clear();

  if(xmutexshowallstatus) xmutexshowallstatus->Lock();

  if(Show_Header(false))  console->PrintMessage(__L(""),0, false, true);
  if(Show_AppStatus())    console->PrintMessage(__L(""),0, false, true);

  if(xmutexshowallstatus) xmutexshowallstatus->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         #*[jig]::HandleEvent
* @brief      Handle Events
* @ingroup    [#*[jig]]
*
* @param[]    xevent : event send to control
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void #*[jig]::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void #*[jig]::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    [#*[jig]]
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void #*[jig]::Clean()
{
  xtimerupdateconsole         = NULL;
  xmutexshowallstatus         = NULL;
}



