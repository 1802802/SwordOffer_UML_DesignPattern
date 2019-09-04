// ������49������
// ��Ŀ����ֻ����������2��3��5��������������Ugly Number����
// ����6��8���ǳ�������14���ǣ���Ϊ������������7�� 
// ϰ�������ǰ�1�����ǵ�һ���������󰴴�С�����˳��ĵ�N��������

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution 
{
public:
	//1.�������Է���Ч�ʿ��ǣ�
	int GetUglyNumber_Solution1(int index) 
	{
		int i = 1;
		int sum = 0;
		while (1)
		{
			int current = i;
			while (current % 2 == 0)
				current /= 2;
			while (current % 3 == 0)
				current /= 3;
			while (current % 5 == 0)
				current /= 5;

			if (current == 1)
				sum++;
			if (index == sum)
				return i;
			i++;
			cout << i << endl;
		}
	}

	//2.���ö�̬�滮������Ϊ���й�����2,3,5�ĵ�������������ɣ������С��Ϊ��ͬ�����µ����ݴ�С������ʱ�䣺3ms��ռ���ڴ棺476k
	//������2,3,5�����ϼ����Լ��ı���������Լ�������ѡ������+1���ɴ˲��ϵش洢������������
	int GetUglyNumber_Solution2(int index)
	{
		if (index < 7)
			return index;
		//�ȷ����ڴ�Ϻã���ȻҪ���ϵ��ƶ����ݵ����ڴ�
		vector<int> uglyNumberSave(index);
		uglyNumberSave[0] = 1;
		int times_2 = 0; int times_3 = 0; int times_5 = 0;
		for (int i = 1; i < index; i++)
		{
			//ע������ĵ�ʽ���������ԣ�ʹ��˵�����һֱ����ֻ��2,3,5
			int next_2 = uglyNumberSave[times_2] * 2;
			int next_3 = uglyNumberSave[times_3] * 3;
			int next_5 = uglyNumberSave[times_5] * 5;
			//ע��min��max�����Ĳ�ֻ��������������Ļ���initialize_listʵ��
			//initialize_list��Ϊһ��ģ���࣬��������������ʼ�������࣬���ұ���Ҳ���Ե�����������ʹ�ã�ֻ�ǱȽϺ��ף�ֻ�ṩ��begin(), end(), size()����������
			uglyNumberSave[i] = min({ next_2, next_3, next_5 });
			//����if�����ڣ���ԭ��������Ҫ��֤uglynumberǰ��������ܳ����ظ�ֵ����curnum�����е��ڶ��next�������
			if (next_2 == uglyNumberSave[i])
				times_2++;
			if (next_3 == uglyNumberSave[i])
				times_3++;
			if (next_5 == uglyNumberSave[i])
				times_5++;
		}
		return uglyNumberSave[index - 1];
	}
};

// ====================���Դ���====================
static void Test(int index, int expected)
{
	Solution s;
	if (s.GetUglyNumber_Solution2(index) == expected)
		printf("solution1 passed\n");
	else
		printf("solution1 failed\n");

	//if (GetUglyNumber_Solution2(index) == expected)
	//	printf("solution2 passed\n");
	//else
	//	printf("solution2 failed\n");
}

int main_offer49(int argc, char* argv[])
{
	Test(1, 1);

	Test(2, 2);
	Test(3, 3);
	Test(4, 4);
	Test(5, 5);
	Test(6, 6);
	Test(7, 8);
	Test(8, 9);
	Test(9, 10);
	Test(10, 12);
	Test(11, 15);

	Test(1500, 859963392);

	Test(0, 0);

	return 0;
}
