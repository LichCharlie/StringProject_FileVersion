#pragma once
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <map>
#include "MyTCHAR.h"
#include "Definition.h"
using namespace std;
//为写字母统计设计，只要文件的写操作正确，读内容不会有任何问题


//字符统计函数，核心在于里面的数组Alphabat占128个size_t，数组size足够asicii码的长度，
//算英文字母的话可以直接按照索引对应，比如扫描到一个a，Alphabat['a']这个元素直接自增
//另外一个核心是第32行，要考虑字符串被修改的情况
//在碎片整理前每个字符串的真实长度不一定是表中的Strenlength，而是要用strlen来计算
void NewLetterStatistics();
