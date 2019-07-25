#include <iostream>
using namespace std;

class Solution 
{
public:
	//1.����ⷨ�����ǵ����������������ѡ�����Ʊ�־λ������������Դ����
	//ţ����������ʱ�䣺5ms��ռ���ڴ棺376k
	int NumberOf1(int n) 
	{
		int count = 0;
		int flag = 1;
		while (flag)
		{
			//��λ�ж�n�еĵ�ǰλ���Ƿ�Ϊ1������+1
			if (flag & n)
				count++;
			flag <<= 1;
		}
		return count;
	}
	//2.˼��ⷨ��(n-1)&n�����ɽ�n���ұߵ�1ȥ����ͨ�����ϵ�ȥ1ֱ��nΪ0���ٶȱ���һ�ֿ죬��Ϊ���Զ���ɾ1��
	//ţ���� ����ʱ�䣺3ms��ռ���ڴ棺480k
	int NumberOf2(int n)
	{
		int count = 0;
		while (n)
		{
			count++;
			n = (n - 1)&n;
		}
		return count;
	}
};

// ====================���Դ���====================
static void Test(int number, unsigned int expected)
{
	Solution s;
	int actual = s.NumberOf1(number);
	if (actual == expected)
		printf("Solution1: Test for %p passed.\n", number);
	else
		printf("Solution1: Test for %p failed.\n", number);

	actual = s.NumberOf2(number);
	if (actual == expected)
		printf("Solution2: Test for %p passed.\n", number);
	else
		printf("Solution2: Test for %p failed.\n", number);

	printf("\n");
}

int main(int argc, char* argv[])
{
	// ����0���ڴ��������0
	Test(0, 0);

	// ����1���ڴ��������1
	Test(1, 1);

	// ����10���ڴ��������2
	Test(10, 2);

	// ����0x7FFFFFFF���ڴ��������31
	Test(0x7FFFFFFF, 31);

	// ����0xFFFFFFFF�����������ڴ��������32
	Test(0xFFFFFFFF, 32);

	// ����0x80000000�����������ڴ��������1
	Test(0x80000000, 1);

	return 0;
}