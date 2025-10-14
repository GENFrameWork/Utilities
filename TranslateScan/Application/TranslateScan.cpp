/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       TranslateScan.cpp
* 
* @class      TRANSLATESCAN
* @brief      Translate Scan class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "TranslateScan.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "VersionFrameWork.h"

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
#include "DIOStreamCipher.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamIPLocalEnumDevices.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamTCPIP.h"
#include "DIOCoreProtocol_Connection.h"
#include "DIOWebClient_XEvent.h"
#include "DIOWebClient.h"

#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"

#include "DIOScraperWeb.h"
#include "DIOScraperWebPublicIP.h"
#include "DIOScraperWebGeolocationIP.h"
#include "DIOScraperWebUserAgentID.h"

#include "DIOCoreProtocol_ConnectionsManager_XEvent.h"

#include "APPFlowLog.h"
#include "APPFlowInternetServices.h"
#include "APPFlowExtended.h"

#include "TranslateScan_CFG.h"
#include "TranslateScan_Manager.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

APPLICATIONCREATEINSTANCE(TRANSLATESCAN, translatescan)

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TRANSLATESCAN::TRANSLATESCAN() : XFSMACHINE(0)
* @brief      Constructor
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TRANSLATESCAN::TRANSLATESCAN() : XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TRANSLATESCAN::~TRANSLATESCAN()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TRANSLATESCAN::~TRANSLATESCAN()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TRANSLATESCAN::InitFSMachine()
* @brief      InitFSMachine
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TRANSLATESCAN::InitFSMachine()
{
  if(!AddState( TRANSLATESCAN_XFSMSTATE_NONE            ,
                TRANSLATESCAN_XFSMEVENT_INI             , TRANSLATESCAN_XFSMSTATE_INI             ,
                TRANSLATESCAN_XFSMEVENT_END             , TRANSLATESCAN_XFSMSTATE_END             ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( TRANSLATESCAN_XFSMSTATE_INI             ,
                TRANSLATESCAN_XFSMEVENT_UPDATE          , TRANSLATESCAN_XFSMSTATE_UPDATE          ,
                TRANSLATESCAN_XFSMEVENT_END             , TRANSLATESCAN_XFSMSTATE_END             ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( TRANSLATESCAN_XFSMSTATE_UPDATE          ,                
                TRANSLATESCAN_XFSMEVENT_END             , TRANSLATESCAN_XFSMSTATE_END             ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( TRANSLATESCAN_XFSMSTATE_END             ,
                TRANSLATESCAN_XFSMEVENT_NONE            , TRANSLATESCAN_XFSMSTATE_NONE            ,
                TRANSLATESCAN_XFSMEVENT_INI             , TRANSLATESCAN_XFSMSTATE_INI             ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TRANSLATESCAN::AppProc_Ini()
* @brief      AppProc_Ini
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TRANSLATESCAN::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  XPATH   xpathsection;
  XPATH   xpath;
  bool    status = false;

  //-------------------------------------------------------------------------------------------------

  if(GetExecParams())
    {
      XSTRING* param = (XSTRING*)GetExecParams()->Get(0);
      if(param)
        { 
          operationdir = param->Get();

          if(operationdir.IsEmpty())  
            {
              XDIR* xdir = GEN_XFACTORY.Create_Dir();
              if(xdir)
                {   
                  xdir->GetActual(operationdir);   

                  GEN_XFACTORY.Delete_Dir(xdir);
                }
            }
        }
    }

  Application_GetName()->AddFormat(APPLICATION_NAMEAPP); 

  GEN_SET_VERSION(Application_GetName()->Get(), APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)
  
  //--------------------------------------------------------------------------------------------------

  ACTIVATEXTHREADGROUP(XTHREADGROUPID_SCHEDULER);
  ACTIVATEXTHREADGROUP(XTHREADGROUPID_DIOSTREAM);

  //--------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME((*Application_GetName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  //--------------------------------------------------------------------------------------------------

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPFLOW_DEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------------------

  xmutexshowallstatus = GEN_XFACTORY.Create_Mutex();
  if(!xmutexshowallstatus) return false;

  //--------------------------------------------------------------------------------------------------

  APPFLOW_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------------------

  /*
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), TRANSLATESCAN_LNG_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }
  */

  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_ENG);

  //--------------------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPStart(&APPFLOW_CFG, this);

  //--------------------------------------------------------------------------------------------------

  SetEvent(TRANSLATESCAN_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TRANSLATESCAN::AppProc_FirstUpdate()
* @brief      AppProc_FirstUpdate
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TRANSLATESCAN::AppProc_FirstUpdate()
{
  XSTRING string;
  XSTRING stringresult;
  bool    status = false;

  //--------------------------------------------------------------------------------------------------

  xtimerupdateconsole = GEN_XFACTORY.CreateTimer();
  if(!xtimerupdateconsole) return false;
  
  //--------------------------------------------------------------------------------------------------
  
  manager = new TRANSLATESCAN_MANAGER();
  if(!manager)
    {
      return false;
    }

  //--------------------------------------------------------------------------------------------------
  
  //console->PrintMessage(__L(" "), 0, false, true);
  //console->WaitKey(__L("  Pulsa una tecla para continuar... (%d)"), 1, false, 5);

  //--------------------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TRANSLATESCAN::AppProc_Update()
* @brief      AppProc_Update
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TRANSLATESCAN::AppProc_Update()
{
  if(GetEvent()==TRANSLATESCAN_XFSMEVENT_NONE) // Not new event
    {
      switch(GetCurrentState())
        {
          case TRANSLATESCAN_XFSMSTATE_NONE       : break;

          case TRANSLATESCAN_XFSMSTATE_INI        : break;

          case TRANSLATESCAN_XFSMSTATE_UPDATE     : if(GetExitType() == APPFLOWBASE_EXITTYPE_UNKNOWN)
                                                      {
                                                        if(xtimerupdateconsole)
                                                          {
                                                            if(xtimerupdateconsole->GetMeasureMilliSeconds() >= 100)
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

          case TRANSLATESCAN_XFSMSTATE_END       : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<TRANSLATESCAN_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case TRANSLATESCAN_XFSMSTATE_NONE   : break;

              case TRANSLATESCAN_XFSMSTATE_INI    : SetEvent(TRANSLATESCAN_XFSMEVENT_UPDATE);
                                              break;

              case TRANSLATESCAN_XFSMSTATE_UPDATE : break;

              case TRANSLATESCAN_XFSMSTATE_END    : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TRANSLATESCAN::AppProc_End()
* @brief      AppProc_End
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TRANSLATESCAN::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;


  //--------------------------------------------------------------------------------------

  SetEvent(TRANSLATESCAN_XFSMEVENT_END);
  
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

  if(manager)
    {
      delete manager;
      manager = NULL;
    }

  //--------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPEnd();
  APPFLOW_EXTENDED.DelInstance();  
  APPFLOW_CFG.DelInstance();

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TRANSLATESCAN::KeyValidSecuences(int key)
* @brief      KeyValidSecuences
* @ingroup    APPLICATION
*
* @param[in]  key :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TRANSLATESCAN::KeyValidSecuences(int key)
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

      case 'T'  : { if(manager)
                      {
                        manager->Operation_Remark_Brief(operationdir);
                      }
                  }
                  break;   


      case 'Y'  : { if(manager)
                      {
                        manager->Operation_Remark_InGroup(operationdir);
                      }
                  }
                  break;   


      case 'R'  : { if(manager)
                      {
                        XSTRING brief_origin;
                        XSTRING brief_target;

                        brief_origin = __L("Sender_SMTPConfig");

                        manager->Operation_Remark_Brief_Construct(brief_origin, brief_target);
                      }
                  }
                  break;                 
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TRANSLATESCAN_MANAGER* TRANSLATESCAN::GetManager()
* @brief      get manager
* @ingroup    APPLICATION
* 
* @return     TRANSLATESCAN_MANAGER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TRANSLATESCAN_MANAGER* TRANSLATESCAN::GetManager()
{
  return manager;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TRANSLATESCAN::Show_AllStatus()
* @brief      Show_AllStatus
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TRANSLATESCAN::Show_AllStatus()
{
  if(xmutexshowallstatus) xmutexshowallstatus->Lock();

  APPFLOW_EXTENDED.ShowAll();
  
  if(xmutexshowallstatus) xmutexshowallstatus->UnLock();

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TRANSLATESCAN::HandleEvent
* @brief      Handle Events
* @ingroup
*
* @param[]    xevent : event send to control
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void TRANSLATESCAN::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;
  
  /*
  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_COREPROTOCOLCONNECTIONSMANAGER   : { DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event = (DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT*)xevent;
                                                            if(!event) return;

                                                            HandleEvent_CoreProtocolConnectionManager(event);
                                                          }
                                                          break;
    }
  */
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void TRANSLATESCAN::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void TRANSLATESCAN::Clean()
{
  xtimerupdateconsole         = NULL;
  xmutexshowallstatus         = NULL;

  manager                     = NULL;
}


#pragma endregion

