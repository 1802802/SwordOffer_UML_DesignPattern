//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int main_zjtd333()
{
	int N, n;
	while (cin >> N)
	{
		vector<int> save;
		while (N--)
		{
			cin >> n;
			save.push_back(n);
		}
		int sum = 1;
		int cur = 1;
		int i = 1;
		
		//��ʼΪ����Ŀ��ǣ��ҵ���һ������
		for (; i < save.size() - 1; i++)
		{
			if (save[i] < save[i - 1] && save[i] < save[i + 1])
				break;
		}

		for (int j = i; j > 0;)
		{
			while (j > 0 && save[j] < save[j - 1])
			{
				cur++;
				sum += cur;
				j--;
			}
			while (j > 0 && save[j] == save[j - 1])
			{
				sum += cur;
				j--;
			}
		}

		i++;
		cur = 1; 	

		//����ֻ�����˳�ʼΪ������ƽ�µ����������Ҫ���ǳ�ʼΪ����
		while (i < save.size())
		{
			while (i < save.size() && save[i - 1] < save[i])
			{
				cur++;
				sum += cur;
				i++;
			}
			while (i < save.size() && save[i - 1] == save[i])
			{
				sum += cur;
				i++;
			}
			while (i < save.size() && save[i - 1] > save[i])
			{
				cur--;
				if (cur <= 0)
					cur = 1;
				sum += cur;
				i++;
			}
		}
		cout << sum * 100 << endl;
	}

	return 0;
}