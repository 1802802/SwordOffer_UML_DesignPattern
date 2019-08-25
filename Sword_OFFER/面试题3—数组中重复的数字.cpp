#include <iostream>
#include <set>
using namespace std;

//��Ŀ����������������޸������Լ������޸�����

//1.����ö�٣�ʱ�临�Ӷ�O(n2)���ռ临�Ӷ�O(1)��ţ��������ʱ��4ms���ڴ�500K
bool duplicate1(int numbers[], int length, int* duplication) 
{
	for (int i = 0; i < length; i++)
	{
		for (int j = i; j < length; j++)
		{
			if (numbers[i] == numbers[j] && i != j)
			{
				*duplication = numbers[i];
				return true;
			}
		}
	}
	return false;
}

//2.���ù�ϣ��/ɢ�к���map�����ԣ���ֻ�ܴ洢һ�����ݣ�ʱ�临�Ӷ�O(n)���ռ临�Ӷ�O(n)��ţ��������ʱ��4ms���ڴ�350K��500K
bool duplicate2(int numbers[], int length, int* duplication)
{
	set<int> number;
	for (int i = 0; i < length; i++)
	{
		auto temp = number.insert(numbers[i]);
		if (!temp.second)
		{
			*duplication = numbers[i];
			return true;
		}
	}
	return false;
}

//3.���ϵĽⷨ���±�ȶԷ���ʱ�临�Ӷ�O(n)���ռ临�Ӷ�O(1)��ţ����ʱ��4ms���ڴ�600K
bool duplicate3(int numbers[], int length, int* duplication)
{
	//1.��������Ϊ�ջ򳤶��������ʱ
	if (numbers == nullptr || length <= 0)
		return false;
	//2.���������е����ݲ�������Ŀ������ֵС��0�����n-1ʱ
	for (int i = 0; i < length; i++)
		if (numbers[i] < 0 || numbers[i] > length - 1)
			return false;
	//3.��ʽ���±�Աȷ����̣����������е���������
	for (int i = 0; i < length; i++)
	{
		//3.1 ��ǰ���ݲ����ڶ�Ӧ��������λ��ʱ�����н�һ���ж�
		while (numbers[i] != i)
		{
			//3.2 ������������λ�õ����ݣ��봦������λ�õ�������ȣ����ʾ�����������
			if (numbers[i] == numbers[numbers[i]])
			{
				*duplication = numbers[i];
				return true;
			}
			//3.3 ��������ڣ��򽫵�ǰ�����ݻ����������Լ���λ����ȥ
			else
			{
				swap(numbers[i], numbers[numbers[i]]);
			}
		}
	}
	return false;
}