#pragma once
#include "DeleteString.h"
//ɾ���ַ�������
//��ֱ�Ӳ����ַ�����ֱ�Ӹı��˹����id���ַ����Ľṹ��Ԫ�������ġ�
//�����ڴ���ʾ���ַ�ͳ�Ƶ�ʱ����ΪIsFragile=1�����������ڴ��ǲ����õģ�����ȥ����ν��ж�����
//ֻ����Ƭ����󣬲��ܰ�����ڴ�ɾ�����Ѻ�����ַ�������ǰ��
void DeleteString(size_t uID)
{
	//�������Ƭ��Ҳ��ֵΪ��Ƭ
	if (g_INDEX[uID].IsFragile)
	{
		g_INDEX[uID].IsFragile = 1;
	}
	//���������Ƭ,˵������ЧԪ�أ���ʱIsFragile��Ϊg_INDEX����Ϊɾ������ЧԪ����Ŀ��һ����Ƭ��Ŀ+1
	else
	{
		g_INDEX[uID].IsFragile = 1;
		g_uValidElemNum--;
		g_uFragileElemNum++;
	}
}