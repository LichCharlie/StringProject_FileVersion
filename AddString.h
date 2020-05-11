#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "MyTCHAR.h"
#include "Definition.h"
#include "GetString.h"
#include "FileOpeation.h"

//判断是否有可利用的碎片空间
bool HasCapableFragile(Flag* IndexArray, size_t uSpaceRequired, size_t* pIndex);
//增加字符串
size_t AddString(Flag* IndexArray);

void SetPhoneNum(long long* llpPhoneNum);
