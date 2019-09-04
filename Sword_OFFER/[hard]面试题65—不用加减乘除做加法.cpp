// ������65�����üӼ��˳����ӷ�
// ��Ŀ��дһ������������������֮�ͣ�Ҫ���ں������ڲ���ʹ�ã�������������
// ����������š�

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "BinaryTree.h"
using namespace std;

//˼·��λ����ʵ�ּӼ��˳�
class Solution 
{
public:
/*
λ������������"��"�Ľ��һ�£�
��� 1^1=0 1^0=1 0^0=0
��� 1+1=0 1+0=1 0+0=0

λ���������<<1�Ľ������"��λ"�Ľ��һ�£�
λ�� 1&1=1 1&0=0 0&0=0
��λ 1+1=1 1+0=0 0+0=0

�������Ƽӷ���Ϊ����������1001+1011��9+11=20��
�� ��λ��ӵ����ƽ�λ���õ�00010�����ý����Ϊ1001��1011��^�����
�� ����������ȥ�Ľ�λ���õ�10010�����ý����Ϊ1001��1011��&���<<1��Ľ����
�� ���������ӣ��õ�10100����Ϊ20
���������޷�ʹ�üӷ���������������10�����޷�ֱ����ӵõ�100����Ҫͨ��ѭ���ظ�����ڲ�����ʵ�ּӷ�
��ѭ����ֹ��������ݹ����ֹ������ͬ�����ǵ��ڼ������õ��Ľ�λΪ0��ֹͣ���㣩

���ԣ����Խ�����ֵ��Ϊ��ǰ��ֵs��������λc����ʱ������ǰ��һλ�����ں�֮���s��������^��&����
*/

	//1.���ּӷ����㣬����ʱ�䣺3ms��ռ���ڴ棺468k
	int Add(int num1, int num2)
	{
		int sum, carry;
		while (num2 != 0)
		{
			//sum�Ǻͣ���carry�ǽ�λ��sum��ʾ����Ģ٣�carry��ʾ����Ģڣ����ϵؽ��Т���ڣ�ֱ����Ϊ0
			sum = num1^num2;
			carry = (num1&num2) << 1;
			num1 = sum;
			num2 = carry;
		}
		return num1;
	}

	int Add2(int num1, int num2)
	{
		if (num2 == 0)
			return num1;
		int sum = num1^num2;
		int carry = (num1&num2) << 1;
		Add2(sum, carry);
	}

	//2.һ�ּ�������
	int Negtive(int num1, int num2)
	{
		//������num1+(-num2),ע�������ò����ģ�����-num2 = ~(num2 - 1) = ~num2 + 1 = Add(~num2,1)
		return Add(num1, Add(~num2, 1));
	}

	//3.һ�ֳ˷����㣨���Ƚ������뱻����ŪΪ�������������ӷ��ţ���ʵ�ֹ��̰���Сѧ�˷��㷨ʵʩ��
	int Multiply(int num1, int num2)
	{
		if (num2 == 0 || num1 == 0)
			return 0;
		//�Ƚ������������ȫ��ŪΪ����
		int multiplicand = (num1 < 0) ? (Add(~num1, 1)) : num1;
		int multiplier = (num2 < 0) ? (Add(~num2, 1)) : num2;
		int multip = 0;
		while (multiplier > 0)
		{
			//������һλ��1������м�����
			if (multiplier & 0x1 == 1)
				multip = Add(multip, multiplicand);
			//�����Ƿ�����˼����㣬��������������һλ����������һλ
			multiplicand <<= 1;
			multiplier >>= 1;
		}
		//�ָ����ţ�num1^num2Ϊ��ֵʱ��ʾ������ţ���˱�Ϊ��ֵ
		//��ע��<���ȼ�����^���ǵü����ţ�
		if ((num1^num2) < 0)
			multip = Add(~multip, 1);
		return multip;
	}

	//4.һ�ֳ�������
	//�������һ����Ԫ�����磬���е�int�����ݶ�������[2 ^ 0, 21, ..., 2^31]����һ�������ʾ
	//��int�����31λ���������뵽�ó�����2^31, 2^30, ..., 2^2, 2^1, 2^0������ȥ����������
	//������ö��������Ӧ�ı����ӵ����У�����������������γ��Ը�С�ı����������Ϳ��Կ��ٱƽ����յĽ����
	
	////�ڴ��ر����ѣ�����C++�ĳ�����˵����ԭ������ʹ�̾���ȥ�˳�����ȥƥ�䱻���������������ͬ�����������ʱ���в�ͬ��

	int Divide(int num1, int num2)
	{
		if (num1 == 0)
			return 0;
		if (num2 == 0)
			return 0;
			//throw new exception("error");
		//�Ƚ������������ȫ��ŪΪ����
		int dividend = (num1 < 0) ? (Add(~num1, 1)) : num1;
		int divider = (num2 < 0) ? (Add(~num2, 1)) : num2;
		int quotient = 0;	//��
		int remainder = 0;	//����
		//����31��0��ʵ�ֳ����Ŀ�������
		for (int i = 31; i >= 0; i--)
		{
			//ע�������dividend��divider�Ƚϣ��ǽ�dividend����iλ�����ǽ�divider����iλ
			//Ŀ�����ڱ���divider����iλ����Щ���ݶ�֡
			if ((dividend >> i) >= divider)
			{
				//���(dividend >> i) >= divider����ʾdividend��divide��ֵ����1<<i����1����iλ�����뵽����
				//��ʱ��ʾ��dividend�м�ȥ��1<<i��divide������dividend��ֵҲ���Ÿ���
				quotient = Add(quotient, 1 << i);
				dividend = Negtive(dividend, divider << i);
			}
		}
		//�ָ��̷��ţ������෴ʱ���̱�Ϊ����������Ϊ����
		//�ָ��������ţ�ע�������Ǹ�����󱻼�û�˵�dividendʵ�ֵģ�������Ÿ��ݱ�����������ķ�������ƥ��
		if ((num1^num2) < 0)
		{
			quotient = Add(~quotient, 1);
			if (num1 < 0)
				remainder = Add(~dividend, 1);
			else
				remainder = dividend;
		}
		else
			//��������ͬʱ��������һ���ķ��ż���ȷ����������
			remainder = (num1 < 0) ? (Add(~dividend, 1)) : (dividend);

		cout << quotient << endl;
		cout << remainder << endl;
		//cout << -11 / 5 << endl;
		//cout << -11 % 5 << endl;
		//cout << 11 / -5 << endl;
		//cout << 11 % -5 << endl;
		return quotient;
	}
};

// ====================���Դ���====================
static void Test(int num1, int num2, int expected)
{
	Solution s;
	int result = s.Divide(num1, num2);
	if (result == expected)
		printf("%d + %d is %d. Passed\n", num1, num2, result);
	else
		printf("%d + %d is %d. FAILED\n", num1, num2, result);
}

int main_offer65(int argc, char* argv[])
{
	Test(1, 2, 3);
	Test(111, 899, 1010);

	Test(-1, 2, 1);
	Test(1, -2, -1);

	Test(3, 0, 3);
	Test(0, -4, -4);

	Test(-2, -8, -10);
	Test(-10, -5, 2);
	Test(11, -5, 2);

	return 0;
}