#pragma once
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <map>
#include "MyTCHAR.h"
#include "Definition.h"
using namespace std;
//Ϊд��ĸͳ����ƣ�ֻҪ�ļ���д������ȷ�������ݲ������κ�����


//�ַ�ͳ�ƺ����������������������Alphabatռ128��size_t������size�㹻asicii��ĳ��ȣ�
//��Ӣ����ĸ�Ļ�����ֱ�Ӱ���������Ӧ������ɨ�赽һ��a��Alphabat['a']���Ԫ��ֱ������
//����һ�������ǵ�32�У�Ҫ�����ַ������޸ĵ����
//����Ƭ����ǰÿ���ַ�������ʵ���Ȳ�һ���Ǳ��е�Strenlength������Ҫ��strlen������
void NewLetterStatistics();
