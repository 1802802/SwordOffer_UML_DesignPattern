#ifndef JIECHENGSHIXIAN
#define JIECHENGSHIXIAN

#include <iostream>
using namespace std;

//阶乘的递归实现是一种线性递归，solve过程是在递的过程中（在归时才进行结果计算）
long factorial1(int n)
{
	if (n == 1)
		return 1;
	return n*factorial1(n - 1);
}

//阶乘的迭代实现
long factorial2(int n)
{
	long sum = 1;
	while (n)
		sum *= n--;
	return sum;
}

int main_factorial()
{
	cout << "阶乘递归：" << factorial1(10) << endl;
	cout << "迭代递归：" << factorial2(10) << endl;
	return 0;
}

#endif