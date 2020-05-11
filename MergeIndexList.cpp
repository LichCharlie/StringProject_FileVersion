#pragma once
#include "MergeIndexList.h"

/*
������
ÿ��ִ��AddString,DeleteString,ModifyString,DiskSort����֮��,Ҳ��������д�����ĺ���֮��ִ�����MergeIndexList������
��֤���ڵ���Ƭ�ϲ���һ����Ƭ�����ı�,�ı�����������Ѿ���֤�˸�ֵg_uValidElemNum�� g_uFragileElemNum����ȫ��ȷ�ģ�Ȼ��
������i<g_uValidElemNum+g_uFragileElemNum;��ÿ����һ��ID
*/
void MergeIndexList(Flag* pIndex)
{
	size_t ID = 0;
	//������������Ҫ�������ٸ�Ԫ�أ�ÿ��Ԫ�ض�Ҫ���һ��
	size_t TotalElemNum = g_uValidElemNum + g_uFragileElemNum;
	//Ԫ�ظ���>0��ѭ��
	if (TotalElemNum > 0)
	{
		for (size_t i = 1; i < TotalElemNum; i++)
		{
			//��飺������������ڵ���Ƭ�ռ䣬��Ҫ�������ϲ�
			if (pIndex[i - 1].IsFragile && pIndex[i].IsFragile)
			{
				//����ǰ���Ԫ�صĳ��ȼ��Ϻ���Ԫ�صĳ���
				pIndex[i - 1].BufferSize += pIndex[i].BufferSize;
				//������һ����Ƭ�ռ�������ֻ��ȫ�ֱ����ģ���Ӱ��ѭ���е�TotalElemNum
				g_uFragileElemNum--;
				//�����Ԫ��ǰ��
				for (size_t j = i; j < TotalElemNum-1; j++)
				{
					pIndex[j] = pIndex[j + 1];
				}
				if (i == TotalElemNum - 1)
				{
					//g_uFragileElemNum--;
					break;
				}
				//֮ǰ�Ѿ���Ԫ�غϲ��ˣ�����ȷ�����ڵĺ����Ƿ�����Ƭ�����´����Ԫ�ؼ���,������У����źϲ�
				i--;
			}
		}
	}
	
	//ÿ����ID�������Ƿ�����Ƭ
	for (size_t i = 0; i < g_uValidElemNum + g_uFragileElemNum; i++)
	{
		pIndex[i].ID = ID;
		ID++;
	}
}