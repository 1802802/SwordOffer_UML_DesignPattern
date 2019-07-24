#include <iostream>
#include <string>
using namespace std;

//һ���ַ����Ļ������жϣ��ݹ鶼�ǴӴ�С��ֻ���еĹ�������Сʱ�ң��е������ʱ�ң�
bool isPalindromeString1(string s)
{
	//1.�ݹ��
	if (s.size() > 1)
	{
		if (s[0] != s[s.size() - 1])
			return false;
		else
			//���Եݹ�
			return isPalindromeString1(s.substr(1, s.size() - 2));
	}
	return true;
}

//һ���ַ����Ļ�����ѭ�����͵ݹ����һëһ�������ǴӴ�С
bool isPalindromeString2(string s)
{
	while (s.size() > 1)
	{
		if (s[0] != s[s.size() - 1])
			return false;
		else
			s = s.substr(1, s.size() - 2);
	}
	return true;
}


int main_isPalindromeString()
{
	string s;
	while (cin >> s)
	{
		if (isPalindromeString1(s))
			cout << "true" << endl;
		else
			cout << "false" << endl;

		if (isPalindromeString2(s))
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}

	return 0;
}