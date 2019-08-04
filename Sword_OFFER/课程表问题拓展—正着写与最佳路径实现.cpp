/*
题目描述：

此文的目的是为了将顺序修改为先完成的先出队，而不是最后完成的
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution_test
{
public:
	//以下为临界矩阵存图，其边界大小随数据而定，只适用于稠密图，数据过大就不能存了

	//1.主体函数，用于实现数据处理（建图与入度表建立）
	vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
	{
		//对于此题条件，当课程有值且没有对应关系时，直接按顺序返回即可
		if (prerequisites.empty())
		{
			vector<int> temp;
			for (int i = 0; i < numCourses; i++)
				temp.push_back(i);
			return temp;
		}
		//1.1 首先建立邻接矩阵图形与节点入度表
		vector<vector<int>> graph;
		vector<int> indegree(numCourses, 0);
		for (int i = 0; i < numCourses; i++)
			graph.push_back(vector<int>(numCourses, 0));
		//这里的prerequisites.size()不能改成numCourses
		for (int i = 0; i < prerequisites.size(); i++)
		{
			graph[prerequisites[i][1]][prerequisites[i][0]] = 1;
			indegree[prerequisites[i][0]]++;
		}

		//1.2 通过拓扑排序寻找环是否存在
		return TopologicalSort(graph, indegree);
	}

	//小顶堆的实现
	struct compara
	{
		bool operator()(const int &a,const int &b) { return a > b; };
	};

	//2.拓扑排序实现（有两种方式，循环递减与队列式）
	//第二种队列式
	vector<int> TopologicalSort(vector<vector<int>>& graph, vector<int>& indegree)
	{
		vector<int> save;
		priority_queue<int,vector<int>, compara> zero_indegree;

		//2.1找到当前的入度为0的点，并将其入度设为-1表示已访问，并使其进入队列
		for (int j = 0; j < indegree.size(); j++)
		{
			if (indegree[j] == 0)
			{
				zero_indegree.push(j);
				save.push_back(j);
				indegree[j] = -1;
			}
		}

		//2.2队列中的首元素出队，并减少出队节点的所有出度的入度
		while (!zero_indegree.empty())
		{
			int zero = zero_indegree.top(); zero_indegree.pop();
			for (int j = 0; j < graph[zero].size(); j++)
			{
				if (graph[zero][j] != 0) //这里可以不用判断此条件，但是无所谓
				{
					indegree[j]--;
					if (indegree[j] == 0)
					{
						zero_indegree.push(j);
						save.push_back(j);
						indegree[j] = -1;
					}
				}
			}
		}

		for (auto &s1 : graph)
		{
			for (auto &s2 : s1)
			{
				cout << s2 << " ";
			}
			cout << endl;
		}

		for (auto &s1 : indegree)
			cout << s1 << " ";
		cout << endl;

		if (save.size() == graph.size())
			return save;
		else
			return vector<int>();
	}
};

int main_topsort_test()
{
	vector<vector<int>> prerequisites;
	//输入: 4, [[1, 0], [2, 0], [3, 1], [3, 2]]
	prerequisites.push_back(vector<int>({ 1,0 }));
	prerequisites.push_back(vector<int>({ 2,0 }));
	prerequisites.push_back(vector<int>({ 3,1 }));
	prerequisites.push_back(vector<int>({ 3,2 }));

	//prerequisites.push_back(vector<int>({ 1,0 }));

	Solution_test s1;
	for (auto &s : s1.findOrder(4, prerequisites))
		cout << s << " ";
	cout << endl;

	return 0;
}