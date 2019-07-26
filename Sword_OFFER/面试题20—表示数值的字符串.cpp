// ������20����ʾ��ֵ���ַ���
// ��Ŀ����ʵ��һ�����������ж��ַ����Ƿ��ʾ��ֵ������������С������
// ���磬�ַ���"+100","5e2","-123","3.1416"��"-1E-16"����ʾ��ֵ�� 
// ����"12e","1a3.14","1.2.3","+-5"��"12e+4.3"�����ǡ�
// ����ʱ�䣺5ms��ռ���ڴ棺496k

#include <iostream>
#include <vector>
using namespace std;

class Solution 
{
public:
	//��ֵ�ı�ʾ��ʽ��A[.[B]][e|EC] �� .[B]][e|EC] ������ACΪ������BΪ�޷�����
	//�ж�˼·���£�����A���ͣ����ж�����B���ͣ���A�����жϽ����ϣ�������ж�C���ͣ���AB�����жϽ����ϣ�
	//���⻹��һ���������⣬�����ں�������ʱ���ݵ���stringָ��ĵ�ַ������ָ�뱾����ΪҪͨ���������ڲ���ʵ��string��ַ�ĺ���

	bool isNumeric(char* string)
	{
		if (string == nullptr)
			return false;
		//1.���ڳ�ʼֵΪ������࣬���������жϵ�ǰ�Ŀ�ͷ�Ƿ�������֣�����numericΪtrue������Ϊfalse
		bool numeric = scanInt(&string);
		//2.�ڵ�һ������str��λ�ñ�ȻΪ'.'��'\0'��'e\E'
		if (*string == '.')
		{
			++string;
			// ����һ�д�����||��ԭ��������true/false���������ݵı仯���仯��
			// 1. С������û���������֣�����.123����0.123��
			// 2. С����������û�����֣�����233.����233.0��
			// 3. ��ȻС����ǰ��ͺ�����������֣�����233.666
			numeric = scanUnsignedInt(&string) || numeric;
		}

		if (*string == 'e' || *string == 'E')
		{
			++string;
			// ����һ�д�����&&��ԭ��������true/false���������ݵı仯���仯��
			// 1. ��e��Eǰ��û������ʱ�������ַ������ܱ�ʾ���֣�����.e1��e1��
			// 2. ��e��E����û������ʱ�������ַ������ܱ�ʾ���֣�����12e��12e+5.4
			numeric = numeric && scanInt(&string);
		}
		//����ж���û��ɨ�赽ͷ
		return numeric && (*string == '\0');
	}

	//�����ж�A��C���͵������Ƿ���ڣ�ȥ�����ź�ʹ��B���жϣ�
	bool scanInt(char** str)
	{
		if (**str == '+' || **str == '-')
			++(*str);
		return scanUnsignedInt(str);
	}

	//�����ж�B���͵������Ƿ���ڣ��޷��������жϣ�
	bool scanUnsignedInt(char** str)
	{
		const char* before = *str;
		while (**str != '\0' && **str >= '0' && **str <= '9')
			++(*str);
		//����ʱ��str��Ȼ�������֣���������e/E��.��\0���ж�str�Ƿ��ƶ��ˣ��ƶ��˷���true��δ�ƶ���ʾû������0-9������false
		return (*str == before) ? (false) : (true);
	}
};



// ====================���Դ���====================
void Test(const char* testName,char* str, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);
	Solution s;
	if (s.isNumeric(str) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}


int main_offer20(int argc, char* argv[])
{
	Test("Test1", "100", true);
	Test("Test2", "123.45e+6", true);
	Test("Test3", "+500", true);
	Test("Test4", "5e2", true);
	Test("Test5", "3.1416", true);
	Test("Test6", "600.", true);
	Test("Test7", "-.123", true);
	Test("Test8", "-1E-16", true);
	Test("Test9", "1.79769313486232E+308", true);

	printf("\n\n");

	Test("Test10", "12e", false);
	Test("Test11", "1a3.14", false);
	Test("Test12", "1+23", false);
	Test("Test13", "1.2.3", false);
	Test("Test14", "+-5", false);
	Test("Test15", "12e+5.4", false);
	Test("Test16", ".", false);
	Test("Test17", ".e1", false);
	Test("Test18", "e1", false);
	Test("Test19", "+.", false);
	Test("Test20", "", false);
	Test("Test21", nullptr, false);

	return 0;
}