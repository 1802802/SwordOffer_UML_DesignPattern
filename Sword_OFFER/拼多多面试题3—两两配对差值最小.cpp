/*
��Ŀ��
����һ������Ϊż��������arr�����������е�����������Բ���ͣ�����Щ����ѡ��������Сֵ��
���ʸ����������ԣ����������ֵ����Сֵ�Ĳ�ֵ��С��

��������:
һ��2�����롣
��һ��Ϊһ������n��2<=n<=10000, �ڶ���Ϊn���������Ŀ�����飬ÿ�������ڵ���2��С�ڵ���100��

�������:
�����С�Ĳ�ֵ��
*/


//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//˼·���Ƚ����е����ִ�������Ȼ��������Ÿ���������С��������������ұߣ�ֱ�������С��ԣ�ȡ����е����ֵ����Сֵ���������

int main_pinduoduo2019_3()
{
	int n, m;
	cin >> n;
	vector<int> save;
	while (n--)
	{
		cin >> m;
		save.push_back(m);
	}
	
	sort(save.begin(), save.end());
	int maxSum = INT_MIN;
	int minSum = INT_MAX;
	for (int i = 0; i < save.size() / 2; i++)
	{
		maxSum = max(maxSum, save[i] + save[save.size() - 1 - i]);
		minSum = min(minSum, save[i] + save[save.size() - 1 - i]);
	}
	cout << maxSum - minSum << endl;

	return 0;
}