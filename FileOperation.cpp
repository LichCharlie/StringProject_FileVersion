#include "FileOpeation.h"

FILE* OpenFile(const TCHAR* filename, const TCHAR* mode)
{
    fp = TFOPEN(filename, mode);
	if (fp == NULL)
	{
		TPRINTF(TEXT("%s open error.\n"), filename);
		return NULL;
	}
TPRINTF(TEXT("%s successfully open.\n"), filename);
	return fp;
}
size_t CloseFile(FILE *fp, const TCHAR* filename)
{
	//关闭失败
	if (fclose(fp)!=NULL)
	{
		TPRINTF(TEXT("%s close error.\n"), filename);
		return 1;
	}
	//关闭成功
	else
	{
        TPRINTF(TEXT("%s close successfully.\n"), filename);
		return 0;
	}
	
}
size_t CaculateOffset(Flag* pIndex, size_t uID)
{
	size_t uSum = 0;
	for (int i = 0; i < uID; i++)
	{
		uSum += pIndex[uID].BufferSize;
	}
	return uSum;
}

