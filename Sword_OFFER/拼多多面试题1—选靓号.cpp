/*
��������:
��һ�а���2������ N��K���ֱ��ʾ�ֻ��������ָ����Լ����������� K ��������ͬ��
�ڶ��а��� N ���ַ���ÿ���ַ�����һ������('0'-'9')������֮��û���κ������հ׷�����ʾС����ֻ����롣
���ݷ�Χ��2 <= K <= N <= 10000

�������:
��һ�а���һ����������ʾ�޸ĳ�һ�����ţ�������Ҫ�Ľ�
�ڶ��а��� N �������ַ�����ʾ���ٻ����޸ĵ����ֻ��š����ж�����Ż��Ѷ����٣�������ֵ�����С�����š�

*/


#include<iostream>
#include<string>
using namespace std;

int main_pinduoduo2019_1()
{
	double N, K;
	string phoneNumber;
	while (cin >> N >> K >> phoneNumber)
	{
		double sum = 0.0;
		for (auto &s : phoneNumber)
			sum += s - '0';
		double avg = sum / N;
		double avg2 = -1.0;
		if (avg - (int)avg > 0.5)
			avg = (int)(avg + 1);
		else if (avg - (int)avg <= 0.5)
			avg = (int)(avg);

		for(auto &s : phoneNumber)


		sum = 0;

		//�����ֵ>avg����Ӵ���С
		for (auto &s : phoneNumber)
		{
			if (!K)
				break;
			
			if ((s - '0' - avg) >= 0)
			{
				int tmp = s - '0' - avg;
				sum += tmp;
				s = avg + '0';
				K--;
			}		
		}
		//�����ֵ<avg�����С����
		for (int i = phoneNumber.size() - 1; i >= 0; i--)
		{
			if (!K)
				break;

			if ((phoneNumber[i] - '0' - avg) < 0)
			{
				int tmp = avg - (phoneNumber[i] - '0');
				sum += tmp;
				phoneNumber[i] = avg + '0';
				K--;
			}
		}

		cout << sum << endl;
		cout << phoneNumber << endl;
	}

	return 0;
}