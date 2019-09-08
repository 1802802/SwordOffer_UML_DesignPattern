//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <stack>
using namespace std;

class TreeNode
{
public:
	char val = ' ';
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
};


//1(2(3,4(,5)),6(7,))
TreeNode* Deserialize(string str, int &start, int &end)
{
	TreeNode* pNode = nullptr;
	if (str[start] >= '0' && str[start] <= '9')
	{
		pNode->val = str[start++];
		pNode->left = Deserialize(str, start, end);
		pNode->right = Deserialize(str, start, end);
		return pNode;
	}
	else if (start < end && str[start] == '(')
	{
		start++;
		if (str[start] >= '0' && str[start] <= '9')
		{
			pNode->val = str[start++];
			pNode->left = Deserialize(str, start, end);
			pNode->right = Deserialize(str, start, end);
			start++;
			return pNode;
		}
		else
		{
			start++;
			return nullptr;
		}
	}
	else if (start < end && str[start] == ',')
	{
		return nullptr;
	}
	else if (start < end && str[start] == ')')
	{
		start++;
		return nullptr;
	}
	return nullptr;
}

string solution(string input)
{
	if (input.empty())
		return nullptr;
	int start = 0; int end = input.size() - 1;
	auto temp = Deserialize(input, start, end);
}

int main_xiaomi111()
{
	string res;

	string _input;
	getline(cin, _input);

	res = solution(_input);
	cout << res << endl;

	return 0;

}