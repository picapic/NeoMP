//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ActnCtrls.hpp>
#include <ActnMan.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ActnMenus.hpp>
#include <ComCtrls.hpp>
//#include <XPStyleActnCtrls.hpp>
#include "perfgrap.h"
#include <Graphics.hpp>
#include <Grids.hpp>
#include <vcl\Clipbrd.hpp>
#include <stdio.h>
#include <winsock.h>
#include <dirent.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <string.h>
#include "PERFGRAP.h"
#include <iostream>
#include "PERFGRAP.h"
#include "sqlite3.h"
#include "privet.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include"imessage.h"

//---------------------------------------------------------------------------
#define SYMBOLIC_LINK_FLAG_DIRECTORY            (0x1)
#define VALID_SYMBOLIC_LINK_FLAGS  SYMBOLIC_LINK_FLAG_DIRECTORY // & whatever other flags we think of!

void killProcessByName(const char *filename)
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof (pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
        if (strcmp(pEntry.szExeFile, filename) == 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                                          (DWORD) pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}

typedef BOOLEAN (APIENTRY *LPFN_CSL)(LPCTSTR, LPCTSTR, DWORD);

LPFN_CSL lpCreateSymbolicLink = (LPFN_CSL) GetProcAddress(GetModuleHandle(TEXT("kernel32")),
    #ifdef UNICODE
    "CreateSymbolicLinkW"
    #else
    "CreateSymbolicLinkA"
    #endif
);

class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *N7;
        TMenuItem *N8;
        TMenuItem *N9;
        TMenuItem *N10;
        TMenuItem *N11;
        TMenuItem *N12;
        TMenuItem *N13;
        TMenuItem *N14;
        TMenuItem *N15;
        TMenuItem *N16;
        TMenuItem *N17;
        TMenuItem *N18;
        TMenuItem *N19;
        TMenuItem *N20;
        TMenuItem *Wiki1;
        TMenuItem *N21;
        TMenuItem *FiltrServerInfo1;
        TMenuItem *StatusBar1;
        TMenuItem *SAMPcom1;
        TMenuItem *N22;
        TMenuItem *About1;
	TMenuItem *StatusBar2;
	TTabControl *TabControl1;
	TPanel *Panel1;
	TImage *Image1;
	TStringGrid *StringGrid1;
	TStringGrid *StringGrid2;
	TStringGrid *StringGrid3;
	TPanel *Panel3;
	TStringGrid *StringGrid4;
	TStringGrid *StringGrid5;
	TStringGrid *StringGrid6;
	TPanel *Panel4;
	TStringGrid *StringGrid7;
	TStringGrid *StringGrid8;
	TStringGrid *StringGrid9;
	TImage *Image2;
	TImage *Image3;
	TImage *Image4;
	TImage *Image5;
	TImage *Image6;
	TImage *Image7;
	TImage *Image8;
	TImage *Image9;
	TImage *Image10;
	TImage *Image11;
	TImage *Image12;
	TImage *Image13;
	TImage *Image14;
	TImage *Image15;
	TImage *Image16;
	TImage *Image17;
	TImage *Image18;
	TImage *Image19;
	TImage *Image20;
	TImage *Image21;
	TImage *Image22;
	TImage *Image23;
	TImage *Image24;
	TImage *Image25;
	TImage *Image26;
	TImage *Image27;
	TImage *Image28;
	TImage *Image29;
	TImage *Image30;
	TLabel *Label1;
	TEdit *Edit1;
	TImage *Image31;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TPerformanceGraph *PerformanceGraph1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *Edit2;
	TEdit *Edit3;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
        TImage *Image32;
        TImage *Image33;
        TImage *Image34;
        TImage *Image35;
        TImage *Image36;
        TImage *Image37;
        TImage *Image38;
        TImage *Image39;
        TImage *Image40;
        TControlBar *ControlBar1;
        TLabel *Label18;
        TMenuItem *Extraoptions1;
        TEdit *Edit4;
        TLabel *Label19;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox8;
        TCheckBox *CheckBox9;
        TCheckBox *CheckBox10;
        TCheckBox *CheckBox11;
        TCheckBox *CheckBox12;
        TCheckBox *CheckBox13;
        TCheckBox *CheckBox14;
        TLabel *Label20;
        TLabel *Label21;
        TLabel *Label22;
        TLabel *Label23;
        void __fastcall N5Click(TObject *Sender);
	void __fastcall FiltrServerInfo1Click(TObject *Sender);
	void __fastcall StatusBar2Click(TObject *Sender);
	void __fastcall TabControl1Change(TObject *Sender);
	void __fastcall Image1MouseLeave(TObject *Sender);
	void __fastcall Image1MouseEnter(TObject *Sender);
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image4MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image4MouseEnter(TObject *Sender);
	void __fastcall Image4MouseLeave(TObject *Sender);
	void __fastcall Image4MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image7MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image7MouseEnter(TObject *Sender);
	void __fastcall Image7MouseLeave(TObject *Sender);
	void __fastcall Image7MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall Image11MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image11MouseEnter(TObject *Sender);
	void __fastcall Image11MouseLeave(TObject *Sender);
	void __fastcall Image11MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image14MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image14MouseEnter(TObject *Sender);
	void __fastcall Image14MouseLeave(TObject *Sender);
	void __fastcall Image14MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image17MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image17MouseEnter(TObject *Sender);
	void __fastcall Image17MouseLeave(TObject *Sender);
	void __fastcall Image17MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image20MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image20MouseEnter(TObject *Sender);
	void __fastcall Image20MouseLeave(TObject *Sender);
	void __fastcall Image20MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image23MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image23MouseEnter(TObject *Sender);
	void __fastcall Image23MouseLeave(TObject *Sender);
	void __fastcall Image23MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image26MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image26MouseEnter(TObject *Sender);
	void __fastcall Image26MouseLeave(TObject *Sender);
	void __fastcall Image26MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image29MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image29MouseEnter(TObject *Sender);
	void __fastcall Image29MouseLeave(TObject *Sender);
	void __fastcall Image29MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormCreate(TObject *Sender);
        void __fastcall Image31Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormCanResize(TObject *Sender, int &NewWidth,
          int &NewHeight, bool &Resize);
        void __fastcall Image21Click(TObject *Sender);
        void __fastcall Image24Click(TObject *Sender);
        void __fastcall N11Click(TObject *Sender);
        void __fastcall N20Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall StringGrid1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall StringGrid1DblClick(TObject *Sender);
        void __fastcall Image30Click(TObject *Sender);
        void __fastcall Image27Click(TObject *Sender);
        void __fastcall StringGrid1DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall About1Click(TObject *Sender);
        void __fastcall Image5Click(TObject *Sender);
        void __fastcall StringGrid2DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall Image18Click(TObject *Sender);
        void __fastcall Image12Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall Edit2Change(TObject *Sender);
        void __fastcall Image15Click(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall Extraoptions1Click(TObject *Sender);
        void __fastcall Image8Click(TObject *Sender);
        void __fastcall Image2Click(TObject *Sender);
        void __fastcall Label17Click(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall Wiki1Click(TObject *Sender);
        void __fastcall SAMPcom1Click(TObject *Sender);
private:	// User declarations
        int gNewWidth;
        int gNewHeight;
        int gOldWidth;
        int gOldHeight;
        bool fExtraOptions;
        int ExtraHeight;

        sqlite3 *conn;
        int rc;
        SOCKET servers_s;
        SOCKET server_s;
        SOCKET internets_s;
        SOCKET internet_s;
        SOCKET hosteds_s;
        SOCKET hosted_s;
        unsigned long thread_servers_lists;
        unsigned long thread_hosteds_lists;
        unsigned long thread_servers_put;
        unsigned long thread_server_put;
        unsigned long thread_servers_get;
        unsigned long thread_server_get;
        unsigned long thread_internets_put;
        unsigned long thread_internet_put;
        unsigned long thread_internets_get;
        unsigned long thread_internets_get1;
        unsigned long thread_internets_get2;
        unsigned long thread_internet_get;
        unsigned long thread_hosteds_put;
        unsigned long thread_hosted_put;
        unsigned long thread_hosteds_get;
        unsigned long thread_hosted_get;
        unsigned long thread_start_program;
        HANDLE hServersLists;
        HANDLE hHostedsLists;
        HANDLE hServersPut;
        HANDLE hServerPut;
        HANDLE hServersGet;
        HANDLE hServerGet;
        HANDLE hInternetsPut;
        HANDLE hInternetPut;
        HANDLE hInternetsGet;
        HANDLE hInternetsGet1;
        HANDLE hInternetsGet2;
        HANDLE hInternetGet;
        HANDLE hHostedsPut;
        HANDLE hHostedPut;
        HANDLE hHostedsGet;
        HANDLE hHostedGet;
        HANDLE hStartProgram;

        int SleepInterval;
public:		// User declarations
        IMes *imes;
        char iLanguage[3];
        unsigned long close_time_stamp;
        TObject *AllText[100];

        void __fastcall ChangeLanguage(void);
        __fastcall TForm1(TComponent* Owner);
        void __fastcall FillServerList(bool);
        void __fastcall FilterServerList(TStringGrid *MainTable, AnsiString filter);
        int __fastcall GetCol(char const *colname, char const *tabname, int row, char *result);
        void __fastcall SetServerProperties(TObject *Sender, int row, bool update_players);
        friend unsigned long __stdcall ThreadGetServersLists(void *Sender);
        friend unsigned long __stdcall ThreadPutServersInfo(void *Sender);
        friend unsigned long __stdcall ThreadGetServersInfo(void *Sender);
        friend unsigned long __stdcall ThreadPutServerInfo(void *Prm);
        friend unsigned long __stdcall ThreadGetServerInfo(void *Prm);
        friend unsigned long __stdcall ThreadStartProgram(void *);
};

struct ThreadParameters {
        TStringGrid *Sender;
        int Row;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
