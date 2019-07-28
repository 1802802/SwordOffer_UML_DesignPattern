//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int main111()
{
	string a;
	string b;
	int n;
	while (getline(cin, a))
	{
		//1.���ݴ���
		getline(cin, b);
		vector<int> avector;
		vector<int> bvector;
		istringstream input1(a);	
		while (input1 >> n)
			avector.push_back(n);
		istringstream input2(b);
		while (input2 >> n)
			bvector.push_back(n);

		//2.�㷨ʵ��
		int errorPlace = -1;
		int findNum = -1;
		int prevNum = INT_MIN;
		int postNum = INT_MAX;

		//2.1����λ�ò���
		for (int i = 1; i < avector.size(); i++)
		{
			if (avector[i] < avector[i - 1])
			{
				errorPlace = i;
				prevNum = avector[i - 1];
				if ((i + 1) < avector.size())
					postNum = avector[i + 1];
			}
		}

		//2.2�Ҳ���errorPlace������
		if (errorPlace == -1)
		{
			cout << "NO" << endl;
			continue;
		}


		//2.3�ҵ���������B��Ѱ�ҷ������������ֵ
		sort(bvector.begin(), bvector.end());
		
		for (int i = 0; i < bvector.size(); i++)
		{
			if (bvector[i] >= prevNum && bvector[i] <= postNum)
				findNum = bvector[i];
		}

		//2.4�Ҳ���findNum������
		if (findNum == -1)
		{
			cout << "NO" << endl;
			continue;
		}

		//2.5������ֵ�޸Ĳ����
		avector[errorPlace] = findNum;
		for (auto &s : avector)
			cout << s << " ";
		cout << endl;
	}
	return 0;
}

//1 3 7 4 10
//2 1 5 8 9