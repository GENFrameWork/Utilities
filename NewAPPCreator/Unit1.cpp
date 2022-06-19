//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "XVector.h"
#include "XBuffer.h"
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


void APPMODULEELEMENT::Clean()
{
  dirtype = NEWAPPCREATOR_DIRTYPE_UNKNOWN;
  namefile.Empty();
}


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
  XPATH      xpath2;

  xpath  = exepath.c_str();
  xpath += NEWAPPCREATOR_ROOTDIR;

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_ROOT                  , xpath);

  xpath2.Set(__L("Jigs\\base"));
  GEN_XPATHSMANAGER.AddPathSection(NEWAPPCREATOR_XPATHSECTIONTYPE_JIGS_BASE       , xpath2);

  xpath2.Set(__L("Jigs\\console"));
  GEN_XPATHSMANAGER.AddPathSection(NEWAPPCREATOR_XPATHSECTIONTYPE_JIGS_CONSOLE    , xpath2);

  xpath2.Set(__L("Jigs\\graphics"));
  GEN_XPATHSMANAGER.AddPathSection(NEWAPPCREATOR_XPATHSECTIONTYPE_JIGS_GRAPHICS   , xpath2);


  cfg  = new NEWAPPCREATOR_CFG(NEWAPPCREATOR_CFGNAMEFILE);
	if(!cfg) return;


  Left                            = cfg->GetXPos();
  Top                             = cfg->GetYPos();

  EditAppPath->Text               = cfg->GetAppPath()->Get();
  EditGENPath->Text               = cfg->GetGENPath()->Get();
  EditCopyright->Text             = cfg->GetAppCopyright()->Get();

  RadioGroupAppType->ItemIndex    = cfg->GetAPPType();
  RadioGroupAppFormat->ItemIndex  = cfg->GetAPPFormat();

  CheckBoxTrace->State            = cfg->GetAddTraceSystem()?cbChecked:cbUnchecked;
  CheckBoxLog->State              = cfg->GetAddLogSystem()?cbChecked:cbUnchecked;
  CheckBoxMemControl->State       = cfg->GetAddMemCtrlSystem()?cbChecked:cbUnchecked;
  CheckBoxCFGFile->State          = cfg->GetAddCFGSystem()?cbChecked:cbUnchecked;



  CDirectoryOutline->Visible      = false;
  CDirectoryOutline->Left         = 96;
  CDirectoryOutline->Top          = 32;

  ButtonCreate->Enabled           = false;
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

  CDirectoryOutline->Left     = NEWAPPCREATOR_SELECTDIRECTORY_XPOS;
  CDirectoryOutline->Top      = NEWAPPCREATOR_SELECTDIRECTORY_APP_YPOS;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::CDirectoryOutlineDblClick(TObject *Sender)
{
  CDirectoryOutline->Visible  = false;

  if(CDirectoryOutline->Top == NEWAPPCREATOR_SELECTDIRECTORY_APP_YPOS)
        EditAppPath->Text = CDirectoryOutline->Directory;
   else EditGENPath->Text = CDirectoryOutline->Directory;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::EditGENPathEnter(TObject *Sender)
{
  CDirectoryOutline->Visible  = true;

  CDirectoryOutline->Left     = NEWAPPCREATOR_SELECTDIRECTORY_XPOS;
  CDirectoryOutline->Top      = NEWAPPCREATOR_SELECTDIRECTORY_GEN_YPOS;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::TimerCheckStateButtonCreateTimer(TObject *Sender)
{
  ButtonCreate->Enabled = (EditAppPath->Text.Length() && EditGENPath->Text.Length() && EditAppName->Text.Length())?true:false;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
  cfg->SetXPos(Left);
  cfg->SetYPos(Top);

  AjustUserInterfaceToCFG();

  cfg->Save();

//if(DIOFACTORY::GetIsInstanced()) DIOFACTORY::DelInstance();

  if(XSLEEP::GetIsInstanced()) XSLEEP::DelInstance();

  if(XSYSTEM::GetIsInstanced()) XSYSTEM::DelInstance();

  if(XFACTORY::GetIsInstanced()) XFACTORY::DelInstance();
}

//---------------------------------------------------------------------------

bool TForm1::AjustUserInterfaceToCFG()
{
  cfg->GetAppPath()->Set(EditAppPath->Text.c_str());
  cfg->GetGENPath()->Set(EditGENPath->Text.c_str());
  cfg->GetAppCopyright()->Set(EditCopyright->Text.c_str());

  cfg->SetAPPType(RadioGroupAppType->ItemIndex);
  cfg->SetAPPFormat(RadioGroupAppFormat->ItemIndex);

  cfg->SetAddTraceSystem((CheckBoxTrace->State==cbChecked)?true:false);
  cfg->SetAddMemCtrlSystem((CheckBoxMemControl->State==cbChecked)?true:false);
  cfg->SetAddLogSystem((CheckBoxLog->State==cbChecked)?true:false);
  cfg->SetAddCFGSystem((CheckBoxCFGFile->State==cbChecked)?true:false);

  return true;
}

//---------------------------------------------------------------------------

APPMODULEELEMENT* TForm1::CreateAppModuleElement(NEWAPPCREATOR_DIRTYPE dirtype, XCHAR* namefileliteral)
{
  APPMODULEELEMENT* appmoduleelement = new APPMODULEELEMENT();
  if(!appmoduleelement) return NULL;

  appmoduleelement->dirtype = dirtype;
  appmoduleelement->namefile.Add(namefileliteral);

  return appmoduleelement;
}

//---------------------------------------------------------------------------

bool TForm1::LoadToMemoryFiles(NEWAPPCREATOR_APPTYPE apptype)
{
  XVECTOR<APPMODULEELEMENT*>  listfiles;
  XPATH                       path;

  listfiles.Add(CreateAppModuleElement(NEWAPPCREATOR_DIRTYPE_APPLICATION, __L("APP_GEN_Defines.h")));
  listfiles.Add(CreateAppModuleElement(NEWAPPCREATOR_DIRTYPE_APPLICATION, __L("jig.h")));
  listfiles.Add(CreateAppModuleElement(NEWAPPCREATOR_DIRTYPE_APPLICATION, __L("jig.cpp")));

  if(cfg->GetAddCFGSystem())
    {
      listfiles.Add(CreateAppModuleElement(NEWAPPCREATOR_DIRTYPE_APPLICATION, __L("jig_CFG.h")));
      listfiles.Add(CreateAppModuleElement(NEWAPPCREATOR_DIRTYPE_APPLICATION,__L("jig_CFG.cpp")));
    }

  listfiles.Add(CreateAppModuleElement(NEWAPPCREATOR_DIRTYPE_PLATFORMS, __L("CMakeLists.txt")));
  listfiles.Add(CreateAppModuleElement(NEWAPPCREATOR_DIRTYPE_PLATFORMS, __L("CMakeSettings.json")));

  switch(apptype)
    {
      case NEWAPPCREATOR_APPTYPE_BASE       : GEN_XPATHSMANAGER.GetPathOfSection(NEWAPPCREATOR_XPATHSECTIONTYPE_JIGS_BASE, path);         break;
      case NEWAPPCREATOR_APPTYPE_CONSOLE    : GEN_XPATHSMANAGER.GetPathOfSection(NEWAPPCREATOR_XPATHSECTIONTYPE_JIGS_CONSOLE, path);      break;
      case NEWAPPCREATOR_APPTYPE_GRAPHICS   : GEN_XPATHSMANAGER.GetPathOfSection(NEWAPPCREATOR_XPATHSECTIONTYPE_JIGS_GRAPHICS, path);     break;
    }

  bool status = false;

  for(XDWORD c=0; c<listfiles.GetSize(); c++)
    {
      XFILETXT* fileTXT = new XFILETXT();
      if(fileTXT)
        {
          XPATH path2;

          path2 = path;
          path2.Slash_Add();
          path2.Add(listfiles.Get(c)->namefile.Get());

          path2.Slash_Normalize(true);

          if(fileTXT->Open(path2))
            {
              status = fileTXT->ReadAllFile();

              fileTXT->Close();
            }

          if(status)
            {
              filestocreate.Add(fileTXT);

            } else delete fileTXT;
        }
    }




    

  listfiles.DeleteContents();
  listfiles.DeleteAll();

  return true;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonCreateClick(TObject *Sender)
{
  AjustUserInterfaceToCFG();

  LoadToMemoryFiles((NEWAPPCREATOR_APPTYPE)cfg->GetAPPType());
}
//---------------------------------------------------------------------------

