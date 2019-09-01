#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <sstream>
using namespace std;

/*
第二题：女朋友和男朋友玩纸牌，各抽n1 n2张牌，女朋友有三种策略：
d：丢弃手牌中最左边的牌
l：将手牌中最左边的牌放到新牌堆最左边
r：将手牌中最左边的牌放到新牌堆最右边。
求能使女朋友和男朋友纸牌顺序及顺序相同的策略。
示例：女朋友抽到三张牌，分别为：1 2 3，男朋友抽到一张牌，为：3
则策略为：d d l或者d d r

第二题是bfs，让每一次的操作为d l r，操作完N次看看形成的串是否等于男朋友的串，是就加入到答案，最后可能会有多个答案，对答案进行升序排序即可。
难点：女朋友的初始串等于男朋友的串，答案为“”，也算是一个答案。
*/

void dfsfind(set<string> &save, string path, int s, string news, string m, string &b)
{
	if (s == 0 && news == b)
	{
		save.insert(path);
		return;
	}
	if (s < 0 || m.size() < 1)
		return;
	dfsfind(save, path + "d", s - 1, news, m.substr(1), b);
	dfsfind(save, path + "l", s - 1, m[0] + news, m.substr(1), b);
	dfsfind(save, path + "r", s - 1, news + m[0], m.substr(1), b);
}

int main_pdd2()
{
	int s; string m, b;
	cin >> s;
	for (int i = 0; i < s; i++)
	{
		set<string> save;
		cin >> m >> b;
		dfsfind(save, string(), s, string(), m, b);
		cout << "{" << endl;
		for (auto &t : save)
			cout << t << endl;
		cout << "}" << endl;
	}
	return 0;
}