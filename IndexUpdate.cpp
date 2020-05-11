
#include "IndexUpdate.h"

void ReadFromIndexFile()
{
	fpIndex = OpenFile(INDEXFILENAME, TEXT("rb"));
	fseek(fpIndex, 0, SEEK_SET);
	//��ȡ��Ч��Ϣ��
	fread(&g_uValidElemNum, sizeof(size_t), 1, fpIndex);
	//��ȡ��Ч��Ϣ��
	fread(&g_uFragileElemNum, sizeof(size_t), 1, fpIndex);
	rewind(fpIndex);
	if (g_uValidElemNum + g_uFragileElemNum > 0)
	{
		g_INDEX = (Flag*)malloc((g_uValidElemNum + g_uFragileElemNum+1) * sizeof(Flag));
		for (int i = 0; i < g_uValidElemNum + g_uFragileElemNum + 1; i++)
		{
			g_INDEX[i].BufferSize = 0;
			g_INDEX[i].FlagOffset = 0;
			g_INDEX[i].ID = 0;
			g_INDEX[i].IsFragile = 0;
			g_INDEX[i].StringLength = 0;
		}
		for (int i = 0; i < g_uValidElemNum + g_uFragileElemNum; i++)
		{
			//�������ϵĽṹ����ö��ϵĽṹ������ļ�,��8�ֽں��濪ʼ����Ϊǰ8���ֽڼ�¼Ԫ������
			fseek(fpIndex, i*sizeof(Flag)+8, SEEK_SET);
			fread(&g_INDEX[i].ID, 4, 1, fpIndex);
			fread(&g_INDEX[i].FlagOffset, 4, 1, fpIndex);
			fread(&g_INDEX[i].StringLength, 4, 1, fpIndex);
			fread(&g_INDEX[i].BufferSize, 4, 1, fpIndex);
			fread(&g_INDEX[i].IsFragile, 4, 1, fpIndex);
			rewind(fpIndex);
		}
	}
	else
	{
		//˵�����ǵ�һ���ַ�����û�в���
		g_INDEX = (Flag*)malloc(sizeof(Flag));
	}

	CloseFile(fpIndex, INDEXFILENAME);
}
void WriteToIndexFile()
{
	fpIndex = OpenFile(INDEXFILENAME, TEXT("wb+"));
	//�Ȱ���Ч��Ϣ��������Ƭ��Ŀд���ļ�
	fseek(fpIndex, 0, SEEK_SET);
	fwrite(&g_uValidElemNum, 4, 1, fpIndex);
	fwrite(&g_uFragileElemNum, 4, 1, fpIndex);
	rewind(fpIndex);

	if (g_uValidElemNum + g_uFragileElemNum > 0)
	{
		for (int i = 0; i < g_uValidElemNum + g_uFragileElemNum; i++)
		{
			fseek(fpIndex, 8+i * sizeof(Flag), SEEK_SET);
			fwrite(&g_INDEX[i].ID, 4, 1, fpIndex);
			fwrite(&g_INDEX[i].FlagOffset, 4, 1, fpIndex);
			fwrite(&g_INDEX[i].StringLength, 4, 1, fpIndex);
			fwrite(&g_INDEX[i].BufferSize, 4, 1, fpIndex);
			fwrite(&g_INDEX[i].IsFragile, 4, 1, fpIndex);
			rewind(fpIndex);
		}
	}
	else
	{
		//˵��û�п�д����
	}
	
	CloseFile(fpIndex, INDEXFILENAME);
}