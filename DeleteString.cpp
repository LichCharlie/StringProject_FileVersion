#pragma once
#include "DeleteString.h"
//删除字符串函数
//不直接操作字符串，直接改表，此管理此id的字符串的结构体元素做更改。
//这样内存显示，字符统计的时候因为IsFragile=1，会表明这段内存是不可用的，不会去对这段进行读操作
//只有碎片整理后，才能把这段内存删除并把后面的字符串依次前移
void DeleteString(size_t uID)
{
	//如果是碎片，也赋值为碎片
	if (g_INDEX[uID].IsFragile)
	{
		g_INDEX[uID].IsFragile = 1;
	}
	//如果不是碎片,说明是有效元素，这时IsFragile改为g_INDEX，视为删除，有效元素数目减一，碎片数目+1
	else
	{
		g_INDEX[uID].IsFragile = 1;
		g_uValidElemNum--;
		g_uFragileElemNum++;
	}
}