/**-------------------------------------------------------------------------------------------------------------------
*
* @file        NewAPPCreator_CFG.cpp
*
* @class       NEWAPPCREATOR_CFG
* @brief       New Application Creator CFG
* @ingroup     UTILITIES
*
* @copyright   GEN Group. All rights reserved.
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

#include "Common_DefaultXTraceCFG.h"

#include "NewAPPCreator_CFG.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NEWAPPCREATOR_CFG::NEWAPPCREATOR_CFG(XCHAR* namefile) : XFILECFG(namefile)
* @brief      Constructor
* @ingroup    UTILITIES
*
* @param[in]  XCHAR* :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
NEWAPPCREATOR_CFG::NEWAPPCREATOR_CFG(XCHAR* namefile) : XFILECFG(namefile)
{
  Clean();

  if(namefile)
    {
      Ini<NEWAPPCREATOR_CFG>();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         NEWAPPCREATOR_CFG::~NEWAPPCREATOR_CFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILITIES
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
NEWAPPCREATOR_CFG::~NEWAPPCREATOR_CFG()
{
	Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTRACEMONITOR_CFG::DoVariableMapping()
* @brief      DoVariableMapping
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool NEWAPPCREATOR_CFG::DoVariableMapping()
{
  XSTRING section;

  if(!XFILECFG::DoVariableMapping())
    {
      return false;
    }

  
	//-----------------------------------------------------
// GENERAL

AddValue(XFILECFG_VALUETYPE_INT			  , NEWAPPCREATOR_CFG_SECTION_GENERAL		  , NEWAPPCREATOR_CFG_GENERAL_XPOS					      , &xpos);
AddValue(XFILECFG_VALUETYPE_INT			  , NEWAPPCREATOR_CFG_SECTION_GENERAL		  , NEWAPPCREATOR_CFG_GENERAL_YPOS					      , &ypos);
AddValue(XFILECFG_VALUETYPE_STRING    , NEWAPPCREATOR_CFG_SECTION_GENERAL		  , NEWAPPCREATOR_CFG_GENERAL_GENPATH   		      , &gen_path);

//-----------------------------------------------------
// Aplication

AddValue(XFILECFG_VALUETYPE_STRING	  , NEWAPPCREATOR_CFG_SECTION_APPLICATION , NEWAPPCREATOR_CFG_APPLICATION_PATH				    , &application_path);
AddValue(XFILECFG_VALUETYPE_STRING	  , NEWAPPCREATOR_CFG_SECTION_APPLICATION , NEWAPPCREATOR_CFG_APPLICATION_NAME				    , &application_name);
AddValue(XFILECFG_VALUETYPE_STRING    , NEWAPPCREATOR_CFG_SECTION_APPLICATION , NEWAPPCREATOR_CFG_APPLICATION_COPYRIGHT	      , &application_copyright);
AddValue(XFILECFG_VALUETYPE_INT			  , NEWAPPCREATOR_CFG_SECTION_APPLICATION , NEWAPPCREATOR_CFG_APPLICATION_TYPE 			      , &application_type);
AddValue(XFILECFG_VALUETYPE_INT			  , NEWAPPCREATOR_CFG_SECTION_APPLICATION , NEWAPPCREATOR_CFG_APPLICATION_FORMAT		      , &application_format);

//-----------------------------------------------------
// Additional

AddValue(XFILECFG_VALUETYPE_BOOLEAN	  , NEWAPPCREATOR_CFG_SECTION_ADDITIONAL  , NEWAPPCREATOR_CFG_ADDITIONAL_TRACESYSTEM	    , &additional_tracesystem);
AddValue(XFILECFG_VALUETYPE_BOOLEAN	  , NEWAPPCREATOR_CFG_SECTION_ADDITIONAL  , NEWAPPCREATOR_CFG_ADDITIONAL_MEMCTRLSYSTEM	  , &additional_memctrlsystem);
AddValue(XFILECFG_VALUETYPE_BOOLEAN	  , NEWAPPCREATOR_CFG_SECTION_ADDITIONAL  , NEWAPPCREATOR_CFG_ADDITIONAL_LOGSYSTEM  		  , &additional_logsystem);
AddValue(XFILECFG_VALUETYPE_BOOLEAN	  , NEWAPPCREATOR_CFG_SECTION_ADDITIONAL  , NEWAPPCREATOR_CFG_ADDITIONAL_CFGSYSTEM 			  , &additional_cfgsystem);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NEWAPPCREATOR_CFG::DoDefault()
* @brief      DoDefault
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool NEWAPPCREATOR_CFG::DoDefault()
{
 	xpos			                  = 613;
	ypos			                  = 349;
  gen_path                    = __L("");

  application_path            = __L("");
  application_name            = __L("");
  application_copyright       = __L("GEN Group");
  application_type            = 0;
  application_format          = 0;

  additional_tracesystem      = true;
  additional_memctrlsystem    = true;
  additional_logsystem        = true;
  additional_cfgsystem        = true;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int NEWAPPCREATOR_CFG::GetXPos()
* @brief      GetXPos
* @ingroup    UTILITIES
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int NEWAPPCREATOR_CFG::GetXPos()
{
  return xpos;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NEWAPPCREATOR_CFG::SetXPos(int xpos)
* @brief      SetXPos
* @ingroup    UTILITIES
*
* @param[in]  xpos :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NEWAPPCREATOR_CFG::SetXPos(int xpos)
{
  this->xpos = xpos;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int NEWAPPCREATOR_CFG::GetYPos()
* @brief      GetYPos
* @ingroup    UTILITIES
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int NEWAPPCREATOR_CFG::GetYPos()
{
  return ypos;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NEWAPPCREATOR_CFG::SetYPos(int ypos)
* @brief      SetYPos
* @ingroup    UTILITIES
*
* @param[in]  ypos :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NEWAPPCREATOR_CFG::SetYPos(int ypos)
{
  this->ypos = ypos;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* NEWAPPCREATOR_CFG::GetGENPath()
* @brief      GetGENPath
* @ingroup    UTILITIES
*
* @return     XSTRING*:
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* NEWAPPCREATOR_CFG::GetGENPath()
{
  return &gen_path;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* NEWAPPCREATOR_CFG::Application_GetPath()
* @brief      Application_GetPath
* @ingroup    
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* NEWAPPCREATOR_CFG::Application_GetPath()
{
  return &application_path;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* NEWAPPCREATOR_CFG::Application_GetName()
* @brief      Application_GetName
* @ingroup    
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* NEWAPPCREATOR_CFG::Application_GetName()
{
  return &application_name;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* NEWAPPCREATOR_CFG::Application_GetCopyright()
* @brief      Application_GetCopyright
* @ingroup    
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* NEWAPPCREATOR_CFG::Application_GetCopyright()
{
  return &application_copyright;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD NEWAPPCREATOR_CFG::Application_GetType()
* @brief      Application_GetType
* @ingroup    
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD NEWAPPCREATOR_CFG::Application_GetType()
{
  return application_type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NEWAPPCREATOR_CFG::Application_SetType(XDWORD type)
* @brief      Application_SetType
* @ingroup    
* 
* @param[in]  type : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NEWAPPCREATOR_CFG::Application_SetType(XDWORD type)
{
  this->application_type = type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD NEWAPPCREATOR_CFG::Application_GetFormat()
* @brief      Application_GetFormat
* @ingroup    
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD NEWAPPCREATOR_CFG::Application_GetFormat()
{
  return application_format;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NEWAPPCREATOR_CFG::Application_SetFormat(XDWORD format)
* @brief      Application_SetFormat
* @ingroup    
* 
* @param[in]  format : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NEWAPPCREATOR_CFG::Application_SetFormat(XDWORD format)
{
  this->application_format = application_format;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NEWAPPCREATOR_CFG::Additional_GetTraceSystem()
* @brief      Additional_GetTraceSystem
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NEWAPPCREATOR_CFG::Additional_GetTraceSystem()
{
  return additional_tracesystem;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NEWAPPCREATOR_CFG::Additional_SetTraceSystem(bool tracesystem)
* @brief      Additional_SetTraceSystem
* @ingroup    
* 
* @param[in]  tracesystem : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NEWAPPCREATOR_CFG::Additional_SetTraceSystem(bool tracesystem)
{
  additional_tracesystem = tracesystem;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NEWAPPCREATOR_CFG::Additional_GetMemCtrlSystem()
* @brief      Additional_GetMemCtrlSystem
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NEWAPPCREATOR_CFG::Additional_GetMemCtrlSystem()
{
  return additional_memctrlsystem;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NEWAPPCREATOR_CFG::Additional_SetMemCtrlSystem(bool memctrlsystem)
* @brief      Additional_SetMemCtrlSystem
* @ingroup    
* 
* @param[in]  memctrlsystem : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NEWAPPCREATOR_CFG::Additional_SetMemCtrlSystem(bool memctrlsystem)
{
  additional_memctrlsystem = memctrlsystem;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NEWAPPCREATOR_CFG::Additional_GetLogSystem()
* @brief      Additional_GetLogSystem
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NEWAPPCREATOR_CFG::Additional_GetLogSystem()
{
  return additional_logsystem;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NEWAPPCREATOR_CFG::Additional_SetLogSystem(bool logsystem)
* @brief      Additional_SetLogSystem
* @ingroup    
* 
* @param[in]  logsystem : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NEWAPPCREATOR_CFG::Additional_SetLogSystem(bool logsystem)
{
  additional_logsystem = logsystem;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NEWAPPCREATOR_CFG::Additional_GetCFGSystem()
* @brief      Additional_GetCFGSystem
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NEWAPPCREATOR_CFG::Additional_GetCFGSystem()
{
  return additional_cfgsystem;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NEWAPPCREATOR_CFG::Additional_SetCFGSystem(bool cfgsystem)
* @brief      Additional_SetCFGSystem
* @ingroup    
* 
* @param[in]  cfgsystem : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NEWAPPCREATOR_CFG::Additional_SetCFGSystem(bool cfgsystem)
{
  additional_cfgsystem = cfgsystem;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NEWAPPCREATOR_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILITIES
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void NEWAPPCREATOR_CFG::Clean()
{
	xpos	                      = 0;
	ypos	                      = 0;
  gen_path.Empty();

  application_path.Empty();
  application_name.Empty();
  application_copyright.Empty();
  application_type            = 0;
  application_format          = 0;

  additional_tracesystem      = false;
  additional_memctrlsystem    = false;
  additional_logsystem        = false;
  additional_cfgsystem        = false;
}

