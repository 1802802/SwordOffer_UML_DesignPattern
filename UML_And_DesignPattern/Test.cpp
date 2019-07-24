#include <iostream>
using namespace std;

#define MAX1(x,y) ((x)>(y) ? (x) : (y))

template<typename T> T inline MAX2(T x, T y) { T _x = x; T _y = y; return (_x) > (_y) ? (_x) : (_y); }

int maintest1()
{
	int a = 8;
	for (int i = 0; a > 0; i++)
	{
		cout << "第" << i << "次a%2：" << a % 2 << endl;
		a = a / 2;
		cout << "第" << i << "次a/2：" << a << endl;
	}

	return 0;
}

int main()
{
	int a = 3;
	int b = 6;
	//auto r = MAX1 (a++, b++);
	auto r = MAX2(a++, b++);
	cout << r << endl;
	int c = 5;
	cout << (c>>2) << endl;

	return 0;
}