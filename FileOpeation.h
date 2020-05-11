#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Definition.h"
#include <stdlib.h>
#include <stdio.h>
FILE* OpenFile(const TCHAR *filename,const TCHAR*mode);
size_t CloseFile(FILE* fp, const TCHAR* filename);
size_t CaculateOffset(Flag* index,size_t ID);
