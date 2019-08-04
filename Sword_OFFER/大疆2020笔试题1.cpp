//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

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