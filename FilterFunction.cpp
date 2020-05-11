#include "FilterFunction.h"

/*
这些函数是防止用户恶意输入无关信息后导致程序出错+崩溃的。是缓冲区处理函数+数值越界判断的函数
最后的spercificoperation函数用来封装switchcase语句中部分用户接口的实现，如果写在switchcase中非常难看

这些函数需要相互配合使用
*/

//为菜单选项服务，如果不输入1-9的数字会直接break；
size_t IdentifyOption()
{
	TPUTS(TEXT("Menu:Have a choose from 1-9"),stdout);
	size_t uOption;
	while (uOption = getchar())
	{
		if (uOption <= '9' && uOption >= '1')
		{
			while (getchar() != '\n')
			{
				continue;
			}
			break;
		}
		else
		{
			while (getchar() != '\n')
			{
				continue;
			}
			TPUTS(TEXT("Menu:Please input a valid Option(1-9)."), stdout);
		}
	}
	return uOption;
}


//判断得出的数字是否合法 ID是被比较的数字 Num是标准，如果ID<Num为真
bool IdentifyValidID(size_t uID, size_t uNum)
{
	if (uID < uNum)
		return g_INDEX;
	else
		return false;
}

//所有输入都写入buf，然后算出输入的数字
//根据设计流程,如果能执行到这个函数说明输入肯定是个数字，然后算出并返回这个数字
//不过这个数字是否合法需要其他不同的函数判断
size_t GetID(TCHAR* buf)
{
	size_t uSum = 0;
	size_t uLength= TSTRLEN(buf);
	for (size_t i = 0; i < TSTRLEN(buf); i++)
	{
		uSum += (buf[i] - TCHARSIGN('0')) * pow(10, --uLength);
	}

	return uSum;

}
//过滤器函数
//buf是数组，size_t是用户输入的字符串长度上限
//OptionFront  OptionBack是前边界和后边界
bool Filter(TCHAR* buf, size_t uMaxDigit, size_t uOptionFront, size_t uOptionBack)
{
	for (int i = 0; i < TSTRLEN(buf); i++)
	{
		if (TSTRLEN(buf) > uMaxDigit || buf[i] < uOptionFront/*0*/ || buf[i] > uOptionBack /*9*/)
		{
			return false;
		}
	}
	return true;
}
void SystemClsLoop()
{
	putchar('\n');
	TCHAR ch = 0;
	TCHAR Arr[2] = { 0 };
	while (1)
	{
		TPUTS(TEXT("press Y or y to clear screen and continue.\n"), stdout);
		ch = *GetString(Arr, 2);
		if (ch == TCHARSIGN('Y') || ch == TCHARSIGN('y'))
		{
			system("cls");
			break;
		}
		else
		{
			TPUTS(TEXT("You put the wrong sentence,try again.\n"), stdout);
		}
	}
}

//因为switch内重复代码冗余而且耦合性太强，做SpecificOptions函数封装，最后参数是函数指针->删除修改查询
bool SpecificOptions(TCHAR* buf2, size_t* pStringID, TCHAR lo, TCHAR hi, size_t uMaxValue,FuctionName fnOperation)
{
	GetString(buf2, 100);
	if (Filter(buf2, 100, lo, hi))
	{
		*pStringID = GetID(buf2);
		if (IdentifyValidID(*pStringID, uMaxValue))
		{
			fnOperation(*pStringID);
			return g_INDEX;
		}
		else
		{
			TPUTS(TEXT("Your input is invalid,back to menu now.\n"), stdout);
			return false;
		}
	}
	else
	{
		TPUTS(TEXT("Your input is invalid,back to menu now.\n"),stdout);
		return false;
	}
}
