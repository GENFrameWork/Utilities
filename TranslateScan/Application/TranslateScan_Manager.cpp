/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       TranslateScan_Manager.cpp
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINE_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "TranslateScan_Manager.h"

#include "XFactory.h"
#include "XDir.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_TRANSLATESCAN_FILETARGET


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TRANSLATESCAN_FILETARGET::TRANSLATESCAN_FILETARGET()
* @brief      Constructor
* @ingroup    APPLICATION
* 
* --------------------------------------------------------------------------------------------------------------------*/
TRANSLATESCAN_FILETARGET::TRANSLATESCAN_FILETARGET()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TRANSLATESCAN_FILETARGET::~TRANSLATESCAN_FILETARGET()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
* 
* --------------------------------------------------------------------------------------------------------------------*/
TRANSLATESCAN_FILETARGET::~TRANSLATESCAN_FILETARGET()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XPATH* TRANSLATESCAN_FILETARGET::GetXPathFile()
* @brief      get Xpath file
* @ingroup    APPLICATION
* 
* @return     XPATH* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* TRANSLATESCAN_FILETARGET::GetXPathFile()
{
  return &xpathfile;
}

  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void TRANSLATESCAN_FILETARGET::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* --------------------------------------------------------------------------------------------------------------------*/
void TRANSLATESCAN_FILETARGET::Clean()
{

}


#pragma endregion


#pragma region CLASS_TRANSLATESCAN_MANAGER


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TRANSLATESCAN_MANAGER::TRANSLATESCAN_MANAGER()
* @brief      Constructor
* @ingroup    APPLICATION
* 
* --------------------------------------------------------------------------------------------------------------------*/
TRANSLATESCAN_MANAGER::TRANSLATESCAN_MANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TRANSLATESCAN_MANAGER::~TRANSLATESCAN_MANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
* 
* --------------------------------------------------------------------------------------------------------------------*/
TRANSLATESCAN_MANAGER::~TRANSLATESCAN_MANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TRANSLATESCAN_MANAGER::SearchFilesTarget(XPATH& inipath, XVECTOR<TRANSLATESCAN_FILETARGET*>* filestarget)
* @brief      search files target
* @ingroup    APPLICATION
* 
* @param[in]  inipath : 
* @param[in]  filestarget : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TRANSLATESCAN_MANAGER::SearchFilesTarget(XCHAR* inipath, XVECTOR<TRANSLATESCAN_FILETARGET*>* filestarget)
{
  XCHAR* extensions[] = { __L(".c"),
                          __L(".cpp"),
                          __L(".h"),
                          __L(".hpp"),
                        };  

  XDIR*         xdir = NULL;
  XDIRELEMENT   searchelement;

  if(!inipath)
    {
      return false;
    }

  if(!filestarget)
    {
      return false;
    }

  xdir = GEN_XFACTORY.Create_Dir();
  if(!xdir)
    {   
      return false;
    }

  if(xdir->FirstSearch(inipath, __L("*"), &searchelement))
    {
      do{
          if(searchelement.GetType() == XDIRELEMENTTYPE_DIR)
            {
              XPATH inisubpath;

              inisubpath = inipath;                            
              inisubpath.Slash_Add();
              inisubpath.Add(searchelement.GetNameFile()->Get());

              SearchFilesTarget(inisubpath.Get(), filestarget);
            }

          if(searchelement.GetType() == XDIRELEMENTTYPE_FILE)
            { 
              XSTRING ext;
              bool    valid = false;  
   
              searchelement.GetNameFile()->GetExt(ext); 
 
              for(XDWORD c=0; c<sizeof(extensions)/sizeof(XCHAR*); c++)
                {
                  if(!ext.Compare(extensions[c],true))
                    {
                      valid = true;    
                    }
                }
            
              if(valid)  
                {
                  TRANSLATESCAN_FILETARGET* filetarget = new TRANSLATESCAN_FILETARGET();
                  if(filestarget)
                    {
                      filetarget->GetXPathFile()->Set(inipath);
                      filetarget->GetXPathFile()->Slash_Add();
                      filetarget->GetXPathFile()->Add(searchelement.GetNameFile()->Get()); 

                      filestarget->Add(filetarget);
                    }
                }
            }
  
        } while(xdir->NextSearch(&searchelement));      
    }
    
  GEN_XFACTORY.Delete_Dir(xdir);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool TRANSLATESCAN_MANAGER::SearchFilesTarget(XPATH& inipath, XVECTOR<TRANSLATESCAN_FILETARGET*>* filestarget)
* @brief      search files target
* @ingroup    APPLICATION
* 
* @param[in]  inipath : 
* @param[in]  filestarget : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool TRANSLATESCAN_MANAGER::SearchFilesTarget(XPATH& inipath, XVECTOR<TRANSLATESCAN_FILETARGET*>* filestarget)
{
  return SearchFilesTarget(inipath.Get(), filestarget);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void TRANSLATESCAN_MANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* --------------------------------------------------------------------------------------------------------------------*/
void TRANSLATESCAN_MANAGER::Clean()
{

}


#pragma endregion


#pragma endregion