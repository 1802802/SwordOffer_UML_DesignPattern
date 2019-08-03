// 面试题51—数组中的逆序对
// 题目：在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。
// 输入一个数组,求出这个数组中的逆序对的总数P。并将P对1000000007取模的结果输出。 即输出P%1000000007
#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

//下面写了个归排

class Solution
{
public:
	//思路：问题就是归并排序的变种，所谓的逆序和就是计算归并排序过程中的交换次数
	//牛客网：运行时间：116ms，占用内存：4324k

	//1.函数1，外接函数，用于向内部的归并算法提供参数
	int InversePairs(vector<int>& data)
	{
		if (data.size() < 2)
			return 0;
		count = 0;
		int mi = (0 + data.size()) / 2;
		mergesort(data, 0, data.size());
		cout << "count:" << count << endl;
		//注意题目要求的取模
		return count;
	}

private:
	//2.函数2，归并排序主函数，用于实现对区间的二分递归操作（mergesort一直划分，直到所有数据为单）
	void mergesort(vector<int>& data, int lo, int hi)
	{
		//递归基
		if (hi - lo < 2)
			return;
		int mi = (hi + lo) / 2;
		mergesort(data, lo, mi);
		mergesort(data, mi, hi);
		merge(data, lo, mi, hi);
	}

	//3.函数3，对数据的比较与排序的函数，在每个mergesort的最后执行此函数进行排序，所以参与其排序的总数往往是2的倍数附近的数
	void merge(vector<int>& data, int lo, int mi, int hi)
	{
		//此处将i1作为temp的下标，i2作为数组data[lo, mi - 1]的下标，i3作为数组data[mi, hi - 1]的下标
		int temp_i1 = 0, left_i2 = lo, right_i3 = mi;
		vector<int> temp(hi - lo, 0);

		//将优美的归并排序算法拆开变成普通的归并排序算法（先把某个区间转完，然后统一转另一个区间）
		while (left_i2 < mi && right_i3 < hi)
		{
			if (data[left_i2] <= data[right_i3])
				temp[temp_i1++] = data[left_i2++];
			else 
			{
				temp[temp_i1++] = data[right_i3++];
				//最秀的操作集中于这一行代码，意思是对应每个右区间中的值，其对应的逆序对的个数为当前left_i2与其后面的所有数
				count += mi - left_i2; //（可这样理解，678 456，对于4和5来说678都是逆序对，但是对于6来说只有78和是，也就是left_i2与其后面的所有数
				count %= 1000000007;   //注意取模，不然通不过牛客网
			}
		}
		//当某个区间被换完后，用没换完的另一个区间补齐
		while (left_i2 < mi)
			temp[temp_i1++] = data[left_i2++];
		while (right_i3 < hi)
			temp[temp_i1++] = data[right_i3++];

		//将temp的数据赋值data实现排序更改
		for (int i = 0; i < hi - lo; i++)
			data[i + lo] = temp[i];
	}
private:
	//归并排序的辅助数组，必须使用
	int count;
};

// ====================测试代码====================
static void Test(char* testName, vector<int> data, int length, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);
	Solution s;
	//cout << "s.InversePairs(data)" << s.InversePairs(data) << endl;
	if (s.InversePairs(data) == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

static void Test1()
{
	vector<int> data = { 1, 2, 3, 4, 7, 6, 5 };
	int expected = 3;

	Test("Test1", data, sizeof(data) / sizeof(int), expected);
}

// 递减排序数组
static void Test2()
{
	vector<int> data = { 6, 5, 4, 3, 2, 1 };
	int expected = 15;

	Test("Test2", data, sizeof(data) / sizeof(int), expected);
}

// 递增排序数组
static void Test3()
{
	vector<int> data = { 1, 2, 3, 4, 5, 6 };
	int expected = 0;

	Test("Test3", data, sizeof(data) / sizeof(int), expected);
}

// 数组中只有一个数字
static void Test4()
{
	vector<int> data = { 1 };
	int expected = 0;

	Test("Test4", data, sizeof(data) / sizeof(int), expected);
}


// 数组中只有两个数字，递增排序
static void Test5()
{
	vector<int> data = { 1, 2 };
	int expected = 0;

	Test("Test5", data, sizeof(data) / sizeof(int), expected);
}

// 数组中只有两个数字，递减排序
static void Test6()
{
	vector<int> data = { 2, 1 };
	int expected = 1;

	Test("Test6", data, sizeof(data) / sizeof(int), expected);
}

// 数组中有相等的数字
static void Test7()
{
	vector<int> data = { 1, 2, 1, 2, 1 };
	int expected = 3;

	Test("Test7", data, sizeof(data) / sizeof(int), expected);
}

static void Test8()
{
	int expected = 0;

	Test("Test8", vector<int>(), 0, expected);
}

int main_offer51(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	Test8();

	return 0;
}


class Solution2 
{
public:
	//思路：归并排序思想，将所有数组分割成各个单一部分，然后在比较中不断地合并数组，最后不断地和合并后的数组比较
	
	int InversePairs(vector<int>& data) 
	{

		if (data.size() < 2)
			return 0;
		int mi = (0 + data.size()) / 2;

		mergesort(data, 0, data.size());

		return 0;
	}

	static void mergesort(vector<int>& data, int lo, int hi)
	{
		//只有两个以上的数据才参与比较
		if (hi - lo < 2)
			return;
		int mi = (lo + hi) / 2;
		mergesort(data, lo, mi);
		mergesort(data, mi, hi);
		merge(data, lo, mi, hi);
	}
	//对数据的比较与排序的函数
	static void merge(vector<int>& data, int lo, int mi, int hi)
	{
		//此处将i1作为temp的下标，i2作为数组data[lo, mi - 1]的下标，i3作为数组data[mi, hi - 1]的下标
		int i1 = 0, i2 = lo, i3 = mi;

		int* temp = new int[hi - lo];
		//从data分割的前后两个数组不断的相互比较，较小值进入temp，然后对应的区间下标++；
		//如果达到某个区间全部比较完（下标到达上界），则另一个数组的元素按顺序进temp
		while ((i2 < mi) || (i3 < hi))
		{
			//归并排序的初始指针i2与i3指向均为左右两区间的头位置，随着不断地向temp数组中赋值而移动

			//下面的判断语句的意思为：左边条件初始往往为true，而右边的判断i3 < hi为第一位，当出现i3 == hi
			//此时表示右区间已满，所以继续执行左区间的赋值语句（前后条件的放置与括号顺序相当讲究）
			if ((i2 < mi) && (!(i3 < hi) || (data[i2] <= data[i3])))
				temp[i1++] = data[i2++];
			//右区间的判断与左区间基本相同
			if ((i3 < hi) && (!(i2 < mi) || (data[i2] > data[i3])))
				temp[i1++] = data[i3++];
		}

		//这里的赋值是将临时数组temp存储的排序值传递进data中原本应该对应的区间内，temp内的数值大小恒定为hi-lo
		for (int i = 0; i < hi - lo; i++)				
		{
			//所排序的区间均为[lo,hi]区间，所以data[i+lo]为temp中所排序的每个数值对应的真实数值
			data[i + lo] = temp[i];					
		}
		delete[] temp;
	}
private:
	//归并排序的辅助数组，必须使用
	int temp[];
};