#include "NewLetterStatistics.h"

void NewLetterStatistics()
{
#ifdef UNICODE
	setlocale(LC_ALL, "chs");
#else
	setlocale(LC_ALL, "English");
#endif // DEBUG
	map<TCHAR, size_t> Word_Count_Table;
	double uWordSum = 0;
	size_t uTotalElemNum = g_uValidElemNum + g_uFragileElemNum;
	for (int i = 0; i < uTotalElemNum; i++)
	{
		if (g_INDEX[i].IsFragile != 1  )
		{
			for (int j = 0; j < (g_INDEX[i].StringLength)/(sizeof(TCHAR)); j++)
			{
				TCHAR temp;
				fseek(fp, g_INDEX[i].FlagOffset+j*sizeof(TCHAR), SEEK_SET);
				fread(&temp, sizeof(TCHAR), 1, fp);
				rewind(fp);
				++Word_Count_Table[temp];
			}
		}
	}
	for (const auto &elem : Word_Count_Table)
	{
		uWordSum += elem.second;
	}
	TPRINTF(TEXT("Total character number = %.0lf\n"), uWordSum);
	for (const auto &elem : Word_Count_Table)
	{
		TPRINTF(TEXT("Character: %c   Count: %d  Proportion: %2.2lf\%%\n"), elem.first, elem.second, 100*elem.second/ uWordSum);
	}
}