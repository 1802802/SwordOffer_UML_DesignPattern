#include <iostream>
#include <vector>
#include <stack>
using namespace std;

//2.ջ��δʵ�֣�ȷʵ�е����ôд��

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
		//��ά����Ľ�������Ҫ����������ֻ�ܽ�һ��һά���飬����memsetȫ����ֵΪfalse
		int pathLength = 0;
		Node<char>* node = new Node<char>;
		bool *isVisited = new bool[rows*cols];
		memset(isVisited, false, rows*cols);

		//������ʼ�����Ϊ�κ�λ�ã�������Ҫ������������λ�ã��ɴ�Ҳ���˵ݹ����̣�ֻ��Ҫ�ҳ��ĸ���˳���·����ȫһ���ľ���
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
		//isVisited��һ��ָ��һ��bool�����ָ�룬��boolֵ�ǳ�������Ȼ���Ǵ��ڶ�����㲻��ȥdelete����
		//delete[] isVisited;
		return false;
	}
private:
	template<typename T> bool isHasPath(char* matrix, int rows, int cols, Node<T>* node, char* str, int pathLength, bool* isVisited)
	{
		node->m_value = matrix[(node->m_row)*cols + node->m_col];
		//�ݹ�������ҵ�·�������һλʱ��ʾ�������
		if (str[pathLength] == '\0')
			return true;
		bool hasPath = false;
		stack<Node<char>*> sta;
		//1.�жϵ�ǰ����Ľڵ��Ƿ���������������뵱ǰ·���ڵ����������δ����������
		if (node->m_row >= 0 && node->m_row < rows && node->m_col >= 0 && node->m_col < cols && node->m_value == str[pathLength] && !isVisited[(node->m_row)*cols + node->m_col])
		{
			//2.�����������󣬽�·��ǰ�ƣ���ǰ��ķ���λ��true
			++pathLength;
			isVisited[(node->m_row)*cols + node->m_col] = true;
			sta.push(node);
			//3.�����������ĸ����������̽

			//�ڵ�����Ĺؼ����������node���ű��ˣ��ĳɲ����ű伴�ɣ�����
			hasPath = isHasPath(matrix, rows, cols, node->move_left(), str, pathLength, isVisited)
				|| isHasPath(matrix, rows, cols, node->move_top(), str, pathLength, isVisited)
				|| isHasPath(matrix, rows, cols, node->move_right(), str, pathLength, isVisited)
				|| isHasPath(matrix, rows, cols, node->move_bottom(), str, pathLength, isVisited);
			//4.����ڵ�ǰ�ڵ��������̽�ж�û���ҵ����������ĵ㣬��ô�ͽ��л��ݣ�·�����ƣ�����λ��false
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

//1.���ȳ����õݹ�ķ�ʽ��ʵ����̽���ݹ��̣�ţ����3ms��376K
//�������ǹ���ջ�ķ�ʽ��������ջ��Ҫ�Ǵ���һ�����״̬����������ʺ���Ͻڵ������ʹ�ã��ݹ�ķ�ʽ��ֱ�ӱ��ջ�ķ�ʽ����Щͷ��
class Solution2
{
public:
	bool hasPath(char* matrix, int rows, int cols, char* str)
	{
		if (matrix == NULL || rows < 1 || cols < 1 || str == NULL)
			return false;
		//��ά����Ľ�������Ҫ����������ֻ�ܽ�һ��һά���飬����memsetȫ����ֵΪfalse
		int pathLength = 0;
		bool *isVisited = new bool[rows*cols];
		memset(isVisited, false, rows*cols);

		//������ʼ�����Ϊ�κ�λ�ã�������Ҫ������������λ�ã��ɴ�Ҳ���˵ݹ����̣�ֻ��Ҫ�ҳ��ĸ���˳���·����ȫһ���ľ���
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
		//�����delete[]���Իã����˾ͻᱨ��
		//delete[] isVisited;
		return false;
	}
private:
	bool isHasPath(char* matrix, int rows, int cols, int row, int col, char* str, int pathLength, bool* isVisited)
	{
		//�ݹ�������ҵ�·�������һλʱ��ʾ�������
		if (str[pathLength] == '\0')
			return true;
		bool hasPath = false;
		//1.�жϵ�ǰ����Ľڵ��Ƿ���������������뵱ǰ·���ڵ����������δ����������
		if (row >= 0 && row < rows && col >= 0 && col < cols && matrix[row*cols + col] == str[pathLength] && !isVisited[row*cols + col])
		{
			//2.�����������󣬽�·��ǰ�ƣ���ǰ��ķ���λ��true
			++pathLength;
			isVisited[row*cols + col] = true;
			//3.�����������ĸ����������̽�������||Ҳ�ܾ��һ��ǰ�淵����trueֱ�Ӿͷ���true�ˣ�
			hasPath = isHasPath(matrix, rows, cols, row, col - 1, str, pathLength, isVisited)
				|| isHasPath(matrix, rows, cols, row - 1, col, str, pathLength, isVisited)
				|| isHasPath(matrix, rows, cols, row, col + 1, str, pathLength, isVisited)
				|| isHasPath(matrix, rows, cols, row + 1, col, str, pathLength, isVisited);
			//4.����ڵ�ǰ�ڵ��������̽�ж�û���ҵ����������ĵ㣬��ô�ͽ��л��ݣ�·�����ƣ�����λ��false
			//��̽���ݷ����������յĽ����Σ���Ҫ���л��ݣ��ɴ˿����ҵ�����·����������������ʵ�����ж�
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