/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Scripts_CFG.cpp
*
* @class      SCRIPTS_CFG
* @brief      Scripts Configuration
* @ingroup    EXAMPLES
*
* @copyright  GEN Group. All right reserved.
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
*---------------------------------------------------------------------------------------------------------------------*/


/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XLog.h"

#include "Scripts.h"

#include "Scripts_CFG.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

SCRIPTS_CFG* SCRIPTS_CFG::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPTS_CFG::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPTS_CFG::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPTS_CFG& SCRIPTS_CFG::GetInstance()
* @brief      GetInstance
* @ingroup
*
* @return     SCRIPTS_CFG& :
*
*---------------------------------------------------------------------------------------------------------------------*/
SCRIPTS_CFG& SCRIPTS_CFG::GetInstance()
{
  if(!instance) instance = new SCRIPTS_CFG(APPLICATION_NAMEFILE);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPTS_CFG::DelInstance()
* @brief      DelInstance
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPTS_CFG::DelInstance()
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
* @fn         bool SCRIPTS_CFG::Default()
* @brief      Default config
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPTS_CFG::Default()
{
  
  //------------------------------------------------------------------------------
    
  GEN_XTRACE_NET_CFG_DEFAULT_01
  
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
* @fn         SCRIPTS_CFG::SCRIPTS_CFG(XCHAR* namefile) : APPLICATIONCFG(namefile)
* @brief      Constructor
* @ingroup
*
* @param[in]  XCHAR* : name of file of config
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
SCRIPTS_CFG::SCRIPTS_CFG(XCHAR* namefile) : APPCFG(namefile)
{
  Clean();

  Default();

  Ini();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPTS_CFG::~SCRIPTS_CFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
SCRIPTS_CFG::~SCRIPTS_CFG()
{
  Clean();
}

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPTS_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void SCRIPTS_CFG::Clean()
{

}


