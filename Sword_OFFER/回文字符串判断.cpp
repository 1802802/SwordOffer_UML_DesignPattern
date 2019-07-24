#include <iostream>
#include <string>
using namespace std;

//一个字符串的回文数判断（递归都是从大到小，只是有的规律在最小时找，有的在最大时找）
bool isPalindromeString1(string s)
{
	//1.递归基
	if (s.size() > 1)
	{
		if (s[0] != s[s.size() - 1])
			return false;
		else
			//线性递归
			return isPalindromeString1(s.substr(1, s.size() - 2));
	}
	return true;
}

//一个字符串的回文数循环，和递归基本一毛一样，都是从大到小
bool isPalindromeString2(string s)
{
	while (s.size() > 1)
	{
		if (s[0] != s[s.size() - 1])
			return false;
		else
			s = s.substr(1, s.size() - 2);
	}
	return true;
}


int main_isPalindromeString()
{
	string s;
	while (cin >> s)
	{
		if (isPalindromeString1(s))
			cout << "true" << endl;
		else
			cout << "false" << endl;

		if (isPalindromeString2(s))
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}

	return 0;
}