#include <iostream>
using namespace std;

class Solution 
{
public:
	//1.常规解法，考虑到整数的正负情况，选择左移标志位，而不是右移源数据
	//牛客网：运行时间：5ms，占用内存：376k
	int NumberOf1(int n) 
	{
		int count = 0;
		int flag = 1;
		while (flag)
		{
			//逐位判断n中的当前位置是否为1，是则+1
			if (flag & n)
				count++;
			flag <<= 1;
		}
		return count;
	}
	//2.思想解法：(n-1)&n，即可将n最右边的1去掉，通过不断地去1直到n为0（速度比上一种快，因为可以定点删1）
	//牛客网 运行时间：3ms，占用内存：480k
	int NumberOf2(int n)
	{
		int count = 0;
		while (n)
		{
			count++;
			n = (n - 1)&n;
		}
		return count;
	}
};

// ====================测试代码====================
static void Test(int number, unsigned int expected)
{
	Solution s;
	int actual = s.NumberOf1(number);
	if (actual == expected)
		printf("Solution1: Test for %p passed.\n", number);
	else
		printf("Solution1: Test for %p failed.\n", number);

	actual = s.NumberOf2(number);
	if (actual == expected)
		printf("Solution2: Test for %p passed.\n", number);
	else
		printf("Solution2: Test for %p failed.\n", number);

	printf("\n");
}

int main(int argc, char* argv[])
{
	// 输入0，期待的输出是0
	Test(0, 0);

	// 输入1，期待的输出是1
	Test(1, 1);

	// 输入10，期待的输出是2
	Test(10, 2);

	// 输入0x7FFFFFFF，期待的输出是31
	Test(0x7FFFFFFF, 31);

	// 输入0xFFFFFFFF（负数），期待的输出是32
	Test(0xFFFFFFFF, 32);

	// 输入0x80000000（负数），期待的输出是1
	Test(0x80000000, 1);

	return 0;
}