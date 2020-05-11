
#include "DiskFragment.h"
/*
之前已经保证表和全局变量都是正确的，现在只遍历每个表元素
如果它是碎片，把它右侧的所有内存向左移，并把它覆盖，同时碎片数目-1,
而最后一个表元素单独处理，因为它后面没有元素可搬运了
*/

//挪表
void DiskSortMerge()
{
	Flag* TempStruct = ReadFromG_INDEX();
	size_t uTotalElemNum = g_uFragileElemNum + g_uValidElemNum;
	for (int i = 0; i < uTotalElemNum; i++)
	{
		if (TempStruct[i].IsFragile == 1)
		{
			const size_t uCurrentMoveBackOffset = TempStruct[i].BufferSize;
			for (int j = i; j < uTotalElemNum; j++)
			{
				TempStruct[j].FlagOffset -= uCurrentMoveBackOffset;
			}
		}
	}
	
	for (int i = 0, k = 0; i < uTotalElemNum; i++)
	{
		if (TempStruct[i].IsFragile == 0)
		{
			g_INDEX[k] = TempStruct[i];
			k++;
		}
	}
	g_uFragileElemNum = 0;
	for (int i = 0; i < g_uValidElemNum; i++)
	{
		g_INDEX[i].ID = i;
	}
	free(TempStruct);
}


Flag* ReadFromG_INDEX()
{
	Flag* FlagPointer = (Flag*)malloc(sizeof(Flag) * (g_uValidElemNum + g_uFragileElemNum));
	for (int i = 0; i < g_uValidElemNum + g_uFragileElemNum; i++)
	{
		FlagPointer[i] = g_INDEX[i];
	}
	return FlagPointer;
}
struct FileFlag
{
	size_t ID;
	size_t FlagOffset;
	size_t NewFlagOffset;
	size_t StringLength;
	size_t BufferSize;
	size_t IsFragile = 0;
};
void FragileStringRemoveLoop()
{
	 
	Flag* FlagPointer =ReadFromG_INDEX();
	size_t uTotalElemNum = g_uFragileElemNum + g_uValidElemNum;
	size_t uValidNum = 0;
	size_t uTotalFragileSize = 0;
	FileFlag* p = (FileFlag*)malloc(sizeof(FileFlag) * uTotalElemNum);
	size_t uFileEndOffset = g_INDEX[uTotalElemNum - 1].FlagOffset + g_INDEX[uTotalElemNum - 1].BufferSize;
	for (int i = 0; i < uTotalElemNum; i++)
	{      //初始化新结构体
			p[i].BufferSize = g_INDEX[i].BufferSize;
			p[i].FlagOffset = g_INDEX[i].FlagOffset;
			p[i].ID = g_INDEX[i].ID;
			p[i].IsFragile = g_INDEX[i].IsFragile;
			p[i].NewFlagOffset = g_INDEX[i].FlagOffset;
			p[i].StringLength= g_INDEX[i].StringLength;
	}
	for (int i = 0; i < uTotalElemNum; i++)
	{
		if (g_INDEX[i].IsFragile == 1)
		{
			const size_t uCurrentFragileSize = g_INDEX[i].BufferSize;
			uTotalFragileSize += uCurrentFragileSize;
			for (int j = i; j < uTotalElemNum; j++)
			{
				p[j].NewFlagOffset -= uCurrentFragileSize;
			}
		}
	}

	for (int i = 0; i < uTotalElemNum; i++)
	{
		if (p[i].IsFragile == 0)
		{
			TCHAR szBuffer[STRING_MAX_LENTH] = { 0 };
			long long llPhoneNum = 0;
			fseek(fp, p[i].FlagOffset,SEEK_SET);
			fread(szBuffer, p[i].StringLength, 1, fp);
			fread(&llPhoneNum, sizeof(long long), 1, fp);
			
			fseek(fp, p[i].NewFlagOffset, SEEK_SET);
			fwrite(szBuffer, p[i].StringLength, 1, fp);
			fwrite(&llPhoneNum, sizeof(long long), 1, fp);

			rewind(fp);
		}
	}
	rewind(fp);

	char* VoidBufferPointer = (char*)malloc(uTotalFragileSize);
	for (int i = 0; i < uTotalFragileSize; i++)
	{
		VoidBufferPointer[i] = 0;
	}
	fseek(fp, uFileEndOffset- uTotalFragileSize,SEEK_SET);
	fwrite(VoidBufferPointer, uTotalFragileSize, 1, fp);
	rewind(fp);
	free(p);
	free(VoidBufferPointer);
}






