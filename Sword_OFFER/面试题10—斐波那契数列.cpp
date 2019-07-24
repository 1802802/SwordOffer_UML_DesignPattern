#include <iostream>
using namespace std;

//ţ��������3ms��384K
//�Ʋ�������������
class Solution1 
{
public:
	int Fibonacci(int n)
	{
		return [&n]() {int f = 1, s = 0; while (n--) { s = f + s; f = s - f; } return s; }();
	}
};

//��̨�����⣬����쳲��������⣬�ȱ�׼��ǰ����һλ����һ������Ķ�̬�滮д��д
class Solution 
{
public:
	int jumpFloor(int number) 
	{
		int first = 1;      //f(-1)
		int second = 0;		//f(0)
		while (number--)
		{
			second = first + second;
			first = second - first;
		}
		return second;
	}
};

//��̬��̨�����⣬ʹ����ѧ���ɷ��õ���ͨ�ʽΪan = 2^(n-1)
//ţ����3ms��460K
class Solution2
{
public:
	int jumpFloorII(int number)
	{
		return 1 << (number - 1);
	}
};