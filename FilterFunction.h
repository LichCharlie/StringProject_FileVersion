#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "MyTCHAR.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Menu.h"
#include "DeleteString.h"
#include "GetString.h"
typedef void(*FuctionName)(size_t);
size_t IdentifyOption();
//判断得出的数字是否合法 ID是被比较的数字 Num是标准，如果ID<Num为真
bool IdentifyValidID(size_t uID, size_t uNum);

//所有输入都写入buf，然后算出输入的数字
//根据设计流程,如果能执行到这个函数说明输入肯定是个数字，然后算出并返回这个数字
//不过这个数字是否合法需要其他不同的函数判断
size_t GetID(TCHAR* buf);

//过滤器函数
//buf是数组，size_t是用户输入的字符串长度上限
//OptionFront  OptionBack是前边界和后边界
bool Filter(TCHAR* buf, size_t uMaxDigit, size_t uOptionFront, size_t uOptionBack);

void SystemClsLoop();

//因为switch内重复代码冗余而且耦合性太强，做SpecificOptions函数封装，最后参数是函数指针->删除修改查询
bool SpecificOptions(TCHAR* buf2, size_t* pStringID, TCHAR lo, TCHAR hi, size_t uMaxValue,FuctionName fnOperation);
