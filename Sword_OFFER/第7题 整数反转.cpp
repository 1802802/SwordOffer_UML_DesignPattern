#include <iostream>
using namespace std;

class Solution {
public:
	int reverse(int x) {
		int minus = 1;
		if (x < 0)
			minus = -1;
		int a[32] = { 0 };
		int i = 0;
		while (x)
		{
			a[i++] = (x % 10);
			x /= 10;
		}
		long long num = 0;
		for (int j = 0; j < i; j++)
		{
			num = num * 10 + a[j];
			if (minus == 1 && num >(int)0x7FFFFFFF || minus == -1 && num < (int)0x80000000)
				return 0;
		}
		return num;
	}
};

int main_leecode7()
{
	Solution s;
	cout << s.reverse(-123) << endl;

	return 0;
}