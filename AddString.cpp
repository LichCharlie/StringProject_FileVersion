
#include "AddString.h"

//判断是否有可利用的碎片空间，如果有返回true
bool HasCapableFragile(Flag* IndexArray, size_t uSpaceRequired, size_t* pIndex)
{
	size_t i = 0;
	//遍历整个内存索引表
	for (; i < g_uValidElemNum + g_uFragileElemNum; i++)
	{
		//如果有内存段的长度能够容纳SpaceRequired，说明可以存储
		if (IndexArray[i].IsFragile)
		{
			if (IndexArray[i].BufferSize >= uSpaceRequired)
			{
				//传出最近并且符合要求的下标
				*pIndex = i;
				return true;
			}
		}
	}
	//如果没有，传出的下标为最新元素的下标 g_uValidElemNum + g_uFragileElemNum
	*pIndex = i;
	return false;
}

size_t AddString(Flag* IndexArray)
{
	size_t uIndex = 0;
	TCHAR buf[STRING_MAX_LENTH];
	long long llPhoneNum = 0;
	GetString(buf, STRING_MAX_LENTH);
	long long  *pllPhoneNum = &llPhoneNum;
	SetPhoneNum(pllPhoneNum);
	
	//算出需要填充字符串的长度
	size_t uNewStringLength = (sizeof(TCHAR)) * (TSTRLEN(buf)) + (sizeof(TCHARSIGN('\0')));
	//TPRINTF(TEXT("NewStringLength=%d\n"), NewStringLength);
	size_t uPhoneNumberLength = sizeof(long long);
	//有可填充的碎片 
	 
	if (HasCapableFragile(IndexArray, uNewStringLength+ uPhoneNumberLength, &uIndex))
	{
		//执行到这里的时候，g_INDEX已经被赋值为一个合理的内存块ID了
		//修改的长度与之前长度相同的情况
		if (IndexArray[uIndex].BufferSize == uNewStringLength+ uPhoneNumberLength)
		{   //先改内存
			fseek(fp, IndexArray[uIndex].FlagOffset, SEEK_SET);
			fwrite(buf, uNewStringLength, 1, fp);
			fwrite(pllPhoneNum, uPhoneNumberLength, 1, fp);
			rewind(fp);
			//再改索引表，表中ID不在这个函数里修改，只需要把它的碎片化标志改为false
			IndexArray[uIndex].IsFragile = 0;
			//这里全局变量需要变化，有效字符串个数+1,碎片字符串个数-1(因为新增了一个字符串，这个字符串完完整整的
			//占据了寻找到的这个空间,所以这个碎片消失了)
			g_uValidElemNum++;
			g_uFragileElemNum--;
		}

		//添加的长度比之前长度短的情况
		else
		{  //先改内存
			fseek(fp, IndexArray[uIndex].FlagOffset, SEEK_SET);
			fwrite(buf, uNewStringLength, 1, fp);
			fwrite(pllPhoneNum, uPhoneNumberLength, 1, fp);
			rewind(fp);
			//TSTRCPY(IndexArray[uIndex].pBufferBegin, buf);
			//先计算出新产生的碎片长度，为赋值给下个元素做准备（因为必然产生碎片，偏移表也就必然更改，下一个元素的
			//长度一定是这个碎片长度
			size_t NewFragileLength = IndexArray[uIndex].BufferSize - (uNewStringLength+ uPhoneNumberLength);
			//再改索引表中遇到的第一个满足条件的元素，ID不用改,在其他函数里统一处理，碎片化标志改为false，长度改为NewStringLength
			IndexArray[uIndex].IsFragile = false;
			IndexArray[uIndex].StringLength = uNewStringLength;
			IndexArray[uIndex].BufferSize = uNewStringLength+ uPhoneNumberLength;
			//后面的表元素后移，为新增的碎片做准备
			for (size_t i = g_uValidElemNum + g_uFragileElemNum; i > uIndex; i--)
			{
				IndexArray[i] = IndexArray[i - 1];
			}
			//再修改最新的表元素，ID不重要，在其他函数统一处理
			//pBufferBegin是前一个元素保存的指针+前一个元素的长度
			IndexArray[uIndex + 1].FlagOffset = IndexArray[uIndex].FlagOffset + IndexArray[uIndex].BufferSize;
			//碎片标志为真
			IndexArray[uIndex + 1].IsFragile = 1;
			//长度为保存的指针算strlen
			IndexArray[uIndex + 1].StringLength = NewFragileLength;
			IndexArray[uIndex + 1].BufferSize = NewFragileLength;
			//有效元素数目+1,碎片元素数量保持不变（+1是因为把一个内存分成了两块，一块成了有效元素，另一块还是碎片）
			g_uValidElemNum++;
		}
	}

	//没有可以填充的碎片位置,就在最末尾加。ID就是g_uValidElemNum+g_uFragileElemNum
	else
	{
		//算偏移
		size_t uOffset = 0;
		for (size_t i = 0; i < g_uValidElemNum + g_uFragileElemNum; i++)
		{
			uOffset += IndexArray[i].BufferSize;
		}
		//新增加的必然不为碎片
		IndexArray[g_uValidElemNum + g_uFragileElemNum].IsFragile = 0;
		//内存的起始地址
		IndexArray[g_uValidElemNum + g_uFragileElemNum].FlagOffset = uOffset;
		//把字符串拷贝进去
		fseek(fp, uOffset, SEEK_SET);
		fwrite(buf, uNewStringLength, 1, fp);
		fwrite(pllPhoneNum, uPhoneNumberLength, 1, fp);
		rewind(fp);
		//长度就是字符串长度
		IndexArray[g_uValidElemNum + g_uFragileElemNum].StringLength = uNewStringLength;
		IndexArray[g_uValidElemNum + g_uFragileElemNum].BufferSize = uNewStringLength+ uPhoneNumberLength;
		//表中索引位置
		uIndex = g_uValidElemNum + g_uFragileElemNum;
		//增加了一个有效元素
		g_uValidElemNum++;
		TPRINTF(TEXT("StringLength=%d\n"), uNewStringLength);
		TPRINTF(TEXT("BufferSize=%d\n"), uNewStringLength + uPhoneNumberLength);
	}
	return uIndex;
}

void SetPhoneNum(long long* llpPhoneNum)
{
	TPRINTF(TEXT("Pls input the phone number.\n"));
	fscanf(stdin,"%lld", llpPhoneNum);
	getchar();
}