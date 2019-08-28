#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

//DFS������·���Ƿ���ڣ�BFS���������·��

bool isHavePath(vector<vector<string>> &save, vector<vector<bool>> &isVisited, int &rows, int &cols, int row, int col)
{
	if (row == rows - 1 && col == cols - 1 && save[rows - 1][cols - 1] == "1")
	{
		isVisited[row][col] = true;
		cout << "enter the DFS�ݹ��" << endl;
		return true;
	}
	bool result = false;
	if (row < rows && col < cols && row >= 0 && col >= 0 && save[row][col] == "1" && isVisited[row][col] == false)
	{
		isVisited[row][col] = true;
		//��||��Ϊ|�������·�����ڼ������·������������DFS�ľ����ԣ��䷽��Ϊ��Ϊ���ƣ������ҵ����·�������ǵ���BFS
		result = isHavePath(save, isVisited, rows, cols, row + 1, col) || isHavePath(save, isVisited, rows, cols, row - 1, col)
			|| isHavePath(save, isVisited, rows, cols, row, col + 1) || isHavePath(save, isVisited, rows, cols, row, col - 1);
		if (!result)
			isVisited[row][col] = false;
	}
	return result;
}

enum Status { AVAILABLE, ROUTE, USED, WALL };

struct Cell
{
	int m_row;
	int m_col;
	Status m_status = AVAILABLE;
	Cell* m_prev = nullptr;
};

//��������ĵ�BFS����Ҫ��� AVAILABLE, ROUTE, USED, WALL ����һ��ָ�����ߵ�·��������BFSһ��һ�����������ܵ�ͼ�����еĶ�������
//����Ҳ�п����е�û�ߵ���ROUTE��ʾ�ýڵ��Ѿ������˵�ǰ·���ļ��㣬USED��ʾ�ýڵ��·�������Ѿ���ɣ�WALL��ʾ����ǽ�޷�����
//����BFS������������ʵ�������з������Ȩ�ص���������Ҫ���Ƿ��������������Ҫ��ϵϿ�˹�����㷨��A*�㷨��D*�㷨�������Ϸ���

/*
1. �Ӷ���u����һ��һ���������չ

2. ���ö��м�¼���ʵ�˳��

3. ����һ���ҵ�����vʱ�����б���������·����ͬʱ���������������ö��д洢���·��������һ����ͨ���У�����֮ǰ��˵�Ļ��ζ��У�

4. Ȼ�������ö���������·������·����
*/

bool isHavePath_BFS(vector<vector<Cell>> &save, int &rows, int &cols, int row, int col)
{
	queue<Cell*> m_queue; int count = 0;
	m_queue.push(&save[row][col]);
	while (!m_queue.empty())
	{
		Cell *cur = m_queue.front(); m_queue.pop();
		if (cur->m_row == rows - 1 && cur->m_col == cols - 1 && save[rows - 1][cols - 1].m_status != WALL)
		{
			cout << "enter the BFS�ݹ��" << endl;
			//���·���ǻ��ݳ�����
			Cell *tmp = cur;
			cur->m_status = AVAILABLE;
			while (tmp != nullptr)
			{
				cout << "<" << tmp->m_row << "," << tmp->m_col << "> ";
				tmp = tmp->m_prev;
			}
			cout << endl;
			count++;
			//return��Ϊ���·��������Ϊ����·��
			//return count;
		}
		else
		{
			if ((cur->m_row) + 1 < rows && (cur->m_col) < cols && (cur->m_row) >= 0 && (cur->m_col) >= 0 && save[(cur->m_row) + 1][(cur->m_col)].m_status == AVAILABLE)
			{
				m_queue.push(&save[(cur->m_row) + 1][(cur->m_col)]);
				save[(cur->m_row) + 1][(cur->m_col)].m_status = ROUTE;
				save[(cur->m_row) + 1][(cur->m_col)].m_prev = cur;
			}
			if ((cur->m_row) < rows && (cur->m_col) + 1 < cols && (cur->m_row) >= 0 && (cur->m_col) >= 0 && save[(cur->m_row)][(cur->m_col) + 1].m_status == AVAILABLE)
			{
				m_queue.push(&save[(cur->m_row)][(cur->m_col) + 1]);
				save[(cur->m_row)][(cur->m_col) + 1].m_status = ROUTE;
				save[(cur->m_row)][(cur->m_col) + 1].m_prev = cur;
			}
			if ((cur->m_row) < rows && (cur->m_col) < cols && (cur->m_row) - 1 >= 0 && (cur->m_col) >= 0 && save[(cur->m_row) - 1][(cur->m_col)].m_status == AVAILABLE)
			{
				m_queue.push(&save[(cur->m_row) - 1][(cur->m_col)]);
				save[(cur->m_row) - 1][(cur->m_col)].m_status = ROUTE;
				save[(cur->m_row) - 1][(cur->m_col)].m_prev = cur;
			}
			if ((cur->m_row) < rows && (cur->m_col) < cols && (cur->m_row) >= 0 && (cur->m_col) - 1 >= 0 && save[(cur->m_row)][(cur->m_col) - 1].m_status == AVAILABLE)
			{
				m_queue.push(&save[(cur->m_row)][(cur->m_col) - 1]);
				save[(cur->m_row)][(cur->m_col) - 1].m_status = ROUTE;
				save[(cur->m_row)][(cur->m_col) - 1].m_prev = cur;
			}
			save[(cur->m_row)][(cur->m_col)].m_status = USED;
		}
	}
	return count;
}

