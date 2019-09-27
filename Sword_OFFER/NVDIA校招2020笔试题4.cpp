#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main_nvdia444()
{
	string input;
	while (cin >> input)
	{
		for (auto &s : input)
			if (s == '<' || s == '>' || s == 'b' || s == 'r' || s == '/')
				s = ' ';
		istringstream in(input);
		vector<vector<vector<int>>> savetotal;
		int n;
		while (in >> n)
		{
			vector<vector<int>> save(n, vector<int>(n, 0));
			int row_start = 0, row_end = n - 1, col_start = 0, col_end = n - 1;
			for (int i = 1; i <= n*n;)
			{
				for (int j = col_start; j <= col_end; j++)
					save[row_start][j] = i++;
				for (int j = row_start + 1; j <= row_end; j++)
					save[j][col_end] = i++;
				for (int j = col_end - 1; j >= col_start; j--)
					save[row_end][j] = i++;
				for (int j = row_end - 1; j > row_start; j--)
					save[j][col_start] = i++;
				row_start++; row_end--; col_start++; col_end--;
			}
			savetotal.push_back(save);
		}
		for (auto &s1 : savetotal)
		{
			for (auto &s2 : s1)
			{
				for (auto &s3 : s2)
				{
					cout << s3;
					if (s3 != s2.back())
						cout << " ";
				}
				if (s2 != s1.back() || s1 != savetotal.back())
					cout << "<br/>";
			}
			cout << "<br/>";
			cout << endl;
			if (s1 != savetotal.back())
				cout << "<br/>";
		}
	}
	return 0;
}

