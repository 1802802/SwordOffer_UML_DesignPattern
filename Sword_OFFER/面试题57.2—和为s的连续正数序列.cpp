// ������57.2��Ϊs��������������
// ��Ŀ������һ������s����ӡ�����к�Ϊs�������������У����ٺ�������������
// ��������15������1+2+3+4+5=4+5+6=7+8=15�����Խ����ӡ��3����������1��5��4��6��7��8��

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "BinaryTree.h"
using namespace std;

//˼·��˫ָ�뷨��һǰһ�����кʹ���s�����Сָ�룬���к�С��s�������ָ��
//����ʱ�䣺5ms��ռ���ڴ棺616k
class Solution 
{
public:
	vector<vector<int> > FindContinuousSequence(int sum) 
	{
		vector<vector<int>> save;

		int first = 1;
		int second = 2;
		int mix = first + second;

		while (first < second)
		{
			//1.���㵱ǰfirst��second���еĺʹ�С���������first��С�����second���������벢˫����
			
			//for (int i = first; i <= second; i++)
			//	mix += i;
			if (mix > sum)
			{
				mix -= first;
				first++;
			}
			else if (mix < sum)
			{
				second++;
				mix += second;
			}
			else
			{
				//2.�ҵ�һ�����к�������飬Ȼ��ǰ��ָ���+1
				vector<int> temp;
				for (int i = first; i <= second; i++)
					temp.push_back(i);
				save.push_back(temp);
				first++;
				second++;
				mix += second - first + 1;
			}
		}
		return save;
	}
};

int main_offer57_2()
{
	Solution s;
	auto tmp = s.FindContinuousSequence(15);
	for (auto &s1 : tmp)
	{
		for (auto &s2 : s1)
		{
			cout << s2 << " ";
		}
		cout << endl;
	}

	return 0;
}