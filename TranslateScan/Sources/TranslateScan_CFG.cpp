/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       TranslateScan_CFG.cpp
* 
* @class      TRANSLATESCAN_CFG
* @brief      Translate Scan configuration class
* @ingroup    APPLICATION
* 
* @copyright  EndoraSoft. All rights reserved.
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

#include "GEN_Defines.h"



/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "TranslateScan_CFG.h"

#include "XLog.h"

#include "TranslateScan.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

TRANSLATESCAN_CFG* TRANSLATESCAN_CFG::instance = NULL;



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TRANSLATESCAN_CFG::GetIsInstanced()
* @brief      Check if the singleton instance is created.
* @ingroup    APPLICATION
*
* @return     bool : true if the instance exists.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TRANSLATESCAN_CFG::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TRANSLATESCAN_CFG& TRANSLATESCAN_CFG::GetInstance(bool ini)
* @brief      Get the singleton instance of the configuration.
* @ingroup    APPLICATION
*
* @param[in]  ini : true to initialize the instance with the application configuration file.
*
* @return     TRANSLATESCAN_CFG& : reference to the singleton instance.
*
*---------------------------------------------------------------------------------------------------------------------*/
TRANSLATESCAN_CFG& TRANSLATESCAN_CFG::GetInstance(bool ini)
{
  if(!instance) instance = GEN_NEW TRANSLATESCAN_CFG(ini?APPLICATION_NAMEFILE:NULL);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TRANSLATESCAN_CFG::DelInstance()
* @brief      Delete the singleton instance of the configuration.
* @ingroup    APPLICATION
*
* @return     bool : true if the instance has been deleted.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TRANSLATESCAN_CFG::DelInstance()
{
  if(instance)
    {
      GEN_DELETE instance;
      instance = NULL;

      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TRANSLATESCAN_CFG::DoVariableMapping()
* @brief      Map the configuration variables.
* @ingroup    APPLICATION
*
* @return     bool : true if it is successful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TRANSLATESCAN_CFG::DoVariableMapping()
{
  if(!APPFLOWCFG::DoVariableMapping())
    {
      return false;
    }
  
  //-----------------------------------------------------
  // MACHINE PROTOCOL

  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TRANSLATESCAN_CFG::DoDefault()
* @brief      Set the default configuration values.
* @ingroup    APPLICATION
*
* @return     bool : true if it is successful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool TRANSLATESCAN_CFG::DoDefault()
{
  if(!APPFLOWCFG::DoDefault()) 
    {
      return false;
    }

  //------------------------------------------------------------------------------

  GEN_XTRACE_NET_CFG_DEFAULT_01

  //------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TRANSLATESCAN_CFG::TRANSLATESCAN_CFG(XCHAR* namefile)
* @brief      Constructor of class.
* @ingroup    APPLICATION
*
* @param[in]  namefile : name of the configuration file.
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
TRANSLATESCAN_CFG::TRANSLATESCAN_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
{
  Clean();

 if(namefile)
   {
     Ini<TRANSLATESCAN_CFG>();
   }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TRANSLATESCAN_CFG::~TRANSLATESCAN_CFG()
* @brief      Destructor of class.
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
TRANSLATESCAN_CFG::~TRANSLATESCAN_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void TRANSLATESCAN_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialize.
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void TRANSLATESCAN_CFG::Clean()
{


}



