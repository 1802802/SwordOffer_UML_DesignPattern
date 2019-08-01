// ������41���������е���λ��
// ��Ŀ����εõ�һ���������е���λ����������������ж�����������ֵ����ô��λ������������ֵ����֮��λ���м����ֵ��
// ������������ж���ż������ֵ����ô��λ������������ֵ����֮���м���������ƽ��ֵ��
// ����ʹ��Insert()������ȡ��������ʹ��GetMedian()������ȡ��ǰ��ȡ���ݵ���λ����

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//����ĺ��Ĺؼ����Ƕ��ڶѵ�ʵ�����ַ�ʽ��vector��make_heap�Ⱥ���ʵ�֣�priority_queue���ȶ��е�ʵ�֣�
//1��vector��ʵ�֣���Ҫ��push_back֮��ʱpush_heap����pop_heap֮��ʱpop_back��pop_heap֮��ԭ����Ԫ�ر��滻���˶�β����Ҫpop����
//2��priority_queue��ʵ�֣���queue�Ĳ�����ʽ�������ƣ���Ĭ��Ϊ�������еĴ󶥶ѣ����������ȼ�������˵����Ĭ��Ϊless(a<b)�󶥶ѣ�������top��popΪ������ĩβ�����׶�
//�������ڱ���������������˵��heap[0]���ǶѶ�

class Solution
{
public:
	//1.�������ϵĽⷨ��ʹ��һ�����ѣ���leftHeap������С�ѣ���rightHeap��������ʱ�䣺3ms��ռ���ڴ棺356k
	//����������ż��ʱ�Ȳ�����С�ѣ��ң���Ȼ����top����leftHeap��������ʱ�Ȳ������ѣ��󣩣�Ȼ����top����rightHeap��
	void Insert(int num)
	{
		//1.1��������Ϊ����ʱ������leftHeap
		if ((leftHeap.size() + rightHeap.size()) & 0x1)
		{
			//ע��heap�ıȽϺ���Ϊ���ȼ��Ƚϣ�����a<bʱΪ��������
			//ע��vetor�Ķѽṹ��ÿ��push֮��Ҫpush_heap���´���ѽṹ����ÿ��pop_heap��Ὣ֮��ĶѶ��Ƶ���β���ǵ�pop��
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
		//1.2��������Ϊż��ʱ������rightHeap��Ȼ��ȡ��top����ǰ��Сֵ������leftHeap
		else
		{
			//ע��vetor�Ķѽṹ��ÿ��push֮��Ҫpush_heap���´���ѽṹ����ÿ��pop_heap��Ὣ֮��ĶѶ��Ƶ���β���ǵ�pop��
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
		//��������Ϊ����ʱ��ȡ���ѣ�leftHeap���ĶѶ���ԭ���������ĵ�����ȡֵ����leftHeap�������1����
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

struct intComp   //ʵ��С���ѵ��ƺ�����
{
	//���ڱȽϺ�����дa>b����ʾ�������У�����ǰС��С���ȳ��ӣ���a<bΪ�������У�Сǰ��󣨴���ȳ��ӣ�
	//����priority_queue��pop��top����ɧ�ģ����ǵ�ֵ�����Ǵ�ͳ��Ϊ������������һ�������������һ�����������Ϊʲô����ΪС���ȳ��ӣ������Ǵ���ȳ���
	//����˵��������ô˵�����vector�洢��ʽ�ģ��������ڴ��д洢ʱ���������۵�top��pop��Ȼ��ʾΪheap[0]
	bool operator() (const double& lhs, const double& rhs) const { return lhs > rhs; };
};

class Solution2
{
public:
	//2.������solution1��ͬ�����������ʹ�����ȶ���priority_queue��ʵ��leftHeap��rightHeap��
	// ���ع����ˣ�ţ����Ϊ����ʱ�䣺3ms��ռ���ڴ棺472k
	void Insert(int num)
	{
		//1.1��������Ϊ����ʱ������leftHeap
		if ((leftHeap.size() + rightHeap.size()) & 0x1)
		{
			//ע��vetor�Ķѽṹ��ÿ��push֮��Ҫpush_heap���´���ѽṹ����ÿ��pop_heap��Ὣ֮��ĶѶ��Ƶ���β���ǵ�pop��
			leftHeap.push(num);
			if (leftHeap.size() > 1)
			{
				num = leftHeap.top();
				leftHeap.pop();
				rightHeap.push(num);
			}
		}
		//1.2��������Ϊż��ʱ������rightHeap��Ȼ��ȡ��top����ǰ��Сֵ������leftHeap
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
		
		//��������Ϊ����ʱ��ȡ���ѣ�leftHeap���ĶѶ���ԭ���������ĵ�����ȡֵ����leftHeap�������1����
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

// ====================���Դ���====================
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