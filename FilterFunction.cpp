#include "FilterFunction.h"

/*
��Щ�����Ƿ�ֹ�û����������޹���Ϣ���³������+�����ġ��ǻ�����������+��ֵԽ���жϵĺ���
����spercificoperation����������װswitchcase����в����û��ӿڵ�ʵ�֣����д��switchcase�зǳ��ѿ�

��Щ������Ҫ�໥���ʹ��
*/

//Ϊ�˵�ѡ��������������1-9�����ֻ�ֱ��break��
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


//�жϵó��������Ƿ�Ϸ� ID�Ǳ��Ƚϵ����� Num�Ǳ�׼�����ID<NumΪ��
bool IdentifyValidID(size_t uID, size_t uNum)
{
	if (uID < uNum)
		return g_INDEX;
	else
		return false;
}

//�������붼д��buf��Ȼ��������������
//�����������,�����ִ�е��������˵������϶��Ǹ����֣�Ȼ������������������
//������������Ƿ�Ϸ���Ҫ������ͬ�ĺ����ж�
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
//����������
//buf�����飬size_t���û�������ַ�����������
//OptionFront  OptionBack��ǰ�߽�ͺ�߽�
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

//��Ϊswitch���ظ�����������������̫ǿ����SpecificOptions������װ���������Ǻ���ָ��->ɾ���޸Ĳ�ѯ
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
