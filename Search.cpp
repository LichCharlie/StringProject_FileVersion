#include "Search.h"

//0 id搜索 1 字符串搜索 2模糊字符串搜索 3模糊电话号码搜索
void SearchOption(size_t option)
{
	
	switch (option)
	{
	case 0:
		SearchByID();
		break;
	case 1:
		SearchAccurateString();
		break;
	case 2:
		SearchByString();
		break;
	case 3:
		SearchByPhoneNum();
		break;
	}
}
//判断ID是否存在并且合法的函数
bool IDExist(size_t* pID, TCHAR* buf)
{
	bool flag = false;
	if (Filter(buf, STRING_MAX_LENTH, TCHARSIGN('0'), TCHARSIGN('9')))
	{
		*pID = GetID(buf);
		if ((IdentifyValidID(*pID, g_uValidElemNum+g_uFragileElemNum) && g_INDEX[*pID].IsFragile == 0))
		{
			return g_INDEX;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
void SearchByID()
{
	size_t uID = 0;
	TCHAR buf[STRING_MAX_LENTH] = { 0 };
	long long llPhoneNum = 0;
	TPRINTF(TEXT("Input the ID of the string (0 - %u)\n"),g_uValidElemNum+g_uFragileElemNum - 1);
	//判断输入是否合法
	GetString(buf, STRING_MAX_LENTH);

	if (IDExist(&uID, buf))
	{
		fseek(fp, g_INDEX[uID].FlagOffset, SEEK_SET);
		fread(buf, g_INDEX[uID].StringLength, 1, fp);
		fread(&llPhoneNum, sizeof(long long), 1, fp);
		TPRINTF(TEXT("ID:%u Name:%s  PhoneNum: %lld\n"), g_INDEX[uID].ID, buf, llPhoneNum);
		rewind(fp);
	}
	else
	{
		TPUTS(TEXT("Invalid ID or Deleted string.\n"), stdout);
		rewind(fp);
	}
}
//判断输入的str是否存在
bool StringExist(TCHAR* SearchedStr, size_t* IDIndex, size_t* pStringNum)
{
	size_t i = 0;
	size_t TotalElemNum = g_uValidElemNum + g_uFragileElemNum;
	size_t ConditionalStringNum = 0;
	bool StrExisted = false;
	while (i < TotalElemNum)
	{
		TCHAR buffer[STRING_MAX_LENTH] = { 0 };
		if (g_INDEX[i].IsFragile == 0)
		{
			fseek(fp, g_INDEX[i].FlagOffset, SEEK_SET);
			fread(buffer, g_INDEX[i].StringLength, 1, fp);
			if (TSTRSTR(buffer, SearchedStr))
			{
				StrExisted = g_INDEX;
				IDIndex[ConditionalStringNum] = i;
				++ConditionalStringNum;
			}
			rewind(fp);
		}
		i++;
		rewind(fp);
	}
	*pStringNum = ConditionalStringNum;
	return StrExisted;
}
//调用了StringExist（）打印存在的函数，否则打印不存在
void SearchByString()
{  //这个数组按照顺序记录出现相同子串的内存ID
	size_t uIndexArr[100] = { 0 };
	size_t uStringNum = 0;
	TPUTS(TEXT("Put your Name you are looking for.\n"), stdout);
	TCHAR buf[STRING_MAX_LENTH] = { 0 };
	//把要查询的字符串传入buf
	GetString(buf, STRING_MAX_LENTH);
	//TPRINTF(TEXT("You are searching for : \"%s\"\n"), buf);
	//exist函数不但判断是否存在要查询的内容，还向StringNum传出内容，内容是符合要求的串的个数
	if (StringExist(buf, uIndexArr, &uStringNum))
	{
		//只需要循环符合要求的串的次数
		for (size_t i = 0; i < uStringNum; i++)
		{
			TCHAR buffer[STRING_MAX_LENTH] = { 0 };
			long long llPhoneNum = 0;
			//表中表，IndexArr[i]的值是符合要求串的ID
			fseek(fp, g_INDEX[uIndexArr[i]].FlagOffset, SEEK_SET);
			fread(buffer, g_INDEX[uIndexArr[i]].StringLength, 1, fp);
			fread(&llPhoneNum, sizeof(long long), 1, fp);
			TPRINTF(TEXT("ID:%u  Name:%s PhoneNum: %lld\n"), g_INDEX[uIndexArr[i]].ID, buffer, llPhoneNum);
			rewind(fp);
		}
	}
	else
	{
		TPRINTF(TEXT("\"%s\"does not exist\n"), buf);
	}
	rewind(fp);
}

void SearchAccurateString()
{  //这个数组按照顺序记录出现完全相同子串的内存ID
	TPUTS(TEXT("put your string you are looking for.\n"), stdout);
	TCHAR buf[STRING_MAX_LENTH] = { 0 };
	//把要查询的字符串传入buf
	GetString(buf, STRING_MAX_LENTH);
	//完全匹配的串是否存在，先默认不存在
	bool IsExisted = false;
	for (size_t i = 0; i < g_uValidElemNum + g_uFragileElemNum; i++)
	{
		TCHAR buffer[STRING_MAX_LENTH] = { 0 };
		long long llPhoneNum = 0;
		if (!g_INDEX[i].IsFragile)
		{
			fseek(fp, g_INDEX[i].FlagOffset, SEEK_SET);
			fread(buffer, g_INDEX[i].StringLength, 1, fp);
			fread(&llPhoneNum, sizeof(long long), 1, fp);
			if (TSTRCMP(buffer, buf) == 0)
			{
				//找到后改为存在
				IsExisted = g_INDEX;
				TPRINTF(TEXT("ID:%u  Name: %s   PhoneNum: %lld \n"), g_INDEX[i].ID, buf, llPhoneNum);
			}
			rewind(fp);
		}
	}
	//不存在
	if(!IsExisted)
	{
		TPRINTF(TEXT("\"%s\"does not exist\n"), buf);
		rewind(fp);
	}
	rewind(fp);
}


bool PhoneNumExist(TCHAR* SearchedStr, size_t* IDIndex, size_t* pStringNum)
{
	size_t i = 0;
	size_t TotalElemNum = g_uValidElemNum + g_uFragileElemNum;
	size_t ConditionalStringNum = 0;
	bool PhoneNumExisted = false;
	while (i < TotalElemNum)
	{
		TCHAR buff[STRING_MAX_LENTH] = { 0 };
		long long PhoneNumBuffer = 0;
		if (g_INDEX[i].IsFragile == 0)
		{
			fseek(fp, g_INDEX[i].FlagOffset+g_INDEX[i].StringLength, SEEK_SET);
			fread(&PhoneNumBuffer, sizeof(long long), 1, fp);
			TLTO(PhoneNumBuffer, buff,10);
			if (TSTRSTR(buff, SearchedStr))
			{
				PhoneNumExisted = g_INDEX;
				IDIndex[ConditionalStringNum] = i;
				++ConditionalStringNum;
			}
			rewind(fp);
		}
		i++;
		rewind(fp);
	}
	*pStringNum = ConditionalStringNum;
	return PhoneNumExisted;
}
//调用了StringExist（）打印存在的函数，否则打印不存在
void SearchByPhoneNum()
{  //这个数组按照顺序记录出现相同子串的内存ID
	size_t uIndexArr[100] = { 0 };
	size_t uStringNum = 0;
	TPUTS(TEXT("put your Phone Number you are looking for.\n"), stdout);
	TCHAR buf[STRING_MAX_LENTH] = { 0 };
	
	//把要查询的字符串传入buf
	GetString(buf, STRING_MAX_LENTH);
	//exist函数不但判断是否存在要查询的内容，还向StringNum传出内容，内容是符合要求的串的个数
	if (PhoneNumExist(buf, uIndexArr, &uStringNum))
	{
		//只需要循环符合要求的串的次数
		for (size_t i = 0; i < uStringNum; i++)
		{
			long long llPhoneNum = 0;
			TCHAR buffer[STRING_MAX_LENTH] = { 0 };
			//表中表，IndexArr[i]的值是符合要求串的ID
			fseek(fp, g_INDEX[uIndexArr[i]].FlagOffset, SEEK_SET);
			fread(buffer, g_INDEX[uIndexArr[i]].StringLength, 1, fp);
			fread(&llPhoneNum, sizeof(long long), 1, fp);
			TPRINTF(TEXT("ID:%u  Name: %s  PhoneNum %lld\n"), g_INDEX[uIndexArr[i]].ID,buffer, llPhoneNum);
			rewind(fp);
		}
	}
	else
	{
		TPRINTF(TEXT("\"%s\" PhoneNum does not exist\n"), buf);
	}
	rewind(fp);
}