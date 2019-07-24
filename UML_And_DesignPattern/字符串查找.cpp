#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

//�ж϶��ַ������Ƿ���ڳ��ַ����г���
int main_1_1()
{
	bool istrue = false;
	string shorts, longs;
	while (cin >> shorts >> longs)
	{
		if (shorts.size() > longs.size())
		{
			cout << "false" << endl;
			continue;
		}
		for (auto &s1 : shorts)
		{
			auto temp = longs.find(s1);
			if (temp != longs.npos)
			{
				int i = 0;
				for (; i < shorts.size(); i++)
				{
					if (longs[temp + i] != shorts[i])
						break;
				}
				if(i == shorts.size())
					istrue = true;
			}
		}
		if (istrue)
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}
	return 0;
}

//�ж϶��ַ����е������ַ��Ƿ���ڳ��ַ����г���
int main_1_2()   //ÿ���ַ�����һ�飬�����е��
{
	string shorts, longs;
	while (cin >> shorts >> longs)
	{
		if (shorts.size() > longs.size())
		{
			cout << "false" << endl;
			continue;
		}
		int num = 0;
		for (auto &s1 : shorts)
		{
			if (longs.find(s1) == longs.npos)
				continue;
			else
				num++;
		}
		if (num == shorts.size())
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}
	return 0;
}

int main_1_3()   //��set�ĵ�һ�Դ棬Ȼ���
{
	string shorts, longs;
	while (cin >> shorts >> longs)
	{
		if (shorts.size() > longs.size())
		{
			cout << "false" << endl;
			continue;
		}
		int num = 0;
		set<char> save;
		for (auto &s1 : shorts)
			save.insert(s1);
		for (auto &s2 : save)
		{
			if (longs.find(s2) == longs.npos)
				break;
			else
				num++;
		}
		if (num == save.size())
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}
	return 0;
}