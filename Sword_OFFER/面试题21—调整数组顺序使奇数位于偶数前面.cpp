// 面试题21—调整数组顺序使奇数位于偶数前面
// 题目：输入一个整数数组，实现一个函数来调整该数组中数字的顺序，
// 使得所有的奇数位于数组的前半部分，所有的偶数位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。

#include <iostream>
#include <vector>
using namespace std;

class Solution 
{
public:
	//1.（自己瞎写的思想）先写个无脑的做法O(n2)，运行时间：3ms，占用内存：480k
	//还可以时间换空间用数组存偶数再插入之类的，时间O(n)，空间O(n)
	//还可以用归并排序的思想做，复杂度O(nlogn)，不过实现起来有点小麻烦
	void reOrderArray1(vector<int> &array) 
	{
		if (array.size() == 0)
			return;
		//核心在于swapnum = array.size() - 1这句限制交换次数，可以实现功能的同时完成稳定交换
		int swapnum = array.size() - 1;
		for (int i = 0; i < array.size(); i++)
		{
			while (!(array[i] & 0x1) && swapnum)
			{
				int temp = array[i];
				for (int j = i; j < array.size() - 1; j++)
					array[j] = array[j + 1];
				array[array.size() - 1] = temp;
				swapnum--;
			}
		}
	}

	//2.插入排序的思想：从小往后不断抽牌，当为奇数时判断前面的偶数往其后面插入（常规为：如果当前的数小于前面的数，则前面的数赋值给当前数）
	//运行时间：3ms，占用内存：468k
	void reOrderArray2(vector<int> &array)
	{
		if (array.size() == 0)
			return;
		for (int i = 1, j; i < array.size(); i++)
		{
			//下面这个判断条件很关键，当array[i]为奇数时才去尝试交换偶数，使排序变稳定
			if ((array[i] & 0x1) == 1)
			{
				int temp = array[i];
				//如果j-1是偶数，则将该偶数向前换（相比标准的插入排序，仅更改了判断条件）
				for (j = i; j > 0 && (array[j - 1] & 0x1) == 0; j--)
					array[j] = array[j - 1];
				array[j] = temp;
			}
		}
	}

	//3.如果用归并排序，可以实现O(nlogn)的时间复杂度，在此先不写

	//4.不稳定的写法，时间为O(n)
	void reOrderArray3(vector<int> &array)
	{
		if (array.size() == 0)
			return;
		//2.1双指针，一头一尾
		int i = 0; int j = array.size() - 1;
		while (i < j)
		{
			//2.2头指针向后移动直到遇到偶数
			while (i < j && (array[i] & 0x1) == 1)
				i++;
			//2.3尾指针向前移动直到遇到奇数
			while (i < j && (array[j] & 0x1) == 0)
				j--;
			//2.4如果偶数在奇数的前后，那么交换
			if (i < j)
			{
				swap(array[i], array[j]);
			}
		}
	}
};

// ====================测试代码====================
void PrintArray(int numbers[], int length)
{
	if (length < 0)
		return;

	for (int i = 0; i < length; ++i)
		printf("%d\t", numbers[i]);

	printf("\n");
}

void Test(char* testName, int numbers[], int length)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	vector<int> copy;
	for (int i = 0; i < length; ++i)
	{
		copy.push_back(numbers[i]);
	}
	Solution s;
	printf("Test for solution 1:\n");
	PrintArray(numbers, length);
	s.reOrderArray2(copy);
	for (auto &s : copy)
		cout << s << "       ";
	cout << endl;

	//printf("Test for solution 2:\n");
	//PrintArray(copy, length);
	//ReorderOddEven_2(copy, length);
	//PrintArray(copy, length);
}

static void Test1()
{
	int numbers[] = { 1, 2, 3, 4, 5, 6, 7 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int));
}

static void Test2()
{
	int numbers[] = { 2, 4, 6, 1, 3, 5, 7 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int));
}

static void Test3()
{
	int numbers[] = { 1, 3, 5, 7, 2, 4, 6 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int));
}

static void Test4()
{
	int numbers[] = { 1 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int));
}

static void Test5()
{
	int numbers[] = { 2 };
	Test("Test5", numbers, sizeof(numbers) / sizeof(int));
}

static void Test6()
{
	Test("Test6", nullptr, 0);
}

int main_offer21(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}