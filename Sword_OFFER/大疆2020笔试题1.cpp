//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;


/*
第一题：
输入：多组测试数据。每组测试数据如下
第一行输入三个整数：N、A、X，分别代表需要解决的bug数量、喝咖啡之后效率提升的倍数、一天最多可以喝掉的咖啡数
第二行输入N个整数，表示在不喝咖啡的情况下解决这些八阿哥所需的时间t1, t2, ..., tN
输出：如果能在八小时内解决这些bug(如果时间为小数，向上取整)，输出解决bug的时间，否则输出0
case:input:
8 2 8
60 60 60 60 60 60 60 60
4 3 3
333 77 100 13
output:
240
175
*/

int main_1111()
{
	int N, A, X, T;
	while (cin >> N >> A >> X)
	{	
		int sum = 0;
		for (int i = 0; i < N; i++)
		{
			cin >> T;
			sum += T;
		}
		int time = 0;
		if (X < 8)
		{
			if (((sum / A) - 60 * X) <= 0)
			{
				if (sum % A == 0)
					time = sum / A;
				else
					time = (sum / A) + 1;
			}		
			else
			{
				int time1 = 0;
				if (sum % A == 0)
					time1 = sum / A;
				else
					time1 = (sum / A) + 1;
				time = (time1 - 60 * X) * A + X;
			}
				
		}
		else
		{
			if (sum % A == 0)
				time = sum / A;
			else
				time = (sum / A) + 1;
		}
		if (time > 480)
			cout << 0 << endl;
		else
			cout << time << endl;
	}
	return 0;
}

/*
函数名： ceil
用 法： double ceil(double x);
功 能： 返回大于或者等于指定表达式的最小整数
*/

int main_dajiang2020_1()
{
	int N, A, X;  
	while (cin >> N >> A >> X)
	{
		int tmp;
		int time = 0;
		int sum = 0;
		for (int i = 0; i < N; ++i)
		{
			cin >> tmp;  
			sum += tmp;
		}
		int coffeTime = A * X * 60;
		if (coffeTime > sum)
		{
			time = ceil((double)(sum) / (double)A);  //加速时间
		}
		else
		{
			time = sum - coffeTime + ceil((double)(sum) / (double)A);  //加速时间+正常处理时间
		}
		if (time > 480)
		{
			cout << 0 << endl;
		}
		else
		{
			cout << time << endl;
		}
	}
	return 0;
}