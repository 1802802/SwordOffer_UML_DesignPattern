/*
�ڶ��⣺
���룺�����������
��һ��������������T��N���ֱ����Ǯ������ʳ��������
��������N�У�ÿ��������������ai, bi, ci(1 <= i <= N) ��������ʳ�ļ۸���ʳ������ȡ���ʳ������
����������������
case:input
	100 2
	1 1 1
	1 1 1
	100 3
	26 100 4
	5 1 4
	5 2 2
	output
	2
	306
*/

//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int main_dajiang2020_2_1()
{
	int N, T;
	while (cin >> N >> T)
	{
		double v, l, c;
		vector<vector<int>> save(N);
		for (int i = 0; i < N; i++)
		{
			cin >> v; cin >> l; cin >> c;
			save[i].push_back(v);
			save[i].push_back(l);
			save[i].push_back(c);
		}
		bool flag = true;
		for (auto &s : save)
		{
			if (s[0] <= T)
				flag = false;
		}
		if (flag)
		{
			cout << 0 << endl;
			continue;
		}

		int currentll = 0;
		//̰�ļ���
		while (true)
		{
			int maxnum = INT_MAX;
			int maxc = 0;

			for (int i = 0; i < save.size(); i++)
			{
				if (((save[i][0] / save[i][1]) < maxnum) && save[i][2] != 0 && save[i][0] < T)
				{
					maxnum = save[i][0] / save[i][1];
					maxc = i;
				}
			}
			if (maxnum == INT_MAX)
			{
				cout << currentll << endl;
				break;
			}
			currentll += save[maxc][1];
			save[maxc][2]--;
			T -= save[maxc][0];
			if (T <= 0)
			{
				cout << currentll << endl;
				break;
			}
		}


	}

	return 0;
}

struct backpack
{
	int p;  //�۸�  
	int sat;  //�����
} 
item[2001];   // ��ʳ�б�

int main_dajiang2020_2_2()  //���ر�������Ķ����Ʋ�ֽⷨ
{
	int money, num;						//money��ʾ��Ǯ����num��ʾ��ʳ������  
	int index = 0;
	int price, satisDegree, curNum;		//��ֺ���ʳ������ ��ֵ�Ŀ���ǽ���ʱ�临�Ӷ�
	int i, j;  int c;					//�������Ż��ķ��� 
	cin >> money >> num;
	for (i = 1; i <= num; i++)
	{
		c = 1;
		cin >> price >> satisDegree >> curNum;       //price��ʾ�۸�satisDegree��ʾ����ȣ�curNum��ʾ����ʳ��������  
		while (curNum - c > 0)     // 1 2 4 8 (1-15) 
		{
			curNum -= c;
			item[++index].p = c*price;
			item[index].sat = c*satisDegree;
			c *= 2;
		}
		item[++index].p = price*curNum;  //���䲻��ָ���Ĳ�ֵ  
		item[index].sat = satisDegree*curNum;
	}
	vector<int> dp(money + 1);   //dp[i]����Ǯ��Ϊi��ʱ���õ���������  
	for (i = 1; i <= index; i++)   //�Բ�ֺ����Ʒ����0-1����  
	{
		for (j = money; j >= item[i].p; j--)
			dp[j] = max(dp[j], dp[j - item[i].p] + item[i].sat);
	}
	printf("%d/money", dp[money]);
	return 0;
}
/*
2 10
1 1 1
1 1 1
3 100
26 100 4
5 1 4
5 2 2
*/