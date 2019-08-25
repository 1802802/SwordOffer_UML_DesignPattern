#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//1.Floyd-Warshall算法，用于实现从i号顶点到j号顶点只经过前k号点的最短路径，时间复杂度O(n3)
//能解决负权边问题，但是不能解决负权回路问题（因为其可能根本不存在最短路径）
static void FloydWarshall(vector<vector<int>> &f, vector<int> &accrossPoint, vector<int> &startPoint, vector<int> &endPoint)
{
	for (int k = 0; k < accrossPoint.size(); k++)
		for (int i = 0; i < startPoint.size(); i++)
			for (int j = 0; j < endPoint.size(); j++)
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
}

//2.Dijkstra算法，用于实现指定一个点到其余各个顶点的最短路径
//f数组为存储路径权重的结果数组（邻接矩阵的方式，默认为各点路径权重），dis数组为源点到所有点的最短权重路径，book数组为已经计算了最短权重路径的点存储
static void Dijkstra(vector<vector<int>> &f, vector<int> &dis, vector<int> &book, int startPoint)
{
	//f数组初始化，除了知道权重的路径，其余全为INT_MAX，自己到自己为0

	//dis数组初始化，存储从源点到其余能到点的权重
	for (int i = 0; i < dis.size(); i++)
		dis[i] = f[startPoint][i];
	//book数组初始化，将源点自身设为1，表示当前已经找到源点的最佳路径
	for (int i = 0; i < book.size(); i++)
		book[startPoint] = 1;
	//Dijkstra算法核心
	int minNum = INT_MAX;
	int id = 0;
	//这里的i没作用，就是个循环
	for (int i = 0; i < f.size() - 1; i++)
	{
		minNum = INT_MAX;
		//遍历所有顶点，找到离源点最近的点，记录其ID
		for (int j = 0; j < f.size(); j++)
		{
			//如果当前顶点还没有加入book数组，同时从源点到该点的距离<min，那么将该值赋值给min，并存储该顶点ID
			if (book[j] == 0 && dis[j] < minNum)
			{
				minNum = dis[j];
				id = j;
			}
		}
		//离源点最近的点ID加入book数组
		book[id] = 1;
		//遍历所有顶点，如果从id顶点到j的权重小于INT_MAX，则源点到j站点的权重dis[j]，更新为dis[j]与从源点到id站点后再到j站点的权重的两者最小值
		for (int j = 0; j < f.size(); j++)
		{
			if (f[id][j] < INT_MAX)
			{
				dis[j] = min(dis[j], dis[id] + f[id][j]);
			}
		}
	}
}