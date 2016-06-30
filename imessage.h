//----------------------imessage.h-----------------
//imessage parser
//Author: Bombo, 2013

#ifndef IMESSAGEH
#define IMESSAGEH

#define BORLAND

#ifdef BORLAND
#define WIN32
#endif

#include<stdio.h>
#include<string.h>
#ifdef WIN32
#include<windows.h>
#else
#include<fcntl.h>
#include<iconv.h>
#include<pthread.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<unistd.h>
#include<signal.h>
#endif

#ifdef BORLAND
#define sprintf_s snprintf
#define strcpy_s(x,y,z) strncpy(x,z,y)
#endif 

class IMes {
  static char *index_mas[102400];
  static char *ptr;
  static size_t len;
  static char *filename;
#ifdef WIN32
  static HANDLE hFile;
  static HANDLE hFileMap;
#else
  static int fd;
  static pthread_mutex_t ptr_mutex;
#endif
public:
  IMes(char *in_filename);
  ~IMes();
  
//----------------------------------------------------------------------------//
//out_text    - result string ( >= 2048 bytes)                                //
//in_name     - request string name                                           //
//in_language - language of translation                                       //
//                                                                            //
//If there is no such string - empty string is returning.                     //
//out_text must be allocated in memory before calling this                    //
//function.                                                                   //
//----------------------------------------------------------------------------//
  void GetIString(char *out_text, char *in_name, char *in_language);

//----------------------------------------------------------------------------//
//in_name       - request string name                                         //
//in_language   - language of translation                                     //
//----------------------------------------------------------------------------//
  char *RetIString(char *in_name, char *in_language);

//----------------------------------------------------------------------------//
//SIGIO handler                                                               //
//----------------------------------------------------------------------------//
  static void UpdatePtr(void);

//----------------------------------------------------------------------------//
//File open check                                                             //
//----------------------------------------------------------------------------//
  bool IsFileOpened(void);
};
#endif
