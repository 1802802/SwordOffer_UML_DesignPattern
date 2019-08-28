#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

//DFS用于找路径是否存在，BFS用于找最短路径

bool isHavePath(vector<vector<string>> &save, vector<vector<bool>> &isVisited, int &rows, int &cols, int row, int col)
{
	if (row == rows - 1 && col == cols - 1 && save[rows - 1][cols - 1] == "1")
	{
		isVisited[row][col] = true;
		cout << "enter the DFS递归基" << endl;
		return true;
	}
	bool result = false;
	if (row < rows && col < cols && row >= 0 && col >= 0 && save[row][col] == "1" && isVisited[row][col] == false)
	{
		isVisited[row][col] = true;
		//将||变为|，避免短路，用于计算多条路径，但是由于DFS的局限性，其方向为人为限制，难以找到最短路径，还是得用BFS
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

//对于这里的的BFS中需要理解 AVAILABLE, ROUTE, USED, WALL ，第一个指可以走的路径，根据BFS一步一格的情况，可能地图中所有的都会走完
//但是也有可能有的没走到，ROUTE表示该节点已经加入了当前路径的计算，USED表示该节点的路径计算已经完成，WALL表示就是墙无法行走
//这里BFS的问题在于其实属于所有方向均等权重的情况，如果要考虑方向操作，可能需要结合迪克斯特拉算法与A*算法与D*算法进行联合分析

/*
1. 从顶点u出发一层一层地向外扩展

2. 利用队列记录访问的顺序

3. 当第一次找到顶点v时队列中便包含了最短路径，同时在搜索过程中利用队列存储最短路径（这是一个普通队列，而非之前所说的环形队列）

4. 然后再利用队列输出最短路径（逆路径）
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
			cout << "enter the BFS递归基" << endl;
			//最短路径是回溯出来的
			Cell *tmp = cur;
			cur->m_status = AVAILABLE;
			while (tmp != nullptr)
			{
				cout << "<" << tmp->m_row << "," << tmp->m_col << "> ";
				tmp = tmp->m_prev;
			}
			cout << endl;
			count++;
			//return则为最短路径，否则为多条路径
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
	//1.数据处理
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

	//2.找
	rows = save.size(); cols = save.front().size();
	bool isFind = isHavePath_BFS(save, rows, cols, 0, 0);

	//3.输出
	if (isFind)
	{
		cout << "已找到路径，并输出到了out.txt文件" << endl;
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
		cout << "未找到路径" << endl;

	return 0;
}


//int main()
//{
//	//1.数据处理
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
//	//2.找
//	//bool isFind = isHavePath(save, isVisited, rows, cols, 0, 0);
//	bool isFind = isHavePath_BFS(save, isVisited, rows, cols, 0, 0);
//
//	//3.输出
//	if (isFind)
//	{
//		cout << "已找到路径，并输出到了out.txt文件" << endl;
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
//		cout << "未找到路径" << endl;
//
//	return 0;
//}