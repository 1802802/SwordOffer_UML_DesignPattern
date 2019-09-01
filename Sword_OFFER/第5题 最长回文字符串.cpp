#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

class Solution
{
public:
	//������չ�㷨���ɣ�ʱ�临�Ӷ�O(n2)���ռ临�Ӷ�O(1)
	string longestPalindrome(string s)
	{
		int maxlen = 0;
		string maxstr = "";
		for (int i = 0; i < s.size(); i++)
		{
			//��������λ�ã��Ե�ǰλ��������չ���뵱ǰλ�ü������λ����������չ������len1��Ϊ������len2��Ϊż�������Զ���maxstr������ѡȡ��С����
			int len1 = expandCenterNum(s, i, i);
			int len2 = expandCenterNum(s, i, i + 1);
			if (maxlen < max(len1, len2))
			{
				maxlen = max(len1, len2);
				maxstr = s.substr(i - ((maxlen - 1) >> 1), maxlen);
			}
		}
		return maxstr;
	}

	int expandCenterNum(string& s, int lo, int hi)
	{
		while (lo >= 0 && hi < s.size() && s[lo] == s[hi])
		{
			lo--;
			hi++;
		}
		return hi - lo - 1;
	}
};