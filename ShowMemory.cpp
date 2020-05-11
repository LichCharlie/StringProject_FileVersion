#include "ShowMemory.h"

/*
内存状态打印，U占用，F非占用
根据删除标记作为判断条件，ElemNum作为循环条件来打印到屏幕
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
			//16个字符换一行，并打印地址，美观
			if ((uOccupiedNum+ uFreeNum) % 0x10== 0)
			{
				putchar('\n');
			}
			//不是碎片打印U
			if (!g_INDEX[i].IsFragile)
			{
				putchar('U');
				uOccupiedNum++;
			}
			//是碎片打印F
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