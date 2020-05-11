#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Definition.h"
#include "MyTCHAR.h"
#include "FilterFunction.h"

void SearchOption(size_t uOption);
bool IDExist(size_t* pID, TCHAR* buf);
bool StringExist(TCHAR* buf, size_t* pIDIndex, size_t* pStringNum);
bool PhoneNumExist(TCHAR* buf, size_t* pIDIndex, size_t* pStringNum);
void SearchByID();
void SearchAccurateString();
void SearchByString();
void SearchByPhoneNum();
