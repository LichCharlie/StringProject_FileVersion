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
//�жϵó��������Ƿ�Ϸ� ID�Ǳ��Ƚϵ����� Num�Ǳ�׼�����ID<NumΪ��
bool IdentifyValidID(size_t uID, size_t uNum);

//�������붼д��buf��Ȼ��������������
//�����������,�����ִ�е��������˵������϶��Ǹ����֣�Ȼ������������������
//������������Ƿ�Ϸ���Ҫ������ͬ�ĺ����ж�
size_t GetID(TCHAR* buf);

//����������
//buf�����飬size_t���û�������ַ�����������
//OptionFront  OptionBack��ǰ�߽�ͺ�߽�
bool Filter(TCHAR* buf, size_t uMaxDigit, size_t uOptionFront, size_t uOptionBack);

void SystemClsLoop();

//��Ϊswitch���ظ�����������������̫ǿ����SpecificOptions������װ���������Ǻ���ָ��->ɾ���޸Ĳ�ѯ
bool SpecificOptions(TCHAR* buf2, size_t* pStringID, TCHAR lo, TCHAR hi, size_t uMaxValue,FuctionName fnOperation);
