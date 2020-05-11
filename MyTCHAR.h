#pragma once
#include <stdlib.h>
//#undef UNICODE
#ifdef UNICODE
#define _main wmain
#define TCHARSIGN(x) L##x
#define TEXT(x) L##x
#define TCHAR wchar_t
#define TSTRCPY wcscpy
#define TPUTS fputws
#define TSTRLEN wcslen
#define TPRINTF wprintf
#define TFGETS fgetws
#define TGETCHAR getwchar
#define TSTRCMP wcscmp
#define TSTRSTR wcsstr
#define TFOPEN _wfopen
#define TFCLOSE fclose
#define TLTO _ltow
#else
#define _main main
#define TCHARSIGN(x) x
#define TEXT(x) x
#define TCHAR char
#define TSTRCPY strcpy
#define TPUTS fputs
#define TSTRLEN strlen
#define TPRINTF printf
#define TFGETS fgets
#define TGETCHAR getchar
#define TSTRCMP strcmp
#define TSTRSTR strstr
#define TFOPEN fopen
#define TFCLOSE fclose
#define TLTO _ltoa
#endif