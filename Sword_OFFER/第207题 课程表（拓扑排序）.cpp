/*
题目描述：

现在你总共有 n 门课需要选，记为 0 到 n-1。

在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]

给定课程总量以及它们的先决条件，判断是否可能完成所有课程的学习？

示例 1:

输入: 2, [[1,0]]
输出: true
解释: 总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。所以这是可能的。

示例 2:

输入: 2, [[1,0],[0,1]]
输出: false
解释: 总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0；并且学习课程 0 之前，你还应先完成课程 1。这是不可能的。
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//注意[0,1]的顺序是先完成1再完成0，所以出队的第一个往往是最后一个才能学习的（顺序是反着的）
//执行用时 : 72 ms，内存消耗 : 81.8 MB，可见邻接矩阵的实现内存消耗较大，而使用队列实现后时间降低

class Solution
{
public:
	//以下为临界矩阵存图，其边界大小随数据而定，只适用于稠密图，数据过大就不能存了

	//1.主体函数，用于实现数据处理（建图与入度表建立）
	bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
	{
		if (prerequisites.empty())
			return true;
		//1.1 首先建立邻接矩阵图形与节点入度表
		vector<vector<int>> graph;
		vector<int> indegree(numCourses, 0);
		for (int i = 0; i < numCourses; i++)
			graph.push_back(vector<int>(numCourses, 0));
		for (int i = 0; i < prerequisites.size(); i++)
		{
			graph[prerequisites[i][0]][prerequisites[i][1]] = 1;
			indegree[prerequisites[i][1]]++;
		}
		//1.2 通过拓扑排序寻找环是否存在
		return TopologicalSort(graph, indegree);
	}

	//2.拓扑排序实现（有两种方式，循环递减与队列式）
	//第二种队列式
	bool TopologicalSort(vector<vector<int>>& graph, vector<int>& indegree)
	{
		vector<int> save;
		queue<int> zero_indegree;

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
			int zero = zero_indegree.front(); zero_indegree.pop();
			for (int j = 0; j < graph[zero].size(); j++)
			{
				if (graph[zero][j] != 0)
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
			return true;
		else
			return false;

	}
};

class Solution2
{
public:
	//以下为临界矩阵存图，其边界大小随数据而定，只适用于稠密图，数据过大就不能存了

	//1.主体函数，用于实现数据处理（建图与入度表建立）
	bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
	{
		if (prerequisites.empty())
			return true;
		//1.1 首先建立邻接矩阵图形与节点入度表
		vector<vector<int>> graph;
		vector<int> indegree(numCourses, 0);
		for (int i = 0; i < numCourses; i++)
			graph.push_back(vector<int>(numCourses, 0));
		for (int i = 0; i < prerequisites.size(); i++)
		{
			graph[prerequisites[i][0]][prerequisites[i][1]] = 1;
			indegree[prerequisites[i][1]]++;
		}
		//1.2 通过拓扑排序寻找环是否存在
		return TopologicalSort(graph, indegree);
	}

	//2.拓扑排序实现（有两种方式，循环递减与队列式）
	//第一种循环递减式
	bool TopologicalSort(vector<vector<int>>& graph, vector<int>& indegree)
	{
		vector<int> save;

		for (int i = 0; i < graph.size(); i++)
		{
			//2.1找到当前的入度为0的点，并将其入度设为-1表示已访问
			int zero_indegree = -1;
			for (int j = 0; j < indegree.size(); j++)
			{
				if (indegree[j] == 0)
				{
					zero_indegree = j;
					indegree[j] = -1;
					save.push_back(j);
					break;
				}
			}

			if (zero_indegree == -1)
				break;

			//2.2将入度为0的点在图中的出度方向全部-1
			for (int j = 0; j < graph[zero_indegree].size(); j++)
			{
				if (graph[zero_indegree][j] != 0)
				{
					indegree[j]--;
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
			return true;
		else
			return false;

	}
};

int main_leecode207()
{
	vector<vector<int>> prerequisites;
	prerequisites.push_back(vector<int>({ 0,1 }));
	prerequisites.push_back(vector<int>({ 0,2 }));
	prerequisites.push_back(vector<int>({ 2,1 }));
	prerequisites.push_back(vector<int>({ 1,2 }));

	Solution s1;
	cout << s1.canFinish(3, prerequisites) << endl;

	Solution s2;
	cout << s2.canFinish(3, prerequisites) << endl;

	return 0;
}