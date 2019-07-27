/*
输入描述:
第一行包含2个整数 N、K，分别表示手机号码数字个数以及靓号至少有 K 个数字相同。
第二行包含 N 个字符，每个字符都是一个数字('0'-'9')，数字之间没有任何其他空白符。表示小多的手机号码。
数据范围：2 <= K <= N <= 10000

输出描述:
第一行包含一个整数，表示修改成一个靓号，最少需要的金额。
第二行包含 N 个数字字符，表示最少花费修改的新手机号。若有多个靓号花费都最少，则输出字典序最小的靓号。

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

		//如果数值>avg，则从大往小
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
		//如果数值<avg，则从小往大
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