#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <vector>    
using namespace std;

class Solution
{
public:
	string longestCommonPrefix(vector<string>& strs)
	{
		if (strs.empty())
			return "";
		string minstr = strs[0];
		for (auto &s : strs)
			minstr = min(minstr, s);
		int minsize = minstr.size();
		if (minsize == 0)
			return "";
		string prefix;
		prefix.push_back(minstr[0]);
		for (int i = 0; i < minsize;)
		{
			for (auto &s : strs)
			{
				if (s[i] != prefix[i])
				{
					prefix.pop_back();
					return prefix;
				}
			}
			prefix.push_back(minstr[++i]);
		}
		prefix.pop_back();
		return prefix;
	}
};

class Solution2
{
public:
	string longestCommonPrefix(vector<string>& strs)
	{
		if (strs.empty())
			return "";
		string minstr = strs[0];
		for (auto &s : strs)
			minstr = min(minstr, s);
		for (int i = 0; i < minstr.size(); i++)
		{
			for (auto &s : strs)
			{
				if (s[i] != minstr[i])
					return minstr.substr(0, i);
			}
		}
		return minstr;
	}
};

int main_leecode14()
{
	Solution2 s;
	vector<string> temp({ "flower","flow","flight" });
	cout << s.longestCommonPrefix(temp) << endl;
	return 0;
}