#include <iostream>
#include <set>
using namespace std;

//题目有两种情况：可以修改数组以及不能修改数组

//1.暴力枚举，时间复杂度O(n2)，空间复杂度O(1)，牛客网运行时间4ms，内存500K
bool duplicate1(int numbers[], int length, int* duplication) 
{
	for (int i = 0; i < length; i++)
	{
		for (int j = i; j < length; j++)
		{
			if (numbers[i] == numbers[j] && i != j)
			{
				*duplication = numbers[i];
				return true;
			}
		}
	}
	return false;
}

//2.利用哈希表/散列函数map的特性，即只能存储一种数据，时间复杂度O(n)，空间复杂度O(n)，牛客网运行时间4ms，内存350K—500K
bool duplicate2(int numbers[], int length, int* duplication)
{
	set<int> number;
	for (int i = 0; i < length; i++)
	{
		auto temp = number.insert(numbers[i]);
		if (!temp.second)
		{
			*duplication = numbers[i];
			return true;
		}
	}
	return false;
}

//3.书上的解法，下标比对法，时间复杂度O(n)，空间复杂度O(1)，牛客网时间4ms，内存600K
bool duplicate3(int numbers[], int length, int* duplication)
{
	//1.保护数组为空或长度输入错误时
	if (numbers == nullptr || length <= 0)
		return false;
	//2.保护数组中的数据不符合题目条件，值小于0或大于n-1时
	for (int i = 0; i < length; i++)
		if (numbers[i] < 0 || numbers[i] > length - 1)
			return false;
	//3.正式的下标对比法流程，遍历数组中的所有数据
	for (int i = 0; i < length; i++)
	{
		//3.1 当前数据不等于对应其所处的位置时，进行进一步判断
		while (numbers[i] != i)
		{
			//3.2 当不处于自身位置的数据，与处于自身位置的数据相等，则表示有两个数相等
			if (numbers[i] == numbers[numbers[i]])
			{
				*duplication = numbers[i];
				return true;
			}
			//3.3 如果不等于，则将当前的数据换到属于其自己的位置上去
			else
			{
				swap(numbers[i], numbers[numbers[i]]);
			}
		}
	}
	return false;
}