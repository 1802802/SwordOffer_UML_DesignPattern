// ������42�����������������
// ��Ŀ��HZż������Щרҵ������������Щ�Ǽ����רҵ��ͬѧ��
// ��������鿪����,���ַ�����:�ڹ��ϵ�һάģʽʶ����,������Ҫ��������������������,������ȫΪ������ʱ��,����ܺý����
// ����,��������а�������,�Ƿ�Ӧ�ð���ĳ������,�������Աߵ��������ֲ����أ�
// ����:{6,-3,-2,7,-15,1,2,2},����������������Ϊ8(�ӵ�0����ʼ,����3��Ϊֹ)��
// ��һ�����飬��������������������еĺͣ���᲻�ᱻ������ס��(�������ĳ���������1)

// ��Ŀ����������һ���������飬������������Ҳ�и�����������һ���������Ķ����
// �����һ�������顣������������ĺ͵����ֵ��Ҫ��ʱ�临�Ӷ�ΪO(n)��

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution 
{
public:
	//1.��̬�滮˼·��DP[i] = max(DP[i-1]+a[i],a[i])��save�д洢��ÿ������ѣ�����ʱ�䣺4ms��ռ���ڴ棺468k
	int FindGreatestSumOfSubArray(vector<int> array) 
	{
		if (array.size() < 1)
			return 0;
		if (array.size() == 1)
			return array[0];
		vector<int> save;
		int maxSum = INT_MIN;
		save.push_back(array[0]);
		for (int i = 1; i < (int)array.size(); i++)
		{
			int sum = max(save[i - 1] + array[i], array[i]);
			save.push_back(sum);
			maxSum = max(sum, maxSum);
		}
		return maxSum;
	}
};

// ====================���Դ���====================
static void Test(char* testName, vector<int> pData, int nLength, int expected, bool expectedFlag)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);
	Solution s;
	int result = s.FindGreatestSumOfSubArray(pData);
	if (result == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 1, -2, 3, 10, -4, 7, 2, -5
static void Test1()
{
	vector<int> data = { 1, -2, 3, 10, -4, 7, 2, -5 };
	Test("Test1", data, sizeof(data) / sizeof(int), 18, false);
}

// �������ֶ��Ǹ���
// -2, -8, -1, -5, -9
static void Test2()
{
	vector<int> data = { -2, -8, -1, -5, -9 };
	Test("Test2", data, sizeof(data) / sizeof(int), -1, false);
}

// �������ֶ�������
// 2, 8, 1, 5, 9
static void Test3()
{
	vector<int> data = { 2, 8, 1, 5, 9 };
	Test("Test3", data, sizeof(data) / sizeof(int), 25, false);
}

// ��Ч����
static void Test4()
{
	Test("Test4", vector<int>(), 0, 0, true);
}

int main_offer42(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();

	return 0;
}