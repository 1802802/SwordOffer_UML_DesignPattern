// 面试题41—数据流中的中位数
// 题目：如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。
// 如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。
// 我们使用Insert()方法读取数据流，使用GetMedian()方法获取当前读取数据的中位数。

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//本题的核心关键：是对于堆的实现两种方式（vector的make_heap等函数实现，priority_queue优先队列的实现）
//1，vector的实现，需要在push_back之后及时push_heap，在pop_heap之后及时pop_back（pop_heap之后，原队首元素被替换到了队尾，需要pop掉）
//2，priority_queue的实现，与queue的操作方式基本相似（其默认为升序排列的大顶堆），对于优先级队列来说，其默认为less(a<b)大顶堆，不过其top和pop为容器的末尾而非首端
//不过对于编译器所看到的来说，heap[0]就是堆顶

class Solution
{
public:
	//1.采用书上的解法，使用一个最大堆（左leftHeap）和最小堆（右rightHeap），运行时间：3ms，占用内存：356k
	//数据总数是偶数时先插入最小堆（右）（然后将其top插入leftHeap），奇数时先插入最大堆（左）（然后将其top插入rightHeap）
	void Insert(int num)
	{
		//1.1数据总数为奇数时，插入leftHeap
		if ((leftHeap.size() + rightHeap.size()) & 0x1)
		{
			//注意heap的比较函数为优先级比较，所以a<b时为升序排列
			//注意vetor的堆结构，每次push之后要push_heap重新处理堆结构，而每次pop_heap后会将之后的堆顶移到堆尾，记得pop掉
			leftHeap.push_back(num);
			push_heap(leftHeap.begin(), leftHeap.end(), [](int a, int b) {return a < b; });
			if (leftHeap.size() > 1)
			{
				num = leftHeap[0];
				pop_heap(leftHeap.begin(), leftHeap.end(), [](int a, int b) {return a < b; });
				leftHeap.pop_back();
				rightHeap.push_back(num);
				push_heap(rightHeap.begin(), rightHeap.end(), [](int a, int b) {return a > b; });
			}
		}
		//1.2数据总数为偶数时，插入rightHeap，然后取其top（当前最小值）进入leftHeap
		else
		{
			//注意vetor的堆结构，每次push之后要push_heap重新处理堆结构，而每次pop_heap后会将之后的堆顶移到堆尾，记得pop掉
			rightHeap.push_back(num);
			push_heap(rightHeap.begin(), rightHeap.end(), [](int a, int b) {return a > b; });
			if (rightHeap.size() > 1)
			{
				num = rightHeap[0];
				pop_heap(rightHeap.begin(), rightHeap.end(), [](int a, int b) {return a > b; });
				rightHeap.pop_back();
				leftHeap.push_back(num);
				push_heap(leftHeap.begin(), leftHeap.end(), [](int a, int b) {return a < b; });
			}
		}
	}

	double GetMedian()
	{
		int size = leftHeap.size() + rightHeap.size();
		if (size == 0)
			return 0.0;
		if (size == 1)
			return rightHeap[0];
		double median = 0.0;
		//数据总数为奇数时，取最大堆（leftHeap）的堆顶（原因在于上文的这种取值方法leftHeap往往会多1个）
		if (size & 0x1)
			median = leftHeap[0];
		else
			median = (leftHeap[0] + rightHeap[0]) / 2.0;

		return median;
	}
private:
	vector<int> leftHeap;
	vector<int> rightHeap;
};

struct intComp   //实现小顶堆的似函数类
{
	//对于比较函数，写a>b，表示降序排列，即大前小后（小的先出队），a<b为降序排列，小前大后（大的先出队）
	//但是priority_queue的pop和top是最骚的，它们的值并非是传统认为的数据容器第一个数，而是最后一个数，这就是为什么降序为小的先出队，升序是大的先出队
	//不过说是上面这么说是针对vector存储方式的，真正在内存中存储时，上面理论的top和pop仍然表示为heap[0]
	bool operator() (const double& lhs, const double& rhs) const { return lhs > rhs; };
};

class Solution2
{
public:
	//2.做法与solution1相同，区别是这次使用优先队列priority_queue来实现leftHeap与rightHeap，
	// 本地过不了，牛客网为运行时间：3ms，占用内存：472k
	void Insert(int num)
	{
		//1.1数据总数为奇数时，插入leftHeap
		if ((leftHeap.size() + rightHeap.size()) & 0x1)
		{
			//注意vetor的堆结构，每次push之后要push_heap重新处理堆结构，而每次pop_heap后会将之后的堆顶移到堆尾，记得pop掉
			leftHeap.push(num);
			if (leftHeap.size() > 1)
			{
				num = leftHeap.top();
				leftHeap.pop();
				rightHeap.push(num);
			}
		}
		//1.2数据总数为偶数时，插入rightHeap，然后取其top（当前最小值）进入leftHeap
		else
		{
			rightHeap.push(num);
			if (rightHeap.size() > 1)
			{
				num = rightHeap.top();
				rightHeap.pop();
				leftHeap.push(num);
			}
		}
	}

	double GetMedian()
	{
		int size = leftHeap.size() + rightHeap.size();
		if (size == 0)
			return 0.0;
		if (size == 1)
			return rightHeap.top();
		double median = 0.0;
		
		//数据总数为奇数时，取最大堆（leftHeap）的堆顶（原因在于上文的这种取值方法leftHeap往往会多1个）
		if (size & 0x1)
			median = leftHeap.top();
		else
			median = (leftHeap.top() + rightHeap.top()) / 2.0;

		return median;
	}
private:
	priority_queue<double> leftHeap;
	priority_queue<double, vector<double>, intComp> rightHeap;
};

// ====================测试代码====================
static void Test(char* testName, Solution& numbers, double expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	cout << abs(numbers.GetMedian()) << " " << expected << endl;
	if (abs(numbers.GetMedian() - expected) < 0.0000001)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

int main_offer41(int argc, char* argv[])
{
	Solution numbers;

	printf("Test1 begins: ");
	try
	{
		numbers.GetMedian();
		printf("FAILED.\n");
	}
	catch (const exception&)
	{
		printf("Passed.\n");
	}

	numbers.Insert(5);
	Test("Test2", numbers, 5);

	numbers.Insert(2);
	Test("Test3", numbers, 3.5);

	numbers.Insert(3);
	Test("Test4", numbers, 3);

	numbers.Insert(4);
	Test("Test6", numbers, 3.5);

	numbers.Insert(1);
	Test("Test5", numbers, 3);

	numbers.Insert(6);
	Test("Test7", numbers, 3.5);

	numbers.Insert(7);
	Test("Test8", numbers, 4);

	numbers.Insert(0);
	Test("Test9", numbers, 3.5);

	numbers.Insert(8);
	Test("Test10", numbers, 4);

	vector<int> a = { 1,2,3,4,5,6,3 };
	make_heap(a.begin(), a.end(), [](int a, int b) {return a > b; }); 
	for (auto &s : a)
		cout << s << " ";
	cout << endl;

	priority_queue<int> b;
	b.push(1);
	b.push(2);
	b.push(4);
	b.push(8);
	cout << b.top() << endl;

	return 0;
}