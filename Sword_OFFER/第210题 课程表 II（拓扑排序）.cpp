/*
题目描述：

现在你总共有 n 门课需要选，记为 0 到 n-1。

在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]

给定课程总量以及它们的先决条件，返回你为了学完所有课程所安排的学习顺序。

可能会有多个正确的顺序，你只要返回一种就可以了。如果不可能完成所有课程，返回一个空数组。

示例 1:

输入: 2, [[1,0]]
输出: [0,1]
解释: 总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1] 。

示例 2:

输入: 4, [[1,0],[2,0],[3,1],[3,2]]
输出: [0,1,2,3] or [0,2,1,3]
解释: 总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
     因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3] 。
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//注意[0,1]的顺序是先完成1再完成0，所以出队的第一个往往是最后一个才能学习的（顺序是反着的）（写反的原因是数据处理的时候处理反了，要注意）
//此题与课程表I的区别在于需要返回一个执行顺序的数组，对本代码而言就是返回save即可
//执行用时 : 112 ms，内存消耗 : 81.8 MB，可见邻接矩阵的实现内存消耗较大，而使用队列实现后时间降低（这里因为写反了转一道变慢了）

class Solution
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
	vector<int> TopologicalSort(vector<vector<int>>& graph, vector<int>& indegree)
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
		{
			vector<int> temp;
			for (int i = save.size() - 1; i >= 0; i--)
				temp.push_back(save[i]);
			return temp;
		}
		else
			return vector<int>();
	}
};

int main_leecode210()
{
	vector<vector<int>> prerequisites;
	prerequisites.push_back(vector<int>({ 0,1 }));
	prerequisites.push_back(vector<int>({ 0,2 }));
	prerequisites.push_back(vector<int>({ 2,1 }));
	prerequisites.push_back(vector<int>({ 1,2 }));

	//prerequisites.push_back(vector<int>({ 1,0 }));

	Solution s1;
	for (auto &s : s1.findOrder(3, prerequisites))
		cout << s << " ";
	cout << endl;

	return 0;
}