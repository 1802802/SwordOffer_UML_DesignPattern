/*
��������:
��һ�а���2������ N��K���ֱ��ʾ�ֻ��������ָ����Լ����������� K ��������ͬ��
�ڶ��а��� N ���ַ���ÿ���ַ�����һ������('0'-'9')������֮��û���κ������հ׷�����ʾС����ֻ����롣
���ݷ�Χ��2 <= K <= N <= 10000

�������:
��һ�а���һ����������ʾ�޸ĳ�һ�����ţ�������Ҫ�Ľ�
�ڶ��а��� N �������ַ�����ʾ���ٻ����޸ĵ����ֻ��š����ж�����Ż��Ѷ����٣�������ֵ�����С�����š�

*/

//���������������ɧ�ġ�������

//˼·����0��9Ϊ�������n��ѭ��10�Σ�ÿ��ѭ����Ѱ�ҵ�����Ϊnʱ�ﵽK��������ͬʱ����С���ۣ������Ǵ��ۣ���β����ֵ���
//�㷨��������n��ʼ������ɢ������̰���㷨˼�루����Ϊ�ȣ�������Ѱ����ͬ�����֣�Ȼ��Ѱ�ұȸ����ִ�1����С1������
//���ȴ�ͷ��β�Ҵ���n�������ٴ�β��ͷ��С��n������֮���Դ����ƣ�ֱ������K����ͬ��

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main_pinduoduo2019_1()
{
	double N, K;
	string phoneNumber;
	while (cin >> N >> K >> phoneNumber)
	{
		//1.��ʼ���׶Σ����ڶ��������ֵ��ԭʼ���ݴ洢

		//1.1 �洢��ʼֵ
		string phoneNumber_back = phoneNumber;
		double K_back = K;
		//1.2 ���ڴ洢����
		map<int, string> save;
		//1.3 ���ּ���
		int sameNum2CurrentNum = 0;      //�洢�뵱ǰnum��ͬ��������
		int currentValue = 0;
		//1.4 ���ڴ洢���Ž��Ƿ��Ѿ����ҵ�
		bool isBestResultFind = false;

		//2.��ѭ����ʵ��0-9��ȫ������
		for (int currentNum = 0; currentNum <= 9; currentNum++)
		{
			//2.1 ������Ž��Ѿ����ҵ���ֱ������ѭ����ִ�е�3��������
			if (isBestResultFind)
				break;

			//2.2 �ȱ���������ֵ�������ͬ��Ŀ�Ѿ�������K��������ֵ��ֵ��save��������
			for (int i = 0; i < N; i++)
			{
				if (phoneNumber[i] - '0' == currentNum)
					sameNum2CurrentNum++;
			}
			if (sameNum2CurrentNum >= K)
			{
				save.insert({ 0,phoneNumber });
				isBestResultFind = true;
				break;
			}

			//2.3 ���2.2δ���㣬�����sameNum2CurrentNum��K��С��������̰���㷨����������
			int maxcurrentNum = currentNum;		//currentNum�������ŵ���
			int mincurrentNum = currentNum;		//currentNum�������ŵ���
			K = K - sameNum2CurrentNum;

			//2.4 ̰���㷨ʵ�֣�currentNumͬʱ��������������1�����±߽�Ϊ9��0�����߽綼�ﵽ������K��ʹ���������ѭ��
			while ( K || (maxcurrentNum > 9 && mincurrentNum < 0))
			{
				if (!K)
					break;

				maxcurrentNum++;
				mincurrentNum--;
				//2.4.1 �ȴ����λ������Сλ���������滻��ֵ
				if (maxcurrentNum <= 9)
				{
					for (int i = 0; i < N; i++)
					{
						if (!K)
							break;
						if (phoneNumber[i] - '0' == maxcurrentNum)
						{
							currentValue += phoneNumber[i] - '0' - currentNum;
							phoneNumber[i] = currentNum + '0';
							K--;
						}
					}
				}
				//2.4.2 Ȼ���ٴ���Сλ�������λ���������滻��ֵ��2.4.1��2.4.2���Ⱥ�˳����Ϊ�˱�֤�ֵ�����С��
				if (mincurrentNum >= 0)
				{
					for (int i = N - 1; i >= 0; i--)
					{
						if (!K)
							break;
						if (phoneNumber[i] - '0' == mincurrentNum)
						{
							currentValue += currentNum - (phoneNumber[i] - '0');
							phoneNumber[i] = currentNum + '0';
							K--;
						}
					}
				}
			}

			//2.5 ��̰���㷨���̽����󣬽������ݵĴ洢�������ݵĻ�ԭ������
			save.insert({ currentValue, phoneNumber });
			phoneNumber = phoneNumber_back;
			K = K_back;
			sameNum2CurrentNum = 0;
			currentValue = 0;
		}
		//3.����ѭ����ɣ��������Žⱻ���ҳ�����������
		cout << save.begin()->first << endl;
		cout << save.begin()->second << endl;	
	}
	return 0;
}

//	�ʼ�ĳ��ԣ�����С�ֵ�����Ϊ��һ���ȼ���Ȼ����û��Ҫ����

//	//2.������С���к���һ��
//	//�����ֵ>=currentNum����Ӵ���С
//	for (int i = 0; i < N; i++)
//	{
//		if (!K)
//			break;

//		if ((phoneNumber[i] - '0' - currentNum) >= 0)
//		{
//			int tmp = phoneNumber[i] - '0' - currentNum;
//			sum += tmp;
//			phoneNumber[i] = currentNum + '0';
//			K--;
//		}
//	}
//	//�����ֵ<currentNum�����С����
//	for (int i = N - 1; i >= 0; i--)
//	{
//		if (!K)
//			break;

//		if ((phoneNumber[i] - '0' - currentNum) < 0)
//		{
//			int tmp = currentNum - (phoneNumber[i] - '0');
//			sum += tmp;
//			phoneNumber[i] = currentNum + '0';
//			K--;
//		}
//	}
//	save.insert({ sum, phoneNumber });
//	phoneNumber = back;
//	K = K_back;
//	sum = 0;