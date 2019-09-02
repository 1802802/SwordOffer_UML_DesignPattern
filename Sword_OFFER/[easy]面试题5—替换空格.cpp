#include <iostream>
using namespace std;

//����ʵ�ַ�ʽ���͵�ʵ���벻�͵�ʵ��
//ע�����⣺������ȷ�������ǽ��о͵�ʵ�֣����ұ�֤��������ַ����������㹻�Ŀռ����࣬lengthΪ�����ַ����ĳ��Ȳ�����Ч����
//1.�͵�ʵ�ִ�ǰ����
//�ص㣺��ǰ�������Ը��ƣ����˿ո�ͱ�%20������Ҫע�⽫������ַ�������2λ
//ʱ�临�Ӷ�O(n2)���ռ临�Ӷ�ΪO(1)��ţ����ʱ��4ms���ڴ�480K
void replaceSpace1(char *str, int length) 
{
	if (str == nullptr)
		return;
	//1,����ʵ�ʳ���
	int num = 0;
	for (int i = 0; str[i] != '\0'; i++)
		num++;
	//2.ɵɵ�ش�ǰ����
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
		{
			for (int j = num; j != i; j--)
			{
				str[j + 2] = str[j];
			}
			str[i++] = '%';
			str[i++] = '2';
			str[i++] = '0';
			num = num + 2;
		}
	}
}

//2.�͵شӺ���ǰ�����ϵĴ��룩��˫ָ�뷨�Ӻ���ǰ������ֵ�����������ݵĶ�κ���
//ʱ�临�Ӷ�O(n)���ռ临�Ӷ�ΪO(1)��ţ����ʱ��3ms���ڴ�616K�����±��ˣ���Ȼ�ռ临�Ӷȸ��ˡ�������
void replaceSpace(char *str, int length)
{
	if (str == nullptr)
		return;
	//1.����ʵ�ʳ���true_length������ո���Ŀnum_space 
	int true_length = 0;
	int num_space = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		true_length++;
		if (str[i] == ' ')
			num_space++;
	}
	//2.�����ĴӺ���ǰ
	int after_length = true_length + num_space * 2;
	while (true_length >= 0 && after_length >= 0)
	{
		if (str[true_length] != ' ')
			str[after_length--] = str[true_length--];
		else
		{
			true_length--;
			str[after_length--] = '0';
			str[after_length--] = '2';
			str[after_length--] = '%';
		}
	}
}

// ====================���Դ���====================
void Test(char* testName, char str[], int length, char expected[])
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	replaceSpace(str, length);

	if (expected == nullptr && str == nullptr)
		printf("passed.\n");
	else if (expected == nullptr && str != nullptr)
		printf("failed.\n");
	else if (strcmp(str, expected) == 0)
		printf("passed.\n");
	else
		printf("failed.\n");
}

// �ո��ھ����м�
void Test1()
{
	const int length = 100;

	char str[length] = "hello world";
	Test("Test1", str, length, "hello%20world");
}

// �ո��ھ��ӿ�ͷ
void Test2()
{
	const int length = 100;

	char str[length] = " helloworld";
	Test("Test2", str, length, "%20helloworld");
}

// �ո��ھ���ĩβ
void Test3()
{
	const int length = 100;

	char str[length] = "helloworld ";
	Test("Test3", str, length, "helloworld%20");
}

// �����������ո�
void Test4()
{
	const int length = 100;

	char str[length] = "hello  world";
	Test("Test4", str, length, "hello%20%20world");
}

// ����nullptr
void Test5()
{
	Test("Test5", nullptr, 0, nullptr);
}

// ��������Ϊ�յ��ַ���
void Test6()
{
	const int length = 100;

	char str[length] = "";
	Test("Test6", str, length, "");
}

//��������Ϊһ���ո���ַ���
void Test7()
{
	const int length = 100;

	char str[length] = " ";
	Test("Test7", str, length, "%20");
}

// ������ַ���û�пո�
void Test8()
{
	const int length = 100;

	char str[length] = "helloworld";
	Test("Test8", str, length, "helloworld");
}

// ������ַ���ȫ�ǿո�
void Test9()
{
	const int length = 100;

	char str[length] = "   ";
	Test("Test9", str, length, "%20%20%20");
}

int main_offer5(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	Test8();
	Test9();

	return 0;
}