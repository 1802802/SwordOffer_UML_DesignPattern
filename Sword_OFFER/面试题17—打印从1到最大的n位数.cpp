// ������17����ӡ1������nλ��
// ��Ŀ����������n����˳���ӡ����1����nλʮ����������������3����
// ��ӡ��1��2��3һֱ������3λ����999��

/*
�������˼�룺
��1����1��n��λ����ӡ���⣬���ٵ����Ϊn����0��9��ȫ�������⣬��ô�Ϳ��Խ�����̽���ݷ�����·�ݹ飩�����̣�
��2�����֡���ӡ�����⣬������Ӧ����ֵ����ֱ��������ڴ�ӡʱ����������ļ��ɣ�������һ��Ҫ�������
��3�����ںܳ���nλ�ַ����Ĵ�ӡ����������ͨ��int���������ִ洢ʵ�֣�������Ҫ�ַ������洢��λ��
*/


#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
	//1.����ʵ�֣�δ����λ������n����5ʱ��GG
	void Print1ToMaxOfNDigits_1(int n)
	{
		int max = 0;
		for (int i = 0; i < n; i++)
			max += 9 * pow(10, i);
		for (int i = 1; i <= max; i++)
			cout << i << endl;
	}

	//2.�߼�ʵ�֣�ͨ���ַ������洢����������(̫�鷳�ˣ��ҷ���)��Ȼ���ӡ
	//3.ȫ����ʵ�֣���nλ������ʮ�����������Ϊn����0��9��ȫ���м���
	void Print1ToMaxOfNDigits_2(int n)
	{
		if (n <= 0)
		{
			cout << "���������n����" << endl;
			return;
		}
		//3.1�����洢�õ��ַ���
		char* number = new char[n + 1];
		number[n] = '\0';

		//3.2�ӵ�0λ��ʼ��ִ��0��9��ȫ����
		for (int i = 0; i < 10; i++)
		{
			number[0] = i + '0';
			Print1ToMaxOfNDigitsRecursively(number, n, 0);
		}

		delete[] number;
	}

	void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index)
	{
		//�ݹ������ȫ����ִ�е����ĸ�λʱ����921��1��ʱ����ӡ���ַ���������
		if (index == length - 1)
		{
			printNumber(number);
			return;
		}
		//��·�ݹ麯��������һ����̽���ݵ�˼�롣�ӵ�0λ����n-1λ���ϵؽ���ȫ����
		for (int i = 0; i < 10; i++)
		{
			number[index + 1] = i + '0';
			Print1ToMaxOfNDigitsRecursively(number, length, index + 1);
		}
	}

	void printNumber(char* number)
	{
		int index = 0;
		//�Ƚ�������λ����Ϊ0��λ��
		while (index < strlen(number) && number[index] == '0')
			index++;
		//Ȼ��Ӳ�Ϊ0��λ�ÿ�ʼ����ӡ
		while (index < strlen(number))
			cout << (number[index++]);
		cout << endl;
	}
};


// ====================���Դ���====================
void Test(int n)
{
	Solution s;
	printf("Test for %d begins:\n", n);

	s.Print1ToMaxOfNDigits_1(n);
	s.Print1ToMaxOfNDigits_2(n);

	printf("\nTest for %d ends.\n", n);
}

int main_offer17(int argc, char* argv[])
{
	Test(1);
	Test(2);
	Test(3);
	Test(0);
	Test(-1);

	return 0;
}