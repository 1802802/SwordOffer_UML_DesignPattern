#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class node
{
public:
	int m_value = INT_MAX;
	int m_level = -1;
	vector<int> m_child;
};

int calculateMaxOil(int numNodes, int sourceNode, vector<vector<int> > & network)
{
	vector<node> save(numNodes + 2, node());
	int maxlevel = 0;
	for (auto &s : network)
	{
		save[s[1]].m_value = s[2];

		if (save[s[0]].m_level == -1)
			save[s[0]].m_level = 0;

		save[s[0]].m_child.push_back(s[1]);
		save[s[1]].m_level = save[s[0]].m_level + 1;
		maxlevel = save[s[1]].m_level;
	}
	for (int i = maxlevel - 1; i >= 0; i--)
	{
		for (auto &s : save)
		{
			if (s.m_level == i)
			{
				int sum = 0;
				for (auto &s2 : s.m_child)
				{
					sum += (save[s2].m_value);
				}
				if (sum < s.m_value)
					s.m_value = sum;
			}
		}
	}
	for (auto &s : save)
	{
		if (s.m_level == 0)
			return s.m_value;
	}
	return 0;
}

int main_zhongxing222()
{
	int numNodes = 6;
	int sourceNode = 4;
	vector<int> vec1({ 1,2,60 });
	vector<int> vec2({ 1,3,40 });
	vector<int> vec3({ 2,4,20 });
	vector<int> vec4({ 2,5,40 });
	vector<int> vec5({ 3,6,25 });
	vector<int> vec6({ 3,7,15 });
	vector<vector<int> > network({ vec1,vec2,vec3,vec4,vec5,vec6 });
	cout << calculateMaxOil(numNodes, sourceNode, network) << endl;
	return 0;
}