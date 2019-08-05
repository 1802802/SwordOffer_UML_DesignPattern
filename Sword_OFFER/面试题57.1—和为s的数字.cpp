// ������57.1����Ϊs����������
// ��Ŀ������һ����������������һ������S���������в�����������ʹ�����ǵĺ�������S��
// ����ж�����ֵĺ͵���S������������ĳ˻���С�ġ�

#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include "BinaryTree.h"
using namespace std;

class Solution 
{
public:
	//˫ָ��һǰһ�������Ӳ������������ָ��ǰ�ƣ�С����Сָ�����
	//����ʱ�䣺3ms��ռ���ڴ棺480k
	vector<int> FindNumbersWithSum(vector<int> array, int sum) 
	{
		int head = 0;
		int end = array.size() - 1;
		while (head < end)
		{
			if (array[head] + array[end] < sum)
				head++;
			else if (array[head] + array[end] > sum)
				end--;
			else
				return vector<int>({ array[head], array[end] });
		}
		return vector<int>();
	}
};

int main_offer57_1()
{
	vector<int> array({ 1,2,4,7,11,15 });
	Solution s;
	vector<int> temp = s.FindNumbersWithSum(array, 15);
	for (auto &s : temp)
		cout << s << endl;
	return 0;
}
