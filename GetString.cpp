
#include "GetString.h"
//����fgets���������Ƴ���+ȥ������������
//�����ַ����׵�ַ
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
		//ֻҪ���ǻس�����\0ָ������
		while (buf[i] != TCHARSIGN('\n') && buf[i] != TCHARSIGN('\0'))
		{
			i++;
		}
		//����if���ж��Ƿ��ǻس����������ĳ�\0����������fgets����������\nд���ַ���
		//���Ա���Ҫ���ǻس�
		if (buf[i] == TCHARSIGN('\n'))
		{
			buf[i] = TCHARSIGN('\0');
		}
		//else˵��ֻ�����һ�����������ˣ�������Ҫ���պ����������������룬�������ջس�
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