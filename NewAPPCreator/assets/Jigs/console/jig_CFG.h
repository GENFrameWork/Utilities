/**-------------------------------------------------------------------------------------------------------------------
*
* @file       #@[jig]_CFG.h
*
* @class      #*[jig]_CFG
* @brief      #@[jig] Configuration
* @ingroup    #*[jig]
*
* @copyright  #=[jig]. All right reserved.
*
*---------------------------------------------------------------------------------------------------------------------*/

#ifndef _#*[jig]CFG_H_
#define _#*[jig]CFG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "APPFlowCFG.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define #*[jig]CFG_SECTIONGENERAL     __L("general")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class #*[jig]_CFG : public APPFLOWCFG
{
  public:

    static bool                     GetIsInstanced                          ();
    static #*[jig]_CFG&             GetInstance                             ();
    static bool                     DelInstance                             ();


    bool                            Default                                 ();

  private:
                                    #*[jig]_CFG                             (XCHAR* namefile);
                                    #*[jig]_CFG                             (#*[jig]_CFG const&);        // Don't implement
    virtual                        ~#*[jig]_CFG                             ();

    void                            operator =                              (#*[jig]_CFG const&);        // Don't implement

    void                            Clean                                   ();

     static #*[jig]_CFG*            instance;
};



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


