#include <iostream>
using namespace std;

//牛客网都是3ms，384K
//菲波那切数列问题
class Solution1 
{
public:
	int Fibonacci(int n)
	{
		return [&n]() {int f = 1, s = 0; while (n--) { s = f + s; f = s - f; } return s; }();
	}
};

//跳台阶问题，就是斐波那契问题，比标准的前移了一位，用一个常规的动态规划写法写
class Solution 
{
public:
	int jumpFloor(int number) 
	{
		int first = 1;      //f(-1)
		int second = 0;		//f(0)
		while (number--)
		{
			second = first + second;
			first = second - first;
		}
		return second;
	}
};

//变态跳台阶问题，使用数学归纳法得到其通项公式为an = 2^(n-1)
//牛客网3ms，460K
class Solution2
{
public:
	int jumpFloorII(int number)
	{
		return 1 << (number - 1);
	}
};