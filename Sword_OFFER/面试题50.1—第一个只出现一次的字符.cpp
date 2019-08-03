// 面试题50.1—第一个只出现一次的字符
// 题目：在一个字符串(0<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符，
// 并返回它的位置,如果没有则返回 -1（需要区分大小写）.
#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution 
{
public:
	//1.使用数据结构的配合（可以选择所有出现位置存起来空间换时间，也可以选择只存次数然后去找）
	//运行时间：4ms，占用内存：480k
	//使用unordered_map为运行时间：5ms，占用内存：492k
	int FirstNotRepeatingChar(string str) 
	{
		map<char, int> save;
		for (auto &s : str)
			if (!save.insert({ s,1 }).second)
				save[s]++;
		for (int i = 0; i < str.size(); i++)
		{
			if (save[str[i]] == 1)
				return i;
		}
		return -1;
	}

	//2.用数组自定义一个哈希表（数组为256位存储所有的ASCII码）
	//运行时间：3ms，占用内存：484k，这样会快一点
	int FirstNotRepeatingChar2(string str)
	{
		//注意，在char型被用作int型使用时，其自动转换为对应的ASCII码编制
		vector<int> save(256, 0);
		for (auto &s : str)
			save[s]++;
		for (int i = 0; i < str.size(); i++)
		{
			if (save[str[i]] == 1)
				return i;
		}
		return -1;
	}
};

int main_offer50_1()
{
	string a;
	Solution s;
	while (cin >> a)
		cout << "find:" << s.FirstNotRepeatingChar(a) << endl;

	return 0;
}