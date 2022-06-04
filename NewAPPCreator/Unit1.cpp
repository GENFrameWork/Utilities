//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "XVector.h"
#include "XBuffer.h"
#include "XPathsManager.h"
#include "XWINDOWSFactory.h"
#include "XWINDOWSSleep.h"
#include "XWINDOWSSystem.h"
#include "XWINDOWSThread.h"
#include "XWINDOWSDateTime.h"
#include "XWINDOWSTrace.h"
#include "XFileCFG.h"
#include "XString.h"
#include "XTrace.h"
#include "XDir.h"
#include "XFile.h"

#include "Unit1.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "cdiroutl"
#pragma resource "*.dfm"

TForm1 *Form1;

//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{

  XFACTORY::SetInstance(new XWINDOWSFACTORY());
  if(!XFACTORY::GetIsInstanced()) return;

  XSLEEP::SetInstance(new XWINDOWSSLEEP());
  if(!XSLEEP::GetIsInstanced()) return;

  XSYSTEM::SetInstance(new XWINDOWSSYSTEM());
  if(!XSYSTEM::GetIsInstanced()) return;

  XBUFFER::SetHardwareUseLittleEndian(GEN_XSYSTEM.HardwareUseLittleEndian());

  AnsiString exefile = Application->ExeName;
  AnsiString exepath = ExtractFilePath(exefile);
  XPATH      xpath;

  xpath  = exepath.c_str();
  xpath += __L("assets");

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);


  CDirectoryOutline->Visible  = false;
  CDirectoryOutline->Left     = 96;
  CDirectoryOutline->Top      = 32;

  ButtonCreate->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
   VersionLabel->Caption = NEWAPPCREATOR_VERSIONLABEL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditAppPathEnter(TObject *Sender)
{
  CDirectoryOutline->Visible  = true;

  CDirectoryOutline->Left     = NEWAPPCREATOR_SELECDIRECTORY_XPOS;
  CDirectoryOutline->Top      = NEWAPPCREATOR_SELECDIRECTORY_APP_YPOS;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CDirectoryOutlineDblClick(TObject *Sender)
{
  CDirectoryOutline->Visible  = false;

  if(CDirectoryOutline->Top == NEWAPPCREATOR_SELECDIRECTORY_APP_YPOS)
        EditAppPath->Text = CDirectoryOutline->Directory;
   else EditGENPath->Text = CDirectoryOutline->Directory;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditGENPathEnter(TObject *Sender)
{
  CDirectoryOutline->Visible  = true;

  CDirectoryOutline->Left     = NEWAPPCREATOR_SELECDIRECTORY_XPOS;
  CDirectoryOutline->Top      = NEWAPPCREATOR_SELECDIRECTORY_GEN_YPOS;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerCheckStateButtonCreateTimer(TObject *Sender)
{
  ButtonCreate->Enabled = (EditAppPath->Text.Length() && EditGENPath->Text.Length() && EditAppName->Text.Length())?true:false;
}
//---------------------------------------------------------------------------

