#ifndef FIBSHIXIAN
#define FIBSHIXIAN

#include <iostream>
using namespace std;

//1.最经典无脑的斐波拉切实现，属于二分递归，将原递归策略不断地进行二分处理
long Fibonacci1(int n)
{
	if (n == 1 || n == 2)
		return 1;
	return Fibonacci1(n - 1) + Fibonacci1(n - 2);
}

//2.优化后的斐波拉切实现，不需要循环地计算F(n-1)和F(n-2)，接受数组的前两位f与s，从而代码更易用
long Fibonacci2(int f, int s, int n)
{
	//2.1递归基的选择相对较长，直接对应了输入的首位和二位
	if (n == 1)
		return f;
	if (n == 2)
		return s;
	if (n == 3)
		return f + s;
	//2.2线性递归的实现，思想为从门的尽头向最开始的门思考（不是从1往n算，是从n往0算，而规律在1往n算找）
	//2.3这里的思想理解关键是，将solve过程放在递的过程中，每次开门都会执行 f0 = s; s0 = f+s; 在n的减小过程中不断执行f+s
	return Fibonacci2(s, f + s, n - 1);
}

//3.普通的循环语句实现
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

//4.极致精简的动态规划法，是计算效率最高的算法（以递归的角度思考，循环的方法实现）
long Fibonacci4(int n)
{
	//4.1此方法思想为：f(-1) = 1; f(0) = 0; f(1) = 1; f(2) = 1; 减少了大量的if判断
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
	cout << "1.经典斐波拉切实现：" << Fibonacci1(n) << endl;
	cout << "2.优化斐波拉切实现：" << Fibonacci2(1, 1, n) << endl;
	cout << "3.循环斐波拉切实现：" << Fibonacci3(n) << endl;
	cout << "4.动态规划斐波拉切实现：" << Fibonacci4(n) << endl;
	//5.最最快的写法，直接在while(cin)循环里加个匿名函数（匿名函数最后加了个()，表示调用了此函数）
	while (cin >> n)
		cout << "lambda表达式斐波拉切实现：" << [&n]() {long f = 1, s = 0; while (n--) { s = f + s; f = s - f; } return s; }() << endl;
	return 0;
}

#endif