//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int main_wangyi333()
{
	int T;
	string input;
	cin >> T;
	while (T--)
	{
		cin >> input;
		vector<int> save;
		int count_N = 0;
		int count_noN = 0;

		//1.��input�ַ��������ݴ���
		for (int i = 0; i < input.size();)
		{
			if (input[i] == 'N')
			{
				i++;
				count_N++;
			}
			else
			{
				save.push_back(count_N);
				count_N = 0;
				for (; i < input.size();)
				{
					if (input[i] != 'N')
					{
						i++;
						count_noN++;
					}
					else
					{
						save.push_back(count_noN);
						count_noN = 0;
						break;
					}
				}
			}
		}
		if (count_N != 0)
		{
			save.push_back(count_N);
			count_N = 0;
		}
		if (count_noN != 0)
		{
			save.push_back(count_noN);
			count_noN = 0;
		}
		save.push_back(0);

		//2.ʵ���㷨
		int maxLength = -999;
		int size = save.size();
		for (int i = 0; i < size; i += 2)
		{
			//��ȫ�����
			if (i - 2 > 0)
			{
				int temp = save[i];
				int flag = 2;
				if (save[i - 1] <= flag)
				{
					temp += save[i - 2];
					temp += save[i - 1];
					flag -= save[i - 1];
				}
				if ((i - 4 > 0) && (save[i - 3] <= flag))
				{
					temp += save[i - 4];
					temp += save[i - 3];
					flag -= save[i - 3];
				}
				maxLength = max(maxLength, temp);
			}

			//��ȫ���ұ�
			if (i + 2 < size)
			{
				int temp = save[i];
				int flag = 2;
				if (save[i + 1] <= flag)
				{
					temp += save[i + 2];
					temp += save[i + 1];
					flag -= save[i + 1];
				}
				if ((i + 4 < size) && (save[i + 3] <= flag))
				{
					temp += save[i + 4];
					temp += save[i + 3];
					flag -= save[i + 3];
				}
				maxLength = max(maxLength, temp);
			}

			//�����������
			if ((i + 2) < size)
			{
				int temp = save[i];
				int flag = 2;
				if (save[i + 1] <= flag)
				{
					temp += save[i + 2];
					temp += save[i + 1];
					flag -= save[i + 1];
				}
				if ((i - 2 > 0) && (save[i - 1] <= flag))
				{
					temp += save[i - 2];
					temp += save[i - 1];
					flag -= save[i - 1];
				}
				maxLength = max(maxLength, temp);
			}

			//�����������
			if ((i - 2) > 0)
			{
				int temp = save[i];
				int flag = 2;
				if (save[i - 1] <= flag)
				{
					temp += save[i - 2];
					temp += save[i - 1];
					flag -= save[i - 1];
				}
				if ((i + 2 < size) && (save[i + 1] <= flag))
				{
					temp += save[i + 2];
					temp += save[i + 1];
					flag -= save[i + 1];
				}
				maxLength = max(maxLength, temp);
			}

			maxLength = max(save[i], maxLength);
		}
		cout << maxLength << endl;
	}
	return 0;
}


//������AC����
//˼��Ϊ˫ָ����϶�̬���ڵ�˼��
#include<iostream>
#include<cstring>
using namespace std;

int main_wangyi2020_333() 
{
	int T;
	cin >> T;
	string s;
	while (T--)
	{
		cin >> s;
		int len = s.size();
		//iΪǰָ�룬jΪ��ָ�룬flagΪ�޸Ĵ���
		int flag = 2, i = 0, j = 0, ans = 0;
		while (j < len)
		{
			if (s[j] == 'N')   
				j++;
			else 
			{
				if (flag > 0)
				{ 
					flag--; j++; 
				}
				else
				{
					ans = max(ans, j - i);
					//����ǰj��λN���޸Ĵ�������ʱ����¼��ǰ���ڴ�С����ǰ��iֱ�����ͷ�һ��flag��j������ǰ
					while (flag == 0)
					{
						if (s[i] == 'N')   
							i++;
						else 
						{ 
							i++; flag++; break; 
						}
					}
				}
			}
		}
		//��ס����ʱҲҪ����һ��
		ans = max(ans, j - i);
		cout << ans << endl;
	}
	return 0;
}