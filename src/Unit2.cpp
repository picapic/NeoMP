//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button3Click(TObject *Sender)
{
        Form2->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button2Click(TObject *Sender)
{
        Form2->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button1Click(TObject *Sender)
{
        StartServer();
        Form2->Close();
}
//---------------------------------------------------------------------------

void TForm2::StartServer()
{
        TStringGrid *MainGrid, *VersGrid;
        AnsiString Path, GamePath;
        char cmd[1024];
        char buff[1024];
        TRegistry *reg = new TRegistry(KEY_ALL_ACCESS);
        OSVERSIONINFO osvi;
        BOOL bIsWindowsXP;

        ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

        GetVersionEx(&osvi);

        bIsWindowsXP = ( (osvi.dwMajorVersion == 5) && (osvi.dwMinorVersion >= 1) )?true:false;

        if (reg) // если всё ОК
            {
            // выбираем нужный корень
            reg->RootKey = HKEY_CURRENT_USER;

            // открываем секцию
            reg->OpenKey("Software\\SAMP\\", true); 

            // записываем значения
            GamePath = reg->ReadString("gta_sa_exe");
            reg->WriteString("gta_sa_exe_bak", GamePath);
            GetCurrentDirectory(sizeof(buff), buff);
            strncat(buff, "\\gta_sa.exe", sizeof(buff)); 
            reg->WriteString("gta_sa_exe", buff);
            
            // закрываем секцию
            reg->CloseKey();
        }

        if(Form1->StringGrid1->Visible)
        {
                MainGrid = Form1->StringGrid1;
                VersGrid = Form1->StringGrid3;
        }
        else if(Form1->StringGrid4->Visible)
        {
                MainGrid = Form1->StringGrid4;
                VersGrid = Form1->StringGrid6;
        }
        else if(Form1->StringGrid7->Visible)
        {
                MainGrid = Form1->StringGrid7;
                VersGrid = Form1->StringGrid9;
        }

        GetCurrentDirectory(sizeof(buff), buff);

        if(strncmp(VersGrid->Cells[1][3].c_str(), "0.3.7", 5) == 0 || strncmp(VersGrid->Cells[1][3].c_str(), "DayZ ;) ", 8) == 0)
                Path = ".\\SAMPDATA\\samp037";
        else if(strncmp(VersGrid->Cells[1][3].c_str(), "0.3z", 4) == 0)
                Path = ".\\SAMPDATA\\samp03z";
        else if(strncmp(VersGrid->Cells[1][3].c_str(), "0.3x", 4) == 0)
                Path = ".\\SAMPDATA\\samp03x";
        else if(strncmp(VersGrid->Cells[1][3].c_str(), "0.3e", 4) == 0)
                Path = ".\\SAMPDATA\\samp03e";
        else if(strncmp(VersGrid->Cells[1][3].c_str(), "0.3d", 4) == 0)
                Path = ".\\SAMPDATA\\samp03d";
        else if(strncmp(VersGrid->Cells[1][3].c_str(), "0.3c", 4) == 0)
                Path = ".\\SAMPDATA\\samp03c";
        else if(strncmp(VersGrid->Cells[1][3].c_str(), "0.3b", 4) == 0)
                Path = ".\\SAMPDATA\\samp03b";
        else if(strncmp(VersGrid->Cells[1][3].c_str(), "0.3a", 4) == 0)
                Path = ".\\SAMPDATA\\samp03a";
        else if(strncmp(VersGrid->Cells[1][3].c_str(), "0.2X", 4) == 0)
                Path = ".\\SAMPDATA\\samp02X";
        else if(strncmp(VersGrid->Cells[1][3].c_str(), "0.2.2", 5) == 0)
                Path = ".\\SAMPDATA\\samp022";

        killProcessByName("gta_sa.exe"); //Иногда требуется
        RemoveDirectory(".\\SAMP");
        if(bIsWindowsXP)
        {
          wsprintf(cmd, ("ln -j .\\SAMP "+Path).c_str());
          WinExec(cmd, 0);
        }
        else
        {
          lpCreateSymbolicLink("SAMP", Path.c_str(), SYMBOLIC_LINK_FLAG_DIRECTORY);
        }
        DeleteFile(".\\samp.dll");
        DeleteFile(".\\samp.saa");
        if(bIsWindowsXP)
        {
          wsprintf(cmd, ("ln "+Path+"\\a .\\samp.dll").c_str());
          WinExec(cmd, 0);
          wsprintf(cmd, ("ln "+Path+"\\b .\\samp.saa").c_str());
          WinExec(cmd, 0);
        }
        else
        {
          CreateHardLink("samp.dll", (Path+"\\a").c_str(), NULL);
          CreateHardLink("samp.saa", (Path+"\\b").c_str(), NULL);
        }
        wsprintf(cmd, ".\\samp.exe %s", Label9->Caption.c_str());
        WinExec(cmd, 0);

        Sleep(1000);

        if (reg) // если всё ОК
            {
            // выбираем нужный корень
            reg->RootKey = HKEY_CURRENT_USER;

            // открываем секцию
            reg->OpenKey("Software\\SAMP\\", true); 

            // записываем значения
            GamePath = reg->ReadString("gta_sa_exe_bak");
            reg->WriteString("gta_sa_exe", GamePath);
            
            // закрываем секцию
            reg->CloseKey();
        }
        delete reg;
}
void __fastcall TForm2::FormShow(TObject *Sender)
{
        Form2->Font->Charset = DEFAULT_CHARSET;
        Form2->Button1->Font->Charset = DEFAULT_CHARSET;
        Form2->Button2->Font->Charset = DEFAULT_CHARSET;
        Form2->Button3->Font->Charset = DEFAULT_CHARSET;
        Form2->Label2->Font->Charset = DEFAULT_CHARSET;
        Form2->Label3->Font->Charset = DEFAULT_CHARSET;
        Form2->Label4->Font->Charset = DEFAULT_CHARSET;
        Form2->Label5->Font->Charset = DEFAULT_CHARSET;
        Form2->Label6->Font->Charset = DEFAULT_CHARSET;
        Form2->Label7->Font->Charset = DEFAULT_CHARSET;
        Form2->Label8->Font->Charset = DEFAULT_CHARSET;

        if(AnsiString(Form1->iLanguage).AnsiCompare("es") == 0 ||
           AnsiString(Form1->iLanguage).AnsiCompare("pt") == 0)
        {
                Form2->Font->Charset = EASTEUROPE_CHARSET;
                Form2->Button1->Font->Charset = EASTEUROPE_CHARSET;
                Form2->Button2->Font->Charset = EASTEUROPE_CHARSET;
                Form2->Button3->Font->Charset = EASTEUROPE_CHARSET;
                Form2->Label2->Font->Charset = EASTEUROPE_CHARSET;
                Form2->Label3->Font->Charset = EASTEUROPE_CHARSET;
                Form2->Label4->Font->Charset = EASTEUROPE_CHARSET;
                Form2->Label5->Font->Charset = EASTEUROPE_CHARSET;
                Form2->Label6->Font->Charset = EASTEUROPE_CHARSET;
                Form2->Label7->Font->Charset = EASTEUROPE_CHARSET;
                Form2->Label8->Font->Charset = EASTEUROPE_CHARSET;
        }
        else if(AnsiString(Form1->iLanguage).AnsiCompare("ru") == 0)
        {
                Form2->Font->Charset = RUSSIAN_CHARSET;
                Form2->Button1->Font->Charset = RUSSIAN_CHARSET;
                Form2->Button2->Font->Charset = RUSSIAN_CHARSET;
                Form2->Button3->Font->Charset = RUSSIAN_CHARSET;
                Form2->Label2->Font->Charset = RUSSIAN_CHARSET;
                Form2->Label3->Font->Charset = RUSSIAN_CHARSET;
                Form2->Label4->Font->Charset = RUSSIAN_CHARSET;
                Form2->Label5->Font->Charset = RUSSIAN_CHARSET;
                Form2->Label6->Font->Charset = RUSSIAN_CHARSET;
                Form2->Label7->Font->Charset = RUSSIAN_CHARSET;
                Form2->Label8->Font->Charset = RUSSIAN_CHARSET;
        }

        Form2->Caption = Form1->imes->RetIString("FORM2_CAPTION_TEXT", Form1->iLanguage);                
        Form2->Button1->Caption = Form1->imes->RetIString("CONNECT_MENU", Form1->iLanguage);
        Form2->Button2->Caption = Form1->imes->RetIString("SAVE_BUTTON", Form1->iLanguage);
        Form2->Button3->Caption = Form1->imes->RetIString("CANCEL_BUTTON", Form1->iLanguage);

        Label2->Caption = Form1->imes->RetIString("SERVER_PASSWORD_PAR", Form1->iLanguage);
	Label3->Caption = Form1->imes->RetIString("RCON_PASSWORD_PAR", Form1->iLanguage);

	Label4->Caption = Form1->imes->RetIString("HOST_ADDR_PAR", Form1->iLanguage);
	Label5->Caption = Form1->imes->RetIString("PLAYERS_PAR", Form1->iLanguage);
	Label6->Caption = Form1->imes->RetIString("PING_PAR", Form1->iLanguage);
	Label7->Caption = Form1->imes->RetIString("MODE_PAR", Form1->iLanguage);
	Label8->Caption = Form1->imes->RetIString("MAP_PAR", Form1->iLanguage);
}
//---------------------------------------------------------------------------
