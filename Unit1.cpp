//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "perfgrap"
#pragma link "PERFGRAP"
#pragma link "PERFGRAP"
#pragma link "PERFGRAP"
#pragma link "PERFGRAP"
#pragma link "PERFGRAP"
#pragma resource "*.dfm"

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
		: TForm(Owner)
{
        TRegistry *reg = new TRegistry(KEY_ALL_ACCESS);

        GroupBox1->Height = 106;
        GroupBox2->Height = 106;
        TabControl1->Height = 488;

        if (reg) // если всё ОК
        {
            // выбираем нужный корень
            reg->RootKey = HKEY_CURRENT_USER;

            // открываем секцию
            reg->OpenKey("Software\\SAMP\\", true);

            if(reg->ValueExists("ExtraOptions"))  //показывать дополнительные опции
            {
                fExtraOptions = (reg->ReadInteger("ExtraOptions") == 0) ? false : true;
            }
            else
            {
                reg->WriteInteger("ExtraOptions", 1);
                if(reg->ValueExists("ExtraOptions"))
                {
                        fExtraOptions = (reg->ReadInteger("ExtraOptions") == 0) ? false : true;
                }
                else
                {
                        fExtraOptions = true;
                }
            }

            // закрываем секцию
            reg->CloseKey();
        }
        delete reg;

        ExtraHeight = 70;

        if(fExtraOptions)
        {
                Height = 550 + ExtraHeight;
                GroupBox1->Height += ExtraHeight;
                GroupBox2->Height += ExtraHeight;
                Form1->Constraints->MinHeight += ExtraHeight;
                Label19->Visible = true;
                Edit4->Visible = true;
                CheckBox4->Visible = true;
                CheckBox5->Visible = true;
                CheckBox6->Visible = true;
                CheckBox7->Visible = true;
                CheckBox8->Visible = true;
                CheckBox9->Visible = true;
                CheckBox10->Visible = true;
                CheckBox11->Visible = true;
                CheckBox12->Visible = true;
                CheckBox13->Visible = true;
        }
        else
        {
                Height = 550;
                Label19->Visible = false;
                Edit4->Visible = false;
                CheckBox4->Visible = false;
                CheckBox5->Visible = false;
                CheckBox6->Visible = false;
                CheckBox7->Visible = false;
                CheckBox8->Visible = false;
                CheckBox9->Visible = false;
                CheckBox10->Visible = false;
                CheckBox11->Visible = false;
                CheckBox12->Visible = false;
                CheckBox13->Visible = false;
        }
        
        return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FiltrServerInfo1Click(TObject *Sender)
{
	FiltrServerInfo1->Checked = FiltrServerInfo1->Checked^1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StatusBar2Click(TObject *Sender)
{
	StatusBar2->Checked = StatusBar2->Checked^1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TabControl1Change(TObject *Sender)
{
        char table[128];
        char request[1024];
        sqlite3_stmt *stmt;
        
	switch(TabControl1->TabIndex)
	{
		case 0:
                        strncpy(table, "favorites", sizeof(table));
			Panel1->Show();
			Panel3->Visible = false;
			Panel4->Visible = false;

                        Image2->Visible = false;
                        Image32->Visible = true;
                        Image8->Visible = true;
                        Image33->Visible = false;
                        Image12->Visible = false;
                        Image34->Visible = true;
                        Image15->Visible = false;
                        Image35->Visible = true;
                        Image18->Visible = false;
                        Image36->Visible = true;
                        Image21->Visible = false;
                        Image37->Visible = true;

                        StringGrid1->Visible = true;
                        StringGrid4->Visible = false;
                        StringGrid7->Visible = false;

                        CheckBox14->Enabled = false;
			break;
		case 1:
                        strncpy(table, "internet", sizeof(table));
                
			Panel1->Visible = false;
			Panel3->Show();
			Panel4->Visible = false;

                        Image2->Visible = false;
                        Image32->Visible = true;
                        Image8->Visible = false;
                        Image33->Visible = true;
                        Image12->Visible = false;
                        Image34->Visible = true;
                        Image15->Visible = true;
                        Image35->Visible = false;
                        Image18->Visible = false;
                        Image36->Visible = true;
                        Image21->Visible = false;
                        Image37->Visible = true;

                        StringGrid1->Visible = false;
                        StringGrid4->Visible = true;
                        StringGrid7->Visible = false;

                        CheckBox14->Enabled = true;
			break;
		case 2:
                        strncpy(table, "hosted", sizeof(table));
                
			Panel1->Visible = false;
			Panel3->Visible = false;
			Panel4->Show();

                        Image2->Visible = false;
                        Image32->Visible = true;
                        Image8->Visible = false;
                        Image33->Visible = true;
                        Image12->Visible = false;
                        Image34->Visible = true;
                        Image15->Visible = true;
                        Image35->Visible = false;
                        Image18->Visible = false;
                        Image36->Visible = true;
                        Image21->Visible = false;
                        Image37->Visible = true;

                        StringGrid1->Visible = false;
                        StringGrid4->Visible = false;
                        StringGrid7->Visible = true;

                        CheckBox14->Enabled = true;
			break;
    }

    memset(request, 0, sizeof(request)/sizeof(char));
    wsprintf(request, "SELECT SUM(players),SUM(maxplayers),count(*) FROM %s", table);
    sqlite3_prepare(Form1->conn, request, -1, &stmt, 0); //подготовка запроса
    sqlite3_step(stmt); //выполняем запрос
    Label18->Caption = AnsiString(imes->RetIString("SERVERS_STR", iLanguage)+AnsiString(sqlite3_column_int(stmt, 0))+
        imes->RetIString("PLAYING_ON_STR", iLanguage)+AnsiString(sqlite3_column_int(stmt, 2))+
        imes->RetIString("ON_SERVERS_STR", iLanguage)+AnsiString(sqlite3_column_int(stmt, 1))+
        imes->RetIString("SLOTS_STR", iLanguage));
    sqlite3_reset(stmt); //сбрасываем инструкцию (stmt)
    sqlite3_finalize(stmt); //очищаем запрос
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseLeave(TObject *Sender)
{
	Image1->Visible = false;
	Image3->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseEnter(TObject *Sender)
{
	Image1->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Image1->Visible = false;
	Image3->Show();
	Image2->Left = 4;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Image3->Visible = false;
//	Image1->Show();
	Image2->Left = 3;

	Image4->Visible = false;
	Image6->Visible = false;
	Image1->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image4MouseLeave(TObject *Sender)
{
	Image4->Visible = false;
	Image6->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image4MouseEnter(TObject *Sender)
{
	Image4->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image4MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Image4->Visible = false;
	Image6->Show();
	Image5->Left = 35;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image4MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Image6->Visible = false;
//	Image4->Show();
	Image5->Left = 34;

	Image7->Visible = false;
	Image9->Visible = false;
	Image4->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image7MouseLeave(TObject *Sender)
{
	Image7->Visible = false;
	Image9->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image7MouseEnter(TObject *Sender)
{
	Image7->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image7MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Image7->Visible = false;
	Image9->Show();
	Image8->Left = 58;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image7MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Image9->Visible = false;
//	Image7->Show();
	Image8->Left = 57;

	Image11->Visible = false;
	Image10->Visible = false;
	Image7->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image11MouseLeave(TObject *Sender)
{
	Image11->Visible = false;
	Image10->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image11MouseEnter(TObject *Sender)
{
	Image11->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image11MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Image11->Visible = false;
	Image10->Show();
	Image12->Left = 81;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image11MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Image10->Visible = false;
//	Image11->Show();
	Image12->Left = 80;

	Image14->Visible = false;
	Image13->Visible = false;
	Image11->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image14MouseLeave(TObject *Sender)
{
	Image14->Visible = false;
	Image13->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image14MouseEnter(TObject *Sender)
{
	Image14->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image14MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Image14->Visible = false;
	Image13->Show();
	Image15->Left = 112;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image14MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Image13->Visible = false;
//      Image14->Show();
	Image15->Left = 111;

	Image17->Visible = false;
	Image16->Visible = false;
	Image14->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image17MouseLeave(TObject *Sender)
{
	Image17->Visible = false;
	Image16->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image17MouseEnter(TObject *Sender)
{
	Image17->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image17MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Image17->Visible = false;
	Image16->Show();
	Image18->Left = 143;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image17MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Image16->Visible = false;
//	Image17->Show();
	Image18->Left = 142;

	Image20->Visible = false;
	Image19->Visible = false;
	Image17->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image20MouseLeave(TObject *Sender)
{
	Image20->Visible = false;
	Image19->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image20MouseEnter(TObject *Sender)
{
	Image20->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image20MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Image20->Visible = false;
	Image19->Show();
	Image21->Left = 166;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image20MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Image19->Visible = false;
//	Image20->Show();
	Image21->Left = 165;

	Image23->Visible = false;
	Image22->Visible = false;
	Image20->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image23MouseLeave(TObject *Sender)
{
	Image23->Visible = false;
	Image22->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image23MouseEnter(TObject *Sender)
{
	Image23->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image23MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Image23->Visible = false;
	Image22->Show();
	Image24->Left = 197;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image23MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Image22->Visible = false;
//	Image23->Show();
	Image24->Left = 196;

	Image26->Visible = false;
	Image25->Visible = false;
	Image23->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image26MouseLeave(TObject *Sender)
{
	Image26->Visible = false;
	Image25->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image26MouseEnter(TObject *Sender)
{
	Image26->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image26MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Image26->Visible = false;
	Image25->Show();
	Image27->Left = 228;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image26MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Image25->Visible = false;
//	Image26->Show();
	Image27->Left = 227;

	Image29->Visible = false;
	Image28->Visible = false;
	Image26->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image29MouseLeave(TObject *Sender)
{
	Image29->Visible = false;
	Image28->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image29MouseEnter(TObject *Sender)
{
	Image29->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image29MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Image29->Visible = false;
	Image28->Show();
	Image30->Left = 251;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image29MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	Image28->Visible = false;
//	Image29->Show();
	Image30->Left = 250;

	Image29->Visible = false;
	Image28->Visible = false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{
	int Column1, Column2, Column3, Column4, Column5, Column6, Column7, Column8, Column9, Column10, Column11, Row0;
        WSADATA wsaData;
        char *sErrMsg;
        AnsiString GamePath, Path;
        char buff[1024];
        char cmd[1024];
        char str[2048];
        char request[1024];
        sqlite3_stmt *stmt;
        DIR *dir;
        FILE *fd;
        TRegistry *reg = new TRegistry(KEY_ALL_ACCESS);
        OSVERSIONINFO osvi;
        BOOL bIsWindowsXP;
        AnsiString ansiLang;

        close_time_stamp = time(NULL);

        imes = new IMes(".\\imes.txt");

        if(!imes->IsFileOpened())
        {
                close_time_stamp = time(NULL) + 3600000;
                MessageBox(NULL, "A second copy of this program is starting or there is an error in imessage file (imes.txt)", "Error", MB_ICONSTOP);
                exit(0);
        }
        memset(iLanguage, 0, sizeof(iLanguage));
        strncpy(iLanguage, "ru", 2); 
        
        ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

        GetVersionEx(&osvi);

        bIsWindowsXP = ( (osvi.dwMajorVersion == 5) && (osvi.dwMinorVersion >= 1) )?true:false;

        Extraoptions1->Checked = fExtraOptions;
        
        if (reg) // если всё ОК
            {
            // выбираем нужный корень
            reg->RootKey = HKEY_CURRENT_USER;

            // открываем секцию
            reg->OpenKey("Software\\SAMP\\", true); 

            // считываем значения
            Edit1->Text = reg->ReadString("PlayerName");
            if(reg->ValueExists("ExtraOptions"))
            {
                fExtraOptions = (reg->ReadInteger("ExtraOptions") == 0) ? false : true;
            }
            else
            {
                reg->WriteInteger("ExtraOptions", 1);
                if(reg->ValueExists("ExtraOptions"))
                {
                    fExtraOptions = (reg->ReadInteger("ExtraOptions") == 0) ? false : true;
                }
                else
                {
                        fExtraOptions = true;
                }
            }
            GamePath = reg->ReadString("gta_sa_exe");
            if(reg->ValueExists("Language"))
            {
                ansiLang = reg->ReadString("Language");
            }
            if(ansiLang.Length() <= 0)
            {
                strncpy(iLanguage, "en", 2);
            }
            else
            {
                strncpy(iLanguage, ansiLang.c_str(), 2);
            }

            // закрываем секцию
            reg->CloseKey();

            Path = GamePath.SubString(0, GamePath.Pos("\\gta_sa.exe"));
            GetCurrentDirectory(sizeof(buff), buff);
            strncat(buff, "\\gta_sa.exe", sizeof(buff));

            dir = opendir("anim");
            fd = fopen("bass.dll", "r");
            if(dir > 0)
            {
                    closedir(dir);
            }
            else
            {
                    if(fd > 0)
                    {
                            fclose(fd);
//                            CreateFile("anim", GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//                            MessageBox(NULL,(Path+"gta_sa.exe").c_str(),"",MB_OK);
//                            CreateHardLink(buff, (Path+"gta_sa.exe").c_str(), NULL);
                            if(bIsWindowsXP)
                            {
                                wsprintf(cmd, ("ln \""+Path+"gta_sa.exe\" "+buff).c_str());
                                WinExec(cmd, 0);
                                wsprintf(cmd, ("ln -j .\\anim \""+Path+"anim\"").c_str());
                                WinExec(cmd, 0);
                                wsprintf(cmd, ("ln -j .\\audio \""+Path+"audio\"").c_str());
                                WinExec(cmd, 0);
                                wsprintf(cmd, ("ln -j .\\data \""+Path+"data\"").c_str());
                                WinExec(cmd, 0);
                                wsprintf(cmd, ("ln -j .\\models \""+Path+"models\"").c_str());
                                WinExec(cmd, 0);
                                wsprintf(cmd, ("ln -j .\\movies \""+Path+"movies\"").c_str());
                                WinExec(cmd, 0);
                                wsprintf(cmd, ("ln -j .\\text \""+Path+"text\"").c_str());
                                WinExec(cmd, 0);
                            }
                            else
                            {
                                if(lpCreateSymbolicLink)
                                {
                                    lpCreateSymbolicLink(buff, (Path+"gta_sa.exe").c_str(), 0);
                                    lpCreateSymbolicLink("anim", (Path+"anim").c_str(), SYMBOLIC_LINK_FLAG_DIRECTORY);
                                    lpCreateSymbolicLink("audio", (Path+"audio").c_str(), SYMBOLIC_LINK_FLAG_DIRECTORY);
                                    lpCreateSymbolicLink("data", (Path+"data").c_str(), SYMBOLIC_LINK_FLAG_DIRECTORY);
                                    lpCreateSymbolicLink("models", (Path+"models").c_str(), SYMBOLIC_LINK_FLAG_DIRECTORY);
                                    lpCreateSymbolicLink("movies", (Path+"movies").c_str(), SYMBOLIC_LINK_FLAG_DIRECTORY);
                                    lpCreateSymbolicLink("text", (Path+"text").c_str(), SYMBOLIC_LINK_FLAG_DIRECTORY);
                                }
                            }
                    }
            }
        }
        delete reg;
        
        WSAStartup(MAKEWORD(2,2), &wsaData);

        //открываем базу данных
        rc = sqlite3_open16( L"Servers.db", &conn );
        sqlite3_exec(conn, "PRAGMA synchronous = OFF", NULL, NULL, &sErrMsg);

        SleepInterval = 20;
        
        Image2->Visible = false;
        Image32->Visible = true;
        Image12->Visible = false;
        Image34->Visible = true;
        Image15->Visible = false;
        Image35->Visible = true;
        Image18->Visible = false;
        Image36->Visible = true;
        Image21->Visible = false;
        Image37->Visible = true;

//        Form1->Height = 550;
        Form1->Width = 868;

        Form1->Font->Charset = DEFAULT_CHARSET;
        Form1->Label2->Font->Charset = DEFAULT_CHARSET;
        Form1->Label3->Font->Charset = DEFAULT_CHARSET;
        Form1->Label4->Font->Charset = DEFAULT_CHARSET;
        Form1->Label5->Font->Charset = DEFAULT_CHARSET;
        Form1->Label6->Font->Charset = DEFAULT_CHARSET;
        Form1->Label7->Font->Charset = DEFAULT_CHARSET;
        Form1->Label8->Font->Charset = DEFAULT_CHARSET;
        Form1->Label14->Font->Charset = DEFAULT_CHARSET;
        Form1->Label18->Font->Charset = DEFAULT_CHARSET;
        Form1->Label19->Font->Charset = DEFAULT_CHARSET;
        Form1->Label20->Font->Charset = DEFAULT_CHARSET;
        Form1->Label21->Font->Charset = DEFAULT_CHARSET;
        Form1->Label22->Font->Charset = DEFAULT_CHARSET;
        Form1->Label23->Font->Charset = DEFAULT_CHARSET;

        Form1->TabControl1->Font->Charset = DEFAULT_CHARSET;

        Form1->GroupBox1->Font->Charset = DEFAULT_CHARSET;
        Form1->GroupBox2->Font->Charset = DEFAULT_CHARSET;
        Form1->CheckBox1->Font->Charset = DEFAULT_CHARSET;
        Form1->CheckBox2->Font->Charset = DEFAULT_CHARSET;
        Form1->CheckBox3->Font->Charset = DEFAULT_CHARSET;
        Form1->CheckBox14->Font->Charset = DEFAULT_CHARSET;

        Form1->StringGrid1->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid2->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid3->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid4->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid5->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid6->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid7->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid8->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid9->Font->Charset = DEFAULT_CHARSET;


        if(AnsiString(Form1->iLanguage).AnsiCompare("es") == 0 ||
           AnsiString(Form1->iLanguage).AnsiCompare("pt") == 0)
        {
                Form1->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label2->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label3->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label4->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label5->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label6->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label7->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label8->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label14->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label18->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label19->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label20->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label21->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label22->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label23->Font->Charset = EASTEUROPE_CHARSET;
                Form1->TabControl1->Font->Charset = EASTEUROPE_CHARSET;

                Form1->GroupBox1->Font->Charset = EASTEUROPE_CHARSET;
                Form1->GroupBox2->Font->Charset = EASTEUROPE_CHARSET;
                Form1->CheckBox1->Font->Charset = EASTEUROPE_CHARSET;
                Form1->CheckBox2->Font->Charset = EASTEUROPE_CHARSET;
                Form1->CheckBox3->Font->Charset = EASTEUROPE_CHARSET;
                Form1->CheckBox14->Font->Charset = EASTEUROPE_CHARSET;

                Form1->StringGrid1->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid2->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid3->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid4->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid5->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid6->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid7->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid8->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid9->Font->Charset = EASTEUROPE_CHARSET;
        }

        Form1->Caption = imes->RetIString("FORM1_CAPTION_TEXT", iLanguage);

        N1->Caption = imes->RetIString("FILE_MENU", iLanguage);
        N2->Caption = imes->RetIString("LOAD_MENU", iLanguage);
        N3->Caption = imes->RetIString("SAVE_MENU", iLanguage);
        N5->Caption = imes->RetIString("EXIT_MENU", iLanguage);
        N6->Caption = imes->RetIString("VIEW_MENU", iLanguage);
        FiltrServerInfo1->Caption = imes->RetIString("FILTER_MENU", iLanguage);
        StatusBar2->Caption = imes->RetIString("STATUS_MENU", iLanguage);
        Extraoptions1->Caption = imes->RetIString("EXTRA_MENU", iLanguage);
        N7->Caption = imes->RetIString("SERVERS_MENU", iLanguage);
        N8->Caption = imes->RetIString("CONNECT_MENU", iLanguage);
        N13->Caption = imes->RetIString("ADD_SERVER_MENU", iLanguage);
        N14->Caption = imes->RetIString("DELETE_SERVER_MENU", iLanguage);
        N15->Caption = imes->RetIString("REFRESH_SERVER_MENU", iLanguage);
        N17->Caption = imes->RetIString("MASTER_LIST_MENU", iLanguage);
        N19->Caption = imes->RetIString("COPY_INFO_MENU", iLanguage);
        N20->Caption = imes->RetIString("SERVER_INFO_MENU", iLanguage);

        N9->Caption = imes->RetIString("TOOLS_MENU", iLanguage);
        N11->Caption = imes->RetIString("SETTINGS_MENU", iLanguage);

        N10->Caption = imes->RetIString("HELP_MENU", iLanguage);
        Wiki1->Caption = imes->RetIString("WIKI_MENU", iLanguage);
        About1->Caption = imes->RetIString("ABOUT_MENU", iLanguage);

        TabControl1->Tabs->Strings[0] = imes->RetIString("FAVORITES_PAR", iLanguage);
        TabControl1->Tabs->Strings[1] = imes->RetIString("INTERNET_PAR", iLanguage);
        TabControl1->Tabs->Strings[2] = imes->RetIString("HOSTED_PAR", iLanguage);

	Label1->Caption = imes->RetIString("PLAYER_NAME_PAR", iLanguage);

	Label2->Caption = imes->RetIString("MODE_PAR", iLanguage);
	Label3->Caption = imes->RetIString("MAP_PAR", iLanguage);

	Label4->Caption = imes->RetIString("HOST_ADDR_PAR", iLanguage);
	Label5->Caption = imes->RetIString("PLAYERS_PAR", iLanguage);
	Label6->Caption = imes->RetIString("PING_PAR", iLanguage);
	Label7->Caption = imes->RetIString("MODE_PAR", iLanguage);
	Label8->Caption = imes->RetIString("MAP_PAR", iLanguage);

      	Label14->Caption = imes->RetIString("PING_COL", iLanguage);

      	Label19->Caption = imes->RetIString("HOST_NAME_PAR", iLanguage);

        GroupBox1->Caption = imes->RetIString("FILTER_PAR", iLanguage);
        GroupBox2->Caption = imes->RetIString("ABOUT_SERVER_PAR", iLanguage);

        CheckBox1->Caption = "";//imes->RetIString("NOT_FULL_PAR", iLanguage);
      	Label20->Caption = imes->RetIString("NOT_FULL_PAR", iLanguage);
        CheckBox2->Caption = "";//imes->RetIString("NOT_EMPTY_PAR", iLanguage);
        Label21->Caption = imes->RetIString("NOT_EMPTY_PAR", iLanguage);
        CheckBox3->Caption = "";//imes->RetIString("NO_PASSWORD_PAR", iLanguage);
        Label22->Caption = imes->RetIString("NO_PASSWORD_PAR", iLanguage);
        CheckBox14->Caption = "";//imes->RetIString("MASTER_LIST_PAR", iLanguage);
        Label23->Caption = imes->RetIString("MASTER_LIST_PAR", iLanguage);

        Row0 = 16;
        
	Column1 = 20;
	Column2 = 300;
	Column3 = 55;
	Column4 = 35;
	Column5 = 100;
	Column6 = 87;

	Column7 = 130;
	Column8 = 70;

	Column9 = 110;
	Column10 = 90;

        Column11 = 500;

        StringGrid1->RowHeights[0] = Row0;
	StringGrid1->ColWidths[0] = Column1;
	StringGrid1->ColWidths[1] = Column2;
	StringGrid1->ColWidths[2] = Column3;
	StringGrid1->ColWidths[3] = Column4;
	StringGrid1->ColWidths[4] = Column5;
	StringGrid1->ColWidths[5] = Column6;
	StringGrid1->ColWidths[6] = Column11;

        StringGrid2->RowHeights[0] = Row0;
	StringGrid2->ColWidths[0] = Column7;
	StringGrid2->ColWidths[1] = Column8;
	StringGrid2->ColWidths[2] = Column11;

        StringGrid3->RowHeights[0] = Row0;
	StringGrid3->ColWidths[0] = Column9;
	StringGrid3->ColWidths[1] = Column10;
	StringGrid3->ColWidths[2] = Column11;

	StringGrid1->Cells[1][0] = imes->RetIString("HOST_NAME_COL", iLanguage);
	StringGrid1->Cells[2][0] = imes->RetIString("PLAYERS_COL", iLanguage);
	StringGrid1->Cells[3][0] = imes->RetIString("PING_COL", iLanguage);
	StringGrid1->Cells[4][0] = imes->RetIString("MODE_COL", iLanguage);
	StringGrid1->Cells[5][0] = imes->RetIString("MAP_COL", iLanguage);

	StringGrid2->Cells[0][0] = imes->RetIString("PLAYER_COL", iLanguage);
	StringGrid2->Cells[1][0] = imes->RetIString("SCORE_COL", iLanguage);

	StringGrid3->Cells[0][0] = imes->RetIString("RULE_COL", iLanguage);
	StringGrid3->Cells[1][0] = imes->RetIString("VALUE_COL", iLanguage);

        StringGrid4->RowHeights[0] = Row0;
	StringGrid4->ColWidths[0] = Column1;
	StringGrid4->ColWidths[1] = Column2;
	StringGrid4->ColWidths[2] = Column3;
	StringGrid4->ColWidths[3] = Column4;
	StringGrid4->ColWidths[4] = Column5;
	StringGrid4->ColWidths[5] = Column6;
      	StringGrid4->ColWidths[6] = Column11;

        StringGrid5->RowHeights[0] = Row0;
	StringGrid5->ColWidths[0] = Column7;
	StringGrid5->ColWidths[1] = Column8;
	StringGrid5->ColWidths[2] = Column11;

        StringGrid6->RowHeights[0] = Row0;
	StringGrid6->ColWidths[0] = Column9;
	StringGrid6->ColWidths[1] = Column10;
	StringGrid6->ColWidths[2] = Column11;

	StringGrid4->Cells[1][0] = imes->RetIString("HOST_NAME_COL", iLanguage);
	StringGrid4->Cells[2][0] = imes->RetIString("PLAYERS_COL", iLanguage);
	StringGrid4->Cells[3][0] = imes->RetIString("PING_COL", iLanguage);
	StringGrid4->Cells[4][0] = imes->RetIString("MODE_COL", iLanguage);
	StringGrid4->Cells[5][0] = imes->RetIString("MAP_COL", iLanguage);

	StringGrid5->Cells[0][0] = imes->RetIString("PLAYER_COL", iLanguage);
	StringGrid5->Cells[1][0] = imes->RetIString("SCORE_COL", iLanguage);

	StringGrid6->Cells[0][0] = imes->RetIString("RULE_COL", iLanguage);
	StringGrid6->Cells[1][0] = imes->RetIString("VALUE_COL", iLanguage);

        StringGrid7->RowHeights[0] = Row0;
	StringGrid7->ColWidths[0] = Column1;
	StringGrid7->ColWidths[1] = Column2;
	StringGrid7->ColWidths[2] = Column3;
	StringGrid7->ColWidths[3] = Column4;
	StringGrid7->ColWidths[4] = Column5;
	StringGrid7->ColWidths[5] = Column6;
	StringGrid7->ColWidths[6] = Column11;

        StringGrid8->RowHeights[0] = Row0;
	StringGrid8->ColWidths[0] = Column7;
	StringGrid8->ColWidths[1] = Column8;
	StringGrid8->ColWidths[2] = Column11;

        StringGrid9->RowHeights[0] = Row0;
	StringGrid9->ColWidths[0] = Column9;
	StringGrid9->ColWidths[1] = Column10;
	StringGrid9->ColWidths[2] = Column11;

	StringGrid7->Cells[1][0] = imes->RetIString("HOST_NAME_COL", iLanguage);
	StringGrid7->Cells[2][0] = imes->RetIString("PLAYERS_COL", iLanguage);
	StringGrid7->Cells[3][0] = imes->RetIString("PING_COL", iLanguage);
	StringGrid7->Cells[4][0] = imes->RetIString("MODE_COL", iLanguage);
	StringGrid7->Cells[5][0] = imes->RetIString("MAP_COL", iLanguage);

	StringGrid8->Cells[0][0] = imes->RetIString("PLAYER_COL", iLanguage);
	StringGrid8->Cells[1][0] = imes->RetIString("SCORE_COL", iLanguage);

	StringGrid9->Cells[0][0] = imes->RetIString("RULE_COL", iLanguage);
	StringGrid9->Cells[1][0] = imes->RetIString("VALUE_COL", iLanguage);

        Form1->DoubleBuffered = true;
        Panel1->DoubleBuffered = true;
        Panel3->DoubleBuffered = true;
        Panel4->DoubleBuffered = true;
        StringGrid1->DoubleBuffered = true;
        StringGrid2->DoubleBuffered = true;
        StringGrid3->DoubleBuffered = true;
        StringGrid4->DoubleBuffered = true;
        StringGrid5->DoubleBuffered = true;
        StringGrid6->DoubleBuffered = true;
        StringGrid7->DoubleBuffered = true;
        StringGrid8->DoubleBuffered = true;
        StringGrid9->DoubleBuffered = true;
        TabControl1->DoubleBuffered = true;
        GroupBox1->DoubleBuffered = true;
        GroupBox2->DoubleBuffered = true;
        Edit2->DoubleBuffered = true;
        Edit3->DoubleBuffered = true;
        CheckBox1->DoubleBuffered = true;
        CheckBox2->DoubleBuffered = true;
        CheckBox3->DoubleBuffered = true;

        StringGrid1->Font->Color = TColor(0);
        StringGrid2->Font->Color = TColor(0);
        StringGrid3->Font->Color = TColor(0);
        StringGrid4->Font->Color = TColor(0);
        StringGrid5->Font->Color = TColor(0);
        StringGrid6->Font->Color = TColor(0);
        StringGrid7->Font->Color = TColor(0);
        StringGrid8->Font->Color = TColor(0);
        StringGrid9->Font->Color = TColor(0);

        StringGrid1->Visible = true;
        StringGrid4->Visible = false;
        StringGrid7->Visible = false;

        CheckBox14->Enabled = false;

        PerformanceGraph1->Width = Form1->ClientWidth - PerformanceGraph1->Left - GroupBox1->Width - 8;
        PerformanceGraph1->Show();

	Panel1->Show();
	Panel3->Hide();
	Panel4->Hide();

        //поток, запускающий все остальные потоки
        hStartProgram = CreateThread(NULL, 0, ThreadStartProgram, (void *)NULL, 0, &thread_start_program);
//        SetServerProperties((TObject *)Form1->StringGrid1, 1, false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image31Click(TObject *Sender)
{
//        Privet(NULL, NULL, "", 1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
        StringGrid1->Width = StringGrid1->Width - (Panel1->Width - (gNewWidth-(Form1->BorderWidth*2)-15));
        StringGrid2->Left = StringGrid1->Width + 6;
        StringGrid3->Left = StringGrid1->Width + 6;

        StringGrid4->Width = StringGrid4->Width - (Panel3->Width - (gNewWidth-(Form1->BorderWidth*2)-15));
        StringGrid5->Left = StringGrid4->Width + 6;
        StringGrid6->Left = StringGrid4->Width + 6;

        StringGrid7->Width = StringGrid7->Width - (Panel4->Width - (gNewWidth-(Form1->BorderWidth*2)-15));
        StringGrid8->Left = StringGrid7->Width + 6;
        StringGrid9->Left = StringGrid7->Width + 6;

        TabControl1->Width = gNewWidth-(Form1->BorderWidth*2)-16;
        TabControl1->Height = gNewHeight-105;//(Form1->BorderWidth*2)-16-ControlBar1->Height-TabControl1->Top;
        
        Panel1->Width = gNewWidth-(Form1->BorderWidth*2)-15;
        Panel3->Width = gNewWidth-(Form1->BorderWidth*2)-15;
        Panel4->Width = gNewWidth-(Form1->BorderWidth*2)-15;

        Panel1->Height = TabControl1->Height-TabControl1->TabHeight-GroupBox1->Height;
        Panel3->Height = TabControl1->Height-TabControl1->TabHeight-GroupBox1->Height;
        Panel4->Height = TabControl1->Height-TabControl1->TabHeight-GroupBox1->Height;

        if(fExtraOptions)
        {
            StringGrid1->Height = TabControl1->ClientHeight - 127 - ExtraHeight;
            StringGrid4->Height = TabControl1->ClientHeight - 127 - ExtraHeight;
            StringGrid7->Height = TabControl1->ClientHeight - 127 - ExtraHeight;

            StringGrid2->Height = TabControl1->ClientHeight - StringGrid3->Height - 157 - ExtraHeight;
            StringGrid5->Height = TabControl1->ClientHeight - StringGrid6->Height - 157 - ExtraHeight;
            StringGrid8->Height = TabControl1->ClientHeight - StringGrid9->Height - 157 - ExtraHeight;
        }
        else
        {
            StringGrid1->Height = TabControl1->ClientHeight - 127;
            StringGrid4->Height = TabControl1->ClientHeight - 127;
            StringGrid7->Height = TabControl1->ClientHeight - 127;

            StringGrid2->Height = TabControl1->ClientHeight - StringGrid3->Height - 157;
            StringGrid5->Height = TabControl1->ClientHeight - StringGrid6->Height - 157;
            StringGrid8->Height = TabControl1->ClientHeight - StringGrid9->Height - 157;
        }

        StringGrid3->Top = StringGrid2->Height + 5;
        StringGrid6->Top = StringGrid5->Height + 5;
        StringGrid9->Top = StringGrid8->Height + 5;

        GroupBox1->Top = StringGrid1->Height + 2;
        GroupBox2->Top = StringGrid1->Height + 2;

        GroupBox2->Width = gNewWidth-(Form1->BorderWidth*2)-15;

        Image31->Left = gNewWidth-(Image31->Width+Form1->BorderWidth+16);

        Label16->Top = StringGrid3->Top + StringGrid3->Height + 7;
        Label15->Top = StringGrid3->Top + StringGrid6->Height + 7;
        Label17->Top = StringGrid3->Top + StringGrid9->Height + 7;

        Label16->Left = gNewWidth-Label16->Width-Form1->BorderWidth*2-15-(StringGrid9->Width-Label16->Width)/2;
        Label15->Left = gNewWidth-Label15->Width-Form1->BorderWidth*2-15-(StringGrid3->Width-Label15->Width)/2;
        Label17->Left = gNewWidth-Label17->Width-Form1->BorderWidth*2-15-(StringGrid6->Width-Label17->Width)/2;

//        ControlBar1->Width = gNewWidth - Form1->BorderWidth*2 - 42;
//        ControlBar1->Top = gNewHeight - Form1->BorderWidth*2 - ControlBar1->Height;

//        PerformanceGraph1->Width = Form1->ClientWidth - PerformanceGraph1->Left - GroupBox1->Width - 5;
//        PerformanceGraph1->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCanResize(TObject *Sender, int &NewWidth,
      int &NewHeight, bool &Resize)
{
        gOldWidth = Form1->Width;
        gOldHeight = Form1->Height;
        gNewWidth = NewWidth;
        gNewHeight = NewHeight;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image21Click(TObject *Sender)
{
        if(StringGrid1->Visible)
                SetServerProperties(StringGrid1, StringGrid1->Row, true);
        else if(StringGrid4->Visible)
                SetServerProperties(StringGrid4, StringGrid4->Row,  true);
        else if(StringGrid7->Visible)
                SetServerProperties(StringGrid7, StringGrid7->Row, true);

        Form2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image24Click(TObject *Sender)
{
        Form3->Show();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N11Click(TObject *Sender)
{
        Form3->Show();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N20Click(TObject *Sender)
{
        Form2->Show();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FillServerList(bool fAllTables)
{
    FILE *fd;
    int i;
    int num, len, sum;
    char *ptr;
    char path[256];
    char ip[32];
    int port;
    WCHAR wc_ip[64];
    char server_name[1024];
    WCHAR wc_server_name[2048];
    WCHAR request[2048];
    char request1[1024];
    char addr1[256], addr2[256], addr_cmp[256];
    sqlite3_stmt *stmt;
    PHOSTENT hp;

    try {
        StringGrid1->RowCount = 3;

        ptr = getenv("userprofile");
        if(ptr != NULL)
        {
                strncpy(path, ptr, sizeof(path));
                strncat(path, "\\Documents\\GTA San Andreas User Files\\SAMP\\USERDATA.DAT", sizeof(path));
                fd = fopen(path, "rb");

                if(fd <= 0)
                {
                        strncpy(path, ptr, sizeof(path));
                        strncat(path, "\\Мои документы\\GTA San Andreas User Files\\SAMP\\USERDATA.DAT", sizeof(path));
                        fd = fopen(path, "rb");
                }

                if(fd <= 0)
                {
                        strncpy(path, ".\\USERDATA.DAT", sizeof(path));
                        fd = fopen(path, "rb");
                }

                //получаем адрес
                hp = gethostbyname("botinform.com");
                if(hp != NULL)
                {
                    wsprintf(addr1, "%d.%d.%d.%d:7777",(unsigned char) hp->h_addr[0], (unsigned char) hp->h_addr[1], (unsigned char) hp->h_addr[2], (unsigned char) hp->h_addr[3]);
                    wsprintf(addr2, "%d.%d.%d.%d:7797",(unsigned char) hp->h_addr[0], (unsigned char) hp->h_addr[1], (unsigned char) hp->h_addr[2], (unsigned char) hp->h_addr[3]);
                }
                else
                {
                    memset(addr1, 0, sizeof(addr1));
                    memset(addr2, 0, sizeof(addr2));
                }

                wsprintf(request1, "DELETE FROM favorites");
                sqlite3_prepare(Form1->conn, request1, -1, &stmt, 0); //подготовка запроса
                sqlite3_step(stmt); //выполняем запрос
                sqlite3_reset(stmt); //сбрасываем инструкцию (stmt)
                sqlite3_finalize(stmt); //очищаем запрос

                if(fd > 0)
                {
                        num = 0;
                        sum = 0;
                        fseek(fd, 8, SEEK_SET);
                        fread(&num, sizeof(num), 1, fd);
                        for(i = 0; i < num; ++i)
                        {
                                len = 0;
                                fread(&len, sizeof(len), 1, fd); //считываем длину адреса сервера
                                sum = sum + len; //увелиыиваем общий счётчик считанных байтов
                                memset(ip, 0, sizeof(ip));
                                fread(ip, len, 1, fd); //получаем адрес сервера
                                mbstowcs(wc_ip, ip, sizeof(ip)); //конвертируем адрес в WCHAR
                                port = 0;
                                fread(&port, 2, 1, fd); //получаем номер порта
                                fseek(fd, 2, SEEK_CUR); //продвигаемся дальше
                                len = 0;
                                fread(&len, sizeof(len), 1, fd); //получаем длину названия сервера
                                memset(server_name, 0, sizeof(server_name));
                                fread(server_name, len, 1, fd); //получаем название сервера
                                wsprintf(addr_cmp,"%s:%d",ip,port);
                                if(strstr(addr_cmp, addr1) == NULL && strstr(addr_cmp, addr2) == NULL)
                                {
                                    //добавляем полученный сервер в список Favorites
                                    StringGrid1->RowCount++;
                                    StringGrid1->Cells[1][i+1] = server_name;
                                    mbstowcs(wc_server_name, server_name, sizeof(server_name));
                                    memset(request, 0, sizeof(request)/sizeof(WCHAR));
                                    swprintf(request, L"INSERT INTO favorites(addr,name,add_int,upd_int,row,mlist) VALUES(\"%ls:%d\",\"%ls\",%d,%d,%d,1)",wc_ip,port,wc_server_name,time(NULL),time(NULL),i+1);
    //                                MessageBoxW(NULL, request, L"", MB_OK);
                                    sqlite3_prepare16(conn, request, -1, &stmt, 0); //подготовка запроса
                                    sqlite3_step(stmt); //выполняем запрос
                                    sqlite3_reset(stmt); //сбрасываем инструкцию (stmt)
                                    sqlite3_finalize(stmt); //очищаем запрос
                                }
                                else
                                {
                                        num--;
                                        i--;
                                        StringGrid1->RowCount--;
                                }
                                if(num <= 0)
                                    StringGrid1->RowCount = 2;
                                else
                                    StringGrid1->RowCount = num+1;

                                fseek(fd, 8, SEEK_CUR);
                        }
                        fclose(fd);
                }

                //дополняем список хорошими серверами
                if(hp != NULL)
                {
                   wsprintf(request1, "INSERT INTO favorites(addr,name,add_int,upd_int,row,mlist) VALUES (\"%d.%d.%d.%d:7797\",\"GTA:SA DayZ Survival\",%d,%d,%d,1), (\"%d.%d.%d.%d:7777\",\"GTA:SA DayZ Survival\",%d,%d,%d,1)",
                  (unsigned char) hp->h_addr[0], (unsigned char) hp->h_addr[1], (unsigned char) hp->h_addr[2], (unsigned char) hp->h_addr[3],
                  time(NULL), time(NULL), num+1,
                  (unsigned char) hp->h_addr[0], (unsigned char) hp->h_addr[1], (unsigned char) hp->h_addr[2], (unsigned char) hp->h_addr[3],
                  time(NULL), time(NULL), num+2);
                  sqlite3_prepare(Form1->conn, request1, -1, &stmt, 0); //подготовка запроса
                  sqlite3_step(stmt); //выполняем запрос
                  sqlite3_reset(stmt); //сбрасываем инструкцию (stmt)
                  sqlite3_finalize(stmt); //очищаем запрос
                }
                if(StringGrid1->RowCount == 2)
                        StringGrid1->RowCount = 3;
                else
                        StringGrid1->RowCount += 2;

                for(i = 1; i < StringGrid1->RowCount; ++i)
                {
                        Form1->SetServerProperties(StringGrid1, i, false);
                }
        }
    }
    catch(Exception *ex)
    {}

    if(fAllTables)
    {
        FilterServerList(StringGrid4, "off");
        FilterServerList(StringGrid7, "off");
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FilterServerList(TStringGrid *MainTable, AnsiString filter)
{
        FILE *fd;
        int i, j, id, row;
        int num, len, sum;
        char *ptr;
        char path[256];
        char ip[32];
        int port;
        char server_name[1024];
        char request[2048];
        char table[256];
        char result[1024], result1[1024];
        const unsigned char *res;
        int players;
        static bool desc;
        static AnsiString prev_filter = "";
        static TStringGrid *pPrevGrid;
        sqlite3_stmt *stmt;
        sqlite3_stmt *stmt_upd;
        TStringGrid *ServerInfo;
        TStringGrid *PlayersInfo;
        TLabel *URLLabel;

        if(filter.AnsiCompare("old") == 0)
        {
            if(prev_filter.Length() > 0)
              filter = prev_filter;
            else
              filter = "";

            desc = !desc;
        }
        else
        {
          filter = AnsiString("ORDER BY ")+filter;
        }
                
        if(MainTable == Form1->StringGrid1)
        {
                strncpy(table, "favorites", sizeof(table)/sizeof(char));
                PlayersInfo = Form1->StringGrid2;
                ServerInfo = Form1->StringGrid3;
                URLLabel = Form1->Label15;
        }
        else if(MainTable == Form1->StringGrid4)
        {
                strncpy(table, "internet", sizeof(table)/sizeof(char));
                PlayersInfo = Form1->StringGrid5;
                ServerInfo = Form1->StringGrid6;
                URLLabel = Form1->Label17;
        }
        else if(MainTable == Form1->StringGrid7)
        {
                strncpy(table, "hosted", sizeof(table)/sizeof(char));
                PlayersInfo = Form1->StringGrid8;
                ServerInfo = Form1->StringGrid9;
                URLLabel = Form1->Label16;
        }

        memset(request, 0, sizeof(request)/sizeof(char));
        wsprintf(request, "UPDATE %s SET row=0",table);
        sqlite3_prepare(conn, request, -1, &stmt, 0); //подготовка запроса
        sqlite3_step(stmt); //выполняем запрос        
        sqlite3_reset(stmt); //сбрасываем инструкцию (stmt)
        sqlite3_finalize(stmt); //очищаем запрос

        if(filter.AnsiCompare(prev_filter) == 0 && pPrevGrid == MainTable)
        {
            desc = !desc;
        }
        else
        {
                if(filter.AnsiCompare("name") == 0)
                        desc = true;
                else
                        desc = false;
        }
        prev_filter = filter;
        pPrevGrid = MainTable;        

        if(filter.AnsiCompare("ORDER BY players") == 0)
        {
            if(desc)
                    filter = "ORDER BY players DESC, maxplayers DESC, name";
            else
                    filter = "ORDER BY players, maxplayers, name";
        }
        else
        {
                if(desc)
                        filter = filter + " DESC";
        }

        if(filter.Length() > 0)
        {
                if(CheckBox4->Checked||CheckBox5->Checked||CheckBox6->Checked||CheckBox7->Checked||CheckBox8->Checked||
                   CheckBox9->Checked||CheckBox10->Checked||CheckBox11->Checked||CheckBox12->Checked||CheckBox13->Checked)
                {
                    memset(request, 0, sizeof(request)/sizeof(char));
                    wsprintf(request, "SELECT addr,name,players,maxplayers,ping,mode,map,lagcomp,version,weather,worldtime,weburl,id FROM %s%s%s%s%s%s%s%s AND (%s OR %s OR %s OR %s OR %s OR %s OR %s OR %s OR %s OR %s) %s",table,
                             Form1->CheckBox2->Checked?" WHERE players>0":" WHERE players>=0",
                             Form1->CheckBox1->Checked?" AND (players!=maxplayers OR maxplayers=0)":"",
                             Form1->CheckBox3->Checked?" AND passwd=0":"",
                             Form1->CheckBox14->Checked?" AND mlist=1":"",
                             (Edit2->Text.Length() > 0)?AnsiString(" AND mode LIKE \"%"+Edit2->Text+"%\"").c_str():"",
                             (Edit3->Text.Length() > 0)?AnsiString(" AND map LIKE \"%"+Edit3->Text+"%\"").c_str():"",
                             (Edit4->Text.Length() > 0)?AnsiString(" AND name LIKE \"%"+Edit4->Text+"%\"").c_str():"",
                             (CheckBox4->Checked)?"version LIKE \"0.2.2%\"":"0",
                             (CheckBox5->Checked)?"version LIKE \"0.2x%\"":"0",
                             (CheckBox6->Checked)?"version LIKE \"0.3a%\"":"0",
                             (CheckBox7->Checked)?"version LIKE \"0.3b%\"":"0",
                             (CheckBox8->Checked)?"version LIKE \"0.3c%\"":"0",
                             (CheckBox9->Checked)?"version LIKE \"0.3d%\"":"0",
                             (CheckBox10->Checked)?"version LIKE \"0.3e%\"":"0",
                             (CheckBox11->Checked)?"version LIKE \"0.3x%\"":"0",
                             (CheckBox12->Checked)?"version LIKE \"0.3z%\"":"0",
                             (CheckBox13->Checked)?"(version LIKE \"0.3.7%\" OR version LIKE \"%DayZ ;) %\")":"0",
                             filter);
                }
                else
                {
                    memset(request, 0, sizeof(request)/sizeof(char));
                    wsprintf(request, "SELECT addr,name,players,maxplayers,ping,mode,map,lagcomp,version,weather,worldtime,weburl,id FROM %s%s%s%s%s%s%s%s %s",table,
                             Form1->CheckBox2->Checked?" WHERE players>0":" WHERE players>=0",
                             Form1->CheckBox1->Checked?" AND (players!=maxplayers OR maxplayers=0)":"",
                             Form1->CheckBox3->Checked?" AND passwd=0":"",
                             Form1->CheckBox14->Checked?" AND mlist=1":"",
                             (Edit2->Text.Length() > 0)?AnsiString(" AND mode LIKE \"%"+Edit2->Text+"%\"").c_str():"",
                             (Edit3->Text.Length() > 0)?AnsiString(" AND map LIKE \"%"+Edit3->Text+"%\"").c_str():"",
                             (Edit4->Text.Length() > 0)?AnsiString(" AND name LIKE \"%"+Edit4->Text+"%\"").c_str():"",
                             filter);
                }
        }
        else
        {
                if(CheckBox4->Checked||CheckBox5->Checked||CheckBox6->Checked||CheckBox7->Checked||CheckBox8->Checked||
                   CheckBox9->Checked||CheckBox10->Checked||CheckBox11->Checked||CheckBox12->Checked||CheckBox13->Checked)
                {
                    memset(request, 0, sizeof(request)/sizeof(char));
                    wsprintf(request, "SELECT addr,name,players,maxplayers,ping,mode,map,lagcomp,version,weather,worldtime,weburl,id FROM %s%s%s%s%s%s%s%s AND (%s OR %s OR %s OR %s OR %s OR %s OR %s OR %s OR %s OR %s) ORDER BY row",table,
                             Form1->CheckBox2->Checked?" WHERE players>0":" WHERE players>=0",
                             Form1->CheckBox1->Checked?" AND (players!=maxplayers OR maxplayers=0)":"",
                             Form1->CheckBox3->Checked?" AND passwd=0":"",
                             Form1->CheckBox14->Checked?" AND mlist=1":"",
                             (Edit2->Text.Length() > 0)?AnsiString(" AND mode LIKE \"%"+Edit2->Text+"%\"").c_str():"",
                             (Edit3->Text.Length() > 0)?AnsiString(" AND map LIKE \"%"+Edit3->Text+"%\"").c_str():"",
                             (Edit4->Text.Length() > 0)?AnsiString(" AND name LIKE \"%"+Edit4->Text+"%\"").c_str():"",
                             (CheckBox4->Checked)?"version LIKE \"0.2.2%\"":"0",
                             (CheckBox5->Checked)?"version LIKE \"0.2x%\"":"0",
                             (CheckBox6->Checked)?"version LIKE \"0.3a%\"":"0",
                             (CheckBox7->Checked)?"version LIKE \"0.3b%\"":"0",
                             (CheckBox8->Checked)?"version LIKE \"0.3c%\"":"0",
                             (CheckBox9->Checked)?"version LIKE \"0.3d%\"":"0",
                             (CheckBox10->Checked)?"version LIKE \"0.3e%\"":"0",
                             (CheckBox11->Checked)?"version LIKE \"0.3x%\"":"0",
                             (CheckBox12->Checked)?"version LIKE \"0.3z%\"":"0",
                             (CheckBox13->Checked)?"(version LIKE \"0.3.7%\" OR version LIKE \"%DayZ ;) %\")":"0");
                }
                else
                {
                    memset(request, 0, sizeof(request)/sizeof(char));
                    wsprintf(request, "SELECT addr,name,players,maxplayers,ping,mode,map,lagcomp,version,weather,worldtime,weburl,id FROM %s%s%s%s%s%s%s%s ORDER BY row",table,
                             Form1->CheckBox2->Checked?" WHERE players>0":" WHERE players>=0",
                             Form1->CheckBox1->Checked?" AND (players!=maxplayers OR maxplayers=0)":"",
                             Form1->CheckBox3->Checked?" AND passwd=0":"",
                             Form1->CheckBox14->Checked?" AND mlist=1":"",
                             (Edit2->Text.Length() > 0)?AnsiString(" AND mode LIKE \"%"+Edit2->Text+"%\"").c_str():"",
                             (Edit3->Text.Length() > 0)?AnsiString(" AND map LIKE \"%"+Edit3->Text+"%\"").c_str():"",
                             (Edit4->Text.Length() > 0)?AnsiString(" AND name LIKE \"%"+Edit4->Text+"%\"").c_str():"");
                }
        }
//        MessageBox(NULL, request, "", MB_OK);

        sqlite3_prepare(conn, request, -1, &stmt, 0); //подготовка запроса
        i = 1;
        MainTable->RowCount = 3;
        while(sqlite3_step(stmt) == SQLITE_ROW) //выполняем запрос
        {
            try {

                MainTable->RowCount++;
                row = i;
                if(MainTable->Row == row && MainTable->Visible)
                {
                  res = sqlite3_column_text( stmt, 11 ); //weburl
                  if(res != NULL)
                    strncpy(result, res, sizeof(result));
                  else
                    memset(result, 0, sizeof(result));
                  ServerInfo->RowCount = 7;
                  ServerInfo->Cells[0][5] = AnsiString(imes->RetIString("WEBURL_RULE", iLanguage));
                  ServerInfo->Cells[1][5] = AnsiString(result);
                  URLLabel->Caption = AnsiString(result);
                }

                res = sqlite3_column_text( stmt, 1 ); //name
                if(res != NULL)
                  strncpy(result, res, sizeof(result));
                else
                  memset(result, 0, sizeof(result));
                MainTable->Cells[1][row] = AnsiString(result);
                if(MainTable->Row == row && MainTable->Visible)
                {
                  GroupBox2->Caption = AnsiString(imes->RetIString("ABOUT_SERVER_PAR", iLanguage))+AnsiString(result);
                  if(Form2 != NULL && !Form2->Visible)
                          Form2->Label1->Caption = AnsiString(result);
                }

                if(MainTable->Row == row && MainTable->Visible)
                {
                  res = sqlite3_column_text( stmt, 0 ); //addr
                  if(res != NULL)
                    strncpy(result, res, sizeof(result));
                  else
                    memset(result, 0, sizeof(result));
                  Label9->Caption = AnsiString(result);
                  if(Form2 != NULL && !Form2->Visible)
                          Form2->Label9->Caption = AnsiString(result);
                }

                res = sqlite3_column_text( stmt, 2 ); //players
                if(res != NULL)
                  strncpy(result, res, sizeof(result));
                else
                  memset(result, 0, sizeof(result));
                players = atoi(result);
                res = sqlite3_column_text( stmt, 3 ); //maxplayers
                if(res != NULL)
                  strncpy(result1, res, sizeof(result1));
                else
                  memset(result1, 0, sizeof(result1));
                MainTable->Cells[2][row] = AnsiString(result)+" / "+AnsiString(result1);
                if(MainTable->Row == row && MainTable->Visible)
                {
                  Label10->Caption = AnsiString(result)+"/"+AnsiString(result1);
                  if(Form2 != NULL && !Form2->Visible)
                          Form2->Label10->Caption = AnsiString(result)+"/"+AnsiString(result1);
                }

                res = sqlite3_column_text( stmt, 4 ); //ping
                if(res != NULL)
                  strncpy(result, res, sizeof(result));
                else
                  memset(result, 0, sizeof(result));
                MainTable->Cells[3][row] = AnsiString(result);
                if(MainTable->Row == row && MainTable->Visible)
                {
                  Label11->Caption = AnsiString(result);
                  if(Form2 != NULL && !Form2->Visible)
                          Form2->Label11->Caption = AnsiString(result);
                }

                res = sqlite3_column_text( stmt, 5 ); //mode
                if(res != NULL)
                  strncpy(result, res, sizeof(result));
                else
                  memset(result, 0, sizeof(result));
                MainTable->Cells[4][row] = AnsiString(result);
                if(MainTable->Row == row && MainTable->Visible)
                {
                  Label12->Caption = AnsiString(result);
                  if(Form2 != NULL && !Form2->Visible)
                          Form2->Label12->Caption = AnsiString(result);
                }

                res = sqlite3_column_text( stmt, 6 ); //map
                if(res != NULL)
                  strncpy(result, res, sizeof(result));
                else
                  memset(result, 0, sizeof(result));
                MainTable->Cells[5][row] = AnsiString(result);
                if(MainTable->Row == row && MainTable->Visible)
                {
                  Label13->Caption = AnsiString(result);
                  if(Form2 != NULL && !Form2->Visible)
                          Form2->Label13->Caption = AnsiString(result);
                  ServerInfo->Cells[0][2] = AnsiString(imes->RetIString("MAPNAME_RULE", iLanguage));
                  ServerInfo->Cells[1][2] = AnsiString(result);
                }

                if(MainTable->Row == row && MainTable->Visible)
                {
                  res = sqlite3_column_text( stmt, 7 ); //lagcomp
                  if(res != NULL)
                    strncpy(result, res, sizeof(result));
                  else
                    memset(result, 0, sizeof(result));
                  ServerInfo->Cells[0][1] = AnsiString(imes->RetIString("LAGCOMP_RULE", iLanguage));
                  ServerInfo->Cells[1][1] = AnsiString(result);

                  res = sqlite3_column_text( stmt, 8 ); //version
                  if(res != NULL)
                    strncpy(result, res, sizeof(result));
                  else
                    memset(result, 0, sizeof(result));
                  ServerInfo->Cells[0][3] = AnsiString(imes->RetIString("VERSION_RULE", iLanguage));
                  ServerInfo->Cells[1][3] = AnsiString(result);

                  res = sqlite3_column_text( stmt, 9 ); //weather
                  if(res != NULL)
                    strncpy(result, res, sizeof(result));
                  else
                    memset(result, 0, sizeof(result));
                  ServerInfo->Cells[0][4] = AnsiString(imes->RetIString("WEATHER_RULE", iLanguage));
                  ServerInfo->Cells[1][4] = AnsiString(result);

                  res = sqlite3_column_text( stmt, 10 ); //worldtime
                  if(res != NULL)
                    strncpy(result, res, sizeof(result));
                  else
                    memset(result, 0, sizeof(result));
                  ServerInfo->Cells[0][6] = AnsiString(imes->RetIString("WORLDTIME_RULE", iLanguage));
                  ServerInfo->Cells[1][6] = AnsiString(result);
                }

                id = sqlite3_column_int( stmt, 12 ); //id
                if(MainTable->Row == row && MainTable->Visible)
                {
                  memset(request, 0, sizeof(request)/sizeof(char));
                  wsprintf(request, "SELECT name,score FROM %s_players WHERE id=%d", table, id);
                  sqlite3_prepare(Form1->conn, request, -1, &stmt_upd, 0); //подготовка запроса

                  if(players > 0)
                  {
                          PlayersInfo->RowCount = players+1;
                  }
                  else
                  {
                    PlayersInfo->RowCount = 2;
                    PlayersInfo->Cells[0][1] = "";
                    PlayersInfo->Cells[1][1] = "";
                  }
          
                  j = 0;
                  while(sqlite3_step(stmt_upd) == SQLITE_ROW)
                  {
                    j++;
                    res = sqlite3_column_text( stmt_upd, 0 ); //name
                    if(res != NULL)
                      strncpy(result, res, sizeof(result));
                    else
                      memset(result, 0, sizeof(result));
                    PlayersInfo->Cells[0][j] = AnsiString(result);
                    res = sqlite3_column_text( stmt_upd, 1 ); //score
                    if(res != NULL)
                      strncpy(result, res, sizeof(result));
                    else
                      memset(result, 0, sizeof(result));
                    PlayersInfo->Cells[1][j] = AnsiString(result);
                  }

                  sqlite3_reset(stmt_upd); //сбрасываем инструкцию (stmt_upd)
                  sqlite3_finalize(stmt_upd); //очищаем запрос
                }                

                memset(request, 0, sizeof(request)/sizeof(char));
                wsprintf(request, "UPDATE %s SET row=%d WHERE id=%d",table,i,id);
                sqlite3_prepare(conn, request, -1, &stmt_upd, 0); //подготовка запроса
                sqlite3_step(stmt_upd);//выполняем запрос
                sqlite3_reset(stmt_upd); //сбрасываем инструкцию (stmt)
                sqlite3_finalize(stmt_upd); //очищаем запрос
                i++;
            }
            catch(Exception *ex)
            {}
        }
//        if(Form1->CheckBox1->Checked || Form1->CheckBox2->Checked || Form1->CheckBox3->Checked)
        if(i > 1)
        {
            try {
                MainTable->RowCount = i;
            }
            catch(Exception *ex)
            {}
        }
        else
        {
            try {
                MainTable->RowCount = 2;
                MainTable->Cells[1][1] = "";
                MainTable->Cells[2][1] = "";
                MainTable->Cells[3][1] = "";
                MainTable->Cells[4][1] = "";
                MainTable->Cells[5][1] = "";
                MainTable->Cells[6][1] = "";
            }
            catch(Exception *ex)
            {}
        }
        sqlite3_reset(stmt); //сбрасываем инструкцию (stmt)
        sqlite3_finalize(stmt); //очищаем запрос
        try {
                MainTable->Refresh();
        }
        catch(Exception *ex)
        {}
}
//---------------------------------------------------------------------------

int __fastcall TForm1::GetCol(char const *colname, char const *tabname, int row, char *result)
{
        char request[2048];
        WCHAR wc_request[2048];
        const unsigned char *res;
        sqlite3_stmt *stmt_gc;

        if(row == 0)
                return -1;

        memset(request, 0, sizeof(request)/sizeof(char));
        wsprintf(request, "SELECT %s FROM %s WHERE row=%d", colname, tabname, row);
        mbstowcs(wc_request, request, sizeof(request));
        sqlite3_prepare16(conn, wc_request, -1, &stmt_gc, 0); //подготовка запроса
        sqlite3_step(stmt_gc); //выполняем запрос
        res = sqlite3_column_text( stmt_gc, 0 );
        if(res != NULL)
                strncpy(result, res, 1024);
        else
                return -1;
        sqlite3_reset(stmt_gc); //сбрасываем инструкцию (stmt)
        sqlite3_finalize(stmt_gc); //очищаем запрос

        return 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        char *sErrMsg;
        TRegistry *reg = new TRegistry(KEY_ALL_ACCESS);

        if (reg) // если всё ОК
            {
            // выбираем нужный корень
            reg->RootKey = HKEY_CURRENT_USER; 

            // открываем секцию
            reg->OpenKey("Software\\SAMP\\", true); 

            // записываем значения
            reg->WriteString("PlayerName", Edit1->Text);

            // записываем значения
            reg->WriteString("Language", AnsiString(iLanguage));

            // закрываем секцию
            reg->CloseKey();
            }
        delete reg;

        if(Form1->servers_s > 0)
                closesocket(Form1->servers_s);
        if(Form1->server_s > 0)
                closesocket(Form1->server_s);
        if(Form1->internets_s > 0)
                closesocket(Form1->internets_s);
        if(Form1->internet_s > 0)
                closesocket(Form1->internet_s);
        if(Form1->hosteds_s > 0)
                closesocket(Form1->hosteds_s);
        if(Form1->hosted_s > 0)
                closesocket(Form1->hosted_s);

        sqlite3_close(conn);

        if(hServersLists != INVALID_HANDLE_VALUE)
        {
                TerminateThread(hServersLists, 0);
                CloseHandle(hServersLists);
        }
        if(hHostedsLists != INVALID_HANDLE_VALUE)
        {
                TerminateThread(hHostedsLists, 0);
                CloseHandle(hHostedsLists);
        }

        if(hServersPut != INVALID_HANDLE_VALUE)
        {
                TerminateThread(hServersPut, 0);
                CloseHandle(hServersPut);
        }
        if(hServerPut != INVALID_HANDLE_VALUE)
        {
                TerminateThread(hServerPut, 0);
                CloseHandle(hServerPut);
        }

        if(hServersGet != INVALID_HANDLE_VALUE)
        {
                TerminateThread(hServersGet, 0);
                CloseHandle(hServersGet);
        }
        if(hServerGet != INVALID_HANDLE_VALUE)
        {
                TerminateThread(hServerGet, 0);
                CloseHandle(hServerGet);
        }

        if(hInternetsPut != INVALID_HANDLE_VALUE)
        {
                TerminateThread(hInternetsPut, 0);
                CloseHandle(hInternetsPut);
        }
        if(hInternetPut != INVALID_HANDLE_VALUE)
        {
                TerminateThread(hInternetPut, 0);
                CloseHandle(hInternetPut);
        }

        if(hInternetsGet != INVALID_HANDLE_VALUE)
        {
                TerminateThread(hInternetsGet, 0);
                CloseHandle(hInternetsGet);
        }
        if(hInternetGet != INVALID_HANDLE_VALUE)
        {
                TerminateThread(hInternetGet, 0);
                CloseHandle(hInternetGet);
        }

        if(hHostedsPut != INVALID_HANDLE_VALUE)
        {
                TerminateThread(hHostedsPut, 0);
                CloseHandle(hHostedsPut);
        }
        if(hHostedPut != INVALID_HANDLE_VALUE)
        {
                TerminateThread(hHostedPut, 0);
                CloseHandle(hHostedPut);
        }

        if(hHostedsGet != INVALID_HANDLE_VALUE)
        {
                TerminateThread(hHostedsGet, 0);
                CloseHandle(hHostedsGet);
        }
        if(hHostedGet != INVALID_HANDLE_VALUE)
        {
                TerminateThread(hHostedGet, 0);
                CloseHandle(hHostedGet);
        }

        WSACleanup();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SetServerProperties(TObject *Sender, int row, bool update_players)
{
        char result[1024], result1[1024];
        char request[1024], table[128];
        sqlite3_stmt *stmt;
        const unsigned char *res;
        TStringGrid *MainTable;
        TStringGrid *ServerInfo;
        TStringGrid *PlayersInfo;
        TLabel *URLLabel;
        int id, i, players;
        static int prev_table;
        AnsiString str1, str2, str3;

        if(row <= 0 || row > ((TStringGrid *)Sender)->RowCount)
                return;

        if(((TStringGrid *)Sender) == StringGrid1)
        {
                MainTable = StringGrid1;
                PlayersInfo = StringGrid2;
                ServerInfo = StringGrid3;
                URLLabel = Label15;
                strncpy(table, "favorites", sizeof(table));
        }
        else if(((TStringGrid *)Sender) == StringGrid4)
        {
                MainTable = StringGrid4;
                PlayersInfo = StringGrid5;
                ServerInfo = StringGrid6;
                URLLabel = Label17;
                strncpy(table, "internet", sizeof(table));
        }
        else if(((TStringGrid *)Sender) == StringGrid7)
        {
                MainTable = StringGrid7;
                PlayersInfo = StringGrid8;
                ServerInfo = StringGrid9;
                URLLabel = Label16;
                strncpy(table, "hosted", sizeof(table));
        }

        memset(request, 0, sizeof(request)/sizeof(char));
        wsprintf(request, "SELECT addr,name,players,maxplayers,ping,mode,map,lagcomp,version,weather,worldtime,weburl,id FROM %s WHERE row=%d", table, row);
        sqlite3_prepare(Form1->conn, request, -1, &stmt, 0); //подготовка запроса
        sqlite3_step(stmt); //выполняем запрос

        if(MainTable->Row == row && MainTable->Visible)
        {
          res = sqlite3_column_text( stmt, 11 ); //weburl
          if(res != NULL)
            strncpy(result, res, sizeof(result));
          else
            memset(result, 0, sizeof(result));
          ServerInfo->RowCount = 7;
          ServerInfo->Cells[0][5] = AnsiString(imes->RetIString("WEBURL_RULE", iLanguage));
          ServerInfo->Cells[1][5] = AnsiString(result);
          URLLabel->Caption = AnsiString(result);
        }

        res = sqlite3_column_text( stmt, 1 ); //name
        if(res != NULL)
          strncpy(result, res, sizeof(result));
        else
          memset(result, 0, sizeof(result));
        MainTable->Cells[1][row] = AnsiString(result);
        if(MainTable->Row == row && MainTable->Visible)
        {
          GroupBox2->Caption = AnsiString(imes->RetIString("ABOUT_SERVER_PAR", iLanguage))+AnsiString(result);
          if(Form2 != NULL && !Form2->Visible)
                  Form2->Label1->Caption = AnsiString(result);
        }

        if(MainTable->Row == row && MainTable->Visible)
        {
          res = sqlite3_column_text( stmt, 0 ); //addr
          if(res != NULL)
            strncpy(result, res, sizeof(result));
          else
            memset(result, 0, sizeof(result));
          Label9->Caption = AnsiString(result);
          if(Form2 != NULL && !Form2->Visible)
                  Form2->Label9->Caption = AnsiString(result);
        }

        res = sqlite3_column_text( stmt, 2 ); //players
        if(res != NULL)
          strncpy(result, res, sizeof(result));
        else
          memset(result, 0, sizeof(result));
        players = atoi(result);
        res = sqlite3_column_text( stmt, 3 ); //maxplayers
        if(res != NULL)
          strncpy(result1, res, sizeof(result1));
        else
          memset(result1, 0, sizeof(result1));
        MainTable->Cells[2][row] = AnsiString(result)+" / "+AnsiString(result1);
        if(MainTable->Row == row && MainTable->Visible)
        {
          Label10->Caption = AnsiString(result)+"/"+AnsiString(result1);
          if(Form2 != NULL && !Form2->Visible)
                  Form2->Label10->Caption = AnsiString(result)+"/"+AnsiString(result1);
        }

        res = sqlite3_column_text( stmt, 4 ); //ping
        if(res != NULL)
          strncpy(result, res, sizeof(result));
        else
          memset(result, 0, sizeof(result));
        MainTable->Cells[3][row] = AnsiString(result);
        if(MainTable->Row == row && MainTable->Visible)
        {
          Label11->Caption = AnsiString(result);
          if(Form2 != NULL && !Form2->Visible)
                  Form2->Label11->Caption = AnsiString(result);
        }

        res = sqlite3_column_text( stmt, 5 ); //mode
        if(res != NULL)
          strncpy(result, res, sizeof(result));
        else
          memset(result, 0, sizeof(result));
        MainTable->Cells[4][row] = AnsiString(result);
        if(MainTable->Row == row && MainTable->Visible)
        {
          Label12->Caption = AnsiString(result);
          if(Form2 != NULL && !Form2->Visible)
                  Form2->Label12->Caption = AnsiString(result);
        }

        res = sqlite3_column_text( stmt, 6 ); //map
        if(res != NULL)
          strncpy(result, res, sizeof(result));
        else
          memset(result, 0, sizeof(result));
        MainTable->Cells[5][row] = AnsiString(result);
        if(MainTable->Row == row && MainTable->Visible)
        {
          Label13->Caption = AnsiString(result);
          if(Form2 != NULL && !Form2->Visible)
                  Form2->Label13->Caption = AnsiString(result);
          ServerInfo->Cells[0][2] = AnsiString(imes->RetIString("MAPNAME_RULE", iLanguage));
          ServerInfo->Cells[1][2] = AnsiString(result);
        }

        if(MainTable->Row == row && MainTable->Visible)
        {
          res = sqlite3_column_text( stmt, 7 ); //lagcomp
          if(res != NULL)
            strncpy(result, res, sizeof(result));
          else
            memset(result, 0, sizeof(result));
          ServerInfo->Cells[0][1] = AnsiString(imes->RetIString("LAGCOMP_RULE", iLanguage));
          ServerInfo->Cells[1][1] = AnsiString(result);

          res = sqlite3_column_text( stmt, 8 ); //version
          if(res != NULL)
            strncpy(result, res, sizeof(result));
          else
            memset(result, 0, sizeof(result));
          ServerInfo->Cells[0][3] = AnsiString(imes->RetIString("VERSION_RULE", iLanguage));
          ServerInfo->Cells[1][3] = AnsiString(result);

          res = sqlite3_column_text( stmt, 9 ); //weather
          if(res != NULL)
            strncpy(result, res, sizeof(result));
          else
            memset(result, 0, sizeof(result));
          ServerInfo->Cells[0][4] = AnsiString(imes->RetIString("WEATHER_RULE", iLanguage));
          ServerInfo->Cells[1][4] = AnsiString(result);

          res = sqlite3_column_text( stmt, 10 ); //worldtime
          if(res != NULL)
            strncpy(result, res, sizeof(result));
          else
            memset(result, 0, sizeof(result));
          ServerInfo->Cells[0][6] = AnsiString(imes->RetIString("WORLDTIME_RULE", iLanguage));
          ServerInfo->Cells[1][6] = AnsiString(result);
        }

        res = sqlite3_column_text( stmt, 12 ); //id
        if(res != NULL)
        {
          strncpy(result, res, sizeof(result));
          id = atoi(result);
        }
        else
          id = 0;

        sqlite3_reset(stmt); //сбрасываем инструкцию (stmt)
        sqlite3_finalize(stmt); //очищаем запрос

        if( (prev_table != id) && (MainTable->Row == row && MainTable->Visible) )
        {
          PlayersInfo->RowCount = 2;
          PlayersInfo->Cells[0][1] = "";
          PlayersInfo->Cells[1][1] = "";
          prev_table = id;
        }

        if(update_players)
        {
          memset(request, 0, sizeof(request)/sizeof(char));
          wsprintf(request, "SELECT name,score FROM %s_players WHERE id=%d", table, id);
          sqlite3_prepare(Form1->conn, request, -1, &stmt, 0); //подготовка запроса

          if(players > 0)
          {
                  PlayersInfo->RowCount = players+1;
          }
          else
          {
            PlayersInfo->RowCount = 2;
            PlayersInfo->Cells[0][1] = "";
            PlayersInfo->Cells[1][1] = "";
          }
          
          i = 0;
          while(sqlite3_step(stmt) == SQLITE_ROW)
          {
            i++;
            res = sqlite3_column_text( stmt, 0 ); //name
            if(res != NULL)
              strncpy(result, res, sizeof(result));
            else
              memset(result, 0, sizeof(result));
            PlayersInfo->Cells[0][i] = AnsiString(result);
            res = sqlite3_column_text( stmt, 1 ); //score
            if(res != NULL)
              strncpy(result, res, sizeof(result));
            else
              memset(result, 0, sizeof(result));
            PlayersInfo->Cells[1][i] = AnsiString(result);
          }

          sqlite3_reset(stmt); //сбрасываем инструкцию (stmt)
          sqlite3_finalize(stmt); //очищаем запрос
        }
        
        if((MainTable == StringGrid1 && StringGrid1->Visible) ||
           (MainTable == StringGrid4 && StringGrid4->Visible) ||
           (MainTable == StringGrid7 && StringGrid7->Visible))
        {
            memset(request, 0, sizeof(request)/sizeof(char));
            wsprintf(request, "SELECT SUM(players),SUM(maxplayers),count(*) FROM %s", table);
            sqlite3_prepare(Form1->conn, request, -1, &stmt, 0); //подготовка запроса
            sqlite3_step(stmt); //выполняем запрос
    //        ControlBar1->Canvas->Font->Name = "Miriam";
    //        ControlBar1->Canvas->Font->Size = 10;
    //        ControlBar1->Canvas->TextOutA(0, 0, "Servers: "+AnsiString(sqlite3_column_int(stmt, 0))+" players, playing on "+AnsiString(sqlite3_column_int(stmt, 2))+" servers. ("+AnsiString(sqlite3_column_int(stmt, 1))+" player slots available)");
            try {
                str1 = AnsiString(sqlite3_column_int(stmt, 0));
                str2 = AnsiString(sqlite3_column_int(stmt, 2));
                str3 = AnsiString(sqlite3_column_int(stmt, 1));

                Label18->Caption = AnsiString(imes->RetIString("SERVERS_STR", iLanguage)+str1+
                imes->RetIString("PLAYING_ON_STR", iLanguage)+str2+
                imes->RetIString("ON_SERVERS_STR", iLanguage)+str3+
                imes->RetIString("SLOTS_STR", iLanguage));
            }
            catch(Exception *ex)
            {}
            
            sqlite3_reset(stmt); //сбрасываем инструкцию (stmt)
            sqlite3_finalize(stmt); //очищаем запрос
        }
        try {
            MainTable->Refresh();
        }
        catch(Exception *ex)
        {}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        int row, col;
        static struct ThreadParameters Param;
        char request[2048];
        sqlite3_stmt *stmt;

        if(Y < ((TStringGrid *)Sender)->RowHeights[0])
        {
                if(Form1->StringGrid4->Visible)
                {
                        memset(request, 0, sizeof(request));
                        wsprintf(request, "DELETE FROM internet WHERE version=\"\" OR name=\"\"");
                        sqlite3_prepare(Form1->conn, request, -1, &stmt, 0); //подготовка запроса
                        sqlite3_step(stmt); //выполняем запрос
                        sqlite3_reset(stmt); //сбрасываем инструкцию (stmt)
                        sqlite3_finalize(stmt); //очищаем запрос
                }
                row = 0;
                if(X < ((TStringGrid *)Sender)->ColWidths[0])
                {
                        col = 0;
                }
                else if(X < (((TStringGrid *)Sender)->ColWidths[0] +
                             ((TStringGrid *)Sender)->ColWidths[1]) )
                {
                        col = 1;
                }
                else if(X < (((TStringGrid *)Sender)->ColWidths[0] +
                             ((TStringGrid *)Sender)->ColWidths[1] +
                             ((TStringGrid *)Sender)->ColWidths[2]) )
                {
                        col = 2;
                }
                else if(X < (((TStringGrid *)Sender)->ColWidths[0] +
                             ((TStringGrid *)Sender)->ColWidths[1] +
                             ((TStringGrid *)Sender)->ColWidths[2] +
                             ((TStringGrid *)Sender)->ColWidths[3]) )
                {
                        col = 3;
                }
                else if(X < (((TStringGrid *)Sender)->ColWidths[0] +
                             ((TStringGrid *)Sender)->ColWidths[1] +
                             ((TStringGrid *)Sender)->ColWidths[2] +
                             ((TStringGrid *)Sender)->ColWidths[3] +
                             ((TStringGrid *)Sender)->ColWidths[4]) )
                {
                        col = 4;
                }
                else if(X < (((TStringGrid *)Sender)->ColWidths[0] +
                             ((TStringGrid *)Sender)->ColWidths[1] +
                             ((TStringGrid *)Sender)->ColWidths[2] +
                             ((TStringGrid *)Sender)->ColWidths[3] +
                             ((TStringGrid *)Sender)->ColWidths[4] +
                             ((TStringGrid *)Sender)->ColWidths[5]) )
                {
                        col = 5;
                }
//                MessageBox(NULL, AnsiString(col).c_str(), "", MB_OK);
                switch(col)
                {
                        case 0:
                                FilterServerList(((TStringGrid *)Sender), "passwd");
                                return;
                        case 1:
                                FilterServerList(((TStringGrid *)Sender), "name");
                                return;
                        case 2:
                                FilterServerList(((TStringGrid *)Sender), "players");
                                return;
                        case 3:
                                FilterServerList(((TStringGrid *)Sender), "ping");
                                return;
                        case 4:
                                FilterServerList(((TStringGrid *)Sender), "mode");
                                return;
                        case 5:
                                FilterServerList(((TStringGrid *)Sender), "map");
                                return;
                }
        }
        else
        {
//                row = (Y-((TStringGrid *)Sender)->RowHeights[0]-1)/(((TStringGrid *)Sender)->DefaultRowHeight+1)+1;
                row = ((TStringGrid *)Sender)->Row;
        }

        if(row > ((TStringGrid *)Sender)->RowCount || row < 0)
                return; 

        SetServerProperties(Sender, row, false);
                
//        MessageBox(NULL, (AnsiString(Y)+","+AnsiString(row)+","+AnsiString(((TStringGrid *)Sender)->RowHeights[0])).c_str(), "", MB_OK);

        if(Form1->StringGrid1->Visible)
        {
                Param.Sender = Form1->StringGrid1;
        }
        else if(Form1->StringGrid4->Visible)
        {
                Param.Sender = Form1->StringGrid4;
        }
        else if(Form1->StringGrid7->Visible)
        {
                Param.Sender = Form1->StringGrid7;
        }
        Param.Row = row;

        if(Form1->StringGrid1->Visible)
        {
                TerminateThread(hServerPut, 0);
                CloseHandle(hServerPut);
                hServerPut = CreateThread(NULL, 0, ThreadPutServerInfo, (void *)&Param, 0, &thread_server_put);
        }
        else if(Form1->StringGrid4->Visible)
        {
                TerminateThread(hInternetPut, 0);
                CloseHandle(hInternetPut);
                hInternetPut = CreateThread(NULL, 0, ThreadPutServerInfo, (void *)&Param, 0, &thread_internet_put);
        }
        else if(Form1->StringGrid7->Visible)
        {
                TerminateThread(hHostedPut, 0);
                CloseHandle(hHostedPut);
                hHostedPut = CreateThread(NULL, 0, ThreadPutServerInfo, (void *)&Param, 0, &thread_hosted_put);
        }

        Image2->Visible = true;
        Image32->Visible = false;
        Image12->Visible = true;
        Image34->Visible = false;
        Image18->Visible = true;
        Image36->Visible = false;
        Image21->Visible = true;
        Image37->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid1DblClick(TObject *Sender)
{
        Form2->Show();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image30Click(TObject *Sender)
{
        Form4->Show();        
}
//---------------------------------------------------------------------------

unsigned long __stdcall ThreadGetServersLists(void *Sender)
{
        int row;
        sqlite3_stmt *stmt_th, *stmt_off;
        char result[204800], result1[1024];
        char table[128];
        TStringGrid *ServerInfo;
        TLabel *URLLabel;
        char request[2048];
        const unsigned char *res;
        static struct sockaddr_in clnt;
        char serv_request[1024];
        char int_addr[5];
        char int_port[3];
        unsigned int port, i, j, r, k, pos, len_h, len_g, len_m;
        int n, id;
        char *ptr, *ptr_end;
        char addr[128];
        int nPass, nPlayers, nMaxPlayers;
        char *versions[] = {"0.2.2","0.2.3","0.3.0","0.3.1","0.3.2","0.3.3","0.3.4","0.3.5b","0.3.6","0.3.7","","","","","","","",""};
        char *list_type[] = {"servers", "hosted"};
        int list_index = 0;
        SOCKET list_s, *sock;
        PHOSTENT hp, hps;
        long ms;

    try {
        if(((TStringGrid *)Sender) == Form1->StringGrid1)
        {
                ServerInfo = Form1->StringGrid3;
                strncpy(table, "favorites", sizeof(table));
                URLLabel = Form1->Label15;
                sock = &(Form1->servers_s);
        }
        else if(((TStringGrid *)Sender) == Form1->StringGrid4)
        {
                ServerInfo = Form1->StringGrid6;
                strncpy(table, "internet", sizeof(table));
                URLLabel = Form1->Label17;
                list_index = 0;
                sock = &(Form1->internets_s);
        }
        else if(((TStringGrid *)Sender) == Form1->StringGrid7)
        {
                ServerInfo = Form1->StringGrid9;
                strncpy(table, "hosted", sizeof(table));
                URLLabel = Form1->Label16;
                list_index = 1;
                sock = &(Form1->hosteds_s);
        }

        sprintf(request, "UPDATE %s SET mlist=0",table); //сбрасываем поле MasterList
        sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
        sqlite3_step(stmt_th); //выполняем запрос
        sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
        sqlite3_finalize(stmt_th); //очищаем запрос

        //получаем адрес
        hp = gethostbyname("lists.sa-mp.com");
        if(hp == NULL)
        {
                ExitThread(2);
        }
        //подключаемся
        for(i = 9; i >= 2; --i)
        {
                if( (list_s = socket(AF_INET, SOCK_STREAM, 0)) < 0){i++; continue;} //при ошибке создания сокета - повторить
                memset(&clnt, 0, sizeof(clnt));
                memcpy((void *)&clnt.sin_addr, (const void *)hp->h_addr, (size_t)hp->h_length);
                clnt.sin_port = htons(80);
                clnt.sin_family = AF_INET;
                if(connect(list_s, (struct sockaddr *) &clnt, sizeof(clnt)) == -1){continue;}
                memset(request, 0, sizeof(request));
                wsprintf(request, "\
GET /%s/%s HTTP/1.1\r\n\
Content-Type: text/html\r\n\
Host: lists.sa-mp.com\r\n\
Accept: text/html, */*\r\n\
User-Agent: Mozilla/3.0 (compatible; SA:MP v0.3e)\r\n\r\n\
", versions[i], list_type[list_index]);

//                MessageBox(NULL, request, "Запрос", MB_OK); //отладка!!!

                send(list_s, request, strlen(request), 0); //отправляем запрос
                memset(result, 0, sizeof(result)); //получаем ответ
                do {
                        n = recv(list_s, result+strlen(result), sizeof(result), 0);
                }
                while(n > 0);

//                MessageBox(NULL, result, versions[i], MB_OK);

                if(strncmp(result+9, "200", 3) != 0)
                {
//                        MessageBox(NULL, result, "Результат", MB_OK); //отладка!!!
                        closesocket(list_s); //отключаемся
                        continue;
                }
//                MessageBox(NULL, result, versions[i], MB_OK);
                if(strlen(result) == 0) //обрабатываем список и вносим в БД
                {
                        closesocket(list_s); //отключаемся
                        continue;
                }
                ptr = strstr(result, "\r\n\r\n");
                if(ptr == NULL)
                {
                        closesocket(list_s); //отключаемся
                        continue;
                }
                ptr += 4;
                ptr_end = strstr(ptr, "\n");
                while(ptr != NULL && ptr_end != NULL)
                {
                  ptr_end[0] = '\0';
                  strncpy(result1, ptr, sizeof(result1));
                  if(strlen(result1) > 8 && strlen(result1) < 22)
                  {
                        sprintf(request, "INSERT INTO %s(addr,add_int,upd_int,row,mlist) VALUES(\"%s\",%d,%d,1,1)",table,result1,time(NULL),time(NULL));
//                        MessageBox(NULL, request, "", MB_OK); //отладка!!!
                        sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
                        sqlite3_step(stmt_th); //выполняем запрос
                        sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                        sqlite3_finalize(stmt_th); //очищаем запрос

                        Sleep(200);

                        memset(request, 0, sizeof(request));
                        sprintf(request, "UPDATE %s SET mlist=1 WHERE addr=\"%s\"",table,result1);
//                        MessageBox(NULL, request, table, MB_OK); //отладка!!!
                        sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
                        sqlite3_step(stmt_th); //выполняем запрос
                        sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                        sqlite3_finalize(stmt_th); //очищаем запрос
                  }
                  if((result - ptr_end)/sizeof(char) > 2)
                  {
                        ptr = ptr_end + 1;
                        ptr_end = strstr(ptr, "\n");                        
                  }
                  else
                  {
                        closesocket(list_s); //отключаемся
                        continue;
                  }
                }
                closesocket(list_s); //отключаемся
                Sleep(1000);
                continue;
        }

        for(k = 0; k < 2; ++k)
        {
                //отправляем запросы к серверам
                memset(request, 0, sizeof(request)/sizeof(char));
                wsprintf(request, "SELECT addr FROM %s WHERE name=\"\" ORDER BY off,row", table);
                sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
                while(sqlite3_step(stmt_th) == SQLITE_ROW) //выполняем запрос
                {
                        res = sqlite3_column_text( stmt_th, 0 );
                        if(res != NULL)
                        {
                                memset(result, 0, sizeof(result));
                                memset(int_addr, 0, sizeof(int_addr));
                                memset(int_port, 0, sizeof(int_port));
                                strncpy(result, res, 1024);
                                if(result[0] < '0' || result[0] > '9')
                                {
                                        for(i = 0, r = 0; i < strlen(result); ++i)
                                        {
                                                if(result[i] == ':')
                                                {
                                                        port = atoi(&result[i+1]);
                                                        result[i] = '\0';
                                                        break;
                                                }
                                        }
                                        hps = gethostbyname(result);
                                        if(hps == NULL)
                                                continue;
                                        memcpy(int_addr, hps->h_addr, 4);
                                        
                                }
                                else
                                {
                                  int_addr[0] = atoi(result);
                                  for(i = 0, r = 0; i < strlen(result); ++i)
                                  {
                                          if(result[i] == '.')
                                          {
                                                  r++;
                                                  int_addr[r] = atoi(&result[i+1]);
                                                  continue;
                                          }
                                          if(result[i] == ':')
                                          {
                                                  port = atoi(&result[i+1]);
                                                  break;
                                          }
                                  }
                                }
                                int_port[0] = (port&0xFF);
                                int_port[1] = (port&0xFF00)>>8;

                                memset(serv_request, 0, sizeof(serv_request));
                                strcpy(serv_request, "SAMP");
                                memcpy(serv_request+4, int_addr, 4);
                                memcpy(serv_request+8, int_port, 2);
                                serv_request[10] = 'i';

                                clnt.sin_family = AF_INET;
                                clnt.sin_port = htons(port);
                                memcpy(&(clnt.sin_addr.S_un.S_un_b), int_addr, 4);
                                memset(clnt.sin_zero, 0, sizeof(clnt.sin_zero));
                                sendto(*sock, serv_request, 11, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                                Sleep(Form1->SleepInterval*5);

                                serv_request[10] = 'p';
                                ms = clock();
                                memcpy(&serv_request[11], &ms, sizeof(long));
                                sendto(*sock, serv_request, 15, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                                Sleep(Form1->SleepInterval*2);
                                ms = clock();
                                memcpy(&serv_request[11], &ms, sizeof(long));
                                sendto(*sock, serv_request, 15, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                                Sleep(Form1->SleepInterval);

                                memset(request, 0, sizeof(request)/sizeof(char));
                                wsprintf(request, "UPDATE %s SET off=off+1 WHERE addr=\"%s\"", table, res);
                                sqlite3_prepare(Form1->conn, request, -1, &stmt_off, 0); //подготовка запроса
                                sqlite3_step(stmt_off); //выполняем запрос

        //                        serv_request[10] = 'r';
        //                        sendto(*sock, serv_request, 11, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
        //                        Sleep(Form1->SleepInterval*5);
                        }
                }
                sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                sqlite3_finalize(stmt_th); //очищаем запрос
        }

        if(((TStringGrid *)Sender) == Form1->StringGrid4)
        {
                Form1->hInternetsPut = CreateThread(NULL, 0, ThreadPutServersInfo, (void *)Form1->StringGrid4, 0, &Form1->thread_internets_put);
        }
        else if(((TStringGrid *)Sender) == Form1->StringGrid7)
        {
                Form1->hHostedsPut = CreateThread(NULL, 0, ThreadPutServersInfo, (void *)Form1->StringGrid7, 0, &Form1->thread_hosteds_put);
        }
    }
    catch (Exception *ex)
    {}

        ExitThread(0);
}
//---------------------------------------------------------------------------

unsigned long __stdcall ThreadPutServersInfo(void *Sender)
{
        int row;
        sqlite3_stmt *stmt_th, *stmt_off;
        char result[1024], result1[1024];
        char table[128];
        TStringGrid *ServerInfo;
        TLabel *URLLabel;
        char request[2048];
        const unsigned char *res;
        static struct sockaddr_in clnt;
        char serv_request[1024];
        char int_addr[5];
        char int_port[3];
        unsigned int port, i, r, pos, len_h, len_g, len_m;
        int n, id;
        char *ptr;
        char addr[128];
        int nPass, nPlayers, nMaxPlayers;
        SOCKET *sock;
        PHOSTENT hps;
        struct timeval tm;
        long ms;

    try {
        if(((TStringGrid *)Sender) == Form1->StringGrid1)
        {
                ServerInfo = Form1->StringGrid3;
                strncpy(table, "favorites", sizeof(table));
                URLLabel = Form1->Label15;
                sock = &(Form1->servers_s);
        }
        else if(((TStringGrid *)Sender) == Form1->StringGrid4)
        {
                ServerInfo = Form1->StringGrid6;
                strncpy(table, "internet", sizeof(table));
                URLLabel = Form1->Label17;
                sock = &(Form1->internets_s);
        }
        else if(((TStringGrid *)Sender) == Form1->StringGrid7)
        {
                ServerInfo = Form1->StringGrid9;
                strncpy(table, "hosted", sizeof(table));
                URLLabel = Form1->Label16;
                sock = &(Form1->hosteds_s);
        }

        memset(request, 0, sizeof(request)/sizeof(char));
        wsprintf(request, "SELECT addr FROM %s ORDER BY off,row", table);
        sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
        while(sqlite3_step(stmt_th) == SQLITE_ROW) //выполняем запрос
        {
                res = sqlite3_column_text( stmt_th, 0 );
                if(res != NULL)
                {
                        memset(result, 0, sizeof(result));
                        memset(int_addr, 0, sizeof(int_addr));
                        memset(int_port, 0, sizeof(int_port));
                        strncpy(result, res, 1024);
                        if(result[0] < '0' || result[0] > '9')
                        {
                                for(i = 0, r = 0; i < strlen(result); ++i)
                                {
                                        if(result[i] == ':')
                                        {
                                                port = atoi(&result[i+1]);
                                                result[i] = '\0';
                                                break;
                                        }
                                }
                                hps = gethostbyname(result);
                                if(hps == NULL)
                                        continue;
                                memcpy(int_addr, hps->h_addr, 4);
                        }
                        else
                        {
                          int_addr[0] = atoi(result);
                          for(i = 0, r = 0; i < strlen(result); ++i)
                          {
                                  if(result[i] == '.')
                                  {
                                          r++;
                                          int_addr[r] = atoi(&result[i+1]);
                                          continue;                                        
                                  }
                                  if(result[i] == ':')
                                  {
                                          port = atoi(&result[i+1]);
                                          break;
                                  }
                          }
                        }
                        int_port[0] = (port&0xFF);
                        int_port[1] = (port&0xFF00)>>8;

                        memset(serv_request, 0, sizeof(serv_request));
                        strcpy(serv_request, "SAMP");
                        memcpy(serv_request+4, int_addr, 4);
                        memcpy(serv_request+8, int_port, 2);
                        serv_request[10] = 'i';

                        clnt.sin_family = AF_INET;
                        clnt.sin_port = htons(port);
                        memcpy(&(clnt.sin_addr.S_un.S_un_b), int_addr, 4);
                        memset(clnt.sin_zero, 0, sizeof(clnt.sin_zero));
                        sendto(*sock, serv_request, 11, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                        Sleep(Form1->SleepInterval*5);
//                        sendto(*sock, serv_request, 11, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
//                        Sleep(Form1->SleepInterval);
                        serv_request[10] = 'r';
                        sendto(*sock, serv_request, 11, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                        Sleep(Form1->SleepInterval*2);

                        if(((TStringGrid *)Sender) == Form1->StringGrid1)
                        {
                            serv_request[10] = 'B';
                            sendto(*sock, serv_request, 11, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                        }
                        Sleep(Form1->SleepInterval*3);

                        ms = clock();
                        serv_request[10] = 'p';
                        memcpy(&serv_request[11], &ms, sizeof(long));
                        sendto(*sock, serv_request, 15, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                        ms = clock();
                        memcpy(&serv_request[11], &ms, sizeof(long));
                        sendto(*sock, serv_request, 15, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                        Sleep(Form1->SleepInterval);

                        memset(request, 0, sizeof(request)/sizeof(char));
                        wsprintf(request, "UPDATE %s SET off=off+1 WHERE addr=\"%s\"", table, res);
                        sqlite3_prepare(Form1->conn, request, -1, &stmt_off, 0); //подготовка запроса
                        sqlite3_step(stmt_off); //выполняем запрос

//                            serv_request[10] = 'c';
//                            sendto(*sock, serv_request, 11, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                        //MessageBox(NULL, result, "", MB_OK);
                }
        }
        sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
        sqlite3_finalize(stmt_th); //очищаем запрос

    }
    catch(Exception *ex)
    {}        
        ExitThread(0);
}

unsigned long __stdcall ThreadGetServersInfo(void *Sender)
{
        int row;
        sqlite3_stmt *stmt_th;
        char result[1024], result1[1024];
        char table[128];
        TStringGrid *ServerInfo;
        TLabel *URLLabel;
        char request[2048];
        const unsigned char *res;
        static struct sockaddr_in clnt;
        char serv_request[1024];
        char int_addr[5];
        char int_port[3];
        unsigned int port, i, r, pos, len_h, len_g, len_m;
        int n, id;
        char *ptr;
        char addr[128];
        int nPass, nPlayers, nMaxPlayers;
        char szHostname[512], szGamemode[512], szMapname[512];
        char lagcomp[128],version[128],weather[128],worldtime[128],weburl[512];
        char players_request[102400];
        SOCKET *sock;
        struct timeval tm;
        long ping, ms;

    try {
        if(((TStringGrid *)Sender) == Form1->StringGrid1)
        {
                ServerInfo = Form1->StringGrid3;
                strncpy(table, "favorites", sizeof(table));
                URLLabel = Form1->Label15;
                sock = &(Form1->servers_s);
        }
        else if(((TStringGrid *)Sender) == Form1->StringGrid4)
        {
                ServerInfo = Form1->StringGrid6;
                strncpy(table, "internet", sizeof(table));
                URLLabel = Form1->Label17;
                sock = &(Form1->internets_s);
        }
        else if(((TStringGrid *)Sender) == Form1->StringGrid7)
        {
                ServerInfo = Form1->StringGrid9;
                strncpy(table, "hosted", sizeof(table));
                URLLabel = Form1->Label16;
                sock = &(Form1->hosteds_s);
        }
        memset(serv_request, 0, sizeof(serv_request));
        while(1)
        {
                n = recv(*sock, serv_request, sizeof(serv_request)-1, 0);
                if(n < 11)
                {
                        Sleep(100);
                        continue;
                }
//                MessageBox(NULL, AnsiString(n).c_str(), "", MB_OK);
                if(((unsigned char)serv_request[4]) != 0)
                {
                  memset(addr, 0, sizeof(addr));
                  ptr = (char *)&port;
                  port = 0;
                  ptr[0] = serv_request[8];
                  ptr[1] = serv_request[9];
                  wsprintf(addr, "%d.%d.%d.%d:%d", (unsigned char)serv_request[4],
                                                   (unsigned char)serv_request[5],
                                                   (unsigned char)serv_request[6],
                                                   (unsigned char)serv_request[7],
                                                    port);

                  memset(request, 0, sizeof(request)/sizeof(char));
                  wsprintf(request, "SELECT row,id FROM %s WHERE addr=\"%s\"", table, addr);
                  sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
                  sqlite3_step(stmt_th); //выполняем запрос
                  row = sqlite3_column_int( stmt_th, 0 );
                  id = sqlite3_column_int( stmt_th, 1 );
                  sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                  sqlite3_finalize(stmt_th); //очищаем запрос
                                                    
                  switch(serv_request[10])
                  {
                        case 'i':
                        {
                            nPass = 0;
                            nPlayers = 0;
                            nMaxPlayers = 0;
                            memset(szHostname, 0, sizeof(szHostname));
                            memset(szGamemode, 0, sizeof(szGamemode));
                            memset(szMapname, 0, sizeof(szMapname));
                            memset(int_port, 0, sizeof(int_port));
/*
                            if((TStringGrid *)Sender == Form1->StringGrid1)
                            {
                              clnt.sin_family = AF_INET;
                              clnt.sin_port = htons(port);
                              memcpy(&(clnt.sin_addr.S_un.S_un_b), serv_request+4, 4);
                              memset(clnt.sin_zero, 0, sizeof(clnt.sin_zero));

                              serv_request[10] = 'r';
                              n = sendto(sock, serv_request, 11, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
//                              serv_request[10] = 'c';
//                              sendto(sock, serv_request, 11, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                            }
*/
                            nPass = (int)((unsigned char)serv_request[11]);
                            ptr = (char *)&nPlayers;
                            ptr[0] = (int)((unsigned char)serv_request[12]);
                            ptr[1] = (int)((unsigned char)serv_request[13]);
                            ptr = (char *)&nMaxPlayers;
                            ptr[0] = (int)((unsigned char)serv_request[14]);
                            ptr[1] = (int)((unsigned char)serv_request[15]);

                            len_h = 0;
                            ptr = (char *)&len_h;
                            ptr[0] = (int)((unsigned char)serv_request[16]);
                            ptr[1] = (int)((unsigned char)serv_request[17]);
                            ptr[2] = (int)((unsigned char)serv_request[18]);
                            ptr[3] = (int)((unsigned char)serv_request[19]);
                            for(i = 0; i < len_h; ++i)
                            {
                                  szHostname[i] = serv_request[20+i];
                            }
                            len_g = 0;
                            ptr = (char *)&len_g;
                            ptr[0] = (int)((unsigned char)serv_request[16+len_h+4]);
                            ptr[1] = (int)((unsigned char)serv_request[17+len_h+4]);
                            ptr[2] = (int)((unsigned char)serv_request[18+len_h+4]);
                            ptr[3] = (int)((unsigned char)serv_request[19+len_h+4]);
                            for(i = 0; i < len_g; ++i)
                            {
                                  szGamemode[i] = serv_request[24+i+len_h];
                            }

                            len_m = 0;
                            ptr = (char *)&len_m;
                            ptr[0] = (int)((unsigned char)serv_request[16+len_h+len_g+8]);
                            ptr[1] = (int)((unsigned char)serv_request[17+len_h+len_g+8]);
                            ptr[2] = (int)((unsigned char)serv_request[18+len_h+len_g+8]);
                            ptr[3] = (int)((unsigned char)serv_request[19+len_h+len_g+8]);
                            for(i = 0; i < len_m; ++i)
                            {
                                  szMapname[i] = serv_request[28+i+len_h+len_g];
                            }

                            memset(request, 0, sizeof(request)/sizeof(char));
                            wsprintf(request, "UPDATE %s SET passwd=%d,players=%d,maxplayers=%d,name=\"%s\",mode=\"%s\",map=\"%s\",off=0 WHERE addr=\"%s\"", table, nPass, nPlayers, nMaxPlayers, szHostname, szGamemode, szMapname, addr);
                            sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
                            sqlite3_step(stmt_th); //выполняем запрос
                            sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                            sqlite3_finalize(stmt_th); //очищаем запрос
                  
                            Form1->SetServerProperties((TObject *)Sender, row, false);

//                            clnt.sin_family = AF_INET;
//                            clnt.sin_port = htons(port);
//                            memcpy(&(clnt.sin_addr.S_un.S_un_b), serv_request+4, 4);
//                            memset(clnt.sin_zero, 0, sizeof(clnt.sin_zero));

//                            serv_request[10] = 'p';
//                            ms = clock();
//                            memcpy(&serv_request[11], &ms, sizeof(long));
//                            sendto(*sock, serv_request, 15, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
//                            Sleep(Form1->SleepInterval*2);
//                            ms = clock();
//                            memcpy(&serv_request[11], &ms, sizeof(long));
//                            sendto(*sock, serv_request, 15, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
//                            Sleep(Form1->SleepInterval);

                            //MessageBox(NULL, addr, "", MB_OK);
                            break;
                        }
                        case 'r':
                        {
                            len_h = 0;
                            ptr = (char *)&len_h;
                            ptr[0] = (int)((unsigned char)serv_request[11]);
                            ptr[1] = (int)((unsigned char)serv_request[12]);

                            for(i = 0, pos = 13; i < len_h; ++i)
                            {
                              len_g = 0;
                              ptr = (char *)&len_g;
                              ptr[0] = (int)((unsigned char)serv_request[pos]);
                              len_m = 0;
                              ptr = (char *)&len_m;
                              ptr[0] = (int)((unsigned char)serv_request[pos+1+len_g]);
                              memset(szHostname, 0, sizeof(szHostname));
                              memset(szGamemode, 0, sizeof(szGamemode));
                              memcpy(szHostname, &serv_request[pos+1], len_g);
                              memcpy(szGamemode, &serv_request[pos+2+len_g], len_m);
                              pos = pos+2+len_g+len_m;

//                              MessageBox(NULL, AnsiString(szHostname).c_str(), "", MB_OK);

                              if(strcmp(szHostname, "lagcomp") == 0)
                              {
                                strncpy(lagcomp, szGamemode, sizeof(lagcomp));
                                continue;
                              }
                              if(strcmp(szHostname, "version") == 0)
                              {
                                strncpy(version, szGamemode, sizeof(version));
                                continue;
                              }
                              if(strcmp(szHostname, "weather") == 0)
                              {
                                strncpy(weather, szGamemode, sizeof(weather));
                                continue;
                              }
                              if(strcmp(szHostname, "worldtime") == 0)
                              {
                                strncpy(worldtime, szGamemode, sizeof(worldtime));
                                continue;
                              }
                              if(strcmp(szHostname, "weburl") == 0)
                              {
                                strncpy(weburl, szGamemode, sizeof(weburl));
                                continue;
                              }
                            }

                            memset(request, 0, sizeof(request)/sizeof(char));
                            wsprintf(request, "UPDATE %s SET lagcomp=\"%s\",version=\"%s\",weather=\"%s\",worldtime=\"%s\",weburl=\"%s\",off=0 WHERE addr=\"%s\"",table,lagcomp,version,weather,worldtime,weburl,addr);
//                                MessageBox(NULL, AnsiString(request).c_str(), "", MB_OK);
                            sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
                            sqlite3_step(stmt_th); //выполняем запрос
                            sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                            sqlite3_finalize(stmt_th); //очищаем запрос

                            Form1->SetServerProperties((TObject *)Sender, row, false);
                            break;
                        }
                        case 'c':
                        {
                            memset(players_request, 0, sizeof(players_request)/sizeof(char));
/*
                            memset(request, 0, sizeof(request)/sizeof(char));
                            wsprintf(request, "SELECT id FROM %s WHERE addr=\"%s\"", table, addr);
//                                MessageBox(NULL, AnsiString(request).c_str(), "", MB_OK);
                            sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
                            sqlite3_step(stmt_th); //выполняем запрос
                            id = sqlite3_column_int( stmt_th, 0 );
                            sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                            sqlite3_finalize(stmt_th); //очищаем запрос
*/
                            memset(request, 0, sizeof(request)/sizeof(char));
                            wsprintf(request, "DELETE FROM %s_players WHERE id=%d", table, id);
                            sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
                            sqlite3_step(stmt_th); //выполняем запрос
                            sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                            sqlite3_finalize(stmt_th); //очищаем запрос

                            len_h = 0;
                            ptr = (char *)&len_h;
                            ptr[0] = (int)((unsigned char)serv_request[11]);
                            ptr[1] = (int)((unsigned char)serv_request[12]);

                            wsprintf(players_request, "INSERT INTO %s_players(id,name,score) VALUES ", table);
                            for(i = 0, pos = 13; i < len_h; ++i)
                            {
                              len_g = 0;
                              ptr = (char *)&len_g;
                              ptr[0] = (int)((unsigned char)serv_request[pos]);
                              memset(szHostname, 0, sizeof(szHostname));
                              memcpy(szHostname, &serv_request[pos+1], len_g);
                              memcpy(&r, &serv_request[pos+1+len_g], 4);
                              pos = pos+5+len_g;
//                              MessageBox(NULL, AnsiString(szHostname).c_str(), "", MB_OK);
                              strncat(players_request, "(", sizeof(players_request)/sizeof(char));
                              strncat(players_request, AnsiString(id).c_str(), sizeof(players_request)/sizeof(char));
                              strncat(players_request, ",\"", sizeof(players_request)/sizeof(char));
                              strncat(players_request, szHostname, sizeof(players_request)/sizeof(char));
                              strncat(players_request, "\",", sizeof(players_request)/sizeof(char));
                              strncat(players_request, AnsiString(r).c_str(), sizeof(players_request)/sizeof(char));
                              if(i < (len_h-1))
                                      strncat(players_request, "),", sizeof(players_request)/sizeof(char));
                              else
                                      strncat(players_request, ")", sizeof(players_request)/sizeof(char));
                            }

//                            MessageBox(NULL, players_request, "", MB_OK);
                            sqlite3_prepare(Form1->conn, players_request, -1, &stmt_th, 0); //подготовка запроса
                            sqlite3_step(stmt_th); //выполняем запрос
                            sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                            sqlite3_finalize(stmt_th); //очищаем запрос
//                              MessageBox(NULL, AnsiString(szHostname).c_str(), "", MB_OK);

                            Form1->SetServerProperties((TObject *)Sender, row, true);
                            break;
                        }
                        case 'p':
                        {
                            ping = 0L;
                            ms = 0L;
                            //gettimeofday(&tm, NULL);
                            ms = clock();//tm.tv_sec * 1000 + tm.tv_usec / 1000;
                            memcpy(&ping, &serv_request[11], sizeof(long));
                            ping = ms - ping;
                            if(ping != 0)
                            {
                                    memset(players_request, 0, sizeof(players_request)/sizeof(char));
                                    wsprintf(players_request, "UPDATE %s SET ping=%d,off=0 WHERE addr=\"%s\"", table, ping, addr);
                                    sqlite3_prepare(Form1->conn, players_request, -1, &stmt_th, 0); //подготовка запроса
                                    sqlite3_step(stmt_th); //выполняем запрос
                                    sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                                    sqlite3_finalize(stmt_th); //очищаем запрос
                                    Form1->SetServerProperties((TObject *)Sender, row, false);
                            }
                            break;
                        }
                  }
                }
                memset(serv_request, 0, sizeof(serv_request));
        }
//        MessageBox(NULL, "The end", "", MB_OK);

    }
    catch(Exception *ex)
    {}
    
        ExitThread(0);
}
//---------------------------------------------------------------------------

unsigned long __stdcall ThreadPutServerInfo(void *Prm)
{
        int row;
        sqlite3_stmt *stmt_th, *stmt_off;        
        char result[1024], result1[1024];
        char table[128];
        TObject *Sender;
        TStringGrid *ServerInfo;
        TLabel *URLLabel;
        char request[2048];
        const unsigned char *res;
        static struct sockaddr_in clnt;
        char serv_request[1024];
        char int_addr[5];
        char int_port[3];
        unsigned int port, i, r, pos, len_h, len_g, len_m;
        int n, id;
        char *ptr;
        char addr[128];
        int nPass, nPlayers, nMaxPlayers;
        SOCKET *sock;
        PHOSTENT hps;
        long ms;

    try {
        Sender = (TObject *)(((struct ThreadParameters *)Prm)->Sender);
        row = ((struct ThreadParameters *)Prm)->Row;

        if(((TStringGrid *)Sender) == Form1->StringGrid1)
        {
                ServerInfo = Form1->StringGrid3;
                strncpy(table, "favorites", sizeof(table));
                URLLabel = Form1->Label15;
                sock = &(Form1->servers_s);
        }
        else if(((TStringGrid *)Sender) == Form1->StringGrid4)
        {
                ServerInfo = Form1->StringGrid6;
                strncpy(table, "internet", sizeof(table));
                URLLabel = Form1->Label17;
                sock = &(Form1->internets_s);
        }
        else if(((TStringGrid *)Sender) == Form1->StringGrid7)
        {
                ServerInfo = Form1->StringGrid9;
                strncpy(table, "hosted", sizeof(table));
                URLLabel = Form1->Label16;
                sock = &(Form1->hosteds_s);
        }
/*
        memset(request, 0, sizeof(request));
        wsprintf(request, "DELETE FROM %s_players", table);
        sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
        sqlite3_step(stmt_th);        
        sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
        sqlite3_finalize(stmt_th); //очищаем запрос
*/        
        
        memset(request, 0, sizeof(request));
        wsprintf(request, "SELECT addr FROM %s WHERE row=%d", table, row);
        sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
        sqlite3_step(stmt_th);        
        res = sqlite3_column_text( stmt_th, 0 );
        if(res != NULL)
        {
                memset(result, 0, sizeof(result));
                memset(int_addr, 0, sizeof(int_addr));
                memset(int_port, 0, sizeof(int_port));
                strncpy(result, res, 1024);
                if(result[0] < '0' || result[0] > '9')
                {
                        for(i = 0, r = 0; i < strlen(result); ++i)
                        {
                                if(result[i] == ':')
                                {
                                        port = atoi(&result[i+1]);
                                        result[i] = '\0';
                                        break;
                                }
                        }
                        hps = gethostbyname(result);
                        if(hps == NULL)
                                ExitThread(0);
//                        MessageBox(NULL, AnsiString().sprintf("%d",hps->h_addr[3]).c_str(), "", MB_OK);
                        for(i = 0; i < 4; ++i)
                        {
                                int_addr[i] = (hps->h_addr[i]);
                        }
                }
                else
                {
                  int_addr[0] = atoi(result);
                  for(i = 0, r = 0; i < strlen(result); ++i)
                  {
                          if(result[i] == '.')
                          {
                                  r++;
                                  int_addr[r] = atoi(&result[i+1]);
                                  continue;
                          }
                          if(result[i] == ':')
                          {
                                  port = atoi(&result[i+1]);
                                  break;
                          }
                  }
                }
                int_port[0] = (port&0xFF);
                int_port[1] = (port&0xFF00)>>8;

                memset(serv_request, 0, sizeof(serv_request));
                strcpy(serv_request, "SAMP");
                memcpy(serv_request+4, int_addr, 4);
                memcpy(serv_request+8, int_port, 2);
                serv_request[10] = 'i';

                clnt.sin_family = AF_INET;
                clnt.sin_port = htons(port);
                memcpy(&(clnt.sin_addr.S_un.S_un_b), int_addr, 4);
                memset(clnt.sin_zero, 0, sizeof(clnt.sin_zero));
                sendto(*sock, serv_request, 11, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                Sleep(Form1->SleepInterval);
                serv_request[10] = 'c';
                sendto(*sock, serv_request, 11, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                Sleep(Form1->SleepInterval);
                serv_request[10] = 'r';
                sendto(*sock, serv_request, 11, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                Sleep(Form1->SleepInterval);

                ms = 0L;
                //gettimeofday(&tm, NULL);
                ms = clock();//tm.tv_sec * 1000 + tm.tv_usec / 1000;
                serv_request[10] = 'p';
                memcpy(&serv_request[11], &ms, sizeof(long));
                sendto(*sock, serv_request, 15, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                ms = clock();
                memcpy(&serv_request[11], &ms, sizeof(long));
                sendto(*sock, serv_request, 15, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                Sleep(Form1->SleepInterval);

                memset(request, 0, sizeof(request)/sizeof(char));
                wsprintf(request, "UPDATE %s SET off=off+1 WHERE addr=\"%s\"", table, res);
                sqlite3_prepare(Form1->conn, request, -1, &stmt_off, 0); //подготовка запроса
                sqlite3_step(stmt_off); //выполняем запрос

//                MessageBox(NULL, result, "", MB_OK);
        }
        sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
        sqlite3_finalize(stmt_th); //очищаем запрос

    }
    catch(Exception *ex)
    {}
            
        ExitThread(0);
}

unsigned long __stdcall ThreadGetServerInfo(void *Prm)
{
        int row;
        sqlite3_stmt *stmt_th;        
        char result[1024], result1[1024];
        char table[128];
        TObject *Sender;
        TStringGrid *ServerInfo;
        TLabel *URLLabel;
        char request[2048];
        const unsigned char *res;
        static struct sockaddr_in clnt;
        char serv_request[1024];
        char int_addr[5];
        char int_port[3];
        unsigned int port, i, r, pos, len_h, len_g, len_m;
        int n, id;
        char *ptr;
        char addr[128];
        int nPass, nPlayers, nMaxPlayers;
        char szHostname[512], szGamemode[512], szMapname[512];
        char lagcomp[128],version[128],weather[128],worldtime[128],weburl[512];
        char players_request[102400];
        SOCKET *sock;
        struct timeval tm;
        long ping, ms;

    try {
        Sender = (TObject *)(((struct ThreadParameters *)Prm)->Sender);
        row = ((struct ThreadParameters *)Prm)->Row;

        memset(table, 0, sizeof(table));
        if(((TStringGrid *)Sender) == Form1->StringGrid1)
        {
                ServerInfo = Form1->StringGrid3;
                strncpy(table, "favorites", sizeof(table));
                URLLabel = Form1->Label15;
                sock = &(Form1->server_s);
        }
        else if(((TStringGrid *)Sender) == Form1->StringGrid4)
        {
                ServerInfo = Form1->StringGrid6;
                strncpy(table, "internet", sizeof(table));
                URLLabel = Form1->Label17;
                sock = &(Form1->internet_s);
        }
        else if(((TStringGrid *)Sender) == Form1->StringGrid7)
        {
                ServerInfo = Form1->StringGrid9;
                strncpy(table, "hosted", sizeof(table));
                URLLabel = Form1->Label16;
                sock = &(Form1->hosted_s);
        }
        
        memset(serv_request, 0, sizeof(serv_request));
        while(1)
        {
                n = recv(*sock, serv_request, sizeof(serv_request)-1, 0);

//                MessageBox(NULL, AnsiString(n).c_str(), "", MB_OK);

                if(n < 11)
                {
                        Sleep(100);
                        continue;
                }

                if(((unsigned char)serv_request[4]) != 0)
                {
                  memset(addr, 0, sizeof(addr));
                  ptr = (char *)&port;
                  port = 0;
                  ptr[0] = serv_request[8];
                  ptr[1] = serv_request[9];
                  wsprintf(addr, "%d.%d.%d.%d:%d", (unsigned char)serv_request[4],
                                                   (unsigned char)serv_request[5],
                                                   (unsigned char)serv_request[6],
                                                   (unsigned char)serv_request[7],
                                                    port);

                  memset(request, 0, sizeof(request)/sizeof(char));
                  wsprintf(request, "SELECT row,id FROM %s WHERE addr=\"%s\"", table, addr);
                  sqlite3_prepare(Form1->conn, request, -1, &(stmt_th), 0); //подготовка запроса
                  sqlite3_step(stmt_th); //выполняем запрос
                  row = sqlite3_column_int( stmt_th, 0 );
                  id = sqlite3_column_int( stmt_th, 1 );
                  sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                  sqlite3_finalize(stmt_th); //очищаем запрос
                                                    
                  switch(serv_request[10])
                  {
                        case 'i':
                        {
                            nPass = 0;
                            nPlayers = 0;
                            nMaxPlayers = 0;
                            memset(szHostname, 0, sizeof(szHostname));
                            memset(szGamemode, 0, sizeof(szGamemode));
                            memset(szMapname, 0, sizeof(szMapname));
//                            MessageBox(NULL, AnsiString(n).c_str(), "", MB_OK);
                            memset(int_port, 0, sizeof(int_port));
                            nPass = (int)((unsigned char)serv_request[11]);
                            ptr = (char *)&nPlayers;
                            ptr[0] = (int)((unsigned char)serv_request[12]);
                            ptr[1] = (int)((unsigned char)serv_request[13]);
                            ptr = (char *)&nMaxPlayers;
                            ptr[0] = (int)((unsigned char)serv_request[14]);
                            ptr[1] = (int)((unsigned char)serv_request[15]);

                            len_h = 0;
                            ptr = (char *)&len_h;
                            ptr[0] = (int)((unsigned char)serv_request[16]);
                            ptr[1] = (int)((unsigned char)serv_request[17]);
                            ptr[2] = (int)((unsigned char)serv_request[18]);
                            ptr[3] = (int)((unsigned char)serv_request[19]);
                            for(i = 0; i < len_h; ++i)
                            {
                                  szHostname[i] = serv_request[20+i];
                            }

                            len_g = 0;
                            ptr = (char *)&len_g;
                            ptr[0] = (int)((unsigned char)serv_request[16+len_h+4]);
                            ptr[1] = (int)((unsigned char)serv_request[17+len_h+4]);
                            ptr[2] = (int)((unsigned char)serv_request[18+len_h+4]);
                            ptr[3] = (int)((unsigned char)serv_request[19+len_h+4]);
                            for(i = 0; i < len_g; ++i)
                            {
                                  szGamemode[i] = serv_request[24+i+len_h];
                            }

                            len_m = 0;
                            ptr = (char *)&len_m;
                            ptr[0] = (int)((unsigned char)serv_request[16+len_h+len_g+8]);
                            ptr[1] = (int)((unsigned char)serv_request[17+len_h+len_g+8]);
                            ptr[2] = (int)((unsigned char)serv_request[18+len_h+len_g+8]);
                            ptr[3] = (int)((unsigned char)serv_request[19+len_h+len_g+8]);
                            for(i = 0; i < len_m; ++i)
                            {
                                  szMapname[i] = serv_request[28+i+len_h+len_g];
                            }

                            if((TStringGrid *)Sender == Form1->StringGrid1)
                            {
//                              serv_request[10] = 'r';
//                              sendto(sock, serv_request, 11, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
//                              serv_request[10] = 'c';
//                              sendto(sock, serv_request, 11, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                            }

                            memset(request, 0, sizeof(request)/sizeof(char));
                            wsprintf(request, "UPDATE %s SET passwd=%d,players=%d,maxplayers=%d,name=\"%s\",mode=\"%s\",map=\"%s\",off=0 WHERE addr=\"%s\"", table, nPass, nPlayers, nMaxPlayers, szHostname, szGamemode, szMapname, addr);
                            sqlite3_prepare(Form1->conn, request, -1, &(stmt_th), 0); //подготовка запроса
                            sqlite3_step(stmt_th); //выполняем запрос
                            sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                            sqlite3_finalize(stmt_th); //очищаем запрос

                            Form1->SetServerProperties((TObject *)Sender, row, false);

//                            clnt.sin_family = AF_INET;
//                            clnt.sin_port = htons(port);
//                            memcpy(&(clnt.sin_addr.S_un.S_un_b), serv_request+4, 4);
//                            memset(clnt.sin_zero, 0, sizeof(clnt.sin_zero));

//                            serv_request[10] = 'p';
//                            ms = clock();
//                            memcpy(&serv_request[11], &ms, sizeof(long));
//                            sendto(*sock, serv_request, 15, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
//                            Sleep(Form1->SleepInterval*2);
//                            ms = clock();
//                            memcpy(&serv_request[11], &ms, sizeof(long));
//                            sendto(*sock, serv_request, 15, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
//                            Sleep(Form1->SleepInterval);

                            //MessageBox(NULL, addr, "", MB_OK);
                            break;
                        }
                        case 'r':
                        {
                            len_h = 0;
                            ptr = (char *)&len_h;
                            ptr[0] = (int)((unsigned char)serv_request[11]);
                            ptr[1] = (int)((unsigned char)serv_request[12]);

                            if((TStringGrid *)Sender == Form1->StringGrid1)
                            {
//                              serv_request[10] = 'c';
//                              sendto(sock, serv_request, 11, 0, (const sockaddr *)&clnt, sizeof(struct sockaddr));
                            }

                            for(i = 0, pos = 13; i < len_h; ++i)
                            {
                              len_g = 0;
                              ptr = (char *)&len_g;
                              ptr[0] = (int)((unsigned char)serv_request[pos]);
                              len_m = 0;
                              ptr = (char *)&len_m;
                              ptr[0] = (int)((unsigned char)serv_request[pos+1+len_g]);
                              memset(szHostname, 0, sizeof(szHostname));
                              memset(szGamemode, 0, sizeof(szGamemode));
                              memcpy(szHostname, &serv_request[pos+1], len_g);
                              memcpy(szGamemode, &serv_request[pos+2+len_g], len_m);
                              pos = pos+2+len_g+len_m;

//                              MessageBox(NULL, AnsiString(szHostname).c_str(), "", MB_OK);

                              if(strcmp(szHostname, "lagcomp") == 0)
                              {
                                strncpy(lagcomp, szGamemode, sizeof(lagcomp));
                                continue;
                              }
                              if(strcmp(szHostname, "version") == 0)
                              {
                                strncpy(version, szGamemode, sizeof(version));
                                continue;
                              }
                              if(strcmp(szHostname, "weather") == 0)
                              {
                                strncpy(weather, szGamemode, sizeof(weather));
                                continue;
                              }
                              if(strcmp(szHostname, "worldtime") == 0)
                              {
                                strncpy(worldtime, szGamemode, sizeof(worldtime));
                                continue;
                              }
                              if(strcmp(szHostname, "weburl") == 0)
                              {
                                strncpy(weburl, szGamemode, sizeof(weburl));
                                continue;
                              }
                            }

                            memset(request, 0, sizeof(request)/sizeof(char));
                            wsprintf(request, "UPDATE %s SET lagcomp=\"%s\",version=\"%s\",weather=\"%s\",worldtime=\"%s\",weburl=\"%s\",off=0 WHERE addr=\"%s\"",table,lagcomp,version,weather,worldtime,weburl,addr);
//                                MessageBox(NULL, AnsiString(request).c_str(), "", MB_OK);
                            sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
                            sqlite3_step(stmt_th); //выполняем запрос
                            sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                            sqlite3_finalize(stmt_th); //очищаем запрос
                            
                            Form1->SetServerProperties((TObject *)Sender, row, false);
                            break;
                        }
                        case 'c':
                        {
                            memset(players_request, 0, sizeof(players_request)/sizeof(char));
                            memset(request, 0, sizeof(request)/sizeof(char));
                            wsprintf(request, "DELETE FROM %s_players WHERE id=%d", table, id);
                            sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
                            sqlite3_step(stmt_th); //выполняем запрос
                            sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                            sqlite3_finalize(stmt_th); //очищаем запрос

                            len_h = 0;
                            ptr = (char *)&len_h;
                            ptr[0] = (int)((unsigned char)serv_request[11]);
                            ptr[1] = (int)((unsigned char)serv_request[12]);

                            wsprintf(players_request, "INSERT INTO %s_players(id,name,score) VALUES ", table);
                            for(i = 0, pos = 13; i < len_h; ++i)
                            {
                              len_g = 0;
                              ptr = (char *)&len_g;
                              ptr[0] = (int)((unsigned char)serv_request[pos]);
                              memset(szHostname, 0, sizeof(szHostname));
                              memcpy(szHostname, &serv_request[pos+1], len_g);
                              memcpy(&r, &serv_request[pos+1+len_g], 4);
                              pos = pos+5+len_g;
//                              MessageBox(NULL, AnsiString(szHostname).c_str(), "", MB_OK);
                              strncat(players_request, "(", sizeof(players_request)/sizeof(char));
                              strncat(players_request, AnsiString(id).c_str(), sizeof(players_request)/sizeof(char));
                              strncat(players_request, ",\"", sizeof(players_request)/sizeof(char));
                              strncat(players_request, szHostname, sizeof(players_request)/sizeof(char));
                              strncat(players_request, "\",", sizeof(players_request)/sizeof(char));
                              strncat(players_request, AnsiString(r).c_str(), sizeof(players_request)/sizeof(char));
                              if(i < (len_h-1))
                                      strncat(players_request, "),", sizeof(players_request)/sizeof(char));
                              else
                                      strncat(players_request, ")", sizeof(players_request)/sizeof(char));
                            }

//                            MessageBox(NULL, players_request, "", MB_OK);
                            sqlite3_prepare(Form1->conn, players_request, -1, &stmt_th, 0); //подготовка запроса
                            sqlite3_step(stmt_th); //выполняем запрос
                            sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                            sqlite3_finalize(stmt_th); //очищаем запрос
//                              MessageBox(NULL, AnsiString(szHostname).c_str(), "", MB_OK);

                            Form1->SetServerProperties((TObject *)Sender, row, true);
                            break;
                        }
                        case 'p':
                        {
                            ping = 0L;
                            ms = 0L;
                            ms = clock();
                            memcpy(&ping, &serv_request[11], sizeof(long));
                            ping = ms - ping;
                            if(ping != 0)
                            {
                                    memset(players_request, 0, sizeof(players_request)/sizeof(char));
                                    wsprintf(players_request, "UPDATE %s SET ping=%d,off=0 WHERE addr=\"%s\"", table, ping, addr);
                                    sqlite3_prepare(Form1->conn, players_request, -1, &stmt_th, 0); //подготовка запроса
                                    sqlite3_step(stmt_th); //выполняем запрос
                                    sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
                                    sqlite3_finalize(stmt_th); //очищаем запрос
                                    Form1->SetServerProperties((TObject *)Sender, row, false);
                            }
                            break;
                        }                        
                  }
                }
                memset(serv_request, 0, sizeof(serv_request));
        }
    }
    catch(Exception *ex)
    {}
            
        ExitThread(0);
}
//---------------------------------------------------------------------------

unsigned long __stdcall ThreadStartProgram(void *)
{

        char *sErrMsg;
        char request[10240];
        sqlite3_stmt *stmt_th;
        static struct ThreadParameters Prm, Prm1, Prm2;

    try {
        Sleep(1000);

        if( (Form1->servers_s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
          ExitThread(1);
        if( (Form1->server_s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
          ExitThread(2);
        if( (Form1->internets_s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
          ExitThread(3);
        if( (Form1->internet_s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
          ExitThread(4);
        if( (Form1->hosteds_s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
          ExitThread(5);
        if( (Form1->hosted_s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
          ExitThread(6);

        sprintf(request, "DELETE FROM internet WHERE off>15");
        sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
        sqlite3_step(stmt_th); //выполняем запрос
        sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
        sqlite3_finalize(stmt_th); //очищаем запрос
        sprintf(request, "DELETE FROM hosted WHERE off>15");
        sqlite3_prepare(Form1->conn, request, -1, &stmt_th, 0); //подготовка запроса
        sqlite3_step(stmt_th); //выполняем запрос
        sqlite3_reset(stmt_th); //сбрасываем инструкцию (stmt)
        sqlite3_finalize(stmt_th); //очищаем запрос

        Form1->hServersGet = CreateThread(NULL, 0, ThreadGetServersInfo, (void *)Form1->StringGrid1, 0, &Form1->thread_servers_get);
        Form1->hServersPut = CreateThread(NULL, 0, ThreadPutServersInfo, (void *)Form1->StringGrid1, 0, &Form1->thread_servers_put);
        Prm.Sender = Form1->StringGrid1;
        Prm.Row = 1;
        Form1->hServerGet = CreateThread(NULL, 0, ThreadGetServerInfo, (void *)&Prm, 0, &Form1->thread_server_get);

        Form1->hInternetsGet = CreateThread(NULL, 0, ThreadGetServersInfo, (void *)Form1->StringGrid4, 0, &Form1->thread_internets_get);
        Prm1.Sender = Form1->StringGrid4;
        Prm1.Row = 1;
        Form1->hInternetGet = CreateThread(NULL, 0, ThreadGetServerInfo, (void *)&Prm1, 0, &Form1->thread_internet_get);

        //подмога для основного потока
//        Form1->hInternetsGet1 = CreateThread(NULL, 0, ThreadGetServersInfo, (void *)Form1->StringGrid4, 0, &Form1->thread_internets_get1);
//        Form1->hInternetsGet2 = CreateThread(NULL, 0, ThreadGetServersInfo, (void *)Form1->StringGrid4, 0, &Form1->thread_internets_get2);

        Form1->hHostedsGet = CreateThread(NULL, 0, ThreadGetServersInfo, (void *)Form1->StringGrid7, 0, &Form1->thread_hosteds_get);
        Prm2.Sender = Form1->StringGrid7;
        Prm2.Row = 1;
        Form1->hHostedGet = CreateThread(NULL, 0, ThreadGetServerInfo, (void *)&Prm2, 0, &Form1->thread_hosted_get);

        Form1->hServersLists = CreateThread(NULL, 0, ThreadGetServersLists, (void *)Form1->StringGrid4, 0, &Form1->thread_servers_lists);
        Form1->hHostedsLists = CreateThread(NULL, 0, ThreadGetServersLists, (void *)Form1->StringGrid7, 0, &Form1->thread_hosteds_lists);

        Form1->FillServerList(true); //заполняем таблицы "favorites", "internet" и "hosted"

    }
    catch(Exception *ex)
    {}
        
        ExitThread(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image27Click(TObject *Sender)
{
/*
        TerminateThread(hServersPut, 0);
        CloseHandle(hServersPut);
        hServersPut = CreateThread(NULL, 0, ThreadPutServersInfo, (void *)StringGrid1, 0, &thread_servers_put);
*/        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
        int row, i;
        char table[1024], result[1024];
        TStringGrid *MainTable;
        TRect rect(3, Rect.top+2, 16, Rect.bottom-2);
        TRect rect_lock(2, -1, 18, 14);

    try {
        if (ARow != 0 && ARow%2 == 1 && ARow != ((TStringGrid *)Sender)->Row)
        {
            ((TStringGrid *)Sender)->Canvas->Brush->Color = TColor(0xEFEFEF);
            ((TStringGrid *)Sender)->Canvas->FillRect(Rect);
//            ((TStringGrid *)Sender)->Canvas->Brush->Color = TColor(0xFFFFFF);
            ((TStringGrid *)Sender)->Font->Color = TColor(0x000000);
            ((TStringGrid *)Sender)->Canvas->TextOut(Rect.Left+2,Rect.Top+3,((TStringGrid *)Sender)->Cells[ACol][ARow]);
        }
        else if (ARow != 0 && ARow%2 == 0 && ARow != ((TStringGrid *)Sender)->Row)
        {
            ((TStringGrid *)Sender)->Canvas->Brush->Color = TColor(0xFFFFFF);
            ((TStringGrid *)Sender)->Canvas->FillRect(Rect);
//            ((TStringGrid *)Sender)->Canvas->Brush->Color = TColor(0xFFFFFF);
            ((TStringGrid *)Sender)->Font->Color = TColor(0);
            ((TStringGrid *)Sender)->Canvas->TextOut(Rect.Left+2,Rect.Top+3,((TStringGrid *)Sender)->Cells[ACol][ARow]);
        }
        
        if(ACol != 0)
                return;

        if(ACol == 0 && ARow == 0)
        {
                ((TStringGrid *)Sender)->Canvas->StretchDraw(rect_lock, Image38->Picture->Bitmap);
                return;
        }

        if(((TStringGrid *)Sender) == StringGrid1)
        {
                MainTable = StringGrid1;
                strncpy(table, "favorites", sizeof(table));
        }
        else if(((TStringGrid *)Sender) == StringGrid4)
        {
                MainTable = StringGrid4;
                strncpy(table, "internet", sizeof(table));
        }
        else if(((TStringGrid *)Sender) == StringGrid7)
        {
                MainTable = StringGrid7;
                strncpy(table, "hosted", sizeof(table));
        }

        if(ACol == 0 && ARow > 0)
        {
            if(GetCol("passwd", table, ARow, result) > 0)
            {
              if(atoi(result) > 0)
                      MainTable->Canvas->StretchDraw(rect, Image40->Picture->Bitmap);
              else
                      MainTable->Canvas->StretchDraw(rect, Image39->Picture->Bitmap);
            }
        }
    }
    catch(Exception *ex)
    {}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::About1Click(TObject *Sender)
{
        Form4->Show();        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Image5Click(TObject *Sender)
{
        TClipboard *Clip = new TClipboard();

        if(!StringGrid1->Visible)
                Clip->AsText = Form1->Label9->Caption;

        delete Clip;

        Form5->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid2DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
    try {
        if (ARow != 0 && ARow%2 == 1)
        {
            ((TStringGrid *)Sender)->Canvas->Brush->Color = TColor(0xEFEFEF);
            ((TStringGrid *)Sender)->Canvas->FillRect(Rect);
            ((TStringGrid *)Sender)->Font->Color = TColor(0x000000);
            ((TStringGrid *)Sender)->Canvas->TextOut(Rect.Left+2,Rect.Top+3,((TStringGrid *)Sender)->Cells[ACol][ARow]);
        } else if (ARow != 0 && ARow%2 == 0)
        {
            ((TStringGrid *)Sender)->Canvas->Brush->Color = TColor(0xFFFFFF);
            ((TStringGrid *)Sender)->Canvas->FillRect(Rect);
            ((TStringGrid *)Sender)->Font->Color = TColor(0x000000);
            ((TStringGrid *)Sender)->Canvas->TextOut(Rect.Left+2,Rect.Top+3,((TStringGrid *)Sender)->Cells[ACol][ARow]);
        }
    }
    catch(Exception *ex)
    {}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image18Click(TObject *Sender)
{
        TClipboard *Clip = new TClipboard();

        Clip->AsText = Form1->Label9->Caption;

        delete Clip;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image12Click(TObject *Sender)
{
        static struct ThreadParameters Param;
        
        if(Form1->StringGrid1->Visible)
        {
                Param.Sender = Form1->StringGrid1;
        }
        else if(Form1->StringGrid4->Visible)
        {
                Param.Sender = Form1->StringGrid4;
        }
        else if(Form1->StringGrid7->Visible)
        {
                Param.Sender = Form1->StringGrid7;
        }
        Param.Row = Param.Sender->Row;

        if(Form1->StringGrid1->Visible)
        {
                TerminateThread(hServerPut, 0);
                CloseHandle(hServerPut);
                hServerPut = CreateThread(NULL, 0, ThreadPutServerInfo, (void *)&Param, 0, &thread_server_put);
        }
        else if(Form1->StringGrid4->Visible)
        {
                TerminateThread(hInternetPut, 0);
                CloseHandle(hInternetPut);
                hInternetPut = CreateThread(NULL, 0, ThreadPutServerInfo, (void *)&Param, 0, &thread_internet_put);
        }
        else if(Form1->StringGrid7->Visible)
        {
                TerminateThread(hHostedPut, 0);
                CloseHandle(hHostedPut);
                hHostedPut = CreateThread(NULL, 0, ThreadPutServerInfo, (void *)&Param, 0, &thread_hosted_put);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
        TStringGrid *MainTable;


        if((TLabel *)Sender == Label20)
                CheckBox1->Checked ^= 1;
        else if((TLabel *)Sender == Label21)
                CheckBox2->Checked ^= 1;
        else if((TLabel *)Sender == Label22)
                CheckBox3->Checked ^= 1;
        else if((TLabel *)Sender == Label23)
                CheckBox14->Checked ^= 1;

        if(Form1->StringGrid1->Visible)
        {
                MainTable = Form1->StringGrid1;
        }
        else if(Form1->StringGrid4->Visible)
        {
                MainTable = Form1->StringGrid4;
        }
        else if(Form1->StringGrid7->Visible)
        {
                MainTable = Form1->StringGrid7;
        }

//        FilterServerList(MainTable, "old");

        FilterServerList(StringGrid1, "old");
        FilterServerList(StringGrid4, "old");
        FilterServerList(StringGrid7, "old");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Change(TObject *Sender)
{
        TStringGrid *MainTable;
        
        if(Form1->StringGrid1->Visible)
        {
                MainTable = Form1->StringGrid1;
        }
        else if(Form1->StringGrid4->Visible)
        {
                MainTable = Form1->StringGrid4;
        }
        else if(Form1->StringGrid7->Visible)
        {
                MainTable = Form1->StringGrid7;
        }

//        FilterServerList(MainTable, "old");

        FilterServerList(StringGrid1, "old");
        FilterServerList(StringGrid4, "old");
        FilterServerList(StringGrid7, "old");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image15Click(TObject *Sender)
{
        if(StringGrid4->Visible)
        {
                TerminateThread(Form1->hServersLists, 0);
                CloseHandle(Form1->hServersLists);
                Form1->hServersLists = CreateThread(NULL, 0, ThreadGetServersLists, (void *)StringGrid4, 0, &thread_servers_lists);
        }
        else if(StringGrid7->Visible)
        {
                TerminateThread(Form1->hHostedsLists, 0);
                CloseHandle(Form1->hHostedsLists);
                Form1->hHostedsLists = CreateThread(NULL, 0, ThreadGetServersLists, (void *)StringGrid7, 0, &thread_hosteds_lists);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
        TRegistry *reg = new TRegistry(KEY_ALL_ACCESS);

        if (reg) // если всё ОК
            {
            // выбираем нужный корень
            reg->RootKey = HKEY_CURRENT_USER;

            // открываем секцию
            reg->OpenKey("Software\\SAMP\\", true);

            // записываем значения
            reg->WriteString("PlayerName", Edit1->Text);

            // закрываем секцию
            reg->CloseKey();
            }
        delete reg;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Extraoptions1Click(TObject *Sender)
{
        fExtraOptions = !fExtraOptions;
        Extraoptions1->Checked = fExtraOptions;
        TRegistry *reg = new TRegistry(KEY_ALL_ACCESS);

        if(fExtraOptions)
        {
                Form1->Height += ExtraHeight;
                GroupBox1->Height += ExtraHeight;
                GroupBox2->Height += ExtraHeight;
                Form1->Constraints->MinHeight += ExtraHeight;
                Label19->Visible = true;
                Edit4->Visible = true;
                CheckBox4->Visible = true;
                CheckBox5->Visible = true;
                CheckBox6->Visible = true;
                CheckBox7->Visible = true;
                CheckBox8->Visible = true;
                CheckBox9->Visible = true;
                CheckBox10->Visible = true;
                CheckBox11->Visible = true;
                CheckBox12->Visible = true;
                CheckBox13->Visible = true;
        }
        else
        {
                GroupBox1->Height -= ExtraHeight;
                GroupBox2->Height -= ExtraHeight;
                Form1->Constraints->MinHeight -= ExtraHeight;
                Form1->Height -= ExtraHeight;
                Label19->Visible = false;
                Edit4->Visible = false;
                CheckBox4->Visible = false;
                CheckBox5->Visible = false;
                CheckBox6->Visible = false;
                CheckBox7->Visible = false;
                CheckBox8->Visible = false;
                CheckBox9->Visible = false;
                CheckBox10->Visible = false;
                CheckBox11->Visible = false;
                CheckBox12->Visible = false;
                CheckBox13->Visible = false;
        }

        if (reg) // если всё ОК
        {
            // выбираем нужный корень
            reg->RootKey = HKEY_CURRENT_USER;

            // открываем секцию
            reg->OpenKey("Software\\SAMP\\", true);

            // записываем значения
            reg->WriteInteger("ExtraOptions", fExtraOptions?1:0);

            // закрываем секцию
            reg->CloseKey();
        }
        delete reg;

        Form1->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image8Click(TObject *Sender)
{
        char *ptr, *ptr_port;
        char file_data[204800], find_data[1024], path[1024], addr[1024], ip[16], port[8];
        FILE *fd;
        int num, n, i, len, file_len, nport;
        unsigned long thread_servers_put;

        ptr = getenv("userprofile");
        if(ptr != NULL)
        {
                strncpy(path, ptr, sizeof(path));
                strncat(path, "\\Documents\\GTA San Andreas User Files\\SAMP\\USERDATA.DAT", sizeof(path));
                fd = fopen(path, "rb");

                if(fd <= 0)
                {
                        strncpy(path, ptr, sizeof(path));
                        strncat(path, "\\Мои документы\\GTA San Andreas User Files\\SAMP\\USERDATA.DAT", sizeof(path));
                        fd = fopen(path, "rb");
                }

                if(fd <= 0)
                {
                        strncpy(path, ".\\USERDATA.DAT", sizeof(path));
                        fd = fopen(path, "rb");
                }

                if(fd > 0) //открыли файл
                {
                        memset(file_data, 0, sizeof(file_data));
                        file_len = fread(file_data, 1, sizeof(file_data), fd); //считываем файл со списком серверов
                        fclose(fd);
                        memset(addr, 0, sizeof(addr));
                        strncpy(addr, Label9->Caption.c_str(), sizeof(addr));
                        while(addr[0] == ' ') //убираем пробелы из начала адреса
                        {
                                n = strlen(addr);
                                memcpy(addr, addr+1, n-1);
                                addr[n-1] = '\0';
                        }
                        ptr_port = strstr(addr, ":");
                        if(ptr_port == NULL) //если формат адреса неправильный - уходим
                                return;
                        memset(ip, 0, sizeof(ip));
                        memset(port, 0, sizeof(port));
                        ptr_port[0] = '\0';
                        strncpy(ip, addr, sizeof(ip));
                        ptr_port[6] = '\0';
                        strncpy(port, ptr_port+1, sizeof(port));
                        nport = atoi(port);
                        n = strlen(ip);

                        len = 0;
                        memset(find_data, 0, sizeof(find_data)); 
                        memcpy(find_data, &n, 4); //записываем длину адреса
                        len += 4;
                        memcpy(find_data+len, ip, n); //записываем сам адрес
                        len += n;
                        memcpy(find_data+len, &nport, 4); //записываем порт
                        len += 4;
                        n = file_len - len - 1;
                        for(i = 0; i < n; ++i)
                        {
                                if(memcmp(file_data+i, find_data, len) == 0)
                                {
                                        //вычисляем длину записи
                                        len = 4+strlen(ip)+4;
                                        len = len + ((int)(*((int *)(&file_data[i+len])))) + 12;
                                        memcpy(file_data+i, file_data+i+len, file_len-len-i);
                                        len = file_len-len;
                                        ((int) (*((int *)(file_data+8))))--; //уменьшаем количество записей о серверах
                                        fd = fopen(path, "wb");
                                        fwrite(file_data, len, 1, fd); //запивсываем изменения в файл
                                        fclose(fd);
                                        break;
                                }
                        }
                }
        }
        Form1->FillServerList(false);
        CreateThread(NULL, 0, ThreadPutServersInfo, (void *)Form1->StringGrid1, 0, &thread_servers_put);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image2Click(TObject *Sender)
{
        Form2->StartServer();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label17Click(TObject *Sender)
{
        int i, j, k;
        AnsiString Browser;
        char command[1024], path[1024];
        TRegistry *reg = new TRegistry(KEY_ALL_ACCESS);

        if (reg) // если всё ОК
            {
            // выбираем нужный корень
            reg->RootKey = HKEY_CURRENT_USER;

            // открываем секцию
            reg->OpenKey("Software\\Classes\\http\\shell\\open\\command", true);

            // считываем значения
            Browser = reg->ReadString("");
            memset(command, 0, sizeof(command));
            memset(path, 0, sizeof(path));
            for(i = 0, j = 0, k = 0; i < Browser.Length(); ++i, ++k)
            {
                path[k] = Browser.c_str()[i];
                if(path[k] == '\"')
                {
                    j++;
                    if(j == 2)
                    {
                            wsprintf(command, "%s %s", path, ((TLabel *)Sender)->Caption.c_str());
                            break;
                    }
                    continue;
                }
            }
//            MessageBox(NULL, command, "", MB_OK);
              WinExec(command, 1);

            // закрываем секцию
            reg->CloseKey();
            }
        delete reg;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
        if(time(NULL) - close_time_stamp < 1000*30)
        {
            Form1->Hide();
            Sleep(10000);
        }
	if(imes != NULL)
	{
		delete imes;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Wiki1Click(TObject *Sender)
{
        int i, j, k;
        AnsiString Browser;
        char command[1024], path[1024];
        TRegistry *reg = new TRegistry(KEY_ALL_ACCESS);

        if (reg) // если всё ОК
            {
            // выбираем нужный корень
            reg->RootKey = HKEY_CURRENT_USER;

            // открываем секцию
            reg->OpenKey("Software\\Classes\\http\\shell\\open\\command", true);

            // считываем значения
            Browser = reg->ReadString("");
            memset(command, 0, sizeof(command));
            memset(path, 0, sizeof(path));
            for(i = 0, j = 0, k = 0; i < Browser.Length(); ++i, ++k)
            {
                path[k] = Browser.c_str()[i];
                if(path[k] == '\"')
                {
                    j++;
                    if(j == 2)
                    {
                            wsprintf(command, "%s wiki.sa-mp.com", path);
                            break;
                    }
                    continue;
                }
            }
//            MessageBox(NULL, command, "", MB_OK);
              WinExec(command, 1);

            // закрываем секцию
            reg->CloseKey();
            }
        delete reg;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SAMPcom1Click(TObject *Sender)
{
        int i, j, k;
        AnsiString Browser;
        char command[1024], path[1024];
        TRegistry *reg = new TRegistry(KEY_ALL_ACCESS);

        if (reg) // если всё ОК
            {
            // выбираем нужный корень
            reg->RootKey = HKEY_CURRENT_USER;

            // открываем секцию
            reg->OpenKey("Software\\Classes\\http\\shell\\open\\command", true);

            // считываем значения
            Browser = reg->ReadString("");
            memset(command, 0, sizeof(command));
            memset(path, 0, sizeof(path));
            for(i = 0, j = 0, k = 0; i < Browser.Length(); ++i, ++k)
            {
                path[k] = Browser.c_str()[i];
                if(path[k] == '\"')
                {
                    j++;
                    if(j == 2)
                    {
                            wsprintf(command, "%s www.sa-mp.com", path);
                            break;
                    }
                    continue;
                }
            }
//            MessageBox(NULL, command, "", MB_OK);
              WinExec(command, 1);

            // закрываем секцию
            reg->CloseKey();
            }
        delete reg;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ChangeLanguage(void)
{
        TabControl1Change(this);

        Form1->Font->Charset = DEFAULT_CHARSET;
        Form1->Label2->Font->Charset = DEFAULT_CHARSET;
        Form1->Label3->Font->Charset = DEFAULT_CHARSET;
        Form1->Label4->Font->Charset = DEFAULT_CHARSET;
        Form1->Label5->Font->Charset = DEFAULT_CHARSET;
        Form1->Label6->Font->Charset = DEFAULT_CHARSET;
        Form1->Label7->Font->Charset = DEFAULT_CHARSET;
        Form1->Label8->Font->Charset = DEFAULT_CHARSET;
        Form1->Label14->Font->Charset = DEFAULT_CHARSET;
        Form1->Label19->Font->Charset = DEFAULT_CHARSET;
        Form1->Label20->Font->Charset = DEFAULT_CHARSET;
        Form1->Label21->Font->Charset = DEFAULT_CHARSET;
        Form1->Label22->Font->Charset = DEFAULT_CHARSET;
        Form1->Label23->Font->Charset = DEFAULT_CHARSET;

        Form1->TabControl1->Font->Charset = DEFAULT_CHARSET;

        Form1->GroupBox1->Font->Charset = DEFAULT_CHARSET;
        Form1->GroupBox2->Font->Charset = DEFAULT_CHARSET;
        Form1->CheckBox1->Font->Charset = DEFAULT_CHARSET;
        Form1->CheckBox2->Font->Charset = DEFAULT_CHARSET;
        Form1->CheckBox3->Font->Charset = DEFAULT_CHARSET;
        Form1->CheckBox14->Font->Charset = DEFAULT_CHARSET;

        Form1->StringGrid1->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid2->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid3->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid4->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid5->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid6->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid7->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid8->Font->Charset = DEFAULT_CHARSET;
        Form1->StringGrid9->Font->Charset = DEFAULT_CHARSET;


        if(AnsiString(Form1->iLanguage).AnsiCompare("es") == 0 ||
           AnsiString(Form1->iLanguage).AnsiCompare("pt") == 0)
        {
                Form1->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label2->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label3->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label4->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label5->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label6->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label7->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label8->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label14->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label19->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label20->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label21->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label22->Font->Charset = EASTEUROPE_CHARSET;
                Form1->Label23->Font->Charset = EASTEUROPE_CHARSET;

                Form1->TabControl1->Font->Charset = EASTEUROPE_CHARSET;

                Form1->GroupBox1->Font->Charset = EASTEUROPE_CHARSET;
                Form1->GroupBox2->Font->Charset = EASTEUROPE_CHARSET;
                Form1->CheckBox1->Font->Charset = EASTEUROPE_CHARSET;
                Form1->CheckBox2->Font->Charset = EASTEUROPE_CHARSET;
                Form1->CheckBox3->Font->Charset = EASTEUROPE_CHARSET;
                Form1->CheckBox14->Font->Charset = EASTEUROPE_CHARSET;

                Form1->StringGrid1->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid2->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid3->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid4->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid5->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid6->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid7->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid8->Font->Charset = EASTEUROPE_CHARSET;
                Form1->StringGrid9->Font->Charset = EASTEUROPE_CHARSET;

        }
/*
        else if(AnsiString(Form1->iLanguage).AnsiCompare("ru") == 0)
        {
                Form1->Font->Charset = RUSSIAN_CHARSET;
                Form1->Label2->Font->Charset = RUSSIAN_CHARSET;
                Form1->Label3->Font->Charset = RUSSIAN_CHARSET;
                Form1->Label4->Font->Charset = RUSSIAN_CHARSET;
                Form1->Label5->Font->Charset = RUSSIAN_CHARSET;
                Form1->Label6->Font->Charset = RUSSIAN_CHARSET;
                Form1->Label7->Font->Charset = RUSSIAN_CHARSET;
                Form1->Label8->Font->Charset = RUSSIAN_CHARSET;
                Form1->Label14->Font->Charset = RUSSIAN_CHARSET;
                Form1->Label19->Font->Charset = RUSSIAN_CHARSET;
                Form1->TabControl1->Font->Charset = RUSSIAN_CHARSET;

                Form1->GroupBox1->Font->Charset = RUSSIAN_CHARSET;
                Form1->GroupBox2->Font->Charset = RUSSIAN_CHARSET;
                Form1->CheckBox1->Font->Charset = RUSSIAN_CHARSET;
                Form1->CheckBox2->Font->Charset = RUSSIAN_CHARSET;
                Form1->CheckBox3->Font->Charset = RUSSIAN_CHARSET;
                Form1->CheckBox14->Font->Charset = RUSSIAN_CHARSET;

                Form1->StringGrid1->Font->Charset = RUSSIAN_CHARSET;
                Form1->StringGrid2->Font->Charset = RUSSIAN_CHARSET;
                Form1->StringGrid3->Font->Charset = RUSSIAN_CHARSET;
                Form1->StringGrid4->Font->Charset = RUSSIAN_CHARSET;
                Form1->StringGrid5->Font->Charset = RUSSIAN_CHARSET;
                Form1->StringGrid6->Font->Charset = RUSSIAN_CHARSET;
                Form1->StringGrid7->Font->Charset = RUSSIAN_CHARSET;
                Form1->StringGrid8->Font->Charset = RUSSIAN_CHARSET;
                Form1->StringGrid9->Font->Charset = RUSSIAN_CHARSET;
        }
*/
        Form1->Caption = imes->RetIString("FORM1_CAPTION_TEXT", iLanguage);

        N1->Caption = imes->RetIString("FILE_MENU", iLanguage);
        N2->Caption = imes->RetIString("LOAD_MENU", iLanguage);
        N3->Caption = imes->RetIString("SAVE_MENU", iLanguage);
        N5->Caption = imes->RetIString("EXIT_MENU", iLanguage);
        N6->Caption = imes->RetIString("VIEW_MENU", iLanguage);
        FiltrServerInfo1->Caption = imes->RetIString("FILTER_MENU", iLanguage);
        StatusBar2->Caption = imes->RetIString("STATUS_MENU", iLanguage);
        Extraoptions1->Caption = imes->RetIString("EXTRA_MENU", iLanguage);
        N7->Caption = imes->RetIString("SERVERS_MENU", iLanguage);
        N8->Caption = imes->RetIString("CONNECT_MENU", iLanguage);
        N13->Caption = imes->RetIString("ADD_SERVER_MENU", iLanguage);
        N14->Caption = imes->RetIString("DELETE_SERVER_MENU", iLanguage);
        N15->Caption = imes->RetIString("REFRESH_SERVER_MENU", iLanguage);
        N17->Caption = imes->RetIString("MASTER_LIST_MENU", iLanguage);
        N19->Caption = imes->RetIString("COPY_INFO_MENU", iLanguage);
        N20->Caption = imes->RetIString("SERVER_INFO_MENU", iLanguage);

        N9->Caption = imes->RetIString("TOOLS_MENU", iLanguage);
        N11->Caption = imes->RetIString("SETTINGS_MENU", iLanguage);

        N10->Caption = imes->RetIString("HELP_MENU", iLanguage);
        Wiki1->Caption = imes->RetIString("WIKI_MENU", iLanguage);
        About1->Caption = imes->RetIString("ABOUT_MENU", iLanguage);

        TabControl1->Tabs->Strings[0] = imes->RetIString("FAVORITES_PAR", iLanguage);
        TabControl1->Tabs->Strings[1] = imes->RetIString("INTERNET_PAR", iLanguage);
        TabControl1->Tabs->Strings[2] = imes->RetIString("HOSTED_PAR", iLanguage);

	Label1->Caption = imes->RetIString("PLAYER_NAME_PAR", iLanguage);

	Label2->Caption = imes->RetIString("MODE_PAR", iLanguage);
	Label3->Caption = imes->RetIString("MAP_PAR", iLanguage);

	Label4->Caption = imes->RetIString("HOST_ADDR_PAR", iLanguage);
	Label5->Caption = imes->RetIString("PLAYERS_PAR", iLanguage);
	Label6->Caption = imes->RetIString("PING_PAR", iLanguage);
	Label7->Caption = imes->RetIString("MODE_PAR", iLanguage);
	Label8->Caption = imes->RetIString("MAP_PAR", iLanguage);

      	Label14->Caption = imes->RetIString("PING_COL", iLanguage);

      	Label19->Caption = imes->RetIString("HOST_NAME_PAR", iLanguage);

        GroupBox1->Caption = imes->RetIString("FILTER_PAR", iLanguage);
        GroupBox2->Caption = imes->RetIString("ABOUT_SERVER_PAR", iLanguage);

        CheckBox1->Caption = "";//imes->RetIString("NOT_FULL_PAR", iLanguage);
      	Label20->Caption = imes->RetIString("NOT_FULL_PAR", iLanguage);
        CheckBox2->Caption = "";//imes->RetIString("NOT_EMPTY_PAR", iLanguage);
        Label21->Caption = imes->RetIString("NOT_EMPTY_PAR", iLanguage);
        CheckBox3->Caption = "";//imes->RetIString("NO_PASSWORD_PAR", iLanguage);
        Label22->Caption = imes->RetIString("NO_PASSWORD_PAR", iLanguage);
        CheckBox14->Caption = "";//imes->RetIString("MASTER_LIST_PAR", iLanguage);
        Label23->Caption = imes->RetIString("MASTER_LIST_PAR", iLanguage);

	StringGrid1->Cells[1][0] = imes->RetIString("HOST_NAME_COL", iLanguage);
	StringGrid1->Cells[2][0] = imes->RetIString("PLAYERS_COL", iLanguage);
	StringGrid1->Cells[3][0] = imes->RetIString("PING_COL", iLanguage);
	StringGrid1->Cells[4][0] = imes->RetIString("MODE_COL", iLanguage);
	StringGrid1->Cells[5][0] = imes->RetIString("MAP_COL", iLanguage);

	StringGrid2->Cells[0][0] = imes->RetIString("PLAYER_COL", iLanguage);
	StringGrid2->Cells[1][0] = imes->RetIString("SCORE_COL", iLanguage);

	StringGrid3->Cells[0][0] = imes->RetIString("RULE_COL", iLanguage);
	StringGrid3->Cells[1][0] = imes->RetIString("VALUE_COL", iLanguage);

	StringGrid4->Cells[1][0] = imes->RetIString("HOST_NAME_COL", iLanguage);
	StringGrid4->Cells[2][0] = imes->RetIString("PLAYERS_COL", iLanguage);
	StringGrid4->Cells[3][0] = imes->RetIString("PING_COL", iLanguage);
	StringGrid4->Cells[4][0] = imes->RetIString("MODE_COL", iLanguage);
	StringGrid4->Cells[5][0] = imes->RetIString("MAP_COL", iLanguage);

	StringGrid5->Cells[0][0] = imes->RetIString("PLAYER_COL", iLanguage);
	StringGrid5->Cells[1][0] = imes->RetIString("SCORE_COL", iLanguage);

	StringGrid6->Cells[0][0] = imes->RetIString("RULE_COL", iLanguage);
	StringGrid6->Cells[1][0] = imes->RetIString("VALUE_COL", iLanguage);

	StringGrid7->Cells[1][0] = imes->RetIString("HOST_NAME_COL", iLanguage);
	StringGrid7->Cells[2][0] = imes->RetIString("PLAYERS_COL", iLanguage);
	StringGrid7->Cells[3][0] = imes->RetIString("PING_COL", iLanguage);
	StringGrid7->Cells[4][0] = imes->RetIString("MODE_COL", iLanguage);
	StringGrid7->Cells[5][0] = imes->RetIString("MAP_COL", iLanguage);

	StringGrid8->Cells[0][0] = imes->RetIString("PLAYER_COL", iLanguage);
	StringGrid8->Cells[1][0] = imes->RetIString("SCORE_COL", iLanguage);

	StringGrid9->Cells[0][0] = imes->RetIString("RULE_COL", iLanguage);
	StringGrid9->Cells[1][0] = imes->RetIString("VALUE_COL", iLanguage);

        Form1->StringGrid3->Cells[0][5] = AnsiString(imes->RetIString("WEBURL_RULE", iLanguage));
        Form1->StringGrid6->Cells[0][5] = AnsiString(imes->RetIString("WEBURL_RULE", iLanguage));
        Form1->StringGrid9->Cells[0][5] = AnsiString(imes->RetIString("WEBURL_RULE", iLanguage));

        Form1->StringGrid3->Cells[0][2] = AnsiString(imes->RetIString("MAPNAME_RULE", iLanguage));
        Form1->StringGrid6->Cells[0][2] = AnsiString(imes->RetIString("MAPNAME_RULE", iLanguage));
        Form1->StringGrid9->Cells[0][2] = AnsiString(imes->RetIString("MAPNAME_RULE", iLanguage));

        Form1->StringGrid3->Cells[0][6] = AnsiString(imes->RetIString("WORLDTIME_RULE", iLanguage));
        Form1->StringGrid6->Cells[0][6] = AnsiString(imes->RetIString("WORLDTIME_RULE", iLanguage));
        Form1->StringGrid9->Cells[0][6] = AnsiString(imes->RetIString("WORLDTIME_RULE", iLanguage));

        Form1->StringGrid3->Cells[0][4] = AnsiString(imes->RetIString("WEATHER_RULE", iLanguage));
        Form1->StringGrid6->Cells[0][4] = AnsiString(imes->RetIString("WEATHER_RULE", iLanguage));
        Form1->StringGrid9->Cells[0][4] = AnsiString(imes->RetIString("WEATHER_RULE", iLanguage));

        Form1->StringGrid3->Cells[0][3] = AnsiString(imes->RetIString("VERSION_RULE", iLanguage));
        Form1->StringGrid6->Cells[0][3] = AnsiString(imes->RetIString("VERSION_RULE", iLanguage));
        Form1->StringGrid9->Cells[0][3] = AnsiString(imes->RetIString("VERSION_RULE", iLanguage));

        Form1->StringGrid3->Cells[0][1] = AnsiString(imes->RetIString("LAGCOMP_RULE", iLanguage));
        Form1->StringGrid6->Cells[0][1] = AnsiString(imes->RetIString("LAGCOMP_RULE", iLanguage));
        Form1->StringGrid9->Cells[0][1] = AnsiString(imes->RetIString("LAGCOMP_RULE", iLanguage));

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
	Form2->Label2->Caption = Form1->imes->RetIString("SERVER_PASSWORD_PAR", Form1->iLanguage);
	Form2->Label3->Caption = Form1->imes->RetIString("RCON_PASSWORD_PAR", Form1->iLanguage);
	Form2->Label4->Caption = Form1->imes->RetIString("HOST_ADDR_PAR", Form1->iLanguage);
	Form2->Label5->Caption = Form1->imes->RetIString("PLAYERS_PAR", Form1->iLanguage);
	Form2->Label6->Caption = Form1->imes->RetIString("PING_PAR", Form1->iLanguage);
	Form2->Label7->Caption = Form1->imes->RetIString("MODE_PAR", Form1->iLanguage);
	Form2->Label8->Caption = Form1->imes->RetIString("MAP_PAR", Form1->iLanguage);


        Form4->Font->Charset = DEFAULT_CHARSET;
        Form4->Label1->Font->Charset = DEFAULT_CHARSET;
        Form4->Label3->Font->Charset = DEFAULT_CHARSET;
        Form4->Label5->Font->Charset = DEFAULT_CHARSET;
        Form4->Label7->Font->Charset = DEFAULT_CHARSET;

        if(AnsiString(Form1->iLanguage).AnsiCompare("es") == 0 ||
           AnsiString(Form1->iLanguage).AnsiCompare("pt") == 0)
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

        Form5->Caption = Form1->imes->RetIString("FORM5_CAPTION_TEXT", Form1->iLanguage);
        Form5->Label1->Caption = Form1->imes->RetIString("FORM5_NEW_SERVER_TEXT", Form1->iLanguage);
        Form5->Button1->Caption = Form1->imes->RetIString("OK_BUTTON", Form1->iLanguage);
        Form5->Button2->Caption = Form1->imes->RetIString("CANCEL_BUTTON", Form1->iLanguage);
}
//---------------------------------------------------------------------------


