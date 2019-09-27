#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int sum = 0;
//10 1 362883

int fun(int MM, int M, int N, int add)
{
	if (MM == (M - 1))
		return 2;
	add = (add * MM ) + (add - MM);
	fun(MM + 1, M, N, add);
	N = N + add;
	sum += N;
	cout << sum << endl;
	return N;
}

int main_kdxf111()
{
	int M, N;
	while (cin >> M >> N)
	{
		sum = N;
		int add = 2;
		int temp = fun(1, M, N, add);
		sum += (N + add);
		cout << temp << endl;
	}

	return 0;
}