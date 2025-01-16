/**-------------------------------------------------------------------------------------------------------------------
*
* @file       #@[jig]_CFG.cpp
*
* @class      #*[jig]_CFG
* @brief      #@[jig] Configuration
* @ingroup    #*[jig]
*
* @copyright  #=[jig]. All right reserved.
*
*---------------------------------------------------------------------------------------------------------------------*/


/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XLog.h"

#include "#@[jig].h"

#include "#@[jig]_CFG.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

#*[jig]_CFG* #*[jig]_CFG::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool #*[jig]_CFG::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    [#*[jig]] 
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool #*[jig]_CFG::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         #*[jig]_CFG& #*[jig]_CFG::GetInstance()
* @brief      GetInstance
* @ingroup    [#*[jig]]
*
* @return     #*[jig]_CFG& :
*
*---------------------------------------------------------------------------------------------------------------------*/
#*[jig]_CFG& #*[jig]_CFG::GetInstance()
{
  if(!instance) instance = new #*[jig]_CFG(APPLICATION_NAMEFILE);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool #*[jig]_CFG::DelInstance()
* @brief      DelInstance
* @ingroup    [#*[jig]]
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool #*[jig]_CFG::DelInstance()
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
* @fn         bool #*[jig]_CFG::Default()
* @brief      Default config
* @ingroup    [#*[jig]]
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool #*[jig]_CFG::Default()
{
  
  //------------------------------------------------------------------------------
    
  GEN_XTRACE_NET_CFG_DEFAULT_01
  
  //------------------------------------------------------------------------------

  log_isactive                          = true;
  log_backupisactive                    = true;
  log_backupmaxfiles                    = 10;
  log_backupiscompress                  = true;

  log_activesectionsID.Empty();

  log_activesectionsID                 += APPFLOW_CFG_LOG_SECTIONID_INITIATION;
  log_activesectionsID                 += __L(",");
  log_activesectionsID                 += APPFLOW_CFG_LOG_SECTIONID_GENERIC;
  log_activesectionsID                 += __L(",");
  log_activesectionsID                 += APPFLOW_CFG_LOG_SECTIONID_STATUSAPP;
  log_activesectionsID                 += __L(",");
  log_activesectionsID                 += APPFLOW_CFG_LOG_SECTIONID_ENDING;

  log_levelmask                         = XLOGLEVEL_ALL;
  log_maxsize                           = 3000;
  log_reductionpercent                  = 10;

  //------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         #*[jig]_CFG::#*[jig]_CFG(XCHAR* namefile) : APPLICATIONCFG(namefile)
* @brief      Constructor
* @ingroup    [#*[jig]]
*
* @param[in]  XCHAR* : name of file of config
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
#*[jig]_CFG::#*[jig]_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
{
  Clean();

  Default();

  Ini();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         #*[jig]_CFG::~#*[jig]_CFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    [#*[jig]]  
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
#*[jig]_CFG::~#*[jig]_CFG()
{
  Clean();
}

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void #*[jig]_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    [#*[jig]]
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void #*[jig]_CFG::Clean()
{

}


