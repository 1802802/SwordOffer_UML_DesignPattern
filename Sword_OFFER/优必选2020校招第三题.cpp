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

//���鵱ǰջ���ж���λ���뵱ǰ�ʺ�λ���г�ͻ��ϵ
bool check(vector<queen> temp, queen &qn)
{
	bool count = 0;
	//��find��ջ�Ĳ��ҿ�һЩ��������N=10֮��ȷʵ�������Ի���
	if (find(temp.begin(), temp.end(), qn) != temp.end())
		return true;
	return false;
}

int searchNqueen(int N)
{
	int resultnum = 0;
	queen qn(0, 0);
	vector<queen> m_stack;  //ջ�洢��ǰ�������˵Ļʺ�λ��
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
			//ÿ��ÿ�е��ң������ǰ���ҵ����ʵģ�push��ջ�������ʱջ�лʺ�λ�����+1
			if (qn.y < N)
			{
				m_stack.push_back(qn);
				if (m_stack.size() >= N)
					resultnum++;
				qn.x++;
				qn.y = 0;
			}
		}
	} while (qn.x > 0 || qn.y < N);  //��ֹ�������ǵ�ǰ�ʺ��˵�һ�еĵ�N�У���ʱ�����Ѿ���·����
	return resultnum;
}

//��̽���ݷ� ջ���N�ʺ�
int main_ybx333()
{
	int N;
	while (cin >> N)
	{
		cout << "Total count: " << searchNqueen(N) << endl;
	}

	return 0;
}