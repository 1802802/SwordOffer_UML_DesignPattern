#include <iostream>
#include <vector>
using namespace std;

//������һ�֣����ϵķ����������Ͻǿ�ʼ��������С��target��ɾ�У�����target��ɾ��
//ɾ��ԭ��һ������������С��target��ɾ��ԭ��һ������С����������target
//���ͨ��vector�ṹ��ȷ����Ŀ�е��к��д�С
//ţ����ʱ��12ms���ڴ�1628K
bool Find(int target, vector<vector<int>> array) 
{
	//1.����õ���ά�����rows��columns�����������Ͻǵĳ�ʼֵ
	int rows = array.size();
	int columns = array[0].size();
	int row = 0;
	int column = columns - 1;

	//2.���ϵ�ѡȡ���Ͻ�����
	while (row < rows && column >= 0)
	{
		if (target > array[row][column])
		{
			row++;
			continue;
		}
		if (target < array[row][column])
		{
			column--;
			continue;
		}
		if (target == array[row][column])
			return true;
	}
	return false;
}