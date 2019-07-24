#include <iostream>
#include <vector>
using namespace std;

//建立一个节点模型，表示当前节点所存储位置，并定义其移动方式
template<typename T> class Node
{
public:
	int m_row;
	int m_column;
	int m_value;
	void move_top() { m_column++; }
	void move_bottom() { m_column--; }
	void move_right() { m_row++; }
	void move_left() { m_row--; }
};

//1.首先尝试用递归的方式来实现试探回溯过程
class Solution
{
public:
	bool hasPath(char* matrix, int rows, int cols, char* str)
	{
		if (matrix == NULL || rows < 1 || cols < 1 || str == NULL)
			return false;
		//二维数组的建立必须要常量，所以只能建一个一维数组，并用memset全部赋值为false
		bool *isVisit = new bool[rows*cols];
		memset(isVisit, false, rows*cols);
		Node<char>* node = new Node<char>;

		//由于起始点可能为任何位置，所以需要将起点遍历所有位置
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				node->m_row = i;
				node->m_column = j;
				node->m_value = matrix[i*rows + j];
				if (isHasPath(matrix, node, str))
				{
					delete node;
					delete[] isVisit;
					return true;
				}
			}
		}
		delete node;
		delete[] isVisit;
		return false;
	}
};

template<typename T> bool isHasPath(char* matrix, Node<T>* node, char* str)
{
	
}

int main()
{
	return 0;
}