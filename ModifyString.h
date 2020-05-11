#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "MyTCHAR.h"
#include "GetString.h"
#include "DeleteString.h"
#include "Definition.h"
/*
这个函数分两种情况
1.修改后的字符串长度小于等于之前的
2.修改后的字符串长度大于之前的
*/

//修改字符串函数
//首先，无法修改碎片，只能修改IsFragile为false的
//然后分两种情况讨论
//1.长度足够，2长度不够
void ModifyString(size_t ID);
