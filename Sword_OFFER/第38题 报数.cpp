#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <vector>    
using namespace std;

class Solution
{
public:
	string countAndSay(int n)
	{
		string result = "1";
		if (n == 1)
			return "1";	
		while (n-- != 1)
		{
			int lo = 0;
			string cur_result = "";
			while (lo <= result.size() - 1)
			{
				int same_cnt = 1;
				while (lo < result.size() - 1 && result[lo + 1] == result[lo])
				{
					same_cnt++;
					lo++;
				}
				cur_result.append(to_string(same_cnt * 10 + result[lo] - '0'));
				lo++;
			}
			cout << cur_result << endl;
			result = cur_result;
		}
		return result;
	}
};

int main_leecode38()
{
	Solution s;
	cout << s.countAndSay(5) << endl;

	return 0;
}