// ������64����Ʊ���������
// ��Ŀ����1+2+��+n��Ҫ����ʹ�ó˳�����for��while��if��else��switch��case
// �ȹؼ��ּ������ж���䣨A?B:C����

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "BinaryTree.h"
using namespace std;

//˼·��������ǻ�����ڣ�ʲô������������һ��

class temp
{
private:
	static int n;
	static int sum;
public:
	temp() { ++n; sum += n; }
	static void initial() { n = 0; sum = 0; }
	static int getsum() { return sum; }
};

//ע��static��Ա�������ʼ��
int temp::n = 0;
int temp::sum = 0;

//����1�����ù��캯��
//����ʱ�䣺4ms��ռ���ڴ棺476k
int Sum_Solution1(int n)
{
	temp::initial();
	temp* t = new temp[n];  //ִ��n��temp�Ĺ��캯��
	delete[] t;
	t = nullptr;

	return temp::getsum();
}

//����2��ʹ��&&����ʵ�ֶ�·��ֵ
//����ʱ�䣺3ms��ռ���ڴ棺504k
int Sum_Solution2(int n)
{
	int ans = n;
	//�ݹ����ֹ����Ϊ���n=0ʱ�Ķ�·
	ans && (ans += Sum_Solution2(n - 1));
	return ans;
}

//����3��ͨ�����飨bool��Ϊ1���Ĵ�Сʵ��n(n+1)/2������ʵ��
//����ʱ�䣺4ms��ռ���ڴ棺492k
int Sum_Solution3(int n)
{
	//VS����ʹ�ã�����gcc�����
	//bool temp[n][n + 1];
	//return (sizeof(temp) >> 1);
	return 0;
}

// ====================���Դ���====================
static void Test(int n, int expected)
{
	printf("Test for %d begins:\n", n);

	if (Sum_Solution1(n) == expected)
		printf("Solution1 passed.\n");
	else
		printf("Solution1 failed.\n");

	if (Sum_Solution2(n) == expected)
		printf("Solution2 passed.\n");
	else
		printf("Solution2 failed.\n");

	if (Sum_Solution3(n) == expected)
		printf("Solution3 passed.\n");
	else
		printf("Solution3 failed.\n");
}

static void Test1()
{
	const unsigned int number = 1;
	int expected = 1;
	Test(number, expected);
	//if (Sum_Solution4<number>::N == expected)
	//	printf("Solution4 passed.\n");
	//else
	//	printf("Solution4 failed.\n");
}

static void Test2()
{
	const unsigned int number = 5;
	int expected = 15;
	Test(number, expected);
	//if (Sum_Solution4<number>::N == expected)
	//	printf("Solution4 passed.\n");
	//else
	//	printf("Solution4 failed.\n");
}

static void Test3()
{
	const unsigned int number = 10;
	int expected = 55;
	Test(number, expected);
	//if (Sum_Solution4<number>::N == expected)
	//	printf("Solution4 passed.\n");
	//else
	//	printf("Solution4 failed.\n");
}

static void Test4()
{
	const unsigned int number = 0;
	int expected = 0;
	Test(number, expected);
	//if (Sum_Solution4<number>::N == expected)
	//	printf("Solution4 passed.\n");
	//else
	//	printf("Solution4 failed.\n");
}

int main_offer64(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();

	return 0;
}