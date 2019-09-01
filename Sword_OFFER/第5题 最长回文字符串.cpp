#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

class Solution
{
public:
	//中心扩展算法即可，时间复杂度O(n2)，空间复杂度O(1)
	string longestPalindrome(string s)
	{
		int maxlen = 0;
		string maxstr = "";
		for (int i = 0; i < s.size(); i++)
		{
			//遍历所有位置，以当前位置中心扩展，与当前位置加其后面位置再中心扩展。其中len1必为奇数，len2必为偶数，所以对于maxstr中起点的选取有小技巧
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