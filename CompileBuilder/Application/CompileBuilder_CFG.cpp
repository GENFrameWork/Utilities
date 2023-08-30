/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CompileBuilder_CFG.cpp
* 
* @class      COMPILEBUILDER_CFG
* @brief      Compile Builder Utility Config
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

#include "CompileBuilder_CFG.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XLog.h"

#include "CompileBuilder.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

CBUILDER_CFG* CBUILDER_CFG::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CBUILDER_CFG::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CBUILDER_CFG::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CBUILDER_CFG& CBUILDER_CFG::GetInstance(bool ini)
* @brief      GetInstance
* @ingroup    APPLICATION
* 
* @param[in]  ini : 
* 
* @return     CBUILDER_CFG& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CBUILDER_CFG& CBUILDER_CFG::GetInstance(bool ini)
{
  if(!instance) instance = new CBUILDER_CFG(ini?APPLICATION_NAMEFILE:NULL);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CBUILDER_CFG::DelInstance()
* @brief      DelInstance
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CBUILDER_CFG::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CBUILDER_CFG::DoVariableMapping()
* @brief      DoVariableMapping
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CBUILDER_CFG::DoVariableMapping()
{
  if(!APPCFG::DoVariableMapping())
    {
      return false;
    }

  //-----------------------------------------------------
  // GENERAL
  
  AddValue(XFILECFG_VALUETYPE_BOOLEAN	  , CBUILDER_CFG_SECTION_GENERAL  , CBUILDER_CFG_GENERAL_SILENTMODE                                 , &silentmode);
                                                                                                 

  //-----------------------------------------------------
  // SCRIPTS

  AddValueSecuence<XSTRING>(XFILECFG_VALUETYPE_STRING, CBUILDER_CFG_SECTION_SCRIPTS        ,  CBUILDER_CFG_SCRIPTS_SCRIPT                 , __L("%03d"), 3, 999 
                                                                                                                                          , scriptslist
                                                                                                                                          , nscripts                                                                      , __L("Script of compilation")        , APP_CFG_DEFAULT_REMARK_COLUMN);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CBUILDER_CFG::DoDefault()
* @brief      DoDefault
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CBUILDER_CFG::DoDefault()
{
  if(!APPCFG::DoDefault()) 
    {
      return false;
    }

  //------------------------------------------------------------------------------

  GEN_XTRACE_NET_CFG_DEFAULT_01

  silentmode                            = false;
  
  //------------------------------------------------------------------------------

  log_isactive                          = true;
  log_backupisactive                    = true;
  log_backupmaxfiles                    = 10;
  log_backupiscompress                  = true;

  log_activesectionsID.Empty();

  log_activesectionsID                 += APP_CFG_LOG_SECTIONID_INITIATION;
  log_activesectionsID                 += __L(",");
  log_activesectionsID                 += APP_CFG_LOG_SECTIONID_GENERIC;
  log_activesectionsID                 += __L(",");
  log_activesectionsID                 += APP_CFG_LOG_SECTIONID_STATUSAPP;
  log_activesectionsID                 += __L(",");
  log_activesectionsID                 += APP_CFG_LOG_SECTIONID_ENDING;

  log_levelmask                         = XLOGLEVEL_ALL;
  log_maxsize                           = 3000;
  log_reductionpercent                  = 10;

  //------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CBUILDER_CFG::End()
* @brief      End
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CBUILDER_CFG::End()
{
  if(!APPCFG::End())
    {
      return false;
    }

  scriptslist.DeleteContents();
  scriptslist.DeleteAll();
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CBUILDER_CFG::IsSilentMode()
* @brief      IsSilentMode
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CBUILDER_CFG::IsSilentMode()
{
  return silentmode;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<XSTRING*>* CBUILDER_CFG::Scripts_GetAll()
* @brief      Scripts_GetAll
* @ingroup    APPLICATION
* 
* @return     XVECTOR<XSTRING*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* CBUILDER_CFG::Scripts_GetAll()
{
  return &scriptslist;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* CBUILDER_CFG::Scripts_GetScript(int index)
* @brief      Scripts_GetScript
* @ingroup    APPLICATION
* 
* @param[in]  index : 
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* CBUILDER_CFG::Scripts_GetScript(int index)
{
  if(index <  0)                      return NULL;
  if(index >= scriptslist.GetSize())  return NULL;

  return scriptslist.Get(index);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CBUILDER_CFG::CBUILDER_CFG(XCHAR* namefile)
* @brief      Constructor
* @ingroup    APPLICATION
* 
* @param[in]  XCHAR* : 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CBUILDER_CFG::CBUILDER_CFG(XCHAR* namefile) : APPCFG(namefile)
{
  Clean();

  if(namefile)
    {
      Ini<CBUILDER_CFG>();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CBUILDER_CFG::~CBUILDER_CFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CBUILDER_CFG::~CBUILDER_CFG()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CBUILDER_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CBUILDER_CFG::Clean()
{
  nscripts    = 0;  
  silentmode  = false;
}

#pragma endregion
