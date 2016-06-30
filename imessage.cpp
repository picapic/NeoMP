//------------------------imessage.cpp---------------------
//imessage parser
//Author: Bombo, 2013

#include"imessage.h"

#ifdef WIN32
void cp_to_utf8(char *out_text, const char *str, int from_cp);
void utf8_to_cp(char *out_text, const char *str, int to_cp);
void utf8_to_wc(char *out_text, const char *str);
#endif

#ifdef WIN32
#else
//thread function for file map update
static void *ThreadSetPtr(void *);
#endif

char *IMes::index_mas[];
char *IMes::ptr;
size_t IMes::len;
char *IMes::filename;
#ifdef WIN32
HANDLE IMes::hFile;
HANDLE IMes::hFileMap;
//mutex def
#else
int IMes::fd;
pthread_mutex_t IMes::ptr_mutex;
#endif

#ifdef WIN32
//thread
#else
//SIGIO handler
static void sig_handler(int nsig)
{
  pthread_t thread;
  pthread_attr_t attr;
  
  if(nsig == SIGIO)
  {
    //thread for non sleep in handler
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread, &attr, ThreadSetPtr, NULL);
    pthread_attr_destroy(&attr);
  }
}
//thread for file mapping update
static void *ThreadSetPtr(void *lpParam)
{
  IMes::UpdatePtr();
  pthread_exit(NULL);
}
#endif

