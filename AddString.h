#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "MyTCHAR.h"
#include "Definition.h"
#include "GetString.h"
#include "FileOpeation.h"

//�ж��Ƿ��п����õ���Ƭ�ռ�
bool HasCapableFragile(Flag* IndexArray, size_t uSpaceRequired, size_t* pIndex);
//�����ַ���
size_t AddString(Flag* IndexArray);

void SetPhoneNum(long long* llpPhoneNum);
