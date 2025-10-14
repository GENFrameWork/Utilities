//---------------------------------------------------------------------------

#include "Unit1.h"

#include <vcl.h>
#pragma hdrstop

USEFORM("Unit1.cpp", MainForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR command, int)
{
  try
    {
      Application->Initialize();
      Application->CreateForm(__classid(TMainForm), &MainForm);
                 if(command[0]) MainForm->Caption = command;

      Application->Run();
    }
  catch (Exception &exception)
    {
      Application->ShowException(&exception);
    }
    
  return 0;
}
//---------------------------------------------------------------------------