IMes::IMes(char *in_filename)
{
  size_t i, j, mas_size;
#ifdef WIN32
  TCHAR w_file_name[256];
  int n;
#else
  struct stat st;
#endif

#ifdef WIN32
#else
  //mutex
  pthread_mutex_init(&ptr_mutex, NULL);
#endif

  ptr = NULL;
  len = 0;

#ifdef WIN32
  //log output
  fprintf(stderr, "file loading...\n");
  fprintf(stderr, "%s\n", in_filename);
  if(strlen(in_filename) == 0)
  {
    fprintf(stderr, "wrong file name\n");
    return;
  }

#else
  if(strlen(in_filename) == 0)
    return;
#endif
  filename = new char[strlen(in_filename)+1];
  memset(filename, 0, strlen(in_filename)+1);
#ifdef WIN32
  n = strlen(in_filename);
  strcpy(filename, in_filename);
#else
  strcpy(filename, in_filename);
#endif

#ifdef WIN32
//craete file map
  memset(w_file_name, 0, sizeof(w_file_name));
  for(int i = 0; i < (int)strlen(in_filename); ++i)
    w_file_name[i] = TCHAR(in_filename[i]);

#ifdef BORLAND
  hFile = CreateFile(in_filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
#else
  hFile = CreateFile((LPCWSTR)w_file_name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
#endif  
//  hFile = CreateFile((LPCWSTR)in_filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

  if(hFile == INVALID_HANDLE_VALUE)
  {
	  fprintf(stderr, "can not open file: %s\n", in_filename);
	  return;
  }

  //get size
  len = GetFileSize(hFile, NULL);

  hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
  if(hFileMap == INVALID_HANDLE_VALUE)
  {
    fprintf(stderr, "hMapFile is invalid\n");
    return;
  }
  ptr = (char *) MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, len);

  if(ptr == NULL)
  {
    fprintf(stderr, "ptr is NULL\n");
    return;
  }
  else
#else
  fd = open(filename, O_RDONLY);
  if(fd < 0)
  {
    perror("IMes(), open ");
    return;
  }
  fstat(fd, &st);
  len = st.st_size;
  ptr = (char *) mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
  if(ptr == MAP_FAILED)
  {
    perror("IMes(), mmap ");
    ptr = NULL;
  }
  else
#endif
  //если создан образ файла в памяти, заполняем массив индексов
//else
  {
    mas_size = sizeof(index_mas)/sizeof(index_mas[0]);
	//обнуляем массив индексов
	for(i = 0; i < mas_size; ++i)
		index_mas[i] = NULL;
	//заполняем массив индексов
    i = 0;
	j = 1;
	while((j < len)&&(i < mas_size))
	{
	  if((ptr[j-1] == ']')&&(ptr[j] == '\n'))
	  {
	    index_mas[i] = &(ptr[j-1]);
		i++;
	  }
	  j++;
	}
  }
  fprintf(stderr, "strings: %d\n", i);

#ifdef WIN32
#else
  signal(SIGIO, sig_handler);
  fcntl(fd, F_NOTIFY, DN_MODIFY|DN_ACCESS);
#endif
}

IMes::~IMes()
{
#ifdef WIN32
//delete file map
  if(ptr != NULL)
	UnmapViewOfFile(ptr);
  if(hFileMap != INVALID_HANDLE_VALUE)
	  CloseHandle(hFileMap);
  if(hFile != INVALID_HANDLE_VALUE)
	CloseHandle(hFile);
#else
  //enter CS
  pthread_mutex_lock(&ptr_mutex);
  fcntl(fd, F_NOTIFY, 0);
  munmap(ptr, len);
  //exit CS
  pthread_mutex_unlock(&ptr_mutex);
  
  //delete mutex
  pthread_mutex_destroy(&ptr_mutex);
  close(fd);
#endif
  delete [] filename;
}

void IMes::GetIString(char *out_text, char *in_name, char *in_language)
{
  char *pstr, *lbl1, *lbl2, *pname;
  char request[128];
  char buff[2048+1];
  char conv_buff[2048+1];
  size_t index; //индекс указателя на строку
  size_t mas_size;
  int req_len;
#ifdef WIN32
//convertion parameters
#else
  iconv_t conv;
  char *ptr_in, *ptr_out;
  size_t size_in, size_out, ret;
#endif

  if(out_text == NULL)
  {
    fprintf(stderr, "GetIString error: out_file is NULL\n");
    return;
  }
  if( (in_name == NULL)||(strlen(in_name) == 0) )
  {
    fprintf(stderr, "GetIString error: no string name\n");
    return;
  }
  if( (in_language == NULL)||(strlen(in_language) != 2) )
  {
    fprintf(stderr, "GetIString error: something wrong with language (NULL, etc.)\n");
    return;
  }

  out_text[0] = '\0';
#ifdef WIN32
//enter CS
#else
  //enter CS
  pthread_mutex_lock(&ptr_mutex);
#endif

  if(ptr == NULL) //no such file
  {
    fprintf(stderr, "GetIString error: ptr is NULL\n");
    //leave CS
#ifdef WIN32
//leaving CS
#else
    pthread_mutex_unlock(&ptr_mutex);
#endif
    return;
  }

  memset(request, 0, sizeof(request));
#ifdef WIN32
  sprintf_s(request, sizeof(request), "\n[%s]\n", in_name);
#else
  snprintf(request, sizeof(request), "\n[%s]\n", in_name);
#endif

//  pstr = strstr(ptr, request);
  req_len = strlen(in_name);
  index = 0;
  mas_size = sizeof(index_mas)/sizeof(index_mas[0]);
  pstr = NULL;
  while((index_mas[index] != NULL)&&(index < mas_size))
  {
    pname = index_mas[index];
	if(pname[-1] == in_name[req_len-1])
	  if(pname[-req_len-1] == '[')
 	    if(pname[-req_len] == in_name[0])
 	      if(strncmp(&pname[-req_len], in_name, req_len) == 0)
	  	  {
		    pstr = pname;
		    break;
		  }
	index++;
  }

  if(pstr == NULL) //no such string
  {
    fprintf(stderr, "GetIString error: no such string- %s", request);

#ifdef WIN32
//leave CS
#else
    pthread_mutex_unlock(&ptr_mutex);
#endif
    return;
  }

  lbl1 = strstr(pstr, "\n\n");
  if(lbl1 == NULL) //no end of string
  {
    fprintf(stderr, "GetIString error: no end of translated string\n");

#ifdef WIN32
//leave CS
#else
    pthread_mutex_unlock(&ptr_mutex);
#endif
    return;
  }

#ifdef WIN32
  sprintf_s(request, sizeof(request), "\n%s {", in_language);
#else
  snprintf(request, sizeof(request), "\n%s {", in_language);
#endif

  lbl2 = strstr(pstr, request); //language searching
  if(lbl2 == NULL) //no such language
  {
    fprintf(stderr, "GetIString error: no such language\n");

#ifdef WIN32
//leave CS
#else
    pthread_mutex_unlock(&ptr_mutex);
#endif
    return;
  }

  if(lbl1 - lbl2 < 0) //no translation
  {
    fprintf(stderr, "GetIString error: no translation of this string\n");
    //leave CS
#ifdef WIN32
#else
    pthread_mutex_unlock(&ptr_mutex);
#endif
    return;
  }

  lbl1 = strstr(lbl2, "};\n"); //searching the end of translation
  if(lbl1 == NULL)
  {
    fprintf(stderr, "GetIString error: no end of translation\n");
    //leave CS
#ifdef WIN32
#else
    pthread_mutex_unlock(&ptr_mutex);
#endif
    return;
  }

  memset(buff, 0, sizeof(buff));

  lbl2 = lbl2 + strlen(request); //jmp to begin of translation
  memcpy(buff, lbl2, (lbl1-lbl2>2048)?2048:(lbl1-lbl2)); //copy

#ifdef WIN32

//text convertion
  if( (strncmp(in_language, "ru", 2) == 0)||
      (strncmp(in_language, "sr", 2) == 0)||
      (strncmp(in_language, "bg", 2) == 0)||
      (strncmp(in_language, "uk", 2) == 0) )
//      (strncmp(in_language, "en", 2) == 0) )
    utf8_to_cp(conv_buff, buff, 1251);
  else if( (strncmp(in_language, "cs", 2) == 0)||
           (strncmp(in_language, "ro", 2) == 0)||
           (strncmp(in_language, "pl", 2) == 0) )
    utf8_to_cp(conv_buff, buff, 1250);
  else if(strncmp(in_language, "tr", 2) == 0)
    utf8_to_cp(conv_buff, buff, 1254);
  else
//    utf8_to_cp(conv_buff, buff, 1252);
    utf8_to_wc(conv_buff, buff);
#else
//  conv = iconv_open("UTF8", "UTF8");

  if( (strncmp(in_language, "ru", 2) == 0)||
      (strncmp(in_language, "sr", 2) == 0)||
      (strncmp(in_language, "bg", 2) == 0)||
      (strncmp(in_language, "uk", 2) == 0) )
//      (strncmp(in_language, "en", 2) == 0) )
    conv = iconv_open("CP1251", "UTF8");
  else if( (strncmp(in_language, "cs", 2) == 0)||
           (strncmp(in_language, "ro", 2) == 0)||
           (strncmp(in_language, "pl", 2) == 0) )
     conv = iconv_open("CP1250", "UTF8");
  else if(strncmp(in_language, "tr", 2) == 0)
     conv = iconv_open("CP1254", "UTF8");
  else 
     conv = iconv_open("CP1252", "UTF8");
					 
  if(conv == (iconv_t)(-1))
  {
     //leave CS
    pthread_mutex_unlock(&ptr_mutex);
    return;
  }

  memset(conv_buff, 0, sizeof(conv_buff));
  size_in = strlen(buff);
  ptr_in = buff;
  size_out = sizeof(conv_buff);
  ptr_out = conv_buff;
  ret = iconv(conv, &ptr_in, &size_in, &ptr_out, &size_out);
  iconv_close(conv);

  if(ret == (size_t)(-1))
  {
    perror("IMes(), iconv ");
    pthread_mutex_unlock(&ptr_mutex);
    return;
  }
#endif

    //leave CS
#ifdef WIN32
#else
  pthread_mutex_unlock(&ptr_mutex);
#endif
  
#ifdef WIN32
  strcpy_s(out_text, 2048, conv_buff);
#else
  strcpy(out_text, conv_buff);
#endif
//  fprintf(stderr, "%s\n", out_text); //debug
  return;
}

char *IMes::RetIString(char *in_name, char *in_language)
{
        static char szRetStr[2048];

        memset(szRetStr, 0, sizeof(szRetStr));
        GetIString(szRetStr, in_name, in_language);

        return szRetStr;
}

void IMes::UpdatePtr()
{
#ifdef WIN32
#else
  struct stat st;
  size_t i, j, mas_size;
#endif
  
    //leave CS
#ifdef WIN32
#else
  pthread_mutex_lock(&ptr_mutex);
#endif

#ifdef WIN32
//file map update
#else
  munmap(ptr, len);
  fstat(fd, &st);
  len = st.st_size;
  ptr = (char *) mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
  if(ptr == MAP_FAILED)
  {
    perror("IMes(), mmap ");
    ptr = NULL;
  }
  else
  {
    mas_size = sizeof(index_mas)/sizeof(index_mas[0]);
	//обнуляем массив индексов
	for(i = 0; i < mas_size; ++i)
		index_mas[i] = NULL;
	//заполняем массив индексов
    i = 0;
	j = 1;
	while((j < len)&&(i < mas_size))
	{
	  if((ptr[j-1] == ']')&&(ptr[j] == '\n'))
	  {
	    index_mas[i] = &(ptr[j-1]);
		i++;
		j++;
	  }
	  j++;
	}
  }
#endif

  //leave CS
#ifdef WIN32
#else
  pthread_mutex_unlock(&ptr_mutex);
#endif
}

//file open check
bool IMes::IsFileOpened(void)
{
        if(len == 0)
                return false;
        else
                return true;
}

#ifdef WIN32
void cp_to_utf8(char *out_text, const char *str, int from_cp)
{
	int result_u, result_c;

	result_u = MultiByteToWideChar(from_cp,0,str,-1,0,0);
	
	if (!result_u)
		return;

	wchar_t *ures = new wchar_t[result_u];

	if(!MultiByteToWideChar(from_cp,0,str,-1,ures,result_u))
	{
		delete[] ures;
		return;
	}

	result_c = WideCharToMultiByte(CP_UTF8,0,ures,-1,0,0,0,0);

	if(!result_c)
	{
		delete [] ures;
		return;
	}

	char *cres = new char[result_c];

	if(!WideCharToMultiByte(CP_UTF8,0,ures,-1,cres,result_c,0,0))
	{
		delete[] cres;
		return;
	}
	delete[] ures;

	strcpy_s(out_text, 2048, cres);
	delete[] cres;
	return;
}

void utf8_to_cp(char *out_text, const char *str, int to_cp)
{
	int result_u, result_c;

	result_u = MultiByteToWideChar(CP_UTF8,0,str,-1,0,0);
	
	if (!result_u)
		return;

	wchar_t *ures = new wchar_t[result_u];

	if(!MultiByteToWideChar(CP_UTF8,0,str,-1,ures,result_u))
	{
		delete[] ures;
		return;
	}

	result_c = WideCharToMultiByte(to_cp,0,ures,-1,0,0,0, 0);

	if(!result_c)
	{
		delete [] ures;
		return;
	}

	char *cres = new char[result_c];

	if(!WideCharToMultiByte(to_cp,0,ures,-1,cres,result_c,0,0))
	{
		delete[] cres;
		return;
	}
	delete[] ures;
	strcpy_s(out_text, 2048, cres);
	delete[] cres;
	return;
}

void utf8_to_wc(char *out_text, const char *str)
{
	int result_u, i;
        char res_str[8];

	result_u = MultiByteToWideChar(CP_UTF8,0,str,-1,0,0);

	if (!result_u)
		return;

	wchar_t *ures = new wchar_t[result_u];

	if(!MultiByteToWideChar(CP_UTF8,0,str,-1,ures,result_u))
	{
		delete[] ures;
		return;
	}

        memset(out_text, 0, 2048);
        for(i = 0; i < result_u; ++i)
        {
                memset(res_str, 0, sizeof(res_str));
                wsprintf(res_str, "%c", (char)((WORD *)ures)[i]);
                strcat((char *)out_text, res_str);
        }
	delete[] ures;
	return;
}

#endif

