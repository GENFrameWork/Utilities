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

#include "XBase.h"
#include "XPath.h"
#include "XString.h"
#include "XVector.h"
#include <Dialogs.hpp>
#include "cdiroutl.h"
#include <Grids.hpp>
#include <Outline.hpp>

//---------------------------------------------------------------------------

#define NEWAPPCREATOR_CFGNAMEFILE	 	 			        __L("NewAPPCreator")
#define NEWAPPCREATOR_VERSIONLABEL                __L("Version 0.1.0")


#define NEWAPPCREATOR_SELECDIRECTORY_XPOS         96
#define NEWAPPCREATOR_SELECDIRECTORY_APP_YPOS     32
#define NEWAPPCREATOR_SELECDIRECTORY_GEN_YPOS     96

//---------------------------------------------------------------------------

class TForm1 : public TForm
{
  __published:	// IDE-managed Components

    TBitBtn*                ButtonExit;
    TBitBtn*                ButtonCreate;
    TLabel*                 VersionLabel;
    TImage*                 IMGMain;
    TEdit*                  EditAppName;
    TLabel*                 LabelNameApp;
    TLabel*                 LabelGENPath;
    TEdit*                  EditGENPath;
    TCDirectoryOutline*     CDirectoryOutline;
    TRadioGroup*            RadioGroupTypeApp;
    TEdit*                  EditAppPath;
  TLabel *LabelAppPath;
  TTimer *TimerCheckStateButtonCreate;

    void __fastcall         ButtonExitClick           (TObject *Sender);
    void __fastcall         FormCreate                (TObject *Sender);
    void __fastcall         EditAppPathEnter          (TObject *Sender);
    void __fastcall         CDirectoryOutlineDblClick (TObject *Sender);
    void __fastcall         EditGENPathEnter          (TObject *Sender);
  void __fastcall TimerCheckStateButtonCreateTimer(TObject *Sender);

  private:	// User declarations

  public:		// User declarations

    __fastcall              TForm1                    (TComponent* Owner);
};

//---------------------------------------------------------------------------

extern PACKAGE TForm1 *Form1;

//---------------------------------------------------------------------------

#endif
