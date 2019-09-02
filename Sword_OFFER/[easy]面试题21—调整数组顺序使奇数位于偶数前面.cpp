// ������21����������˳��ʹ����λ��ż��ǰ��
// ��Ŀ������һ���������飬ʵ��һ�����������������������ֵ�˳��
// ʹ�����е�����λ�������ǰ�벿�֣����е�ż��λ������ĺ�벿�֣�����֤������������ż����ż��֮������λ�ò��䡣

#include <iostream>
#include <vector>
using namespace std;

class Solution 
{
public:
	//1.���Լ�Ϲд��˼�룩��д�����Ե�����O(n2)������ʱ�䣺3ms��ռ���ڴ棺480k
	//������ʱ�任�ռ��������ż���ٲ���֮��ģ�ʱ��O(n)���ռ�O(n)
	//�������ù鲢�����˼���������Ӷ�O(nlogn)������ʵ�������е�С�鷳
	void reOrderArray1(vector<int> &array) 
	{
		if (array.size() == 0)
			return;
		//��������swapnum = array.size() - 1������ƽ�������������ʵ�ֹ��ܵ�ͬʱ����ȶ�����
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

	//2.���������˼�룺��С���󲻶ϳ��ƣ���Ϊ����ʱ�ж�ǰ���ż�����������루����Ϊ�������ǰ����С��ǰ���������ǰ�������ֵ����ǰ����
	//����ʱ�䣺3ms��ռ���ڴ棺468k
	void reOrderArray2(vector<int> &array)
	{
		if (array.size() == 0)
			return;
		for (int i = 1, j; i < array.size(); i++)
		{
			//��������ж������ܹؼ�����array[i]Ϊ����ʱ��ȥ���Խ���ż����ʹ������ȶ�
			if ((array[i] & 0x1) == 1)
			{
				int temp = array[i];
				//���j-1��ż�����򽫸�ż����ǰ������ȱ�׼�Ĳ������򣬽��������ж�������
				for (j = i; j > 0 && (array[j - 1] & 0x1) == 0; j--)
					array[j] = array[j - 1];
				array[j] = temp;
			}
		}
	}

	//3.����ù鲢���򣬿���ʵ��O(nlogn)��ʱ�临�Ӷȣ��ڴ��Ȳ�д

	//4.���ȶ���д����ʱ��ΪO(n)
	void reOrderArray3(vector<int> &array)
	{
		if (array.size() == 0)
			return;
		//2.1˫ָ�룬һͷһβ
		int i = 0; int j = array.size() - 1;
		while (i < j)
		{
			//2.2ͷָ������ƶ�ֱ������ż��
			while (i < j && (array[i] & 0x1) == 1)
				i++;
			//2.3βָ����ǰ�ƶ�ֱ����������
			while (i < j && (array[j] & 0x1) == 0)
				j--;
			//2.4���ż����������ǰ����ô����
			if (i < j)
			{
				swap(array[i], array[j]);
			}
		}
	}
};

// ====================���Դ���====================
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