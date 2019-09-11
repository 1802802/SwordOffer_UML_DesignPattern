#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <vector>    
using namespace std;

int solution(string str)
{
	int sum = 0;

	for (auto &s : str)
	{
		if (s == '(')
			sum++;
		else if (s == ')')
			sum--;
		else if (s == '0')
			return sum;
		else
			return -1;
	}
	return -1;

	return sum;
}

int main_vivo111()
{
	string str("");
	getline(cin, str);

	int sum = solution(str);
	cout << sum << endl;
	return 0;
}