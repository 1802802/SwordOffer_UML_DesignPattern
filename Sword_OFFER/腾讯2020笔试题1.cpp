#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

int main_tencent1()
{
	int n;
	while (cin >> n)
	{
		long long adult = 1;
		long long unadult = 0;
		long long egg = 0;
		long long sale_egg = 0;
		long long sum = 0;
		for (int i = 1; i <= n; i++)
		{
			adult = adult + unadult;
			unadult = egg;
			sale_egg = adult >> 1;
			egg = adult - sale_egg;
			sum += sale_egg;
		}
		cout << sum << endl;
	}


	return 0;
}