int main_huaweimianshi()
{
	//1.���ݴ���
	string in;
	int rows = 0, cols = 0;
	ifstream input("input.txt");
	vector<vector<Cell>> save;
	vector<Cell> temp;
	while (input >> in)
	{
		if (in != "\\r\\n")
		{
			Cell t;
			t.m_row = rows;
			t.m_col = cols++;
			if (in == "1")
				t.m_status = AVAILABLE;
			else
				t.m_status = WALL;
			temp.push_back(t);
		}
		else
		{
			save.push_back(temp);
			cols = 0;
			rows++;
			temp.clear();
		}
	}

	//2.��
	rows = save.size(); cols = save.front().size();
	bool isFind = isHavePath_BFS(save, rows, cols, 0, 0);

	//3.���
	if (isFind)
	{
		cout << "���ҵ�·�������������out.txt�ļ�" << endl;
		ofstream out("out.txt");
		for (auto &s1 : save)
		{
			for (auto &s2 : s1)
			{
				//out << s2.m_status << " ";
				if(s2.m_status != WALL)
					out << 1 << " ";
				else
					out << 0 << " ";
			}
			out << "\\r\\n" << endl;
		}
	}
	else
		cout << "δ�ҵ�·��" << endl;

	return 0;
}


//int main()
//{
//	//1.���ݴ���
//	string in;
//	int rows, cols;
//	ifstream input("input.txt");
//	vector<vector<string>> save;
//	vector<string> temp;
//	while (input >> in)
//	{
//		if (in != "\\r\\n")
//		{
//			temp.push_back(in);
//		}
//		else
//		{
//			save.push_back(temp);
//			cols = temp.size();
//			temp.clear();
//		}
//	}
//	rows = save.size();
//	vector<vector<bool>> isVisited(rows, vector<bool>(cols, false));
//
//	//2.��
//	//bool isFind = isHavePath(save, isVisited, rows, cols, 0, 0);
//	bool isFind = isHavePath_BFS(save, isVisited, rows, cols, 0, 0);
//
//	//3.���
//	if (isFind)
//	{
//		cout << "���ҵ�·�������������out.txt�ļ�" << endl;
//		ofstream out("out.txt");
//		for (auto &s1 : isVisited)
//		{
//			for (auto &s2 : s1)
//			{
//				out << s2 << " ";
//			}
//			out << "\\r\\n" << endl;
//		}
//	}
//	else
//		cout << "δ�ҵ�·��" << endl;
//
//	return 0;
//}