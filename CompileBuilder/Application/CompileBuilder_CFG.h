/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CompileBuilder_CFG.h
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

#ifndef _COMPILEBUILDER_CFG_H_
#define _COMPILEBUILDER_CFG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "APPCFG.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define CBUILDER_CFG_SECTION_GENERAL        __L("general")
#define CBUILDER_CFG_GENERAL_SILENTMODE     __L("silentmode")

#define CBUILDER_CFG_SECTION_SCRIPTS        __L("scripts")
#define CBUILDER_CFG_SCRIPTS_SCRIPT         __L("script")

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class CBUILDER_CFG : public APPCFG
{
  public:

    static bool                     GetIsInstanced                          ();
    static CBUILDER_CFG&            GetInstance                             (bool ini = true);
    static bool                     DelInstance                             ();

    bool                            DoVariableMapping                       (); 
    bool                            DoDefault                               ();

    bool                            End                                     ();

    bool                            IsSilentMode                            ();

    XVECTOR<XSTRING*>*              Scripts_GetAll                          ();
    XSTRING*                        Scripts_GetScript                       (int index);

  private:
                                    CBUILDER_CFG                            (XCHAR* namefile);
                                    CBUILDER_CFG                            (CBUILDER_CFG const&);        // Don't implement
    virtual                        ~CBUILDER_CFG                            ();

    void                            operator =                              (CBUILDER_CFG const&);        // Don't implement

    void                            Clean                                   ();

    static CBUILDER_CFG*            instance;

    bool                            silentmode;

    int                             nscripts;
    XVECTOR<XSTRING*>               scriptslist;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

