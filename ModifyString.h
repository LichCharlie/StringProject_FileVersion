#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "MyTCHAR.h"
#include "GetString.h"
#include "DeleteString.h"
#include "Definition.h"
/*
����������������
1.�޸ĺ���ַ�������С�ڵ���֮ǰ��
2.�޸ĺ���ַ������ȴ���֮ǰ��
*/

//�޸��ַ�������
//���ȣ��޷��޸���Ƭ��ֻ���޸�IsFragileΪfalse��
//Ȼ��������������
//1.�����㹻��2���Ȳ���
void ModifyString(size_t ID);
