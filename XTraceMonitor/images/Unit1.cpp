//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{


}
//---------------------------------------------------------------------------

void __fastcall TForm1::ValueListEditor1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{

  if(ARow)
  ValueListEditor1->Canvas->Brush->Color = clBlue;
  ValueListEditor1->Canvas->FillRect(Rect);


  /*
  if(( ARow % 2 ) == 0 )
    {
        if( ARow == 0 )
            StringGrid1->Canvas->Brush->Color = clBlue;
        else
            StringGrid1->Canvas->Brush->Color = clGray;


        StringGrid1->Canvas->FillRect( Rect );
    }
  */
}
//---------------------------------------------------------------------------
