// ������44��1��n������1���ֵĸ���
// ��Ŀ��������0123456789101112131415���ĸ�ʽ���л���һ���ַ������С�����
// �������У���5λ����0��ʼ��������5����13λ��1����19λ��4���ȵȡ���дһ
// ������������λ��Ӧ�����֡�

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
	//1.�ҵ���ǰ����λ���ĸ�λ������
	//num��ʾ��ǰλ����ʼλ�ã�i��ʾ��ǰ��λ��ֵ��indexPlace��ʾ���������֣�indexOffsetΪ�����ֵ�ƫ����
	int num = 1;
	int i = 1;
	int indexPlace = 0;
	int indexOffset = 0;
	while (index > num)
	{
		//indexPlace �� indexOffset ��Ҫ��ÿ��ѭ������м��㣬��Ϊÿ��������ʼ���λ��������ͬ
		indexPlace = (index - num) / i;
		indexOffset = (index - num) % i;
		num += i * 9 * pow(10, i - 1);
		i++;
	}
	i--;
	//2.����i�Ĵ�С������λ�������е��ĸ�����λ��
	int indexStatus = pow(10, i - 1) + indexPlace;
	string tmp = to_string(indexStatus);
	return tmp[indexOffset] - '0';
}

// ====================���Դ���====================
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
	test("Test5", 189, 9);  // ����99�����һλ��9
	test("Test6", 190, 1);  // ����100�ĵ�һλ��1
	test("Test7", 1000, 3); // ����370�ĵ�һλ��3
	test("Test8", 1001, 7); // ����370�ĵڶ�λ��7
	test("Test9", 1002, 0); // ����370�ĵ���λ��0
	return 0;
}