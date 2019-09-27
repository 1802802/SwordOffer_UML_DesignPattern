//#include <iostream>
//#include <string>
//#include <algorithm>
//#include <vector>
//#include <map>
//#include <sstream>
//using namespace std;
//
//#include <iostream>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//static void Dijkstra(vector<vector<int>> &f, vector<vector<int>> &dis, vector<int> &book, int startPoint)
//{
//	for (int i = 0; i < dis.size(); i++)
//		dis[i] = f[startPoint][i];
//	for (int i = 0; i < book.size(); i++)
//		book[startPoint] = 1;
//
//	int minNum = INT_MAX;
//	int id = 0;
//
//	for (int i = 0; i < f.size() - 1; i++)
//	{
//		minNum = INT_MAX;
//		for (int j = 0; j < f.size(); j++)
//		{
//			if (book[j] == 0 && dis[j] < minNum)
//			{
//				minNum = dis[j];
//				id = j;
//			}
//		}
//
//		book[id] = 1;
//
//		for (int j = 0; j < f.size(); j++)
//		{
//			if (f[id][j] < INT_MAX)
//			{
//				dis[j] = min(dis[j], dis[id] + f[id][j]);
//			}
//		}
//	}
//}