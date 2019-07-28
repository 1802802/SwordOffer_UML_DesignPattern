//#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

//currentָ��ǰ�Ѿ��ѻ�ľ�ŵ�����ˣ��ݹ麯��ǰ����Ǽ��ŵ����ϲ�������������һ�û���ܷŵĸ��ߵĻ�ľ
int findbox(vector<vector<int>> &heap, vector<vector<int>> &box, int current)
{
	//1.�ݹ�����������ԣ�
	int maxHeap = current;
	if (current == box.size())
		return box.size() - 1;
	for (int i = 0; i <= current; i++)
	{
		int sum = 0;
		for (int j = i + 1; j <= current; j++)
			sum += heap[j][1];
		//���ǵ���ĿҪ��Ӧ���Ǵ��ڻ��Ǵ��ڵ�����
		if (sum > (7 * heap[i][1]))
			return current - 1;
	}
	//2.�ݹ麯��
	for (int i = 0; i < box.size(); i++)
	{
		if (box[i][0] < heap[current][0] && box[i][2] == 0)
		{
			heap[current + 1][0] = box[i][0];
			heap[current + 1][1] = box[i][1];
			box[i][2] = 1;
			maxHeap = max(maxHeap, findbox(heap, box, current + 1));
			//���ݲ���
			box[i][2] = 0;
			heap[current + 1][0] = 0;
			heap[current + 1][1] = 0;
		}
	}
	return maxHeap;
}

int main4444()
{
	//1.���ݴ�����
	int m;
	int in;
	while (cin >> m)
	{
		//boxΪ��ľ���飬heapΪ�ѵĻ�ľ����
		vector<vector<int>> box(m);
		vector<vector<int>> heap(m);
		for (int i = 0; i < m; i++)
		{
			cin >> in;
			box[i].push_back(in);
		}
		for (int i = 0; i < m; i++)
		{
			cin >> in;
			box[i].push_back(in);
			box[i].push_back(0); //0��δʹ�ã�1��ʹ��
		}
		for (int i = 0; i < m; i++)
		{
			heap[i].push_back(0);
			heap[i].push_back(0);
		}

		//2.�㷨����
		int sumMax = 0;
		for (int i = 0; i < box.size(); i++)
		{
			//2.1 ��ʼ��ֵ��ѭ����ÿ��boxΪ���
			heap[0][0] = box[i][0];
			heap[0][1] = box[i][1];
			box[i][2] = 1;
			//2.2 �ݹ�ȡֵ
			sumMax = max(sumMax, findbox(heap, box, 0));
			//2.3 ��ԭ����
			for (auto &s : box)
				s[2] = 0;
			for (auto &s : heap)
			{
				s[0] = 0;
				s[1] = 0;
			}
		}
		//��1��ԭ������Ϊ�����Ǵ�0��ʼ��ģ��߶��Ǵ�1��ʼ���
		cout << sumMax + 1 << endl;
	}
	return 0;
}

//1 2 3 4 5 6 7 8 9 10
//1 1 1 1 1 1 1 1 1 10