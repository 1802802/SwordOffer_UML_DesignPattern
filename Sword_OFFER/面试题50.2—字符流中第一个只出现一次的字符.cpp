// 面试题50.2—字符流中第一个只出现一次的字符
// 题目：在一个字符串(0<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符，
// 并返回它的位置,如果没有则返回 -1（需要区分大小写）.
#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

class CharStatistics
{
public:
	//思路：用char进行流输入，在每次输入后进行打印（或者用某个容器存储，类似于hash表的存储过程）
	void FirstAppearingOnce(stringstream& input)
	{
		char str;
		string totalStr;
		vector<int> save(256, 0);
		while (input >> str)
		{
			save[str]++;
			totalStr += str;
			for (int i = 0; i < totalStr.size(); i++)
			{
				if (save[totalStr[i]] == 1)
				{
					cout << totalStr[i] << " ";
					break;
				}
			}
		}
	}
};

// ====================测试代码====================

int main_offer50_2(int argc, char* argv[])
{
	CharStatistics s;
	stringstream input;
	input << "asadf dw w 3 fws 22 ";
	s.FirstAppearingOnce(input);

	return 0;
}