#pragma once
#include "MergeIndexList.h"

/*
并表函数
每次执行AddString,DeleteString,ModifyString,DiskSort函数之后,也就是所有写操作的函数之后执行这个MergeIndexList并表函数
保证相邻的碎片合并成一个碎片，并改表,改表操作结束后，已经保证了赋值g_uValidElemNum和 g_uFragileElemNum是完全正确的，然后
遍历表，i<g_uValidElemNum+g_uFragileElemNum;给每个表一个ID
*/
void MergeIndexList(Flag* pIndex)
{
	size_t ID = 0;
	//必须先算下需要遍历多少个元素，每个元素都要检查一遍
	size_t TotalElemNum = g_uValidElemNum + g_uFragileElemNum;
	//元素个数>0才循环
	if (TotalElemNum > 0)
	{
		for (size_t i = 1; i < TotalElemNum; i++)
		{
			//检查：如果有两块相邻的碎片空间，就要把它俩合并
			if (pIndex[i - 1].IsFragile && pIndex[i].IsFragile)
			{
				//先让前面的元素的长度加上后面元素的长度
				pIndex[i - 1].BufferSize += pIndex[i].BufferSize;
				//减少了一个碎片空间数量，只是全局变量的，不影响循环中的TotalElemNum
				g_uFragileElemNum--;
				//后面的元素前移
				for (size_t j = i; j < TotalElemNum-1; j++)
				{
					pIndex[j] = pIndex[j + 1];
				}
				if (i == TotalElemNum - 1)
				{
					//g_uFragileElemNum--;
					break;
				}
				//之前已经把元素合并了，但不确定相邻的后面是否还是碎片，重新从这个元素检索,如果还有，接着合并
				i--;
			}
		}
	}
	
	//每个表赋ID，不论是否是碎片
	for (size_t i = 0; i < g_uValidElemNum + g_uFragileElemNum; i++)
	{
		pIndex[i].ID = ID;
		ID++;
	}
}