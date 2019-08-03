// ������51�������е������
// ��Ŀ���������е��������֣����ǰ��һ�����ִ��ں�������֣����������������һ������ԡ�
// ����һ������,�����������е�����Ե�����P������P��1000000007ȡģ�Ľ������� �����P%1000000007
#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

//����д�˸�����

class Solution
{
public:
	//˼·��������ǹ鲢����ı��֣���ν������;��Ǽ���鲢��������еĽ�������
	//ţ����������ʱ�䣺116ms��ռ���ڴ棺4324k

	//1.����1����Ӻ������������ڲ��Ĺ鲢�㷨�ṩ����
	int InversePairs(vector<int>& data)
	{
		if (data.size() < 2)
			return 0;
		count = 0;
		int mi = (0 + data.size()) / 2;
		mergesort(data, 0, data.size());
		cout << "count:" << count << endl;
		//ע����ĿҪ���ȡģ
		return count;
	}

private:
	//2.����2���鲢����������������ʵ�ֶ�����Ķ��ֵݹ������mergesortһֱ���֣�ֱ����������Ϊ����
	void mergesort(vector<int>& data, int lo, int hi)
	{
		//�ݹ��
		if (hi - lo < 2)
			return;
		int mi = (hi + lo) / 2;
		mergesort(data, lo, mi);
		mergesort(data, mi, hi);
		merge(data, lo, mi, hi);
	}

	//3.����3�������ݵıȽ�������ĺ�������ÿ��mergesort�����ִ�д˺��������������Բ��������������������2�ı�����������
	void merge(vector<int>& data, int lo, int mi, int hi)
	{
		//�˴���i1��Ϊtemp���±꣬i2��Ϊ����data[lo, mi - 1]���±꣬i3��Ϊ����data[mi, hi - 1]���±�
		int temp_i1 = 0, left_i2 = lo, right_i3 = mi;
		vector<int> temp(hi - lo, 0);

		//�������Ĺ鲢�����㷨�𿪱����ͨ�Ĺ鲢�����㷨���Ȱ�ĳ������ת�꣬Ȼ��ͳһת��һ�����䣩
		while (left_i2 < mi && right_i3 < hi)
		{
			if (data[left_i2] <= data[right_i3])
				temp[temp_i1++] = data[left_i2++];
			else 
			{
				temp[temp_i1++] = data[right_i3++];
				//����Ĳ�����������һ�д��룬��˼�Ƕ�Ӧÿ���������е�ֵ�����Ӧ������Եĸ���Ϊ��ǰleft_i2��������������
				count += mi - left_i2; //����������⣬678 456������4��5��˵678��������ԣ����Ƕ���6��˵ֻ��78���ǣ�Ҳ����left_i2��������������
				count %= 1000000007;   //ע��ȡģ����Ȼͨ����ţ����
			}
		}
		//��ĳ�����䱻�������û�������һ�����䲹��
		while (left_i2 < mi)
			temp[temp_i1++] = data[left_i2++];
		while (right_i3 < hi)
			temp[temp_i1++] = data[right_i3++];

		//��temp�����ݸ�ֵdataʵ���������
		for (int i = 0; i < hi - lo; i++)
			data[i + lo] = temp[i];
	}
private:
	//�鲢����ĸ������飬����ʹ��
	int count;
};

// ====================���Դ���====================
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

// �ݼ���������
static void Test2()
{
	vector<int> data = { 6, 5, 4, 3, 2, 1 };
	int expected = 15;

	Test("Test2", data, sizeof(data) / sizeof(int), expected);
}

// ������������
static void Test3()
{
	vector<int> data = { 1, 2, 3, 4, 5, 6 };
	int expected = 0;

	Test("Test3", data, sizeof(data) / sizeof(int), expected);
}

// ������ֻ��һ������
static void Test4()
{
	vector<int> data = { 1 };
	int expected = 0;

	Test("Test4", data, sizeof(data) / sizeof(int), expected);
}


// ������ֻ���������֣���������
static void Test5()
{
	vector<int> data = { 1, 2 };
	int expected = 0;

	Test("Test5", data, sizeof(data) / sizeof(int), expected);
}

// ������ֻ���������֣��ݼ�����
static void Test6()
{
	vector<int> data = { 2, 1 };
	int expected = 1;

	Test("Test6", data, sizeof(data) / sizeof(int), expected);
}

// ����������ȵ�����
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
	//˼·���鲢����˼�룬����������ָ�ɸ�����һ���֣�Ȼ���ڱȽ��в��ϵغϲ����飬��󲻶ϵغͺϲ��������Ƚ�
	
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
		//ֻ���������ϵ����ݲŲ���Ƚ�
		if (hi - lo < 2)
			return;
		int mi = (lo + hi) / 2;
		mergesort(data, lo, mi);
		mergesort(data, mi, hi);
		merge(data, lo, mi, hi);
	}
	//�����ݵıȽ�������ĺ���
	static void merge(vector<int>& data, int lo, int mi, int hi)
	{
		//�˴���i1��Ϊtemp���±꣬i2��Ϊ����data[lo, mi - 1]���±꣬i3��Ϊ����data[mi, hi - 1]���±�
		int i1 = 0, i2 = lo, i3 = mi;

		int* temp = new int[hi - lo];
		//��data�ָ��ǰ���������鲻�ϵ��໥�Ƚϣ���Сֵ����temp��Ȼ���Ӧ�������±�++��
		//����ﵽĳ������ȫ���Ƚ��꣨�±굽���Ͻ磩������һ�������Ԫ�ذ�˳���temp
		while ((i2 < mi) || (i3 < hi))
		{
			//�鲢����ĳ�ʼָ��i2��i3ָ���Ϊ�����������ͷλ�ã����Ų��ϵ���temp�����и�ֵ���ƶ�

			//������ж�������˼Ϊ�����������ʼ����Ϊtrue�����ұߵ��ж�i3 < hiΪ��һλ��������i3 == hi
			//��ʱ��ʾ���������������Լ���ִ��������ĸ�ֵ��䣨ǰ�������ķ���������˳���൱������
			if ((i2 < mi) && (!(i3 < hi) || (data[i2] <= data[i3])))
				temp[i1++] = data[i2++];
			//��������ж��������������ͬ
			if ((i3 < hi) && (!(i2 < mi) || (data[i2] > data[i3])))
				temp[i1++] = data[i3++];
		}

		//����ĸ�ֵ�ǽ���ʱ����temp�洢������ֵ���ݽ�data��ԭ��Ӧ�ö�Ӧ�������ڣ�temp�ڵ���ֵ��С�㶨Ϊhi-lo
		for (int i = 0; i < hi - lo; i++)				
		{
			//������������Ϊ[lo,hi]���䣬����data[i+lo]Ϊtemp���������ÿ����ֵ��Ӧ����ʵ��ֵ
			data[i + lo] = temp[i];					
		}
		delete[] temp;
	}
private:
	//�鲢����ĸ������飬����ʹ��
	int temp[];
};