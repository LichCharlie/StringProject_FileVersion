#include "Definition.h"
//��¼�ܹ��ж��ٸ���Ч�ڴ��
size_t g_uFragileElemNum = 0;
size_t g_uValidElemNum=0;
//�ļ���
const TCHAR* FILENAME = TEXT("data.bin");
const TCHAR* INDEXFILENAME= TEXT("index.bin");
FILE* fp;
FILE* fpIndex;
//�ڴ�
//�ַ������Ա����飬���Ǹ��ṹ������
Flag *g_INDEX=NULL;
