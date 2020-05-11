
#include "IndexUpdate.h"

void ReadFromIndexFile()
{
	fpIndex = OpenFile(INDEXFILENAME, TEXT("rb"));
	fseek(fpIndex, 0, SEEK_SET);
	//读取有效信息数
	fread(&g_uValidElemNum, sizeof(size_t), 1, fpIndex);
	//读取无效信息数
	fread(&g_uFragileElemNum, sizeof(size_t), 1, fpIndex);
	rewind(fpIndex);
	if (g_uValidElemNum + g_uFragileElemNum > 0)
	{
		g_INDEX = (Flag*)malloc((g_uValidElemNum + g_uFragileElemNum+1) * sizeof(Flag));
		for (int i = 0; i < g_uValidElemNum + g_uFragileElemNum + 1; i++)
		{
			g_INDEX[i].BufferSize = 0;
			g_INDEX[i].FlagOffset = 0;
			g_INDEX[i].ID = 0;
			g_INDEX[i].IsFragile = 0;
			g_INDEX[i].StringLength = 0;
		}
		for (int i = 0; i < g_uValidElemNum + g_uFragileElemNum; i++)
		{
			//读到堆上的结构体里，用堆上的结构体操作文件,从8字节后面开始，因为前8个字节记录元素数量
			fseek(fpIndex, i*sizeof(Flag)+8, SEEK_SET);
			fread(&g_INDEX[i].ID, 4, 1, fpIndex);
			fread(&g_INDEX[i].FlagOffset, 4, 1, fpIndex);
			fread(&g_INDEX[i].StringLength, 4, 1, fpIndex);
			fread(&g_INDEX[i].BufferSize, 4, 1, fpIndex);
			fread(&g_INDEX[i].IsFragile, 4, 1, fpIndex);
			rewind(fpIndex);
		}
	}
	else
	{
		//说明这是第一个字符串，没有操作
		g_INDEX = (Flag*)malloc(sizeof(Flag));
	}

	CloseFile(fpIndex, INDEXFILENAME);
}
void WriteToIndexFile()
{
	fpIndex = OpenFile(INDEXFILENAME, TEXT("wb+"));
	//先把有效信息数量和碎片数目写进文件
	fseek(fpIndex, 0, SEEK_SET);
	fwrite(&g_uValidElemNum, 4, 1, fpIndex);
	fwrite(&g_uFragileElemNum, 4, 1, fpIndex);
	rewind(fpIndex);

	if (g_uValidElemNum + g_uFragileElemNum > 0)
	{
		for (int i = 0; i < g_uValidElemNum + g_uFragileElemNum; i++)
		{
			fseek(fpIndex, 8+i * sizeof(Flag), SEEK_SET);
			fwrite(&g_INDEX[i].ID, 4, 1, fpIndex);
			fwrite(&g_INDEX[i].FlagOffset, 4, 1, fpIndex);
			fwrite(&g_INDEX[i].StringLength, 4, 1, fpIndex);
			fwrite(&g_INDEX[i].BufferSize, 4, 1, fpIndex);
			fwrite(&g_INDEX[i].IsFragile, 4, 1, fpIndex);
			rewind(fpIndex);
		}
	}
	else
	{
		//说明没有可写数据
	}
	
	CloseFile(fpIndex, INDEXFILENAME);
}