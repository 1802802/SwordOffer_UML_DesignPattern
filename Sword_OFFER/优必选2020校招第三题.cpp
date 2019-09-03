//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

class queen
{
public:
	queen(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	bool operator==(const queen &q) const { return (x == q.x) || (y == q.y) || (x + y == q.x + q.y) || (x - y) == (q.x - q.y); }
	bool operator!=(const queen &q) const { return !(*this == q); }
	int x, y;
};

//检验当前栈内有多少位置与当前皇后位置有冲突关系
bool check(vector<queen> temp, queen &qn)
{
	bool count = 0;
	//用find比栈的查找快一些，但是在N=10之后确实还是明显缓慢
	if (find(temp.begin(), temp.end(), qn) != temp.end())
		return true;
	return false;
}

int searchNqueen(int N)
{
	int resultnum = 0;
	queen qn(0, 0);
	vector<queen> m_stack;  //栈存储当前所放置了的皇后位置
	do
	{
		if (m_stack.size() >= N || qn.y >= N)
		{
			qn = m_stack.back(); m_stack.pop_back();
			qn.y++;
		}
		else
		{
			while (qn.y < N && check(m_stack, qn))
			{
				qn.y++;
			}
			//每行每行的找，如果当前列找到合适的，push进栈。如果此时栈中皇后到位，结果+1
			if (qn.y < N)
			{
				m_stack.push_back(qn);
				if (m_stack.size() >= N)
					resultnum++;
				qn.x++;
				qn.y = 0;
			}
		}
	} while (qn.x > 0 || qn.y < N);  //终止条件就是当前皇后到了第一行的第N列，此时代表已经无路可走
	return resultnum;
}

//试探回溯法 栈解决N皇后
int main_ybx333()
{
	int N;
	while (cin >> N)
	{
		cout << "Total count: " << searchNqueen(N) << endl;
	}

	return 0;
}