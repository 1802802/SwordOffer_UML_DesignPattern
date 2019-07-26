// 面试题20—表示数值的字符串
// 题目：请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
// 例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。 
// 但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。
// 运行时间：5ms，占用内存：496k

#include <iostream>
#include <vector>
using namespace std;

class Solution 
{
public:
	//数值的表示格式：A[.[B]][e|EC] 与 .[B]][e|EC] ，其中AC为整数，B为无符号数
	//判断思路如下：先找A类型，再判断有无B类型（与A类型判断结果结合），最后判断C类型（与AB类型判断结果结合）
	//此题还有一个核心问题，就是在函数传递时传递的是string指针的地址而不是指针本身，因为要通过函数的内部来实现string地址的后移

	bool isNumeric(char* string)
	{
		if (string == nullptr)
			return false;
		//1.由于初始值为数字最多，所以首先判断当前的开头是否存在数字，有则numeric为true，否则为false
		bool numeric = scanInt(&string);
		//2.在第一步过后，str的位置必然为'.'或'\0'或'e\E'
		if (*string == '.')
		{
			++string;
			// 下面一行代码用||的原因：所以其true/false是随着数据的变化而变化的
			// 1. 小数可以没有整数部分，例如.123等于0.123；
			// 2. 小数点后面可以没有数字，例如233.等于233.0；
			// 3. 当然小数点前面和后面可以有数字，例如233.666
			numeric = scanUnsignedInt(&string) || numeric;
		}

		if (*string == 'e' || *string == 'E')
		{
			++string;
			// 下面一行代码用&&的原因：所以其true/false是随着数据的变化而变化的
			// 1. 当e或E前面没有数字时，整个字符串不能表示数字，例如.e1、e1；
			// 2. 当e或E后面没有整数时，整个字符串不能表示数字，例如12e、12e+5.4
			numeric = numeric && scanInt(&string);
		}
		//最后判断有没有扫描到头
		return numeric && (*string == '\0');
	}

	//用于判断A与C类型的数字是否存在（去除符号后使用B的判断）
	bool scanInt(char** str)
	{
		if (**str == '+' || **str == '-')
			++(*str);
		return scanUnsignedInt(str);
	}

	//用于判断B类型的数字是否存在（无符号数的判断）
	bool scanUnsignedInt(char** str)
	{
		const char* before = *str;
		while (**str != '\0' && **str >= '0' && **str <= '9')
			++(*str);
		//到此时，str必然不是数字，而可能是e/E或.或\0，判断str是否移动了，移动了返回true，未移动表示没有数字0-9，返回false
		return (*str == before) ? (false) : (true);
	}
};



// ====================测试代码====================
void Test(const char* testName,char* str, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);
	Solution s;
	if (s.isNumeric(str) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}


int main_offer20(int argc, char* argv[])
{
	Test("Test1", "100", true);
	Test("Test2", "123.45e+6", true);
	Test("Test3", "+500", true);
	Test("Test4", "5e2", true);
	Test("Test5", "3.1416", true);
	Test("Test6", "600.", true);
	Test("Test7", "-.123", true);
	Test("Test8", "-1E-16", true);
	Test("Test9", "1.79769313486232E+308", true);

	printf("\n\n");

	Test("Test10", "12e", false);
	Test("Test11", "1a3.14", false);
	Test("Test12", "1+23", false);
	Test("Test13", "1.2.3", false);
	Test("Test14", "+-5", false);
	Test("Test15", "12e+5.4", false);
	Test("Test16", ".", false);
	Test("Test17", ".e1", false);
	Test("Test18", "e1", false);
	Test("Test19", "+.", false);
	Test("Test20", "", false);
	Test("Test21", nullptr, false);

	return 0;
}