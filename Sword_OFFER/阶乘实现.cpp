#ifndef JIECHENGSHIXIAN
#define JIECHENGSHIXIAN

#include <iostream>
using namespace std;

//�׳˵ĵݹ�ʵ����һ�����Եݹ飬solve�������ڵݵĹ����У��ڹ�ʱ�Ž��н�����㣩
long factorial1(int n)
{
	if (n == 1)
		return 1;
	return n*factorial1(n - 1);
}

//�׳˵ĵ���ʵ��
long factorial2(int n)
{
	long sum = 1;
	while (n)
		sum *= n--;
	return sum;
}

int main_factorial()
{
	cout << "�׳˵ݹ飺" << factorial1(10) << endl;
	cout << "�����ݹ飺" << factorial2(10) << endl;
	return 0;
}

#endif