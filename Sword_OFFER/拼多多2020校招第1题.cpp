#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;

struct compare
{
	bool operator()(int &a, int &b)
	{
		if ((a & 0x1) && !(b & 0x1))
			return true;
		else if (!(a & 0x1) && (b & 0x1))
			return false;
		else
		{
			if (a < b)
				return true;
			else
				return false;
		}
	}
};

int main_mindefisrtti()
{
	string s; int N;
	while (cin >> s)
	{
		for (auto &t : s)
			if (t == ',' || t == ';')
				t = ' ';
		istringstream input(s); vector<int> out;
		priority_queue<string, vector<int>, compare> m_queue;
		//最后一个就是N
		while (input >> N)
			m_queue.push(N);
		bool flag = false;
		for (int i = 0; i < N; i++)
		{
			if (!flag && m_queue.top() == N)
			{
				flag = true;
				i--;
				continue;
			}
			out.push_back(m_queue.top());
			m_queue.pop();
		}
		for (int i = 0; i < out.size() - 1; i++)
			cout << out[i] << ",";
		cout << out[out.size() - 1] << endl;
	}
	return 0;
}

int main_pdd11111()
{
	vector<int> odd;
	vector<int> even;
	string s;
	int N;
	while (cin >> s)
	{
		for (auto &t : s)
			if (t == ',' || t == ';')
				t = ' ';
		istringstream input(s);
		int temp = 0;
		int last = 0;
		while (input >> temp)
		{
			if (temp & 0x1)
			{
				odd.push_back(temp);
				last = 0;
			}
			else
			{
				even.push_back(temp);
				last = 1;
			}
		}
		N = temp;
		if (last == 0)
			odd.pop_back();
		else
			even.pop_back();

		sort(odd.begin(), odd.end(), [](int &a, int &b) {return a > b; });
		sort(even.begin(), even.end(), [](int &a, int &b) {return a > b; });

		vector<int> out;
		if (N <= even.size())
		{
			for (int i = 0; i < N; i++)
				out.push_back(even[i]);
		}
		else
		{
			for (int i = 0; i < even.size(); i++)
				out.push_back(even[i]);
			for (int i = 0; i < N - even.size(); i++)
				out.push_back(odd[i]);
		}

		for (int i = 0; i < out.size() - 1; i++)
			cout << out[i] << ",";
		cout << out[out.size() - 1] << endl;
	}

	return 0;
}