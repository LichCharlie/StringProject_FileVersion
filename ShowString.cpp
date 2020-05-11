#include "ShowString.h"
//展示字符串
void ShowStrings()
{
	TPRINTF(TEXT("Valid Elem=%u\n"),g_uValidElemNum);
	TPRINTF(TEXT("Fragile Elem=%u\n\n"), g_uFragileElemNum);
		
	for (size_t i = 0; i < g_uValidElemNum + g_uFragileElemNum; i++)
	{   //只要不是碎片就打印
		if (g_INDEX[i].IsFragile==0)
		{
			TCHAR buf[STRING_MAX_LENTH] = { 0 };
			long long llPhoneNum;
			fseek(fp, g_INDEX[i].FlagOffset, SEEK_SET);
			fread(buf, g_INDEX[i].StringLength, 1, fp);
			fread(&llPhoneNum, sizeof(long long), 1, fp);
			
			TPRINTF(TEXT("ID: %u  NameLength:%u   PhoneNumber: %lld\n"), g_INDEX[i].ID, g_INDEX[i].StringLength,  llPhoneNum);
			TPRINTF(TEXT("Name: %s \n"),buf);
		}
		//如果是碎片也显示它是碎片
		else
		{
			TPRINTF(TEXT("ID: %u  Fragment\n"), g_INDEX[i].ID);
		}
		rewind(fp);
	}
}
