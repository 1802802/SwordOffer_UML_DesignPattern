#include <iostream>
#include <queue>
#include <deque>
#include <thread>
#include <time.h>
#include <vector>
using namespace std;

int main_nvdia111()
{
	int sum = 0;
	bool flag = false;
	for (int i = 2020; i <= 10000; i++)
	{
		flag = false;
		for (int j = 2; j * j <= i; j++)
		{
			if (i%j == 0)
			{
				flag = true;
				break;
			}
		}
		if (!flag)
			sum++;
	}
	cout << sum << endl;
	return 0;
}