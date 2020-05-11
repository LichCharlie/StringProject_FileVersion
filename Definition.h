#pragma once
#include "MyTCHAR.h"
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define STRING_MAX_LENTH 100
extern const TCHAR* FILENAME;
extern const TCHAR* INDEXFILENAME;
extern FILE* fp;
extern FILE* fpIndex;
struct Flag
{
	size_t ID;
	size_t FlagOffset;
	size_t StringLength;
	size_t BufferSize;
	size_t IsFragile=0;
};
extern size_t g_uValidElemNum;
extern size_t g_uFragileElemNum;
extern struct Flag;
//extern TCHAR g_szBuf[1024 * 1024];
//字符串属性表数组，就是个结构体数组
extern Flag *g_INDEX;