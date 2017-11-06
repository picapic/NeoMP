//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
        Form4->Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        Form4->Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormShow(TObject *Sender)
{
        Form4->Font->Charset = DEFAULT_CHARSET;
        Form4->Label1->Font->Charset = DEFAULT_CHARSET;
        Form4->Label3->Font->Charset = DEFAULT_CHARSET;
        Form4->Label5->Font->Charset = DEFAULT_CHARSET;
        Form4->Label7->Font->Charset = DEFAULT_CHARSET;

        if(AnsiString(Form1->iLanguage).AnsiCompare("es") == 0)
        {
                Form4->Font->Charset = EASTEUROPE_CHARSET;
                Form4->Label1->Font->Charset = EASTEUROPE_CHARSET;
                Form4->Label3->Font->Charset = EASTEUROPE_CHARSET;
                Form4->Label5->Font->Charset = EASTEUROPE_CHARSET;
                Form4->Label7->Font->Charset = EASTEUROPE_CHARSET;
        }
        else if(AnsiString(Form1->iLanguage).AnsiCompare("pt") == 0)
        {
                Form4->Font->Charset = EASTEUROPE_CHARSET;
                Form4->Label1->Font->Charset = EASTEUROPE_CHARSET;
                Form4->Label3->Font->Charset = EASTEUROPE_CHARSET;
                Form4->Label5->Font->Charset = EASTEUROPE_CHARSET;
                Form4->Label7->Font->Charset = EASTEUROPE_CHARSET;
        }
        else if(AnsiString(Form1->iLanguage).AnsiCompare("ru") == 0)
        {
                Form4->Font->Charset = RUSSIAN_CHARSET;
                Form4->Label1->Font->Charset = RUSSIAN_CHARSET;
                Form4->Label3->Font->Charset = RUSSIAN_CHARSET;
                Form4->Label5->Font->Charset = RUSSIAN_CHARSET;
                Form4->Label7->Font->Charset = RUSSIAN_CHARSET;
        }

        Form4->Caption = Form1->imes->RetIString("ABOUT_MENU", Form1->iLanguage);

        Form4->Label1->Caption = Form1->imes->RetIString("FORM4_AUTHOR_TEXT", Form1->iLanguage);
        Form4->Label3->Caption = Form1->imes->RetIString("FORM4_VERSION_TEXT", Form1->iLanguage);
        Form4->Label5->Caption = Form1->imes->RetIString("FORM4_DATE_TEXT", Form1->iLanguage);
        Form4->Label7->Caption = Form1->imes->RetIString("FORM4_THANKS_TEXT", Form1->iLanguage);

        Form4->Label9->Caption = "";
        Form4->Label9->Caption = Form4->Label9->Caption + "L";
        Form4->Label9->Caption = Form4->Label9->Caption + "ó";
        Form4->Label9->Caption = Form4->Label9->Caption + "s";
}
//---------------------------------------------------------------------------



