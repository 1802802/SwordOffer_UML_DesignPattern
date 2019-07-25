// 面试题17：打印1到最大的n位数
// 题目：输入数字n，按顺序打印出从1最大的n位十进制数。比如输入3，则
// 打印出1、2、3一直到最大的3位数即999。

/*
本题核心思想：
（1）将1到n的位数打印问题，快速地理解为n个从0到9的全排列问题，那么就可以进入试探回溯法（多路递归）的流程；
（2）这种“打印”的题，往往对应的数值难以直接求出，在打印时多用下巧妙的技巧，而不是一定要算出数字
（3）对于很长的n位字符串的打印，往往很难通过int这样的数字存储实现，所以需要字符串来存储其位数
*/


#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
	//1.常规实现，未考虑位数，当n大于5时就GG
	void Print1ToMaxOfNDigits_1(int n)
	{
		int max = 0;
		for (int i = 0; i < n; i++)
			max += 9 * pow(10, i);
		for (int i = 1; i <= max; i++)
			cout << i << endl;
	}

	//2.高级实现，通过字符串来存储与运算数字(太麻烦了，我放弃)，然后打印
	//3.全排列实现：将n位的所有十进制数，理解为n个从0到9的全排列即可
	void Print1ToMaxOfNDigits_2(int n)
	{
		if (n <= 0)
		{
			cout << "输入的数字n错误" << endl;
			return;
		}
		//3.1建立存储用的字符串
		char* number = new char[n + 1];
		number[n] = '\0';

		//3.2从第0位开始，执行0到9的全排列
		for (int i = 0; i < 10; i++)
		{
			number[0] = i + '0';
			Print1ToMaxOfNDigitsRecursively(number, n, 0);
		}

		delete[] number;
	}

	void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index)
	{
		//递归基，当全排列执行到最后的个位时（如921的1）时，打印出字符串并返回
		if (index == length - 1)
		{
			printNumber(number);
			return;
		}
		//多路递归函数，这是一种试探回溯的思想。从第0位到第n-1位不断地进行全排列
		for (int i = 0; i < 10; i++)
		{
			number[index + 1] = i + '0';
			Print1ToMaxOfNDigitsRecursively(number, length, index + 1);
		}
	}

	void printNumber(char* number)
	{
		int index = 0;
		//先将索引定位到不为0的位置
		while (index < strlen(number) && number[index] == '0')
			index++;
		//然后从不为0的位置开始向后打印
		while (index < strlen(number))
			cout << (number[index++]);
		cout << endl;
	}
};


// ====================测试代码====================
void Test(int n)
{
	Solution s;
	printf("Test for %d begins:\n", n);

	s.Print1ToMaxOfNDigits_1(n);
	s.Print1ToMaxOfNDigits_2(n);

	printf("\nTest for %d ends.\n", n);
}

int main_offer17(int argc, char* argv[])
{
	Test(1);
	Test(2);
	Test(3);
	Test(0);
	Test(-1);

	return 0;
}