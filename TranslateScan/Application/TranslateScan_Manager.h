/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       TranslateScan_Manager.h
* 
* @class      TRANSLATESCAN_MANAGER
* @brief      Translate Scan Manager class
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

#ifndef _TRANSLATESCAN_MANAGER_H_
#define _TRANSLATESCAN_MANAGER_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XVector.h"
#include "XPath.h"
#include "XFileTXT.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

typedef bool (*TRANSLANTESCAN_FOUNDINFILE_PTRFUNC)(XPATH* pathfile, XFILETXT* filetxt, int line, int index, XSTRING& result);
typedef bool (*TRANSLANTESCAN_CHANGEINFILE_PTRFUNC)(XPATH* pathfile, XFILETXT* filetxt, XSTRING& searchstring,int line, int index, XSTRING& result);

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class TRANSLATESCAN_FILETARGET
{
  public:
                             TRANSLATESCAN_FILETARGET                   ();
    virtual                 ~TRANSLATESCAN_FILETARGET                   ();

    XPATH*                   GetXPathFile                               ();
  
  private:

    void                     Clean                                      ();
    XPATH                    xpathfile;
};



class TRANSLATESCAN_MANAGER
{
  public:
                             TRANSLATESCAN_MANAGER                      ();
    virtual                 ~TRANSLATESCAN_MANAGER                      ();

    bool                     SearchFilesTarget                          (XCHAR* inipath, XVECTOR<TRANSLATESCAN_FILETARGET*>* filestarget);
    bool                     SearchFilesTarget                          (XPATH& inipath, XVECTOR<TRANSLATESCAN_FILETARGET*>* filestarget);

    bool                     SearchInFile                               (XPATH& pathfile, XCHAR* searchstring, TRANSLANTESCAN_FOUNDINFILE_PTRFUNC foundinfileptrfunc, TRANSLANTESCAN_CHANGEINFILE_PTRFUNC changeinfileptrfunc = NULL);

    bool                     Operation_Remark_Brief                     (XPATH& operationdir);
    static bool              Operation_Remark_Brief_SearchLine          (XPATH* pathfile, XFILETXT* filetxt, int nline, int index, XSTRING& brief);
    static bool              Operation_Remark_Brief_ChangeLine          (XPATH* pathfile, XFILETXT* filetxt, XSTRING& seachstring, int nline, int index, XSTRING& result);
    static bool              Operation_Remark_Brief_Construct           (XSTRING& brief_origin, XSTRING& brief_target);

    bool                     Operation_Remark_InGroup                   (XPATH& operationdir);
    static bool              Operation_Remark_InGroup_SearchLine        (XPATH* pathfile, XFILETXT* filetxt, int nline, int index, XSTRING& result);
    static bool              Operation_Remark_InGroup_ChangeLine        (XPATH* pathfile, XFILETXT* filetxt, XSTRING& searchstring, int nline, int index, XSTRING& result);

  private:

    void                     Clean                                      ();
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif


