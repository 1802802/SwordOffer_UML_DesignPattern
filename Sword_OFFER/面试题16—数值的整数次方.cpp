#include <iostream>
using namespace std;

/*
本题核心思想：
（1）输入参数的合法判断，以及对于这些信息的传递方式；
（2）对于double类型的各种限制，比如不能用==0.0，需要用fabs等，精度判断方式：fabs(n-0.0)<0.000001
（3）对于次方运算的快速运算方式：通过判断n为偶数还是奇数来计算，以及当次数为负数时的倒数处理
直接a^n = a^(n/2)*a^(n/2) (偶数even)或 a^n = a^((n-1)/2)*a^((n-1)/2)*a (奇数odd）
（4）对于判断奇数/偶数的操作：将数n & (0x1)，得到的数要么是1要么是0
*/


class Solution 
{
public:
	bool g_InvalidInput = false;
	//1.基础做法，一般实现。牛客网4ms，460K
	double Power(double base, int exponent) 
	{
		g_InvalidInput = false;
		//1.首先判断输入的base是否为0.0，
		if (fabs(base - 0.0) < 0.0000001 && exponent < 0)
		{
			g_InvalidInput = true;
			cout << "base为0时，exponent不能小于0" << endl;
			return 0.0;
		}
		double result = 1.0;
		//2.对输入的次方进行int型处理
		unsigned int absExponent = abs(exponent);
		//3.进行pow的计算流程
		for (int i = 0; i < absExponent; i++)
			result *= base;
		//4.根据exponent本身的大小进行数据美化
		if (exponent < 0)
			result = 1.0 / result;
		return result;
	}

	//2.优化做法。优化了result的计算过程，运行时间：3ms，占用内存：364k
	double Power2(double base, int exponent)
	{
		g_InvalidInput = false;
		//1.首先判断输入的base是否为0.0，
		if (fabs(base - 0.0) < 0.0000001 && exponent < 0)
		{
			g_InvalidInput = true;
			cout << "base为0时，exponent不能小于0" << endl;
			return 0.0;
		}
		//2.对输入的次方进行int型处理（除2）
		unsigned int absExponent = abs(exponent);
		//3.进行pow的计算流程
		double result = calculate(base, absExponent);
		//4.根据exponent本身的大小进行数据美化
		if (exponent < 0)
			result = 1.0 / result;
		return result;
	}

	double calculate(double base, unsigned int exponent)
	{
		if (exponent == 0)
			return 1;
		if (exponent == 1)
			return base;
		//递归的快速实现次方运算
		double result = calculate(base, exponent >> 1);
		//判断次数是奇数还是偶数
		if (exponent & 0x1 == 1)
			result = result*result*base;
		else
			result = result*result;
		return result;
	}
};

int main_offer16()
{
	Solution s;
	cout << s.Power2(2, -3) << endl;

	return 0;
}