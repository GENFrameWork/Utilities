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
	XSTRING section;
	XSTRING key;

	Clean();

	//-----------------------------------------------------
	// GENERAL

	AddValue(XFILECFG_VALUETYPE_INT			  , NEWAPPCREATOR_CFG_SECTION_GENERAL		  , NEWAPPCREATOR_CFG_GENERAL_XPOS					      , &xpos);
	AddValue(XFILECFG_VALUETYPE_INT			  , NEWAPPCREATOR_CFG_SECTION_GENERAL		  , NEWAPPCREATOR_CFG_GENERAL_YPOS					      , &ypos);
	AddValue(XFILECFG_VALUETYPE_STRING	  , NEWAPPCREATOR_CFG_SECTION_GENERAL		  , NEWAPPCREATOR_CFG_GENERAL_APPPATH				      , &app_path);
	AddValue(XFILECFG_VALUETYPE_STRING    , NEWAPPCREATOR_CFG_SECTION_GENERAL		  , NEWAPPCREATOR_CFG_GENERAL_GENPATH   		      , &gen_path);
  AddValue(XFILECFG_VALUETYPE_STRING    , NEWAPPCREATOR_CFG_SECTION_GENERAL		  , NEWAPPCREATOR_CFG_GENERAL_APPCOPYRIGHT	      , &app_copyright);
  AddValue(XFILECFG_VALUETYPE_INT			  , NEWAPPCREATOR_CFG_SECTION_GENERAL		  , NEWAPPCREATOR_CFG_GENERAL_APPTYPE 			      , &app_type);
  AddValue(XFILECFG_VALUETYPE_INT			  , NEWAPPCREATOR_CFG_SECTION_GENERAL		  , NEWAPPCREATOR_CFG_GENERAL_APPFORMAT			      , &app_format);

  
	//-----------------------------------------------------
	// Additional

	AddValue(XFILECFG_VALUETYPE_BOOLEAN	  , NEWAPPCREATOR_CFG_SECTION_ADDITIONAL  , NEWAPPCREATOR_CFG_ADDITIONAL_TRACESYSTEM	    , &trace_system);
  AddValue(XFILECFG_VALUETYPE_BOOLEAN	  , NEWAPPCREATOR_CFG_SECTION_ADDITIONAL  , NEWAPPCREATOR_CFG_ADDITIONAL_MEMCTRLSYSTEM	  , &memctrl_system);
	AddValue(XFILECFG_VALUETYPE_BOOLEAN	  , NEWAPPCREATOR_CFG_SECTION_ADDITIONAL  , NEWAPPCREATOR_CFG_ADDITIONAL_LOGSYSTEM  		  , &log_system);
  AddValue(XFILECFG_VALUETYPE_BOOLEAN	  , NEWAPPCREATOR_CFG_SECTION_ADDITIONAL  , NEWAPPCREATOR_CFG_ADDITIONAL_CFGSYSTEM 			  , &cfg_system);

	Default();

	Ini();
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
	End();
	Clean();
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
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
* @fn         XSTRING* NEWAPPCREATOR_CFG::GetAppPath()
* @brief      GetAppPath
* @ingroup    UTILITIES
*
* @return     XSTRING*:
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* NEWAPPCREATOR_CFG::GetAppPath()
{
  return &app_path;
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
* @fn         XSTRING* NEWAPPCREATOR_CFG::GetAppCopyright()
* @brief      GetAppCopyright
* @ingroup    UTILITIES
*
* @return     XSTRING*:
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* NEWAPPCREATOR_CFG::GetAppCopyright()
{
  return &app_copyright;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD NEWAPPCREATOR_CFG::GetAPPType()
* @brief      GetAPPType
* @ingroup
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD NEWAPPCREATOR_CFG::GetAPPType()
{
  return app_type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NEWAPPCREATOR_CFG::SetAPPType(XDWORD app_type)
* @brief      SetAPPType
* @ingroup
*
* @param[in]  app_type :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void NEWAPPCREATOR_CFG::SetAPPType(XDWORD app_type)
{
  this->app_type = app_type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD NEWAPPCREATOR_CFG::GetAPPFormat()
* @brief      GetAPPFormat
* @ingroup    
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD NEWAPPCREATOR_CFG::GetAPPFormat()
{
  return app_format;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NEWAPPCREATOR_CFG::SetAPPFormat(XDWORD app_format)
* @brief      SetAPPFormat
* @ingroup    
* 
* @param[in]  app_format : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NEWAPPCREATOR_CFG::SetAPPFormat(XDWORD app_format)
{
  this->app_format = app_format;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NEWAPPCREATOR_CFG::GetAddTraceSystem()
* @brief      GetAddTraceSystem
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NEWAPPCREATOR_CFG::GetAddTraceSystem()
{
  return trace_system;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NEWAPPCREATOR_CFG::SetAddTraceSystem(bool trace_system)
* @brief      SetAddTraceSystem
* @ingroup    
* 
* @param[in]  trace_system : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NEWAPPCREATOR_CFG::SetAddTraceSystem(bool trace_system)
{
  this->trace_system = trace_system;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NEWAPPCREATOR_CFG::GetAddMemCtrlSystem()
* @brief      GetAddMemCtrlSystem
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NEWAPPCREATOR_CFG::GetAddMemCtrlSystem()
{
  return memctrl_system;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NEWAPPCREATOR_CFG::SetAddMemCtrlSystem(bool memctrl_system)
* @brief      SetAddMemCtrlSystem
* @ingroup    
* 
* @param[in]  memctrl_system : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NEWAPPCREATOR_CFG::SetAddMemCtrlSystem(bool memctrl_system)
{
  this->memctrl_system = memctrl_system;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NEWAPPCREATOR_CFG::GetAddLogSystem()
* @brief      GetAddLogSystem
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NEWAPPCREATOR_CFG::GetAddLogSystem()
{
  return log_system;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void NEWAPPCREATOR_CFG::SetAddLogSystem(bool log_system)
* @brief      SetAddLogSystem
* @ingroup    
* 
* @param[in]  log_system : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void NEWAPPCREATOR_CFG::SetAddLogSystem(bool log_system)
{
  this->log_system = log_system;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NEWAPPCREATOR_CFG::GetAddCFGSystem()
* @brief      GetAddCFGSystem
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool NEWAPPCREATOR_CFG::GetAddCFGSystem()
{
  return cfg_system;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void NEWAPPCREATOR_CFG::SetAddCFGSystem(bool cfg_system)
* @brief      SetAddCFGSystem
* @ingroup
*
* @param[in]  cfg_system :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void NEWAPPCREATOR_CFG::SetAddCFGSystem(bool cfg_system)
{
  this->cfg_system = cfg_system;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool NEWAPPCREATOR_CFG::Default()
* @brief      Default
* @ingroup    UTILITIES
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool NEWAPPCREATOR_CFG::Default()
{
	xpos			        = 613;
	ypos			        = 349;

  app_path          = __L("");
  gen_path          = __L("");
  app_copyright     = __L("GEN Group");

  app_type          = 0;
  app_format        = 0;

  trace_system      = true;
  memctrl_system    = true;
  log_system        = true;
  cfg_system        = true;

	return true;
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
	xpos	            = 0;
	ypos	            = 0;

  app_path.Empty();
  gen_path.Empty();
  app_copyright.Empty();

  app_type          = 0;
  app_format        = 0;

  trace_system      = false;
  memctrl_system    = false;
  log_system        = false;
  cfg_system        = false;
}

