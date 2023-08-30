/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CompileBuilder.cpp
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "CompileBuilder.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "Version.h"

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
#include "XTranslation_GEN.h"
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

#include "APPLog.h"

#include "Script_Language_G.h"
#include "Script_Language_Lua.h"
#include "Script_Language_Javascript.h"
#include "Script_Lib_CFG.h"

#include "CompileBuilder_CFG.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE
 
APPLICATIONCREATEINSTANCE(CBUILDER, scripts)

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CBUILDER::CBUILDER()
* @brief      Constructor
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CBUILDER::CBUILDER() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CBUILDER::~CBUILDER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CBUILDER::~CBUILDER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CBUILDER::InitFSMachine()
* @brief      InitFSMachine
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CBUILDER::InitFSMachine()
{
  if(!AddState( CBUILDER_XFSMSTATE_NONE            ,
                CBUILDER_XFSMEVENT_INI             , CBUILDER_XFSMSTATE_INI           ,
                CBUILDER_XFSMEVENT_END             , CBUILDER_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( CBUILDER_XFSMSTATE_INI             ,
                CBUILDER_XFSMEVENT_UPDATE          , CBUILDER_XFSMSTATE_UPDATE        ,                
                CBUILDER_XFSMEVENT_END             , CBUILDER_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( CBUILDER_XFSMSTATE_UPDATE          ,               
                CBUILDER_XFSMEVENT_END             , CBUILDER_XFSMSTATE_END           ,                 
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( CBUILDER_XFSMSTATE_END             ,
                CBUILDER_XFSMEVENT_NONE            , CBUILDER_XFSMSTATE_NONE          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CBUILDER::AppProc_Ini()
* @brief      AppProc_Ini
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CBUILDER::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  XPATH   xpathsection;
  XPATH   xpath;
  bool    status;

  //-------------------------------------------------------------------------------------------------

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  GetApplicationName()->Set(APPLICATION_NAMEAPP);

  //--------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME((*GetApplicationName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  //--------------------------------------------------------------------------------------------------

  XPATH   pathassets;
  XSTRING ext;

  if(GetExecParams())
    {
      XSTRING* param = (XSTRING*)GetExecParams()->Get(0);
      if(param) 
        {
          pathassets = param->Get();
          pathassets.Slash_Add();
          pathassets += APPLICATION_NAMEFILE;
          pathassets.Slash_Add();
          pathassets += APPDEFAULT_DIRECTORY_ROOT;
        }
    }

  GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT)->xpath->Set(pathassets);
//GEN_XPATHSMANAGER.AdjustRootPathDefault(APPDEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_SCRIPTS, APPDEFAULT_DIRECTORY_SCRIPTS);

  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------

  xmutexshowallstatus = GEN_XFACTORY.Create_Mutex();
  if(!xmutexshowallstatus) return false;

  //--------------------------------------------------------------------------------------

  APP_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Application ROOT path: %s"),  GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT)->xpath->Get());

  //--------------------------------------------------------------------------------------

    
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), APPLICATION_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }
    
  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA);

  //--------------------------------------------------------------------------------------

  if(!APP_CFG.IsSilentMode())
    {
      Show_Header(true);
    }

  //--------------------------------------------------------------------------------------

  if(APP_CFG.Log_IsActive())
    {
      string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Activando sistema LOG"));
      if(!APP_CFG.IsSilentMode())
        {
          console->PrintMessage(string.Get(), 1, true, false);
        }

      status = APP_LOG.Ini(&APP_CFG, APPLICATION_NAMEFILE , APPLICATION_VERSION
                                                          , APPLICATION_SUBVERSION
                                                          , APPLICATION_SUBVERSIONERR);

      stringresult.Format((status)?__L("Ok."):__L("ERROR!"));
      if(!APP_CFG.IsSilentMode())
        {
          console->PrintMessage(stringresult.Get(), 0, false, true);
        }

      XSTRING SO_ID;
      status = GEN_XSYSTEM.GetOperativeSystemID(SO_ID);

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%s"),  GEN_VERSION.GetAppVersion()->Get());   
      XTRACE_PRINTSTATUS(__L("S.O. version"), SO_ID.Get()); 

      stringresult.Format((status)?__L("Ok."):__L("ERROR!"));
      APP_LOG_ENTRY(((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), APP_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());
           
      APP_LOG_ENTRY(((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), APP_CFG_LOG_SECTIONID_INITIATION, false,  __L("Identificacion SO: %s"), SO_ID.Get());

      XDWORD total = 0;
      XDWORD free  = 0;

      GEN_XSYSTEM.GetMemoryInfo(total,free);

      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_INITIATION, false, XT_L(XTRANSLATION_GEN_ID_APPLOG_TOTALMEMORY), total, free, GEN_XSYSTEM.GetFreeMemoryPercent());
    }

  //--------------------------------------------------------------------------------------

  SetEvent(CBUILDER_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CBUILDER::AppProc_FirstUpdate()
* @brief      AppProc_FirstUpdate
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CBUILDER::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  xtimerupdateconsole = GEN_XFACTORY.CreateTimer();
  if(!xtimerupdateconsole) return false;

  xtimerscriptrun = GEN_XFACTORY.CreateTimer();
  if(!xtimerscriptrun) return false;

  //--------------------------------------------------------------------------------------

  SubscribeEvent(SCRIPT_XEVENT_TYPE_ERROR, this);
  SubscribeEvent(SCRIPT_XEVENT_TYPE_BREAK, this);

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CBUILDER::AppProc_Update()
* @brief      AppProc_Update
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CBUILDER::AppProc_Update()
{
  if(GetEvent()==CBUILDER_XFSMEVENT_NONE) // Not new event
    {
      switch(GetCurrentState())
        {
          case CBUILDER_XFSMSTATE_NONE        : break;

          case CBUILDER_XFSMSTATE_INI         : break;

          case CBUILDER_XFSMSTATE_UPDATE      : break;

          case CBUILDER_XFSMSTATE_END         : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<CBUILDER_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case CBUILDER_XFSMSTATE_NONE    : break;

              case CBUILDER_XFSMSTATE_INI     : SetEvent(CBUILDER_XFSMEVENT_UPDATE);                                                
                                                break;

              case CBUILDER_XFSMSTATE_UPDATE  : { if(!APP_CFG.IsSilentMode())                                             
                                                    {
                                                      Show_AllStatus();
                                                    }
                                                   else
                                                    {
                                                      Show_BlankLine();
                                                    }        
                                                    
                                                  if(xtimerglobal)
                                                    {
                                                      xtimerglobal->Reset();
                                                    }

                                                  XVECTOR<XSTRING*>* listscripts = APP_CFG.Scripts_GetAll();
                                                  if(listscripts)
                                                    {                                                                                                    
                                                      for(XDWORD c=0; c<listscripts->GetSize(); c++)
                                                        {  
                                                          XSTRING* namescript = listscripts->Get(c);    
                                                          if(namescript)
                                                            {
                                                              if(!namescript->IsEmpty())
                                                                {
                                                                  SCRIPT* script = CreateScripToExec(namescript->Get());                                                  
                                                                  if(script)
                                                                    {                                                  
                                                                      XSTRING measurestr;

                                                                      xtimerscriptrun->Reset();
                                                                  
                                                                      script->Run();
                                                                        
                                                                      xtimerscriptrun->GetMeasureString(measurestr, true);
  
                                                                      XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("[%s] Ejecucion en %s."), namescript->Get(), measurestr.Get());    

                                                                      DeleteScripToExec(script);                                                   
                                                                    }
                                                                }
                                                            } 
                                                        }
                                                    }
                                                 
                                                  Show_BlankLine();
                                                  
                                                  if(xtimerglobal)
                                                    { 
                                                      XSTRING string;
                                                      XSTRING string2;

                                                      string  = __L("Tiempo de funcionamiento");
                                                      xtimerglobal->GetMeasureString(string2, true);
                                                      Show_Line(string, string2);                                                      
                                                    }

                                                  Show_BlankLine();
                                                  Show_BlankLine();
                                                  
                                                  SetExitType(APPBASE_EXITTYPE_BY_APPLICATION);  
                                                  SetEvent(CBUILDER_XFSMEVENT_END); 

                                                  PrintExitMessage_Active(false);                                                
                                                }
                                                break;

              case CBUILDER_XFSMSTATE_END     : 
                                                break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CBUILDER::AppProc_End()
* @brief      AppProc_End
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CBUILDER::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  UnSubscribeEvent(SCRIPT_XEVENT_TYPE_ERROR, this);
  UnSubscribeEvent(SCRIPT_XEVENT_TYPE_BREAK, this);

  //--------------------------------------------------------------------------------------

  SetEvent(CBUILDER_XFSMEVENT_END);

  //--------------------------------------------------------------------------------------

  if(xmutexshowallstatus)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexshowallstatus);
      xmutexshowallstatus = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(xtimerscriptrun)
    {
      GEN_XFACTORY.DeleteTimer(xtimerscriptrun);
      xtimerscriptrun = NULL;
    }

  if(xtimerupdateconsole)
    {
      GEN_XFACTORY.DeleteTimer(xtimerupdateconsole);
      xtimerupdateconsole = NULL;
    }

  //--------------------------------------------------------------------------------------

  APP_LOG.DelInstance();

  //--------------------------------------------------------------------------------------

  APP_CFG.DelInstance();

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CBUILDER::CreateScripToExec(XCHAR* namefilescript)
* @brief      CreateScripToExec
* @ingroup    APPLICATION
* 
* @param[in]  namefilescript : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT* CBUILDER::CreateScripToExec(XCHAR* namefilescript)
{  
  SCRIPT* script = SCRIPT::Create(namefilescript);

  if(!script) 
    {
      return NULL;
    }

  SCRIPT_SET_LIB_CFG(APP_CFG);
  
  XPATH xpath;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_SCRIPTS, xpath);
  xpath.Slash_Add();
  xpath += namefilescript;

  if(!script->Load(xpath))
    {
      delete script;
      return NULL;    
    }

  return script;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CBUILDER::DeleteScripToExec()
* @brief      DeleteScripToExec
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CBUILDER::DeleteScripToExec(SCRIPT* script)
{
  if(!script) return false;

  delete script;
  script = NULL;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CBUILDER::Show_AppStatus()
* @brief      Show_AppStatus
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CBUILDER::Show_AppStatus()
{
  XSTRING string;
  XSTRING string2;

  XDWORD  total;
  XDWORD  free;

  GEN_XSYSTEM.GetMemoryInfo(total,free);

  string  = __L("Memoria total");
  string2.Format(__L("%d Kb, libre %d Kb (el %d%%%%)"), total, free, GEN_XSYSTEM.GetFreeMemoryPercent());
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

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CBUILDER::Show_AllStatus()
* @brief      Show_AllStatus
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CBUILDER::Show_AllStatus()
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
* @fn         void CBUILDER::HandleEvent_Script(SCRIPT_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* @param[in]  event : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CBUILDER::HandleEvent_Script(SCRIPT_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case SCRIPT_XEVENT_TYPE_ERROR     : XTRACE_PRINTCOLOR(4,__L("Script ERROR [%d]: %s line %d -> \"%s\""), event->GetError(), event->GetErrorText()->Get(), event->GetNLine(), event->GetCurrentToken()->Get());
                                          break;

      case SCRIPT_XEVENT_TYPE_BREAK     : XTRACE_PRINTCOLOR(4,__L("Script BREAK: line %d -> \"%s\""), event->GetNLine(), event->GetCurrentToken()->Get());
                                          break;

    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CBUILDER::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* @param[in]  xevent : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CBUILDER::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
       case XEVENT_TYPE_SCRIPT      : { SCRIPT_XEVENT* event = (SCRIPT_XEVENT*)xevent;
                                        if(!event) return;

                                        HandleEvent_Script(event);
                                      }
                                      break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CBUILDER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CBUILDER::Clean()
{
  xtimerupdateconsole         = NULL;
  xtimerscriptrun             = NULL;

  xmutexshowallstatus         = NULL;  
  
  script                      = NULL;
}


#pragma endregion

