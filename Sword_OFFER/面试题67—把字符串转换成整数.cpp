// 面试题67：把字符串转换成整数
// 题目：请你写一个函数StrToInt，实现把字符串转换成整数这个功能。当然，不
// 能使用atoi或者其他类似的库函数。

#include <iostream>
#include <string>
using namespace std;

//此题需要实现的功能有：
//1.StrToInt的核心操作：num = 10*num + minus*(*str - '0')
//2.边界条件INT数据溢出处理（0x7FFFFFFF，0x80000000）
//3.边界条件空字符串处理（*str == '\0'或index == str.size()）
//4.边界条件有无正负号与只有正负号（在最开始时判断首位是否为正负号，然后判断下一位是否合法）
//5.错误标志输出g_status（在C的atoi中，其在非法输入后会返回0同时将标志位置为InValid，注意）

class Solution 
{
public:
	enum Status { Valid, InValid };
	Status g_status;

	//首先是const char* 类型的StrToInt
	int StrToInt(const char* str) 
	{
		//0.基本初始化操作
		g_status = InValid;
		long long num = 0;

		//1.判断输入合法性（string类型无需在最后加上\0表示结尾，而char的所有类型都需要）
		if (str != nullptr && *str != '\0')
		{
			int minus = 1;
			//1.1判断首位是否为+-号，是则对minus进行处理再str++
			if (*str == '+')
				str++;
			else if (*str == '-')
			{
				str++;
				minus = -1;
			}
			//1.2判断当前位是否不为\0，不是则进入详细计算，是则等着被跳出吧
			if (*str != '\0')
				num = StrToIntCore(str, minus);
		}
		return static_cast<int>(num);
	}

	//2.实现函数核心转换
	long long StrToIntCore(const char* cur, int minus)
	{
		long long num = 0;
		while (*cur != '\0')
		{
			//2.1判断当前cur是否为合法数字0到9
			if (*cur >= '0' && *cur <= '9')
			{
				num = 10 * num + minus*(*cur - '0');  //核心实现功能代码
				//2.1.1判断当前string内数字是否超过了INT型的上限或下限（注意负数的0x80000000将其强制转换为整型int）
				if ((minus == 1 && num > 0x7FFFFFFF) || (minus == -1 && num < static_cast<int>(0x80000000)))
				{
					num = 0;
					break;
				}
				cur++;
			}
			//2.2不合法则直接GG
			else
			{
				num = 0;
				break;
			}
		}
		//3.判断当前位是否成功执行到了\0结束位，如果是则标识Valid，不是则保持默认InValid
		if (*cur == 0)
			g_status = Valid;
		return num;
	}


	//然后是string类型的str
	//运行时间：3ms，占用内存：456k
	int StrToInt(string str)
	{
		long long num = 0;
		long long size = str.size();
		g_status = InValid;

		if (str.size() > 0)
		{
			int minus = 1;
			int index = 0;
			if (str[index] == '+')
				index++;
			else if (str[index] == '-')
			{
				index++;
				minus = -1;
			}
			if (index < size)
				num = StrToIntCore(str, minus, index);
		}
		return static_cast<int>(num);
	}

	//string转int的核心函数
	long long StrToIntCore(string str,int minus, int index)
	{
		long long size = str.size();
		long long num = 0;
		while (index < size)
		{
			if (str[index] <= '9' && str[index] >= '0')
			{
				num = 10 * num + minus*(str[index++] - '0');
				if ((minus == 1 && num > 0x7FFFFFFF) && (minus == -1 && num < static_cast<int>(0x80000000)))
				{
					num = 0;
					break;
				}
			}
			else
			{
				num = 0;
				break;
			}
		}
		if (index == size)
			g_status = Valid;
		return num;
	}
};

// ====================测试代码====================
static void Test(const char* string)
{
	Solution s;
	int result = s.StrToInt(string);
	if (result == 0 && s.g_status == s.InValid)
		printf("the input %s is invalid.\n", string);
	else
		printf("number for %s is: %d.\n", string, result);
}

int main_offer67(int argc, char* argv[])
{
	Test(nullptr);

	Test("");

	Test("123");

	Test("+123");

	Test("-123");

	Test("1a33");

	Test("+0");

	Test("-0");

	//有效的最大正整数, 0x7FFFFFFF
	Test("+2147483647");

	Test("-2147483647");

	Test("+2147483648");

	//有效的最小负整数, 0x80000000
	Test("-2147483648");

	Test("+2147483649");

	Test("-2147483649");

	Test("+");

	Test("-");

	return 0;
}