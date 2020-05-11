#pragma once
#include "ModifyString.h"
/*
这个函数分两种情况
1.修改后的字符串长度等于之前的
2.修改后的字符串长度大于之前的
3.修改后的字符串长度等于之前的
*/
//修改字符串函数
//首先，无法修改碎片，只能修改IsFragile为false的
//然后分三种情况讨论
//1.长度恰好等于
//2原来的内存足够  
//3.内存不够
void ModifyString(size_t ID)
{
	//如果是碎片，不可修改！
	if (g_INDEX[ID].IsFragile)
	{
		TPUTS(TEXT("You can't modify a fragment.\n"),stdout);
	}
	//不是碎片，分三种情况
	else
	{
		//先把需要写出的字符串写入缓冲区,提前得出需要多大的内存
		TPUTS(TEXT("Please input the new string.\n"), stdout);
		TCHAR buf[STRING_MAX_LENTH] = { 0 };
		long long llPhoneNumber = 0;
		GetString(buf, STRING_MAX_LENTH);
		SetPhoneNum(&llPhoneNumber);
		size_t uModifyStringLength = (sizeof(TCHAR)) * ((TSTRLEN(buf)) + 1);
		printf("uModifyStringLength=%d\n", uModifyStringLength);
		//如果和需要修改的字符串长度相等，只需要拷贝,全局变量不需要变动
		if (uModifyStringLength == g_INDEX[ID].BufferSize-sizeof(long long))
		{
			TCHAR buffer[STRING_MAX_LENTH] = { 0 };
			fseek(fp, g_INDEX[ID].FlagOffset, SEEK_SET);
			fwrite(buf, uModifyStringLength, 1, fp);
			fwrite(&llPhoneNumber, sizeof(long long), 1, fp);
			rewind(fp);
			TPUTS(TEXT("Modify Succeed.\n"), stdout);
		}
		//新字符串过长，无法装下，原视为删除，在内存最后增加
		else if (uModifyStringLength > g_INDEX[ID].BufferSize - sizeof(long long))
		{
			size_t offset = 0;
			//这里删除g_INDEX(ID)，全局变量碎片数增加1，有效字符串数量减1，但总数还是不变的
			DeleteString(ID);
			//算出字符串被粘贴地址 相对于 给定内存g_szBuf的偏移 offset
			for (size_t i = 0; i < g_uValidElemNum + g_uFragileElemNum; i++)
			{
				offset += g_INDEX[i].BufferSize;
			}
			//内存拷贝完毕
			fseek(fp, offset, SEEK_SET);
			fwrite(buf, uModifyStringLength, 1, fp);
			fwrite(&llPhoneNumber, sizeof(long long), 1, fp);
			rewind(fp);
			//填充表
			//不是碎片
			g_INDEX[g_uValidElemNum + g_uFragileElemNum].IsFragile = 0;
			//字符串起始地址
			g_INDEX[g_uValidElemNum + g_uFragileElemNum].FlagOffset = offset;
			//字符串长度
			g_INDEX[g_uValidElemNum + g_uFragileElemNum].StringLength = uModifyStringLength;
			g_INDEX[g_uValidElemNum + g_uFragileElemNum].BufferSize = uModifyStringLength + sizeof(long long);
			//有效字符串数目+1
			g_uValidElemNum++;
			TPUTS(TEXT("Modify Succeed.\n"), stdout);
		}

		//ModifyStringLength < g_INDEX[ID].StringLength
		else
		{
			//先改内存
			fseek(fp, g_INDEX[ID].FlagOffset, SEEK_SET);
			fwrite(buf, uModifyStringLength, 1, fp);
			fwrite(&llPhoneNumber, sizeof(long long), 1, fp);
			rewind(fp);
			//计算新产生的碎片大小
			size_t NewFragileLength = g_INDEX[ID].BufferSize - uModifyStringLength- sizeof(long long);
			//再改索引表中遇到的第一个满足条件的元素，ID不用改，最后统一整理,碎片化标志改为false，长度改为ModifyStringLength
			g_INDEX[ID].IsFragile = 0;
			g_INDEX[ID].StringLength = uModifyStringLength;
			g_INDEX[ID].BufferSize = uModifyStringLength + sizeof(long long);

			//后面的表元素后移，为新增的碎片做准备
			for (size_t i = g_uValidElemNum + g_uFragileElemNum; i > ID; i--)
			{
				g_INDEX[i] = g_INDEX[i - 1];
			}
			//再修改最新的表元素，ID不重要，因为遍历以 是不是碎片为标准，
			//pBufferBegin是前一个元素保存的指针+前一个元素的长度
			g_INDEX[ID + 1].FlagOffset = g_INDEX[ID].FlagOffset + g_INDEX[ID].BufferSize;
			//碎片标志为真
			g_INDEX[ID + 1].IsFragile = 1;
			//长度为NewFragileLength
			g_INDEX[ID + 1].StringLength = NewFragileLength;
			g_INDEX[ID + 1].BufferSize = NewFragileLength;
			//碎片元素数目+1,有效元素数量保持不变
			g_uFragileElemNum++;
			TPUTS(TEXT("Modify Succeed.\n"), stdout);
		}
	}
}

