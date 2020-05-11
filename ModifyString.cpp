#pragma once
#include "ModifyString.h"
/*
����������������
1.�޸ĺ���ַ������ȵ���֮ǰ��
2.�޸ĺ���ַ������ȴ���֮ǰ��
3.�޸ĺ���ַ������ȵ���֮ǰ��
*/
//�޸��ַ�������
//���ȣ��޷��޸���Ƭ��ֻ���޸�IsFragileΪfalse��
//Ȼ��������������
//1.����ǡ�õ���
//2ԭ�����ڴ��㹻  
//3.�ڴ治��
void ModifyString(size_t ID)
{
	//�������Ƭ�������޸ģ�
	if (g_INDEX[ID].IsFragile)
	{
		TPUTS(TEXT("You can't modify a fragment.\n"),stdout);
	}
	//������Ƭ�����������
	else
	{
		//�Ȱ���Ҫд�����ַ���д�뻺����,��ǰ�ó���Ҫ�����ڴ�
		TPUTS(TEXT("Please input the new string.\n"), stdout);
		TCHAR buf[STRING_MAX_LENTH] = { 0 };
		long long llPhoneNumber = 0;
		GetString(buf, STRING_MAX_LENTH);
		SetPhoneNum(&llPhoneNumber);
		size_t uModifyStringLength = (sizeof(TCHAR)) * ((TSTRLEN(buf)) + 1);
		printf("uModifyStringLength=%d\n", uModifyStringLength);
		//�������Ҫ�޸ĵ��ַ���������ȣ�ֻ��Ҫ����,ȫ�ֱ�������Ҫ�䶯
		if (uModifyStringLength == g_INDEX[ID].BufferSize-sizeof(long long))
		{
			TCHAR buffer[STRING_MAX_LENTH] = { 0 };
			fseek(fp, g_INDEX[ID].FlagOffset, SEEK_SET);
			fwrite(buf, uModifyStringLength, 1, fp);
			fwrite(&llPhoneNumber, sizeof(long long), 1, fp);
			rewind(fp);
			TPUTS(TEXT("Modify Succeed.\n"), stdout);
		}
		//���ַ����������޷�װ�£�ԭ��Ϊɾ�������ڴ��������
		else if (uModifyStringLength > g_INDEX[ID].BufferSize - sizeof(long long))
		{
			size_t offset = 0;
			//����ɾ��g_INDEX(ID)��ȫ�ֱ�����Ƭ������1����Ч�ַ���������1�����������ǲ����
			DeleteString(ID);
			//����ַ�����ճ����ַ ����� �����ڴ�g_szBuf��ƫ�� offset
			for (size_t i = 0; i < g_uValidElemNum + g_uFragileElemNum; i++)
			{
				offset += g_INDEX[i].BufferSize;
			}
			//�ڴ濽�����
			fseek(fp, offset, SEEK_SET);
			fwrite(buf, uModifyStringLength, 1, fp);
			fwrite(&llPhoneNumber, sizeof(long long), 1, fp);
			rewind(fp);
			//����
			//������Ƭ
			g_INDEX[g_uValidElemNum + g_uFragileElemNum].IsFragile = 0;
			//�ַ�����ʼ��ַ
			g_INDEX[g_uValidElemNum + g_uFragileElemNum].FlagOffset = offset;
			//�ַ�������
			g_INDEX[g_uValidElemNum + g_uFragileElemNum].StringLength = uModifyStringLength;
			g_INDEX[g_uValidElemNum + g_uFragileElemNum].BufferSize = uModifyStringLength + sizeof(long long);
			//��Ч�ַ�����Ŀ+1
			g_uValidElemNum++;
			TPUTS(TEXT("Modify Succeed.\n"), stdout);
		}

		//ModifyStringLength < g_INDEX[ID].StringLength
		else
		{
			//�ȸ��ڴ�
			fseek(fp, g_INDEX[ID].FlagOffset, SEEK_SET);
			fwrite(buf, uModifyStringLength, 1, fp);
			fwrite(&llPhoneNumber, sizeof(long long), 1, fp);
			rewind(fp);
			//�����²�������Ƭ��С
			size_t NewFragileLength = g_INDEX[ID].BufferSize - uModifyStringLength- sizeof(long long);
			//�ٸ��������������ĵ�һ������������Ԫ�أ�ID���øģ����ͳһ����,��Ƭ����־��Ϊfalse�����ȸ�ΪModifyStringLength
			g_INDEX[ID].IsFragile = 0;
			g_INDEX[ID].StringLength = uModifyStringLength;
			g_INDEX[ID].BufferSize = uModifyStringLength + sizeof(long long);

			//����ı�Ԫ�غ��ƣ�Ϊ��������Ƭ��׼��
			for (size_t i = g_uValidElemNum + g_uFragileElemNum; i > ID; i--)
			{
				g_INDEX[i] = g_INDEX[i - 1];
			}
			//���޸����µı�Ԫ�أ�ID����Ҫ����Ϊ������ �ǲ�����ƬΪ��׼��
			//pBufferBegin��ǰһ��Ԫ�ر����ָ��+ǰһ��Ԫ�صĳ���
			g_INDEX[ID + 1].FlagOffset = g_INDEX[ID].FlagOffset + g_INDEX[ID].BufferSize;
			//��Ƭ��־Ϊ��
			g_INDEX[ID + 1].IsFragile = 1;
			//����ΪNewFragileLength
			g_INDEX[ID + 1].StringLength = NewFragileLength;
			g_INDEX[ID + 1].BufferSize = NewFragileLength;
			//��ƬԪ����Ŀ+1,��ЧԪ���������ֲ���
			g_uFragileElemNum++;
			TPUTS(TEXT("Modify Succeed.\n"), stdout);
		}
	}
}

