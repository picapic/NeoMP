//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

int nLanguage;
char szLanguage[][3] = {"ru","en","es","pt","ro","fr","uk","cs","de","it","pl","tr","sr","bg"};

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button2Click(TObject *Sender)
{
        Form3->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button1Click(TObject *Sender)
{
        int i;
        TRegistry *reg = new TRegistry(KEY_ALL_ACCESS);

        if (reg) // если всё ОК
            {
            // выбираем нужный корень
            reg->RootKey = HKEY_CURRENT_USER;

            // открываем секцию
            reg->OpenKey("Software\\SAMP\\", true);

            // записываем значения
//            reg->WriteString("gta_sa_exe", Edit1->Text);
              reg->WriteInteger("SaveServPasses", CheckBox1->Checked?1:0);
              reg->WriteInteger("SaveRconPasses", CheckBox2->Checked?1:0);

            // закрываем секцию
            reg->CloseKey();
            }
        delete reg;

        strncpy(Form1->iLanguage, szLanguage[ComboBox1->ItemIndex], 2);
        Form1->ChangeLanguage();

        OnFormShow();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button3Click(TObject *Sender)
{
        int i;

        OpenDialog1->FileName = "gta_sa.exe";
        OpenDialog1->InitialDir = ".";
        OpenDialog1->Execute();
        for(i = OpenDialog1->FileName.Length(); i > 0; --i)
        {
                if(OpenDialog1->FileName.c_str()[i] == '\\')
                {
                        OpenDialog1->FileName.c_str()[i+1] = '\0';
                        break;
                }
        }
        if(OpenDialog1->FileName.Length() > 10)
                Edit1->Text = OpenDialog1->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormCreate(TObject *Sender)
{
        int i;
        TRegistry *reg = new TRegistry(KEY_ALL_ACCESS);
        
        if (reg) // если всё ОК
            {
            // выбираем нужный корень
            reg->RootKey = HKEY_CURRENT_USER; 

            // открываем секцию
            reg->OpenKey("Software\\SAMP\\", true); 

            // записываем значения
            Edit1->Text = reg->ReadString("gta_sa_exe");
            if(reg->ValueExists("SaveServPasses"))
                    CheckBox1->Checked = reg->ReadInteger("SaveServPasses");
            if(reg->ValueExists("SaveRconPasses"))
                    CheckBox2->Checked = reg->ReadInteger("SaveRconPasses");

            for(i = Edit1->Text.Length(); i > 0; --i)
            {
                    if(Edit1->Text.c_str()[i] == '\\')
                    {
                            Edit1->Text = Edit1->Text.SubString(0, i+1);
                            break;
                    }
            }

            // закрываем секцию
            reg->CloseKey();
            }
        delete reg;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormShow(TObject *Sender)
{
        OnFormShow();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button4Click(TObject *Sender)
{
        int i;
        TRegistry *reg = new TRegistry(KEY_ALL_ACCESS);

        if (reg) // если всё ОК
            {
            // выбираем нужный корень
            reg->RootKey = HKEY_CURRENT_USER;

            // открываем секцию
            reg->OpenKey("Software\\SAMP\\", true);

            // записываем значения
//            reg->WriteString("gta_sa_exe", Edit1->Text);
              reg->WriteInteger("SaveServPasses", CheckBox1->Checked?1:0);
              reg->WriteInteger("SaveRconPasses", CheckBox2->Checked?1:0);

            // закрываем секцию
            reg->CloseKey();
            }
        delete reg;

        strncpy(Form1->iLanguage, szLanguage[ComboBox1->ItemIndex], 2);
        Form1->ChangeLanguage();

        OnFormShow();

        Form3->Close();        
}
//---------------------------------------------------------------------------

void OnFormShow()
{
        int i;
        TRegistry *reg = new TRegistry(KEY_ALL_ACCESS);

        if (reg) // если всё ОК
            {
            // выбираем нужный корень
            reg->RootKey = HKEY_CURRENT_USER; 

            // открываем секцию
            reg->OpenKey("Software\\SAMP\\", true); 

            // записываем значения
            Form3->Edit1->Text = reg->ReadString("gta_sa_exe");
            if(reg->ValueExists("SaveRconPasses"))
                    Form3->CheckBox1->Checked = reg->ReadInteger("SaveServPasses");
            if(reg->ValueExists("SaveRconPasses"))
                    Form3->CheckBox2->Checked = reg->ReadInteger("SaveRconPasses");

            for(i = Form3->Edit1->Text.Length(); i > 0; --i)
            {
                    if(Form3->Edit1->Text.c_str()[i] == '\\')
                    {
                            Form3->Edit1->Text = Form3->Edit1->Text.SubString(0, i+1);
                            break;
                    }
            }

            // закрываем секцию
            reg->CloseKey();
            }
        delete reg;

        Form3->ComboBox1->Clear();
        for(i = 0; i < sizeof(szLanguage)/sizeof(szLanguage[0]); ++i)
        {
//                Form3->ComboBox1->AddItem(szLanguageName[i], NULL);
                Form3->ComboBox1->AddItem(Form1->imes->RetIString("LANGUAGE_NAME", szLanguage[i]), NULL);
                if(strncmp(Form1->iLanguage, szLanguage[i], 2) == 0)
                {
                        nLanguage = i;
                }
        }
        Form3->ComboBox1->ItemIndex = nLanguage;

        Form3->Caption = Form1->imes->RetIString("SETTINGS_MENU", Form1->iLanguage);

        Form3->GroupBox1->Caption = Form1->imes->RetIString("FORM3_PASSWORDS_TEXT", Form1->iLanguage);

        Form3->CheckBox1->Caption = Form1->imes->RetIString("FORM3_SERVER_PASS_TEXT", Form1->iLanguage);
        Form3->CheckBox2->Caption = Form1->imes->RetIString("FORM3_RCON_PASS_TEXT", Form1->iLanguage);

        Form3->Label1->Caption = Form1->imes->RetIString("FORM3_LOCATION_TEXT", Form1->iLanguage);
        Form3->Label2->Caption = Form1->imes->RetIString("FORM3_LANGUAGE_TEXT", Form1->iLanguage);

        Form3->Button1->Caption = Form1->imes->RetIString("SAVE_BUTTON", Form1->iLanguage);
        Form3->Button2->Caption = Form1->imes->RetIString("CANCEL_BUTTON", Form1->iLanguage);
        Form3->Button4->Caption = Form1->imes->RetIString("OK_BUTTON", Form1->iLanguage);
}
//---------------------------------------------------------------------------


