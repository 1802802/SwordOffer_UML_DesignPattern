// ������67�����ַ���ת��������
// ��Ŀ������дһ������StrToInt��ʵ�ְ��ַ���ת��������������ܡ���Ȼ����
// ��ʹ��atoi�����������ƵĿ⺯����

#include <iostream>
#include <string>
using namespace std;

//������Ҫʵ�ֵĹ����У�
//1.StrToInt�ĺ��Ĳ�����num = 10*num + minus*(*str - '0')
//2.�߽�����INT�����������0x7FFFFFFF��0x80000000��
//3.�߽��������ַ�������*str == '\0'��index == str.size()��
//4.�߽�����������������ֻ�������ţ����ʼʱ�ж���λ�Ƿ�Ϊ�����ţ�Ȼ���ж���һλ�Ƿ�Ϸ���
//5.�����־���g_status����C��atoi�У����ڷǷ������᷵��0ͬʱ����־λ��ΪInValid��ע�⣩

class Solution 
{
public:
	enum Status { Valid, InValid };
	Status g_status;

	//������const char* ���͵�StrToInt
	int StrToInt(const char* str) 
	{
		//0.������ʼ������
		g_status = InValid;
		long long num = 0;

		//1.�ж�����Ϸ��ԣ�string����������������\0��ʾ��β����char���������Ͷ���Ҫ��
		if (str != nullptr && *str != '\0')
		{
			int minus = 1;
			//1.1�ж���λ�Ƿ�Ϊ+-�ţ������minus���д�����str++
			if (*str == '+')
				str++;
			else if (*str == '-')
			{
				str++;
				minus = -1;
			}
			//1.2�жϵ�ǰλ�Ƿ�Ϊ\0�������������ϸ���㣬������ű�������
			if (*str != '\0')
				num = StrToIntCore(str, minus);
		}
		return static_cast<int>(num);
	}

	//2.ʵ�ֺ�������ת��
	long long StrToIntCore(const char* cur, int minus)
	{
		long long num = 0;
		while (*cur != '\0')
		{
			//2.1�жϵ�ǰcur�Ƿ�Ϊ�Ϸ�����0��9
			if (*cur >= '0' && *cur <= '9')
			{
				num = 10 * num + minus*(*cur - '0');  //����ʵ�ֹ��ܴ���
				//2.1.1�жϵ�ǰstring�������Ƿ񳬹���INT�͵����޻����ޣ�ע�⸺����0x80000000����ǿ��ת��Ϊ����int��
				if ((minus == 1 && num > 0x7FFFFFFF) || (minus == -1 && num < static_cast<int>(0x80000000)))
				{
					num = 0;
					break;
				}
				cur++;
			}
			//2.2���Ϸ���ֱ��GG
			else
			{
				num = 0;
				break;
			}
		}
		//3.�жϵ�ǰλ�Ƿ�ɹ�ִ�е���\0����λ����������ʶValid�������򱣳�Ĭ��InValid
		if (*cur == 0)
			g_status = Valid;
		return num;
	}


	//Ȼ����string���͵�str
	//����ʱ�䣺3ms��ռ���ڴ棺456k
	int StrToInt(string str)
	{
		long long num = 0;
		long long size = str.size();
		g_status = InValid;

		if (str.size() > 0)
		{
			int minus = 1;
			int index = 0;
			if (str[index] == '+')
				index++;
			else if (str[index] == '-')
			{
				index++;
				minus = -1;
			}
			if (index < size)
				num = StrToIntCore(str, minus, index);
		}
		return static_cast<int>(num);
	}

	//stringתint�ĺ��ĺ���
	long long StrToIntCore(string str,int minus, int index)
	{
		long long size = str.size();
		long long num = 0;
		while (index < size)
		{
			if (str[index] <= '9' && str[index] >= '0')
			{
				num = 10 * num + minus*(str[index++] - '0');
				if ((minus == 1 && num > 0x7FFFFFFF) && (minus == -1 && num < static_cast<int>(0x80000000)))
				{
					num = 0;
					break;
				}
			}
			else
			{
				num = 0;
				break;
			}
		}
		if (index == size)
			g_status = Valid;
		return num;
	}
};

// ====================���Դ���====================
static void Test(const char* string)
{
	Solution s;
	int result = s.StrToInt(string);
	if (result == 0 && s.g_status == s.InValid)
		printf("the input %s is invalid.\n", string);
	else
		printf("number for %s is: %d.\n", string, result);
}

int main_offer67(int argc, char* argv[])
{
	Test(nullptr);

	Test("");

	Test("123");

	Test("+123");

	Test("-123");

	Test("1a33");

	Test("+0");

	Test("-0");

	//��Ч�����������, 0x7FFFFFFF
	Test("+2147483647");

	Test("-2147483647");

	Test("+2147483648");

	//��Ч����С������, 0x80000000
	Test("-2147483648");

	Test("+2147483649");

	Test("-2147483649");

	Test("+");

	Test("-");

	return 0;
}