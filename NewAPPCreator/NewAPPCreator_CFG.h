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


#define NEWAPPCREATOR_CFG_SECTION_GENERAL				        __L("general")
#define NEWAPPCREATOR_CFG_XPOS									        __L("xpos")
#define NEWAPPCREATOR_CFG_YPOS									        __L("ypos")
#define NEWAPPCREATOR_CFG_APPPATH									      __L("app_path")
#define NEWAPPCREATOR_CFG_GENPATH									      __L("gen_path")
#define NEWAPPCREATOR_CFG_APPTYPE                       __L("app_type")

//---- CLASS -------------------------------------------------------------------------------


class NEWAPPCREATOR_CFG : public XFILECFG
{
	public:
																	  NEWAPPCREATOR_CFG																(XCHAR* namefile);
		virtual												 ~NEWAPPCREATOR_CFG																();


		int															GetXPos																					();
    void														SetXPos																					(int xpos);
    int															GetYPos																					();
    void														SetYPos																					(int ypos);

    XSTRING*                        GetAppPath                                      ();
    XSTRING*                        GetGENPath                                      ();

    XDWORD                          GetAPPType                                      ();
    void                            SetAPPType                                      (XDWORD APPType);

		virtual bool										Default																					();

	private:

		void														Clean																						();

		int															xpos;
		int															ypos;

    XSTRING                         app_path;
    XSTRING                         gen_path;

    XDWORD                          app_type;
};


//---- INLINE FUNCTIONS --------------------------------------------------------------------

#endif

