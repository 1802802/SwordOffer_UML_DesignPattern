// 面试题44—1到n整数中1出现的个数
// 题目：数字以0123456789101112131415…的格式序列化到一个字符序列中。在这
// 个序列中，第5位（从0开始计数）是5，第13位是1，第19位是4，等等。请写一
// 个函数求任意位对应的数字。

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int digitAtIndex(int index)
{
	if (index < 0)
		return -1;
	if (index == 0)
		return 0;
	if (index == 1)
		return 1;
	//1.找到当前数字位于哪个位数区间
	//num表示当前位数起始位置，i表示当前的位数值，indexPlace表示所处的数字，indexOffset为该数字的偏移量
	int num = 1;
	int i = 1;
	int indexPlace = 0;
	int indexOffset = 0;
	while (index > num)
	{
		//indexPlace 和 indexOffset 需要在每个循环里进行计算，因为每个数的起始点和位数都不相同
		indexPlace = (index - num) / i;
		indexOffset = (index - num) % i;
		num += i * 9 * pow(10, i - 1);
		i++;
	}
	i--;
	//2.根据i的大小计算其位于区间中的哪个数的位置
	int indexStatus = pow(10, i - 1) + indexPlace;
	string tmp = to_string(indexStatus);
	return tmp[indexOffset] - '0';
}

// ====================测试代码====================
void test(const char* testName, int inputIndex, int expectedOutput)
{
	if (digitAtIndex(inputIndex) == expectedOutput)
		cout << testName << " passed." << endl;
	else
		cout << testName << " FAILED." << endl;
}


int main_offer44()
{
	int a;
	//while (cin >> a)
	//	cout << digitAtIndex(a) << endl;
	test("Test1", 0, 0);
	test("Test2", 1, 1);
	test("Test3", 9, 9);
	test("Test4", 10, 1);
	test("Test5", 189, 9);  // 数字99的最后一位，9
	test("Test6", 190, 1);  // 数字100的第一位，1
	test("Test7", 1000, 3); // 数字370的第一位，3
	test("Test8", 1001, 7); // 数字370的第二位，7
	test("Test9", 1002, 0); // 数字370的第三位，0
	return 0;
}