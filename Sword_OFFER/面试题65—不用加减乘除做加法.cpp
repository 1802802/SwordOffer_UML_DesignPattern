// 面试题65：不用加减乘除做加法
// 题目：写一个函数，求两个整数之和，要求在函数体内不得使用＋、－、×、÷
// 四则运算符号。

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "BinaryTree.h"
using namespace std;

//思路：位运算实现加减乘除
class Solution 
{
public:
/*
位的异或运算跟求"和"的结果一致：
异或 1^1=0 1^0=1 0^0=0
求和 1+1=0 1+0=1 0+0=0

位的与运算后<<1的结果跟求"进位"的结果一致：
位与 1&1=1 1&0=0 0&0=0
进位 1+1=1 1+0=0 0+0=0

而二进制加法分为三步：（如1001+1011，9+11=20）
① 各位相加但不计进位，得到00010；（该结果即为1001与1011的^结果）
② 记下所被略去的进位，得到10010；（该结果即为1001与1011的&结果<<1后的结果）
③ 将①与②相加，得到10100，即为20
但是由于无法使用加法，所以最后的两个10两者无法直接相加得到100，需要通过循环重复①与②步骤来实现加法
（循环终止的条件与递归的终止条件相同，都是当②计算所得到的进位为0即停止计算）

所以，可以将异或的值作为当前的值s，而当进位c存在时，将其前移一位，用于和之后的s继续进行^与&运算
*/

	//1.两种加法运算，运行时间：3ms，占用内存：468k
	int Add(int num1, int num2)
	{
		int sum, carry;
		while (num2 != 0)
		{
			//sum是和，而carry是进位，sum表示计算的①，carry表示计算的②，不断地进行①与②，直到②为0
			sum = num1^num2;
			carry = (num1&num2) << 1;
			num1 = sum;
			num2 = carry;
		}
		return num1;
	}

	int Add2(int num1, int num2)
	{
		if (num2 == 0)
			return num1;
		int sum = num1^num2;
		int carry = (num1&num2) << 1;
		Add2(sum, carry);
	}

	//2.一种减法运算
	int Negtive(int num1, int num2)
	{
		//减法即num1+(-num2),注意计算机用补码存的，所以-num2 = ~(num2 - 1) = ~num2 + 1 = Add(~num2,1)
		return Add(num1, Add(~num2, 1));
	}

	//3.一种乘法运算（首先将乘数与被乘数弄为正数，最后再添加符号，而实现过程按照小学乘法算法实施）
	int Multiply(int num1, int num2)
	{
		if (num2 == 0 || num1 == 0)
			return 0;
		//先将被乘数与乘数全部弄为正数
		int multiplicand = (num1 < 0) ? (Add(~num1, 1)) : num1;
		int multiplier = (num2 < 0) ? (Add(~num2, 1)) : num2;
		int multip = 0;
		while (multiplier > 0)
		{
			//如果最后一位是1，则进行加运算
			if (multiplier & 0x1 == 1)
				multip = Add(multip, multiplicand);
			//无论是否进行了加运算，都将被乘数左移一位，乘数右移一位
			multiplicand <<= 1;
			multiplier >>= 1;
		}
		//恢复符号，num1^num2为负值时表示两者异号，相乘必为负值
		//（注意<优先级高于^，记得加括号）
		if ((num1^num2) < 0)
			multip = Add(~multip, 1);
		return multip;
	}

	//4.一种除法运算
	//计算机是一个二元的世界，所有的int型数据都可以用[2 ^ 0, 21, ..., 2^31]这样一组基来表示
	//（int型最高31位）。不难想到用除数的2^31, 2^30, ..., 2^2, 2^1, 2^0倍尝试去减被除数，
	//如果减得动，则把相应的倍数加到商中；如果减不动，则依次尝试更小的倍数。这样就可以快速逼近最终的结果。
	
	////在此特别提醒，对于C++的除法来说，其原则在于使商尽量去乘除数后去匹配被除数（其根两数的同符号与异符号时均有不同）

	int Divide(int num1, int num2)
	{
		if (num1 == 0)
			return 0;
		if (num2 == 0)
			return 0;
			//throw new exception("error");
		//先将被除数与除数全部弄为正数
		int dividend = (num1 < 0) ? (Add(~num1, 1)) : num1;
		int divider = (num2 < 0) ? (Add(~num2, 1)) : num2;
		int quotient = 0;	//商
		int remainder = 0;	//余数
		//遍历31到0，实现除数的快速运算
		for (int i = 31; i >= 0; i--)
		{
			//注意这里的dividend与divider比较，是将dividend右移i位而不是将divider左移i位
			//目的在于避免divider左移i位后有些数据丢帧
			if ((dividend >> i) >= divider)
			{
				//如果(dividend >> i) >= divider，表示dividend除divide的值大于1<<i，则将1左移i位并加入到商中
				//此时表示从dividend中减去了1<<i个divide，所以dividend的值也跟着更新
				quotient = Add(quotient, 1 << i);
				dividend = Negtive(dividend, divider << i);
			}
		}
		//恢复商符号，符号相反时，商必为负数，否则为正数
		//恢复余数符号，注意余数是根据最后被减没了的dividend实现的，而其符号根据被除数与除数的符号性相匹配
		if ((num1^num2) < 0)
		{
			quotient = Add(~quotient, 1);
			if (num1 < 0)
				remainder = Add(~dividend, 1);
			else
				remainder = dividend;
		}
		else
			//当符号相同时，根据任一数的符号即可确定余数符号
			remainder = (num1 < 0) ? (Add(~dividend, 1)) : (dividend);

		cout << quotient << endl;
		cout << remainder << endl;
		//cout << -11 / 5 << endl;
		//cout << -11 % 5 << endl;
		//cout << 11 / -5 << endl;
		//cout << 11 % -5 << endl;
		return quotient;
	}
};

// ====================测试代码====================
static void Test(int num1, int num2, int expected)
{
	Solution s;
	int result = s.Divide(num1, num2);
	if (result == expected)
		printf("%d + %d is %d. Passed\n", num1, num2, result);
	else
		printf("%d + %d is %d. FAILED\n", num1, num2, result);
}

int main_offer65(int argc, char* argv[])
{
	Test(1, 2, 3);
	Test(111, 899, 1010);

	Test(-1, 2, 1);
	Test(1, -2, -1);

	Test(3, 0, 3);
	Test(0, -4, -4);

	Test(-2, -8, -10);
	Test(-10, -5, 2);
	Test(11, -5, 2);

	return 0;
}