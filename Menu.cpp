#include "Menu.h"
const TCHAR  *szMenuOption[9] =
{
	TEXT("1.Add String"),
	TEXT("2.Delete String"),
	TEXT("3.Modify String"),
	TEXT("4.Search String(By ID+By String)"),
	TEXT("5.Memory Map"),
	TEXT("6.Letter Statistics"),
	TEXT("7.Disk Fragment Sort"),
	TEXT("8.ShowStrings"),
	TEXT("9.Quit")
};
//���˵�
void DrawMenu()
{
	int i = 0;
	TPRINTF(TEXT("Memory Allocation Project----------LEI ZHANG\n"));
	while (i < sizeof(szMenuOption) / sizeof(*szMenuOption))
	{
		TPRINTF(TEXT("%s\n"), szMenuOption[i]);
		++i;
	}
}
//ѡ��
int Switch()
{
	TCHAR szBuf[100] = { 0 };
	TCHAR szBuf2[100] = { 0 };
	TPUTS(TEXT("Menu:Have a choose from 1-9\n"),stdout);
	//����ѡ��
	GetString(szBuf, 100);
	//��֤��Ч���뵼�º������������ҹ�����Ч���롣ֻ������'0'-'9'���ܽ����ڲ㺯��
	if (Filter(szBuf, 1, TCHARSIGN('0'), TCHARSIGN('9')))
	{
		switch (*szBuf)
		{
			//���
		case TCHARSIGN('1'):
		{
			TPUTS(TEXT("Please input your string.\n"), stdout);
			ReadFromIndexFile();
			fp=OpenFile(FILENAME, TEXT("rb+"));
			size_t uID=AddString(g_INDEX);
			CloseFile(fp, FILENAME);
			MergeIndexList(g_INDEX);
	        WriteToIndexFile();
			TPRINTF(TEXT("ID:%u  Length:%u\n"), g_INDEX[uID].ID,  g_INDEX[uID].StringLength);
			free(g_INDEX);
			break;
		}
		//ɾ��
		case TCHARSIGN('2'):
		{
			TPUTS(TEXT("Please input the ID of the string you want to delete.\n"),stdout);
		    size_t uIDDelete;
			ReadFromIndexFile();
		    if (SpecificOptions(szBuf2, &uIDDelete, TCHARSIGN('0'), TCHARSIGN('9'),g_uValidElemNum + g_uFragileElemNum, DeleteString))
	     	{
			TPUTS(TEXT("Delete Succeed.\n"), stdout);
			MergeIndexList(g_INDEX);
		    }
			WriteToIndexFile();
			free(g_INDEX);
			break;
		}
		//�޸�
		case TCHARSIGN('3'):
		{
			TPUTS(TEXT("Please input the ID of the string you want to modify.\n"),stdout);
			size_t uIDMofidy;
			size_t IsClosed = 0;
			ReadFromIndexFile();
			fp=OpenFile(FILENAME, TEXT("rb+"));
		    if (SpecificOptions(szBuf2, &uIDMofidy, TCHARSIGN('0'), TCHARSIGN('9'), g_uValidElemNum + g_uFragileElemNum, ModifyString))
			{
				IsClosed =CloseFile(fp,FILENAME);
				MergeIndexList(g_INDEX);
			}
			if (IsClosed!= 0)
			{
				CloseFile(fp, FILENAME);
			}
			WriteToIndexFile();
			free(g_INDEX);
			break;
		}
		////��ѯ
		case TCHARSIGN('4'):
		{
			TPUTS(TEXT("Input the g_INDEX of Search Pattern\n"), stdout);
			TPUTS(TEXT("0:ID Search\n"), stdout);
			TPUTS(TEXT("1:Accurate Name Search\n"), stdout);
			TPUTS(TEXT("2:Name Fuzzy Search\n"), stdout);
			TPUTS(TEXT("3:PhoneNumber Fuzzy Search\n"), stdout);
			size_t uSerachID;
			ReadFromIndexFile();
			fpIndex = OpenFile(INDEXFILENAME, TEXT("rb"));
			fp=OpenFile(FILENAME, TEXT("rb"));
			SpecificOptions(szBuf2, &uSerachID, TCHARSIGN('0'), TCHARSIGN('4'),4, SearchOption);
			CloseFile(fp,FILENAME);
			free(g_INDEX);
			break;
		}
		//�ڴ��ӡ
		case TCHARSIGN('5'):
		{
			ReadFromIndexFile();
			ShowMemory();
			free(g_INDEX);
			break;
		}
		//�ַ�ͳ��
		case TCHARSIGN('6'):
		{
			ReadFromIndexFile();
			fp=OpenFile(FILENAME, TEXT("rb"));
			NewLetterStatistics();
			CloseFile(fp,FILENAME);
			free(g_INDEX);
			break;
		}
		//��Ƭ����
		case TCHARSIGN('7'):
		{
			//��index.bin
			ReadFromIndexFile();
			//����data.bin
			fp=OpenFile(FILENAME, TEXT("rb+"));
			FragileStringRemoveLoop();
		    CloseFile(fp, FILENAME);

			//����index.bin
			DiskSortMerge();
			WriteToIndexFile();
			free(g_INDEX);  

			TPUTS(TEXT("Memory sorted!\n"), stdout);
			break;
		}
		//�ַ�����ӡ
		case TCHARSIGN('8'):
		{ 
			ReadFromIndexFile();
			fp=OpenFile(FILENAME, TEXT("rb"));
			ShowStrings();
			CloseFile(fp,FILENAME);
			free(g_INDEX);
			break;
		}
		//�˳�
		case TCHARSIGN('9'):
		{
			TPUTS(TEXT("Bye!\n"), stdout);
			break;
		}
		}
		return *szBuf;
	}
}
