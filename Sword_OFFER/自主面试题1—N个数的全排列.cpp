#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print(vector<int> print, int n)
{
	vector<int> num(n, 0);
	vector<int> use(n, 0);
	for (int i = -1; i < n; i++)
	{
		while (use[++i] == 1);
		if (i != n)
		{
			use[i] = 1;

		}
	}
}

int main_zizhu1()
{
	//�Դ����㷨��ʵ��
	int num[5] = { 1,2,5,6,9 };
	do
	{
		cout << num[0] << " " << num[1] << " " << num[2] << " " << num[3] << " " << num[4] << endl;
	} while (next_permutation(num, num + 5));
	return 0;
}

void swap(char *a, int i, int j)
{
	char temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void quanpailie(char array[], int len, int index)
{
	if (index == len)//ȫ���н���
	{
		cout << array << endl;
	}
	else
	{
		for (int i = index; i<len; ++i)
		{
			swap(array, index, i);//����i��Ԫ�ؽ�������ǰindex�±괦 
			quanpailie(array, len, index + 1);//�Եݹ�ķ�ʽ��ʣ�µ�Ԫ�ؽ���ȫ���� 
			swap(array, index, i);//����i��Ԫ�طŻ�ԭ�� 
		}
	}
}

int main_zizhu11()
{
	char array[3] = { 0 };
	cin >> array;
	quanpailie(array, strlen(array), 0);
	return 0;
}