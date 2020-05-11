
#include "AddString.h"

//�ж��Ƿ��п����õ���Ƭ�ռ䣬����з���true
bool HasCapableFragile(Flag* IndexArray, size_t uSpaceRequired, size_t* pIndex)
{
	size_t i = 0;
	//���������ڴ�������
	for (; i < g_uValidElemNum + g_uFragileElemNum; i++)
	{
		//������ڴ�εĳ����ܹ�����SpaceRequired��˵�����Դ洢
		if (IndexArray[i].IsFragile)
		{
			if (IndexArray[i].BufferSize >= uSpaceRequired)
			{
				//����������ҷ���Ҫ����±�
				*pIndex = i;
				return true;
			}
		}
	}
	//���û�У��������±�Ϊ����Ԫ�ص��±� g_uValidElemNum + g_uFragileElemNum
	*pIndex = i;
	return false;
}

size_t AddString(Flag* IndexArray)
{
	size_t uIndex = 0;
	TCHAR buf[STRING_MAX_LENTH];
	long long llPhoneNum = 0;
	GetString(buf, STRING_MAX_LENTH);
	long long  *pllPhoneNum = &llPhoneNum;
	SetPhoneNum(pllPhoneNum);
	
	//�����Ҫ����ַ����ĳ���
	size_t uNewStringLength = (sizeof(TCHAR)) * (TSTRLEN(buf)) + (sizeof(TCHARSIGN('\0')));
	//TPRINTF(TEXT("NewStringLength=%d\n"), NewStringLength);
	size_t uPhoneNumberLength = sizeof(long long);
	//�п�������Ƭ 
	 
	if (HasCapableFragile(IndexArray, uNewStringLength+ uPhoneNumberLength, &uIndex))
	{
		//ִ�е������ʱ��g_INDEX�Ѿ�����ֵΪһ��������ڴ��ID��
		//�޸ĵĳ�����֮ǰ������ͬ�����
		if (IndexArray[uIndex].BufferSize == uNewStringLength+ uPhoneNumberLength)
		{   //�ȸ��ڴ�
			fseek(fp, IndexArray[uIndex].FlagOffset, SEEK_SET);
			fwrite(buf, uNewStringLength, 1, fp);
			fwrite(pllPhoneNum, uPhoneNumberLength, 1, fp);
			rewind(fp);
			//�ٸ�����������ID��������������޸ģ�ֻ��Ҫ��������Ƭ����־��Ϊfalse
			IndexArray[uIndex].IsFragile = 0;
			//����ȫ�ֱ�����Ҫ�仯����Ч�ַ�������+1,��Ƭ�ַ�������-1(��Ϊ������һ���ַ���������ַ�������������
			//ռ����Ѱ�ҵ�������ռ�,���������Ƭ��ʧ��)
			g_uValidElemNum++;
			g_uFragileElemNum--;
		}

		//��ӵĳ��ȱ�֮ǰ���ȶ̵����
		else
		{  //�ȸ��ڴ�
			fseek(fp, IndexArray[uIndex].FlagOffset, SEEK_SET);
			fwrite(buf, uNewStringLength, 1, fp);
			fwrite(pllPhoneNum, uPhoneNumberLength, 1, fp);
			rewind(fp);
			//TSTRCPY(IndexArray[uIndex].pBufferBegin, buf);
			//�ȼ�����²�������Ƭ���ȣ�Ϊ��ֵ���¸�Ԫ����׼������Ϊ��Ȼ������Ƭ��ƫ�Ʊ�Ҳ�ͱ�Ȼ���ģ���һ��Ԫ�ص�
			//����һ���������Ƭ����
			size_t NewFragileLength = IndexArray[uIndex].BufferSize - (uNewStringLength+ uPhoneNumberLength);
			//�ٸ��������������ĵ�һ������������Ԫ�أ�ID���ø�,������������ͳһ������Ƭ����־��Ϊfalse�����ȸ�ΪNewStringLength
			IndexArray[uIndex].IsFragile = false;
			IndexArray[uIndex].StringLength = uNewStringLength;
			IndexArray[uIndex].BufferSize = uNewStringLength+ uPhoneNumberLength;
			//����ı�Ԫ�غ��ƣ�Ϊ��������Ƭ��׼��
			for (size_t i = g_uValidElemNum + g_uFragileElemNum; i > uIndex; i--)
			{
				IndexArray[i] = IndexArray[i - 1];
			}
			//���޸����µı�Ԫ�أ�ID����Ҫ������������ͳһ����
			//pBufferBegin��ǰһ��Ԫ�ر����ָ��+ǰһ��Ԫ�صĳ���
			IndexArray[uIndex + 1].FlagOffset = IndexArray[uIndex].FlagOffset + IndexArray[uIndex].BufferSize;
			//��Ƭ��־Ϊ��
			IndexArray[uIndex + 1].IsFragile = 1;
			//����Ϊ�����ָ����strlen
			IndexArray[uIndex + 1].StringLength = NewFragileLength;
			IndexArray[uIndex + 1].BufferSize = NewFragileLength;
			//��ЧԪ����Ŀ+1,��ƬԪ���������ֲ��䣨+1����Ϊ��һ���ڴ�ֳ������飬һ�������ЧԪ�أ���һ�黹����Ƭ��
			g_uValidElemNum++;
		}
	}

	//û�п���������Ƭλ��,������ĩβ�ӡ�ID����g_uValidElemNum+g_uFragileElemNum
	else
	{
		//��ƫ��
		size_t uOffset = 0;
		for (size_t i = 0; i < g_uValidElemNum + g_uFragileElemNum; i++)
		{
			uOffset += IndexArray[i].BufferSize;
		}
		//�����ӵı�Ȼ��Ϊ��Ƭ
		IndexArray[g_uValidElemNum + g_uFragileElemNum].IsFragile = 0;
		//�ڴ����ʼ��ַ
		IndexArray[g_uValidElemNum + g_uFragileElemNum].FlagOffset = uOffset;
		//���ַ���������ȥ
		fseek(fp, uOffset, SEEK_SET);
		fwrite(buf, uNewStringLength, 1, fp);
		fwrite(pllPhoneNum, uPhoneNumberLength, 1, fp);
		rewind(fp);
		//���Ⱦ����ַ�������
		IndexArray[g_uValidElemNum + g_uFragileElemNum].StringLength = uNewStringLength;
		IndexArray[g_uValidElemNum + g_uFragileElemNum].BufferSize = uNewStringLength+ uPhoneNumberLength;
		//��������λ��
		uIndex = g_uValidElemNum + g_uFragileElemNum;
		//������һ����ЧԪ��
		g_uValidElemNum++;
		TPRINTF(TEXT("StringLength=%d\n"), uNewStringLength);
		TPRINTF(TEXT("BufferSize=%d\n"), uNewStringLength + uPhoneNumberLength);
	}
	return uIndex;
}

void SetPhoneNum(long long* llpPhoneNum)
{
	TPRINTF(TEXT("Pls input the phone number.\n"));
	fscanf(stdin,"%lld", llpPhoneNum);
	getchar();
}