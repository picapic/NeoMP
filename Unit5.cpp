//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button1Click(TObject *Sender)
{
        char *ptr, *ptr_port;
        char file_data[204800], path[1024], addr[1024], ip[16], port[8];
        FILE *fd;
        int num, n, len, nport;
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

                if(fd > 0)
                {
                        memset(file_data, 0, sizeof(file_data));
                        len = fread(file_data, 1, sizeof(file_data), fd); //считываем файл со списком серверов
                        fclose(fd);
                        memset(addr, 0, sizeof(addr));
                        strncpy(addr, Edit1->Text.c_str(), sizeof(addr));
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

                        memcpy(file_data+len, &n, 4); //записываем длину адреса
                        len += 4;
                        memcpy(file_data+len, ip, n); //записываем сам адрес
                        len += n;
                        memcpy(file_data+len, &nport, 4); //записываем порт
                        len += 4;
                        wsprintf(addr, "(Retrieving info...) %s:%d", ip, nport);
                        n = strlen(addr);
                        memcpy(file_data+len, &n, 4); //записываем длину названия
                        len += 4;
                        memcpy(file_data+len, addr, n); //записываем само название
                        len += n+8; //добавляем 8 нулей в конец записи
                        ((int) (*((int *)(file_data+8))))++; //увеличиваем количество записей о серверах

                        fd = fopen(path, "wb");
                        fwrite(file_data, len, 1, fd);
                        fclose(fd);
                }
        }
        Form1->FillServerList(false);
        CreateThread(NULL, 0, ThreadPutServersInfo, (void *)Form1->StringGrid1, 0, &thread_servers_put);
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button2Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm5::FormShow(TObject *Sender)
{
        TClipboard *Clip = new TClipboard();

        if(Clip->HasFormat(CF_TEXT))
        Edit1->Text = Clip->AsText;

        delete Clip;

        Form5->Caption = Form1->imes->RetIString("FORM5_CAPTION_TEXT", Form1->iLanguage);
        Form5->Label1->Caption = Form1->imes->RetIString("FORM5_NEW_SERVER_TEXT", Form1->iLanguage);

        Form5->Button1->Caption = Form1->imes->RetIString("OK_BUTTON", Form1->iLanguage);
        Form5->Button2->Caption = Form1->imes->RetIString("CANCEL_BUTTON", Form1->iLanguage);
}
//---------------------------------------------------------------------------
