#ifndef FIBSHIXIAN
#define FIBSHIXIAN

#include <iostream>
using namespace std;

//1.������Ե�쳲�����ʵ�֣����ڶ��ֵݹ飬��ԭ�ݹ���Բ��ϵؽ��ж��ִ���
long Fibonacci1(int n)
{
	if (n == 1 || n == 2)
		return 1;
	return Fibonacci1(n - 1) + Fibonacci1(n - 2);
}

//2.�Ż����쳲�����ʵ�֣�����Ҫѭ���ؼ���F(n-1)��F(n-2)�����������ǰ��λf��s���Ӷ����������
long Fibonacci2(int f, int s, int n)
{
	//2.1�ݹ����ѡ����Խϳ���ֱ�Ӷ�Ӧ���������λ�Ͷ�λ
	if (n == 1)
		return f;
	if (n == 2)
		return s;
	if (n == 3)
		return f + s;
	//2.2���Եݹ��ʵ�֣�˼��Ϊ���ŵľ�ͷ���ʼ����˼�������Ǵ�1��n�㣬�Ǵ�n��0�㣬��������1��n���ң�
	//2.3�����˼�����ؼ��ǣ���solve���̷��ڵݵĹ����У�ÿ�ο��Ŷ���ִ�� f0 = s; s0 = f+s; ��n�ļ�С�����в���ִ��f+s
	return Fibonacci2(s, f + s, n - 1);
}

//3.��ͨ��ѭ�����ʵ��
long Fibonacci3(int n)
{
	if (n == 1 || n == 2)
		return 1;
	int f = 1;
	int s = 1;
	long sum = 0;
	while (n-- > 3)
	{
		s = f + s;
		f = s - f;
	}
	return f + s;
}

//4.���¾���Ķ�̬�滮�����Ǽ���Ч����ߵ��㷨���Եݹ�ĽǶ�˼����ѭ���ķ���ʵ�֣�
long Fibonacci4(int n)
{
	//4.1�˷���˼��Ϊ��f(-1) = 1; f(0) = 0; f(1) = 1; f(2) = 1; �����˴�����if�ж�
	long f = 1, s = 0;
	while (n--)
	{
		s = f + s;
		f = s - f;
	}
	return s;
}

int main_fibonacci()
{
	int n = 30;
	cout << "1.����쳲�����ʵ�֣�" << Fibonacci1(n) << endl;
	cout << "2.�Ż�쳲�����ʵ�֣�" << Fibonacci2(1, 1, n) << endl;
	cout << "3.ѭ��쳲�����ʵ�֣�" << Fibonacci3(n) << endl;
	cout << "4.��̬�滮쳲�����ʵ�֣�" << Fibonacci4(n) << endl;
	//5.������д����ֱ����while(cin)ѭ����Ӹ������������������������˸�()����ʾ�����˴˺�����
	while (cin >> n)
		cout << "lambda���ʽ쳲�����ʵ�֣�" << [&n]() {long f = 1, s = 0; while (n--) { s = f + s; f = s - f; } return s; }() << endl;
	return 0;
}

#endif