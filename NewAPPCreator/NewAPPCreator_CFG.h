/**-------------------------------------------------------------------------------------------------------------------
*
* @file        NewAPPCreator_CFG.h
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

#ifndef _NEWAPPCREATOR_CFG_H_
#define _NEWAPPCREATOR_CFG_H_


//---- INCLUDES ----------------------------------------------------------------------------

#include "XBase.h"
#include "XString.h"
#include "XFileCFG.h"


//---- DEFINES & ENUMS  --------------------------------------------------------------------


#define NEWAPPCREATOR_CFG_SECTION_GENERAL				          __L("general")
#define NEWAPPCREATOR_CFG_GENERAL_XPOS							      __L("xpos")
#define NEWAPPCREATOR_CFG_GENERAL_YPOS									  __L("ypos")
#define NEWAPPCREATOR_CFG_GENERAL_GENPATH									__L("gen_path")

#define NEWAPPCREATOR_CFG_SECTION_APPLICATION 	          __L("general")
#define NEWAPPCREATOR_CFG_APPLICATION_PATH								__L("path")
#define NEWAPPCREATOR_CFG_APPLICATION_NAME								__L("name")
#define NEWAPPCREATOR_CFG_APPLICATION_COPYRIGHT						__L("copyright")
#define NEWAPPCREATOR_CFG_APPLICATION_TYPE                __L("type")
#define NEWAPPCREATOR_CFG_APPLICATION_FORMAT              __L("format")

#define NEWAPPCREATOR_CFG_SECTION_ADDITIONAL		          __L("additional")
#define NEWAPPCREATOR_CFG_ADDITIONAL_TRACESYSTEM	        __L("tracesystem")
#define NEWAPPCREATOR_CFG_ADDITIONAL_MEMCTRLSYSTEM  	    __L("memctrlsystem")
#define NEWAPPCREATOR_CFG_ADDITIONAL_LOGSYSTEM  	        __L("logsystem")
#define NEWAPPCREATOR_CFG_ADDITIONAL_CFGSYSTEM	          __L("CFGsystem")

//---- CLASS -------------------------------------------------------------------------------


class NEWAPPCREATOR_CFG : public XFILECFG
{
	public:
																	  NEWAPPCREATOR_CFG																(XCHAR* namefile);
		virtual												 ~NEWAPPCREATOR_CFG																();

    bool                            DoVariableMapping                               ();
    bool                            DoDefault                                       ();
    
		int															GetXPos																					();
    void														SetXPos																					(int xpos);
    int															GetYPos																					();
    void														SetYPos																					(int ypos);
    XSTRING*                        GetGENPath                                      ();

    XSTRING*                        Application_GetPath                             ();
    XSTRING*                        Application_GetName                             ();
    XSTRING*                        Application_GetCopyright                        ();
    XDWORD                          Application_GetType                             ();
    void                            Application_SetType                             (XDWORD type);
    XDWORD                          Application_GetFormat                           ();
    void                            Application_SetFormat                           (XDWORD format);

    bool                            Additional_GetTraceSystem                       ();
    void                            Additional_SetTraceSystem                       (bool tracesystem);
    bool                            Additional_GetMemCtrlSystem                     ();
    void                            Additional_SetMemCtrlSystem                     (bool memctrlsystem);
    bool                            Additional_GetLogSystem                         ();
    void                            Additional_SetLogSystem                         (bool logsystem);
    bool                            Additional_GetCFGSystem                         ();
    void                            Additional_SetCFGSystem                         (bool cfgsystem);

	private:

		void														Clean																						();

		int															xpos;
		int															ypos;
    XSTRING                         gen_path;

    XSTRING                         application_path;
    XSTRING                         application_name;
    XSTRING                         application_copyright;
    XDWORD                          application_type;
    XDWORD                          application_format;

    bool                            additional_tracesystem;
    bool                            additional_memctrlsystem;
  	bool                            additional_logsystem;
    bool                            additional_cfgsystem;
};


//---- INLINE FUNCTIONS --------------------------------------------------------------------

#endif

