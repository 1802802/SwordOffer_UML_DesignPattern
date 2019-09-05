#include <iostream>
#include <vector>
#include <stack>
using namespace std;

//2.栈（未实现，确实有点蠢这么写）

template<typename T> class Node
{
public:
	int m_row = 0;
	int m_col = 0;
	T m_value;
	void setValue(int row, int col, T value) { m_row = row; m_col = col; m_value = value; }
	Node<T>* move_top() { m_row--; return this; }
	Node<T>* move_bottom() { m_row++; return this; }
	Node<T>* move_left() { m_col--; return this; }
	Node<T>* move_right() { m_col++; return this; }
};

class Solution
{
public:
	bool hasPath(char* matrix, int rows, int cols, char* str)
	{
		if (matrix == NULL || rows < 1 || cols < 1 || str == NULL)
			return false;
		//二维数组的建立必须要常量，所以只能建一个一维数组，并用memset全部赋值为false
		int pathLength = 0;
		Node<char>* node = new Node<char>;
		bool *isVisited = new bool[rows*cols];
		memset(isVisited, false, rows*cols);

		//由于起始点可能为任何位置，所以需要将起点遍历所有位置，由此也简化了递归流程，只需要找出四个点顺序和路径完全一样的就行
		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < cols; col++)
			{
				node->setValue(row, col, matrix[row*cols + col]);
				if (isHasPath(matrix, rows, cols, node, str, pathLength, isVisited))
				{
					//delete[] isVisited;
					return true;
				}
			}
		}
		//isVisited是一个指向一个bool数组的指针，而bool值是常量，虽然它们存在堆里，但你不能去delete常量
		//delete[] isVisited;
		return false;
	}
private:
	template<typename T> bool isHasPath(char* matrix, int rows, int cols, Node<T>* node, char* str, int pathLength, bool* isVisited)
	{
		node->m_value = matrix[(node->m_row)*cols + node->m_col];
		//递归基，当找到路径的最后一位时表示查找完成
		if (str[pathLength] == '\0')
			return true;
		bool hasPath = false;
		stack<Node<char>*> sta;
		//1.判断当前输入的节点是否满足基本条件、与当前路径节点相等条件、未被访问条件
		if (node->m_row >= 0 && node->m_row < rows && node->m_col >= 0 && node->m_col < cols && node->m_value == str[pathLength] && !isVisited[(node->m_row)*cols + node->m_col])
		{
			//2.当满足条件后，将路径前移，当前点的访问位赋true
			++pathLength;
			isVisited[(node->m_row)*cols + node->m_col] = true;
			sta.push(node);
			//3.从上下左右四个方向进行试探

			//节点问题的关键在于这里的node跟着变了，改成不跟着变即可，哈哈
			hasPath = isHasPath(matrix, rows, cols, node->move_left(), str, pathLength, isVisited)
				|| isHasPath(matrix, rows, cols, node->move_top(), str, pathLength, isVisited)
				|| isHasPath(matrix, rows, cols, node->move_right(), str, pathLength, isVisited)
				|| isHasPath(matrix, rows, cols, node->move_bottom(), str, pathLength, isVisited);
			//4.如果在当前节点的所有试探中都没有找到符合条件的点，那么就进行回溯，路径后移，访问位赋false
			if (!hasPath)
			{
				--pathLength;
				isVisited[(node->m_row)*cols + node->m_col] = false;
			}
		}
		if (!sta.empty())
		{
			node = sta.top();
			sta.pop();
		}

		return hasPath;
	}
};

//1.首先尝试用递归的方式来实现试探回溯过程，牛客网3ms，376K
//后来考虑过用栈的方式，发现用栈主要是存上一个点的状态，这种情况适合配合节点类进行使用，递归的方式想直接变成栈的方式会有些头疼
class Solution2
{
public:
	bool hasPath(char* matrix, int rows, int cols, char* str)
	{
		if (matrix == NULL || rows < 1 || cols < 1 || str == NULL)
			return false;
		//二维数组的建立必须要常量，所以只能建一个一维数组，并用memset全部赋值为false
		int pathLength = 0;
		bool *isVisited = new bool[rows*cols];
		memset(isVisited, false, rows*cols);

		//由于起始点可能为任何位置，所以需要将起点遍历所有位置，由此也简化了递归流程，只需要找出四个点顺序和路径完全一样的就行
		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < cols; col++)
			{
				if (isHasPath(matrix, rows, cols, row, col, str, pathLength, isVisited))
				{
					//delete[] isVisited;
					return true;
				}
			}
		}
		//这里的delete[]很迷幻，有了就会报错
		//delete[] isVisited;
		return false;
	}
private:
	bool isHasPath(char* matrix, int rows, int cols, int row, int col, char* str, int pathLength, bool* isVisited)
	{
		//递归基，当找到路径的最后一位时表示查找完成
		if (str[pathLength] == '\0')
			return true;
		bool hasPath = false;
		//1.判断当前输入的节点是否满足基本条件、与当前路径节点相等条件、未被访问条件
		if (row >= 0 && row < rows && col >= 0 && col < cols && matrix[row*cols + col] == str[pathLength] && !isVisited[row*cols + col])
		{
			//2.当满足条件后，将路径前移，当前点的访问位赋true
			++pathLength;
			isVisited[row*cols + col] = true;
			//3.从上下左右四个方向进行试探（这里的||也很精妙，一旦前面返回了true直接就返回true了）
			hasPath = isHasPath(matrix, rows, cols, row, col - 1, str, pathLength, isVisited)
				|| isHasPath(matrix, rows, cols, row - 1, col, str, pathLength, isVisited)
				|| isHasPath(matrix, rows, cols, row, col + 1, str, pathLength, isVisited)
				|| isHasPath(matrix, rows, cols, row + 1, col, str, pathLength, isVisited);
			//4.如果在当前节点的所有试探中都没有找到符合条件的点，那么就进行回溯，路径后移，访问位赋false
			//试探回溯法，无论最终的结果如何，都要进行回溯（由此可以找到多条路径），所以这里其实不用判断
			if (!hasPath)
			{
				--pathLength;
				isVisited[row*cols + col] = false;
			}
		}
		return hasPath;
	}
};

int main_offer12()
{
	char *matrix = "abcdefghijkl", *str = "bfgk";
	int rows = 3, cols = 4; 
	Solution s;
	cout << s.hasPath(matrix, rows, cols, str) << endl;

	return 0;
}