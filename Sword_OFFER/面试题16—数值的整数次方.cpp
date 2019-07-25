#include <iostream>
using namespace std;

/*
�������˼�룺
��1����������ĺϷ��жϣ��Լ�������Щ��Ϣ�Ĵ��ݷ�ʽ��
��2������double���͵ĸ������ƣ����粻����==0.0����Ҫ��fabs�ȣ������жϷ�ʽ��fabs(n-0.0)<0.000001
��3�����ڴη�����Ŀ������㷽ʽ��ͨ���ж�nΪż���������������㣬�Լ�������Ϊ����ʱ�ĵ�������
ֱ��a^n = a^(n/2)*a^(n/2) (ż��even)�� a^n = a^((n-1)/2)*a^((n-1)/2)*a (����odd��
��4�������ж�����/ż���Ĳ���������n & (0x1)���õ�����Ҫô��1Ҫô��0
*/


class Solution 
{
public:
	bool g_InvalidInput = false;
	//1.����������һ��ʵ�֡�ţ����4ms��460K
	double Power(double base, int exponent) 
	{
		g_InvalidInput = false;
		//1.�����ж������base�Ƿ�Ϊ0.0��
		if (fabs(base - 0.0) < 0.0000001 && exponent < 0)
		{
			g_InvalidInput = true;
			cout << "baseΪ0ʱ��exponent����С��0" << endl;
			return 0.0;
		}
		double result = 1.0;
		//2.������Ĵη�����int�ʹ���
		unsigned int absExponent = abs(exponent);
		//3.����pow�ļ�������
		for (int i = 0; i < absExponent; i++)
			result *= base;
		//4.����exponent����Ĵ�С������������
		if (exponent < 0)
			result = 1.0 / result;
		return result;
	}

	//2.�Ż��������Ż���result�ļ�����̣�����ʱ�䣺3ms��ռ���ڴ棺364k
	double Power2(double base, int exponent)
	{
		g_InvalidInput = false;
		//1.�����ж������base�Ƿ�Ϊ0.0��
		if (fabs(base - 0.0) < 0.0000001 && exponent < 0)
		{
			g_InvalidInput = true;
			cout << "baseΪ0ʱ��exponent����С��0" << endl;
			return 0.0;
		}
		//2.������Ĵη�����int�ʹ�����2��
		unsigned int absExponent = abs(exponent);
		//3.����pow�ļ�������
		double result = calculate(base, absExponent);
		//4.����exponent����Ĵ�С������������
		if (exponent < 0)
			result = 1.0 / result;
		return result;
	}

	double calculate(double base, unsigned int exponent)
	{
		if (exponent == 0)
			return 1;
		if (exponent == 1)
			return base;
		//�ݹ�Ŀ���ʵ�ִη�����
		double result = calculate(base, exponent >> 1);
		//�жϴ�������������ż��
		if (exponent & 0x1 == 1)
			result = result*result*base;
		else
			result = result*result;
		return result;
	}
};

int main_offer16()
{
	Solution s;
	cout << s.Power2(2, -3) << endl;

	return 0;
}