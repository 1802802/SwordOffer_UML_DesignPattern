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
	//自带的算法库实现
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
	if (index == len)//全排列结束
	{
		cout << array << endl;
	}
	else
	{
		for (int i = index; i<len; ++i)
		{
			swap(array, index, i);//将第i个元素交换至当前index下标处 
			quanpailie(array, len, index + 1);//以递归的方式对剩下的元素进行全排列 
			swap(array, index, i);//将第i个元素放回原处 
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