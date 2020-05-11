#include "ShowMemory.h"

/*
�ڴ�״̬��ӡ��Uռ�ã�F��ռ��
����ɾ�������Ϊ�ж�������ElemNum��Ϊѭ����������ӡ����Ļ
*/
void ShowMemory()
{
	size_t uOccupiedNum = 0;
	size_t uFreeNum = 0;
	TPRINTF(TEXT("Valid Elem=%u\n"),g_uValidElemNum );
	TPRINTF(TEXT("Fragile Elem=%u\n\n"), g_uFragileElemNum);
	for (size_t i = 0; i <  g_uFragileElemNum+g_uValidElemNum; i++)
	{
		for (size_t j = 0; j < g_INDEX[i].BufferSize; j++)
		{
			//16���ַ���һ�У�����ӡ��ַ������
			if ((uOccupiedNum+ uFreeNum) % 0x10== 0)
			{
				putchar('\n');
			}
			//������Ƭ��ӡU
			if (!g_INDEX[i].IsFragile)
			{
				putchar('U');
				uOccupiedNum++;
			}
			//����Ƭ��ӡF
			else if(g_INDEX[i].IsFragile)
			{
				putchar('F');
				uFreeNum++;
			}
		}
	}
	putchar('\n');
	putchar('\n');
	TPRINTF(TEXT("U count: %u\tF count:  %u\n"), uOccupiedNum, uFreeNum);
	putchar('\n');
}