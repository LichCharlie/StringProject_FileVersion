#include "ShowString.h"
//չʾ�ַ���
void ShowStrings()
{
	TPRINTF(TEXT("Valid Elem=%u\n"),g_uValidElemNum);
	TPRINTF(TEXT("Fragile Elem=%u\n\n"), g_uFragileElemNum);
		
	for (size_t i = 0; i < g_uValidElemNum + g_uFragileElemNum; i++)
	{   //ֻҪ������Ƭ�ʹ�ӡ
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
		//�������ƬҲ��ʾ������Ƭ
		else
		{
			TPRINTF(TEXT("ID: %u  Fragment\n"), g_INDEX[i].ID);
		}
		rewind(fp);
	}
}
