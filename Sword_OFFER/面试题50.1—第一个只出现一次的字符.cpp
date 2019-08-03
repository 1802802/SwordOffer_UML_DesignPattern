// ������50.1����һ��ֻ����һ�ε��ַ�
// ��Ŀ����һ���ַ���(0<=�ַ�������<=10000��ȫ������ĸ���)���ҵ���һ��ֻ����һ�ε��ַ���
// ����������λ��,���û���򷵻� -1����Ҫ���ִ�Сд��.
#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution 
{
public:
	//1.ʹ�����ݽṹ����ϣ�����ѡ�����г���λ�ô������ռ任ʱ�䣬Ҳ����ѡ��ֻ�����Ȼ��ȥ�ң�
	//����ʱ�䣺4ms��ռ���ڴ棺480k
	//ʹ��unordered_mapΪ����ʱ�䣺5ms��ռ���ڴ棺492k
	int FirstNotRepeatingChar(string str) 
	{
		map<char, int> save;
		for (auto &s : str)
			if (!save.insert({ s,1 }).second)
				save[s]++;
		for (int i = 0; i < str.size(); i++)
		{
			if (save[str[i]] == 1)
				return i;
		}
		return -1;
	}

	//2.�������Զ���һ����ϣ������Ϊ256λ�洢���е�ASCII�룩
	//����ʱ�䣺3ms��ռ���ڴ棺484k���������һ��
	int FirstNotRepeatingChar2(string str)
	{
		//ע�⣬��char�ͱ�����int��ʹ��ʱ�����Զ�ת��Ϊ��Ӧ��ASCII�����
		vector<int> save(256, 0);
		for (auto &s : str)
			save[s]++;
		for (int i = 0; i < str.size(); i++)
		{
			if (save[str[i]] == 1)
				return i;
		}
		return -1;
	}
};

int main_offer50_1()
{
	string a;
	Solution s;
	while (cin >> a)
		cout << "find:" << s.FirstNotRepeatingChar(a) << endl;

	return 0;
}