// ������29��˳ʱ���ӡ����
// ��Ŀ������һ�����󣬰��մ���������˳ʱ���˳�����δ�ӡ��ÿһ�����֣�
// ���磬�����������4 X 4���� 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 
// �����δ�ӡ������1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.

#include <iostream>
#include <vector>
using namespace std;

class Solution 
{
public:
	//����ʱ�䣺3ms��ռ���ڴ棺504k

	/*˼·��Ҳ���ľ��󷨣�����ÿ�������Դ�ѭ�������Ҷ˵�ռ����ĿҲ��ͬ���������£�
	Ϊ������Ҫ���󣨵�һ�����Ҿ���ռ�������˵㣬�ڶ������¾������������������ռ��һ���˵㣬���Ĵ����Ͼ���ռ�ݶ˵㣩
	��ͼ��֪����һ�εĴ����Ҵ�ӡռ���������˵㣬������Ӧ���ֲ�ͬ���������˳��ִ�У����m��n���󣩡�
	----
	|??|
	|??|
	---|
	
	������n��n�����˳ʱ��swap�ľ��󻮷����£�
	Ϊ�糵�ľ����ĸ������ռ��һ���˵㣩�������ڽ��������˳ʱ�����ʱ����ת֮���
	----|
	|--||
	||?||
	||--|
	|----
	*/
	//

	//�����������־��δ治���ڵ����⣬�������������Ӧ�������������Ҿ���ض�������
	//��˳ָ����ת֮����������ľ��αض����ڣ���Ҫ���������ݲ�����
	vector<int> printMatrix(vector<vector<int> > matrix)
	{
		vector<int> save;
		if (matrix.empty())
			return save;

		//row_startΪ��ʼ�кţ�row_endΪ����кţ�col_startΪ��ʼ�кţ�col_endΪ����к�	
		int row_start = 0, row_end = matrix.size() - 1;
		int col_start = 0, col_end = matrix[0].size() - 1;

		//����ѭ������������ʼ�к�С������к�����ʼ�к�С������кţ�ÿ��ѭ������һ��Ȧ��
		while (row_start <= row_end && col_start <= col_end)
		{
			//1.���Ҿ���û�����ƣ�ռ�������˵㣬��Ҫ����һ��һ�вŴ��ڣ�����û�����ƣ�
			for (int i = col_start; i <= col_end; i++)
				save.push_back(matrix[row_start][i]);
			//2.���¾����������ƣ���Ҫ��������һ�вŴ��ڣ�
			if (row_start < row_end)
				for (int i = row_start + 1; i <= row_end; i++)
					save.push_back(matrix[i][col_end]);
			//3.��������������ƺ������ƣ���Ҫ�����������вŴ��ڣ�
			if (row_start < row_end && col_start < col_end)
				for (int i = col_end - 1; i >= col_start; i--)
					save.push_back(matrix[row_end][i]);
			//4.���Ͼ��������⣬û�ж˵㣬��������Ҫ���ǵ�������Ҫ����һ�㣬ͬʱҲ�������ƣ���Ҫ�����������вŴ��ڣ�
			if (row_start < row_end - 1 && col_start < col_end)
				for (int i = row_end - 1; i > row_start; i--)
					save.push_back(matrix[i][col_start]);
			//�����һȦ��������ʼ��+1������-1
			row_start++; row_end--; col_start++; col_end--;
		}

		return save;
	}
};

// ====================���Դ���====================
void Test(int columns, int rows)
{
	printf("Test Begin: %d columns, %d rows.\n", columns, rows);

	if (columns < 1 || rows < 1)
		return;

	vector<vector<int> > numbers(rows);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			numbers[i].push_back(i * columns + j + 1);
		}
	}
	Solution s;
	vector<int> tmp = s.printMatrix(numbers);
	for (auto &s1 : tmp)
	{
		cout << s1 << " ";
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	/*
	1
	*/
	Test(1, 1);

	/*
	1    2
	3    4
	*/
	Test(2, 2);

	/*
	1    2    3    4
	5    6    7    8
	9    10   11   12
	13   14   15   16
	*/
	Test(4, 4);

	/*
	1    2    3    4    5
	6    7    8    9    10
	11   12   13   14   15
	16   17   18   19   20
	21   22   23   24   25
	*/
	Test(5, 5);

	/*
	1
	2
	3
	4
	5
	*/
	Test(1, 5);

	/*
	1    2
	3    4
	5    6
	7    8
	9    10
	*/
	Test(2, 5);

	/*
	1    2    3
	4    5    6
	7    8    9
	10   11   12
	13   14   15
	*/
	Test(3, 5);

	/*
	1    2    3    4
	5    6    7    8
	9    10   11   12
	13   14   15   16
	17   18   19   20
	*/
	Test(4, 5);

	/*
	1    2    3    4    5
	*/
	Test(5, 1);

	/*
	1    2    3    4    5
	6    7    8    9    10
	*/
	Test(5, 2);

	/*
	1    2    3    4    5
	6    7    8    9    10
	11   12   13   14    15
	*/
	Test(5, 3);

	/*
	1    2    3    4    5
	6    7    8    9    10
	11   12   13   14   15
	16   17   18   19   20
	*/
	Test(5, 4);

	return 0;
}


//���Ե�ʹ���ľ��󷨵ķ���������ʧ���ˣ����ַ������������ڶ���˳ָ��Ľ�����������n��n�Ľ������������Ǵ�ӡ
//˼·�����Ĳ���ӡ�����������rows������columns������ÿһ���Ĳ��������������һ����
//1.���÷糵�ľ��η�
vector<int> printMatrixsssss(vector<vector<int> > matrix)
{
	vector<int> save;
	vector<int> save1;
	vector<int> save2;
	vector<int> save3;
	vector<int> save4;

	if (matrix.empty())
		return save;

	int rows = matrix.size();
	int columns = matrix[0].size();
	int lsize = columns - 1;
	int num = 0;

	//1.1ѭ����Ȧ��ʵ�ַ�Χ������
	for (int i = 0; i < rows >> 1; i++)
	{
		//1.2ѭ����Ȧ��ʵ��˳ʱ�������
		for (int j = num; j < lsize; j++)
		{
			if (i >= 0 && j >= 0)
				save1.push_back(matrix[i][j]);
			if (j >= 0 && columns - i - 1 >= 0)
				save2.push_back(matrix[j][columns - i - 1]);
			if (rows - i - 1 >= 0 && columns - j - 1 >= 0)
				save3.push_back(matrix[rows - i - 1][columns - j - 1]);
			if (rows - j - 1 >= 0 && i >= 0)
				save4.push_back(matrix[rows - j - 1][i]);
		}
		save.insert(save.end(), save1.begin(), save1.end());
		save.insert(save.end(), save2.begin(), save2.end());
		save.insert(save.end(), save3.begin(), save3.end());
		save.insert(save.end(), save4.begin(), save4.end());
		save1.clear();
		save2.clear();
		save3.clear();
		save4.clear();
		lsize--;
		num++;
	}

	return save;
}