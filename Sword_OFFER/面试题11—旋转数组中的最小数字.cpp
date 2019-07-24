#include <iostream>
#include <vector>
using namespace std;

//1.���Է���˳����ң�ʱ�临�Ӷ�O(n)
//ţ����31ms���ڴ�863K
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

//2.��������Ĳ��ҷ�������ֲ���˼���Ӧ��
//˼�룺���ݵ���������ת����Ϊ�������е����ԣ�����ת��������Ϊǰ�������������У�����ǰ��˫ָ�뷨
//ţ����25ms���ڴ�608K������ԭ������жϴ������Ҫ��
class Solution2
{
public:
	int minNumberInRotateArray(vector<int> rotateArray)
	{
		if (rotateArray.size() <= 0)
			return 0;
		int index1 = 0, indexMid = 0;
		int index2 = rotateArray.size() - 1;
		//��������ȫ��ת��һ��ͳ�ʼһëһ������������⴦�������������һλС�����һλ
		if (rotateArray[index1] < rotateArray[index2])
			return rotateArray[index1];
		while (index2 - index1 != 1) //��������������ʱ����ѭ��
		{
			indexMid = (index1 + index2) >> 1;
			//���indexMid��ֵС��index2��ֵ������indexMid���ں���ĵ������У��������ָ��ǰ��
			if (rotateArray[indexMid] <= rotateArray[index2])
				index2 = indexMid;
			//���indexMid��ֵ����index1��ֵ������indexMid����ǰ��ĵ������У���ǰ���ָ�����
			else if (rotateArray[indexMid] >= rotateArray[index1])
				index1 = indexMid;
		}
		return rotateArray[index2]; //���յõ����������У�indexΪ�󷽵ĵ������й����ģ��������Ϊ��Сֵ
	}
};

//3.������ǵĸ���һ�㣬����������Ϊ11101������ֻ������������ɵ������index1,2,mid������ȫ��һ��ʱ��
//������������ڵ��������ҵ���ֵ������Сֵ�������������ֻ�ܲ���˳�����
//ţ����25ms���ڴ�616K������11101����ش�����ڴ����ˣ�
class Solution3
{
public:
	int minNumberInRotateArray(vector<int> rotateArray)
	{
		if (rotateArray.size() <= 0)
			return 0;
		int index1 = 0, indexMid = 0;
		int index2 = rotateArray.size() - 1;
		//3.1��������ȫ��ת��һ��ͳ�ʼһëһ������������⴦�������������һλС�����һλ
		if (rotateArray[index1] < rotateArray[index2])
			return rotateArray[index1];
		while (index2 - index1 != 1) //��������������ʱ����ѭ��
		{
			indexMid = (index1 + index2) >> 1;
			//3.2ȫ����ͬ������������������µ����ʱ�������ڲ����������Ѿ�������ȫ��ͬ�ˣ�		
			if (rotateArray[index1] == rotateArray[indexMid] && rotateArray[indexMid] == rotateArray[index2])
			{
				int min = rotateArray[index1];
				for (int i = index1; i < index2; i++)
					if (min > rotateArray[i])
						min = rotateArray[i];
				return min;
			}
			//3.3��������
			//���indexMid��ֵС��index2��ֵ������indexMid���ں���ĵ������У��������ָ��ǰ��
			if (rotateArray[indexMid] <= rotateArray[index2])
				index2 = indexMid;
			//���indexMid��ֵ����index1��ֵ������indexMid����ǰ��ĵ������У���ǰ���ָ�����
			else if (rotateArray[indexMid] >= rotateArray[index1])
				index1 = indexMid;
		}
		return rotateArray[index2]; //���յõ����������У�indexΪ�󷽵ĵ������й����ģ��������Ϊ��Сֵ
	}
};