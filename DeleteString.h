#pragma once
#include "Definition.h"
#include "MyTCHAR.h"
#include "Menu.h"
#include <math.h>
//删除字符串函数
//不直接操作字符串，直接改表，此管理此id的字符串的结构体元素做更改。
//这样内存显示，字符统计的时候因为IsFragile=g_INDEX，会表明这段内存是不可用的，不会去对这段进行读操作
//只有碎片整理后，才能把这段内存删除并把后面的字符串依次前移

void DeleteString(size_t uID);
