//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;


/*
��һ�⣺
���룺����������ݡ�ÿ�������������
��һ����������������N��A��X���ֱ������Ҫ�����bug�������ȿ���֮��Ч�������ı�����һ�������Ժȵ��Ŀ�����
�ڶ�������N����������ʾ�ڲ��ȿ��ȵ�����½����Щ�˰��������ʱ��t1, t2, ..., tN
�����������ڰ�Сʱ�ڽ����Щbug(���ʱ��ΪС��������ȡ��)��������bug��ʱ�䣬�������0
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
�������� ceil
�� ���� double ceil(double x);
�� �ܣ� ���ش��ڻ��ߵ���ָ�����ʽ����С����
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
			time = ceil((double)(sum) / (double)A);  //����ʱ��
		}
		else
		{
			time = sum - coffeTime + ceil((double)(sum) / (double)A);  //����ʱ��+��������ʱ��
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