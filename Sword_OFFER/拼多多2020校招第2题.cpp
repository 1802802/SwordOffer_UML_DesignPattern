#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <sstream>
using namespace std;

/*
�ڶ��⣺Ů���Ѻ���������ֽ�ƣ�����n1 n2���ƣ�Ů���������ֲ��ԣ�
d����������������ߵ���
l��������������ߵ��Ʒŵ����ƶ������
r��������������ߵ��Ʒŵ����ƶ����ұߡ�
����ʹŮ���Ѻ�������ֽ��˳��˳����ͬ�Ĳ��ԡ�
ʾ����Ů���ѳ鵽�����ƣ��ֱ�Ϊ��1 2 3�������ѳ鵽һ���ƣ�Ϊ��3
�����Ϊ��d d l����d d r

�ڶ�����bfs����ÿһ�εĲ���Ϊd l r��������N�ο����γɵĴ��Ƿ���������ѵĴ����Ǿͼ��뵽�𰸣������ܻ��ж���𰸣��Դ𰸽����������򼴿ɡ�
�ѵ㣺Ů���ѵĳ�ʼ�����������ѵĴ�����Ϊ������Ҳ����һ���𰸡�
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