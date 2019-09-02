#include <iostream>
using namespace std;

//两种实现方式：就地实现与不就地实现
//注意审题：书中明确表明的是进行就地实现，并且保证了输入的字符串后面有足够的空间闲余，length为整个字符串的长度不是有效长度
//1.就地实现从前往后
//特点：从前往后无脑复制，到了空格就变%20，但是要注意将后面的字符都后移2位
//时间复杂度O(n2)，空间复杂度为O(1)，牛客网时间4ms，内存480K
void replaceSpace1(char *str, int length) 
{
	if (str == nullptr)
		return;
	//1,计算实际长度
	int num = 0;
	for (int i = 0; str[i] != '\0'; i++)
		num++;
	//2.傻傻地从前往后
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

//2.就地从后往前（书上的代码），双指针法从后往前遍历赋值，避免了数据的多次后移
//时间复杂度O(n)，空间复杂度为O(1)，牛客网时间3ms，内存616K（我懵逼了，居然空间复杂度高了。。。）
void replaceSpace(char *str, int length)
{
	if (str == nullptr)
		return;
	//1.计算实际长度true_length，计算空格数目num_space 
	int true_length = 0;
	int num_space = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		true_length++;
		if (str[i] == ' ')
			num_space++;
	}
	//2.聪明的从后往前
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

// ====================测试代码====================
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

// 空格在句子中间
void Test1()
{
	const int length = 100;

	char str[length] = "hello world";
	Test("Test1", str, length, "hello%20world");
}

// 空格在句子开头
void Test2()
{
	const int length = 100;

	char str[length] = " helloworld";
	Test("Test2", str, length, "%20helloworld");
}

// 空格在句子末尾
void Test3()
{
	const int length = 100;

	char str[length] = "helloworld ";
	Test("Test3", str, length, "helloworld%20");
}

// 连续有两个空格
void Test4()
{
	const int length = 100;

	char str[length] = "hello  world";
	Test("Test4", str, length, "hello%20%20world");
}

// 传入nullptr
void Test5()
{
	Test("Test5", nullptr, 0, nullptr);
}

// 传入内容为空的字符串
void Test6()
{
	const int length = 100;

	char str[length] = "";
	Test("Test6", str, length, "");
}

//传入内容为一个空格的字符串
void Test7()
{
	const int length = 100;

	char str[length] = " ";
	Test("Test7", str, length, "%20");
}

// 传入的字符串没有空格
void Test8()
{
	const int length = 100;

	char str[length] = "helloworld";
	Test("Test8", str, length, "helloworld");
}

// 传入的字符串全是空格
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