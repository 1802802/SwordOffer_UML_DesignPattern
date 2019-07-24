#include <iostream>
#include <vector>
using namespace std;

//����һ���ڵ�ģ�ͣ���ʾ��ǰ�ڵ����洢λ�ã����������ƶ���ʽ
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

//1.���ȳ����õݹ�ķ�ʽ��ʵ����̽���ݹ���
class Solution
{
public:
	bool hasPath(char* matrix, int rows, int cols, char* str)
	{
		if (matrix == NULL || rows < 1 || cols < 1 || str == NULL)
			return false;
		//��ά����Ľ�������Ҫ����������ֻ�ܽ�һ��һά���飬����memsetȫ����ֵΪfalse
		bool *isVisit = new bool[rows*cols];
		memset(isVisit, false, rows*cols);
		Node<char>* node = new Node<char>;

		//������ʼ�����Ϊ�κ�λ�ã�������Ҫ������������λ��
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