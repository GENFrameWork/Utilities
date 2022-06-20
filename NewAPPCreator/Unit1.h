//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H

//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
#include <Outline.hpp>
#include <Dialogs.hpp>
#include <cdiroutl.h>

#include "XBase.h"
#include "XPath.h"
#include "XString.h"
#include "XVector.h"
#include "XFileTXT.h"
#include "XPathsManager.h"

#include "NewAPPCreator_CFG.h"

//---------------------------------------------------------------------------

#define NEWAPPCREATOR_CFGNAMEFILE	 	 			            __L("NewAPPCreator")
#define NEWAPPCREATOR_VERSIONLABEL                    __L("Version 0.1.0")
#define NEWAPPCREATOR_ROOTDIR                         __L("assets")


#define NEWAPPCREATOR_SELECTDIRECTORY_XPOS            96
#define NEWAPPCREATOR_SELECTDIRECTORY_APP_YPOS        32
#define NEWAPPCREATOR_SELECTDIRECTORY_GEN_YPOS        96

#define NEWAPPCREATOR_XPATHSECTIONTYPE_JIGS_BASE      XPATHSMANAGERSECTIONTYPE_GENERIC1
#define NEWAPPCREATOR_XPATHSECTIONTYPE_JIGS_CONSOLE   XPATHSMANAGERSECTIONTYPE_GENERIC2
#define NEWAPPCREATOR_XPATHSECTIONTYPE_JIGS_GRAPHICS  XPATHSMANAGERSECTIONTYPE_GENERIC3

enum NEWAPPCREATOR_APPTYPE
{
  NEWAPPCREATOR_APPTYPE_UNKNOWN       = -1,
  NEWAPPCREATOR_APPTYPE_BASE              ,
  NEWAPPCREATOR_APPTYPE_CONSOLE           ,
  NEWAPPCREATOR_APPTYPE_GRAPHICS          ,
};

enum NEWAPPCREATOR_DIRTYPE
{
  NEWAPPCREATOR_DIRTYPE_UNKNOWN       = 0 ,
  NEWAPPCREATOR_DIRTYPE_APPLICATION       ,
  NEWAPPCREATOR_DIRTYPE_PLATFORMS         ,
};

//---------------------------------------------------------------------------

class APPMODULEELEMENT
{
  public:

    NEWAPPCREATOR_DIRTYPE   dirtype;
    XSTRING                 namefile;
    XFILETXT*               fileTXT;

  private:

    void                    Clean                               ();
};



class TForm1 : public TForm
{
  __published:	// IDE-managed Components

    TBitBtn*                        ButtonExit;
    TBitBtn*                        ButtonCreate;
    TLabel*                         VersionLabel;
    TImage*                         IMGMain;
    TEdit*                          EditAppName;
    TLabel*                         LabelAppName;
    TLabel*                         LabelGENPath;
    TEdit*                          EditGENPath;
    TCDirectoryOutline*             CDirectoryOutline;
    TRadioGroup*                    RadioGroupAppType;
    TEdit*                          EditAppPath;
    TLabel*                         LabelAppPath;
    TTimer*                         TimerCheckStateButtonCreate;
    TCheckBox*                      CheckBoxLog;
    TCheckBox*                      CheckBoxTrace;
    TEdit*                          EditCopyright;
    TLabel*                         LabelCopyright;
    TCheckBox*                      CheckBoxCFGFile;
    TCheckBox*                      CheckBoxMemControl;
    TRadioGroup*                    RadioGroupAppFormat;

    void __fastcall                 ButtonExitClick                     (TObject *Sender);
    void __fastcall                 FormCreate                          (TObject *Sender);
    void __fastcall                 EditAppPathEnter                    (TObject *Sender);
    void __fastcall                 CDirectoryOutlineDblClick           (TObject *Sender);
    void __fastcall                 EditGENPathEnter                    (TObject *Sender);
    void __fastcall                 TimerCheckStateButtonCreateTimer    (TObject *Sender);
    void __fastcall                 FormClose                           (TObject *Sender, TCloseAction &Action);
    void __fastcall                 ButtonCreateClick                   (TObject *Sender);

  private:	// User declarations

    NEWAPPCREATOR_CFG*		          cfg;
    XVECTOR<APPMODULEELEMENT*>      appmoduleselements;

  public:		// User declarations

    __fastcall                      TForm1                              (TComponent* Owner);

    bool                            AjustUserInterfaceToCFG             ();
    APPMODULEELEMENT*               CreateAppModuleElement              (NEWAPPCREATOR_DIRTYPE dirtype, XCHAR* namefileliteral);
    bool                            LoadToMemoryFiles                   (NEWAPPCREATOR_APPTYPE apptype);
    bool                            ChangeFileInMemory                  (APPMODULEELEMENT* appmoduleelement, XCHAR* search, XCHAR* changeto); 
};

//---------------------------------------------------------------------------

extern PACKAGE TForm1 *Form1;

//---------------------------------------------------------------------------

#endif
