#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//1.Floyd-Warshall�㷨������ʵ�ִ�i�Ŷ��㵽j�Ŷ���ֻ����ǰk�ŵ�����·����ʱ�临�Ӷ�O(n3)
//�ܽ����Ȩ�����⣬���ǲ��ܽ����Ȩ��·���⣨��Ϊ����ܸ������������·����
static void FloydWarshall(vector<vector<int>> &f, vector<int> &accrossPoint, vector<int> &startPoint, vector<int> &endPoint)
{
	for (int k = 0; k < accrossPoint.size(); k++)
		for (int i = 0; i < startPoint.size(); i++)
			for (int j = 0; j < endPoint.size(); j++)
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
}

//2.Dijkstra�㷨������ʵ��ָ��һ���㵽���������������·��
//f����Ϊ�洢·��Ȩ�صĽ�����飨�ڽӾ���ķ�ʽ��Ĭ��Ϊ����·��Ȩ�أ���dis����ΪԴ�㵽���е�����Ȩ��·����book����Ϊ�Ѿ����������Ȩ��·���ĵ�洢
static void Dijkstra(vector<vector<int>> &f, vector<int> &dis, vector<int> &book, int startPoint)
{
	//f�����ʼ��������֪��Ȩ�ص�·��������ȫΪINT_MAX���Լ����Լ�Ϊ0

	//dis�����ʼ�����洢��Դ�㵽�����ܵ����Ȩ��
	for (int i = 0; i < dis.size(); i++)
		dis[i] = f[startPoint][i];
	//book�����ʼ������Դ��������Ϊ1����ʾ��ǰ�Ѿ��ҵ�Դ������·��
	for (int i = 0; i < book.size(); i++)
		book[startPoint] = 1;
	//Dijkstra�㷨����
	int minNum = INT_MAX;
	int id = 0;
	//�����iû���ã����Ǹ�ѭ��
	for (int i = 0; i < f.size() - 1; i++)
	{
		minNum = INT_MAX;
		//�������ж��㣬�ҵ���Դ������ĵ㣬��¼��ID
		for (int j = 0; j < f.size(); j++)
		{
			//�����ǰ���㻹û�м���book���飬ͬʱ��Դ�㵽�õ�ľ���<min����ô����ֵ��ֵ��min�����洢�ö���ID
			if (book[j] == 0 && dis[j] < minNum)
			{
				minNum = dis[j];
				id = j;
			}
		}
		//��Դ������ĵ�ID����book����
		book[id] = 1;
		//�������ж��㣬�����id���㵽j��Ȩ��С��INT_MAX����Դ�㵽jվ���Ȩ��dis[j]������Ϊdis[j]���Դ�㵽idվ����ٵ�jվ���Ȩ�ص�������Сֵ
		for (int j = 0; j < f.size(); j++)
		{
			if (f[id][j] < INT_MAX)
			{
				dis[j] = min(dis[j], dis[id] + f[id][j]);
			}
		}
	}
}