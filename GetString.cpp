
#include "GetString.h"
//改造fgets函数，限制长度+去除不规则输入
//返回字符串首地址
TCHAR* GetString(TCHAR* buf, size_t uSize)
{
#ifdef UNICODE
	setlocale(LC_ALL, "chs");
#endif // UNICODE

	TCHAR* ret_val;
	size_t i = 0;
	ret_val = TFGETS(buf, uSize, stdin);
	if (ret_val)
	{
		//只要不是回车或者\0指针自增
		while (buf[i] != TCHARSIGN('\n') && buf[i] != TCHARSIGN('\0'))
		{
			i++;
		}
		//这里if会判断是否是回车，并把它改成\0，本质上是fgets这个函数会把\n写入字符串
		//所以必须要考虑回车
		if (buf[i] == TCHARSIGN('\n'))
		{
			buf[i] = TCHARSIGN('\0');
		}
		//else说明只有最后一种情况，溢出了，这样就要吸收后面的所有溢出的输入，并且吸收回车
		else
		{
			while (getchar() != TCHARSIGN('\n'))
			{
				continue;
			}
		}
		return ret_val;
	}
}