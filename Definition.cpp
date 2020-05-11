#include "Definition.h"
//记录总共有多少个有效内存块
size_t g_uFragileElemNum = 0;
size_t g_uValidElemNum=0;
//文件名
const TCHAR* FILENAME = TEXT("data.bin");
const TCHAR* INDEXFILENAME= TEXT("index.bin");
FILE* fp;
FILE* fpIndex;
//内存
//字符串属性表数组，就是个结构体数组
Flag *g_INDEX=NULL;
