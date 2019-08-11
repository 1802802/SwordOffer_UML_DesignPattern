//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int main_zjtd222()
{
	int N, K;
	string S;
	while (cin >> N >> K)
	{
		cin >> S;
		string B;

		B.push_back(S[0]);
		for (int i = 1; i < N; i++)
		{
			//int temp = B[0] - '0';
			int temp = 0;
			if (i < K - 1)
			{
				temp = B[0] - '0';
				for (int j = 1; j < B.size(); j++)
					temp ^= (B[j] - '0');
			}
			if (i >= K - 1)
			{
				temp = B[i - K + 1] - '0';
				for (int j = i - K + 2; j < i && j < N; j++)
					temp ^= (B[j] - '0');
			}
			if ((S[i] - '0') == temp)
				B.push_back('0');
			else
				B.push_back('1');
		}
		cout << B << endl;
	}

	return 0;
}

int main_zjtd22222()
{
	int N, K;
	string S;
	while (cin >> N >> K)
	{
		cin >> S;
		string B;

		B.push_back(S[0]);
		for (int i = 1; i < N; i++)
		{
			//int temp = B[0] - '0';
			int temp = 0;
			if (i < K)
			{
				temp = B[0] - '0';
				for (int j = 1; j < B.size(); j++)
					temp ^= (B[j] - '0');
			}
			if (i >= K)
			{
				temp = B[i - K] - '0';
				for (int j = i - K + 1; j < i && j < N; j++)
					temp ^= (B[j] - '0');
			}
			if ((S[i] - '0') == temp)
				B.push_back('0');
			else
				B.push_back('1');
		}
		cout << B << endl;
	}

	return 0;
}