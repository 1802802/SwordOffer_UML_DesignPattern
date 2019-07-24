#include <iostream>
#include <vector>
using namespace std;

//1.无脑法，顺序查找，时间复杂度O(n)
//牛客网31ms，内存863K
class Solution1
{
public:
	int minNumberInRotateArray(vector<int> rotateArray) 
	{
		if (rotateArray.size() == 0)
			return 0;
		int min;
		for (auto &s : rotateArray)
		{
			if (s < min)
				min = s;
		}
		return min;
	}
};

//2.排序数组的查找法（与二分查找思想对应）
//思想：根据递增序列旋转后仍为递增序列的特性，将旋转后的数组分为前后两个递增序列，采用前后双指针法
//牛客网25ms，内存608K（加入原数组的判断处理很重要）
class Solution2
{
public:
	int minNumberInRotateArray(vector<int> rotateArray)
	{
		if (rotateArray.size() <= 0)
			return 0;
		int index1 = 0, indexMid = 0;
		int index2 = rotateArray.size() - 1;
		//对数组完全旋转了一遍和初始一毛一样的情况的特殊处理，即发现数组第一位小于最后一位
		if (rotateArray[index1] < rotateArray[index2])
			return rotateArray[index1];
		while (index2 - index1 != 1) //当两个索引贴近时跳出循环
		{
			indexMid = (index1 + index2) >> 1;
			//如果indexMid的值小于index2的值，代表indexMid处于后面的递增序列，将后面的指针前移
			if (rotateArray[indexMid] <= rotateArray[index2])
				index2 = indexMid;
			//如果indexMid的值大于index1的值，代表indexMid处于前面的递增序列，将前面的指针后移
			else if (rotateArray[indexMid] >= rotateArray[index1])
				index1 = indexMid;
		}
		return rotateArray[index2]; //最终得到两个索引中，index为后方的递增序列过来的，所以其必为最小值
	}
};

//3.如果考虑的更深一点，当遇到数组为11101这样的只有两个数字组成的情况，index1,2,mid的数据全部一样时，
//如果还采用现在的做法，找到的值并非最小值，所以这种情况只能采用顺序查找
//牛客网25ms，内存616K（加入11101的相关处理后内存变大了）
class Solution3
{
public:
	int minNumberInRotateArray(vector<int> rotateArray)
	{
		if (rotateArray.size() <= 0)
			return 0;
		int index1 = 0, indexMid = 0;
		int index2 = rotateArray.size() - 1;
		//3.1对数组完全旋转了一遍和初始一毛一样的情况的特殊处理，即发现数组第一位小于最后一位
		if (rotateArray[index1] < rotateArray[index2])
			return rotateArray[index1];
		while (index2 - index1 != 1) //当两个索引贴近时跳出循环
		{
			indexMid = (index1 + index2) >> 1;
			//3.2全部相同的情况处理（当满足以下的情况时，代表内部的所有数已经基本完全相同了）		
			if (rotateArray[index1] == rotateArray[indexMid] && rotateArray[indexMid] == rotateArray[index2])
			{
				int min = rotateArray[index1];
				for (int i = index1; i < index2; i++)
					if (min > rotateArray[i])
						min = rotateArray[i];
				return min;
			}
			//3.3常规流程
			//如果indexMid的值小于index2的值，代表indexMid处于后面的递增序列，将后面的指针前移
			if (rotateArray[indexMid] <= rotateArray[index2])
				index2 = indexMid;
			//如果indexMid的值大于index1的值，代表indexMid处于前面的递增序列，将前面的指针后移
			else if (rotateArray[indexMid] >= rotateArray[index1])
				index1 = indexMid;
		}
		return rotateArray[index2]; //最终得到两个索引中，index为后方的递增序列过来的，所以其必为最小值
	}
};