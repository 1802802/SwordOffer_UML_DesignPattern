// ������50.2���ַ����е�һ��ֻ����һ�ε��ַ�
// ��Ŀ����һ���ַ���(0<=�ַ�������<=10000��ȫ������ĸ���)���ҵ���һ��ֻ����һ�ε��ַ���
// ����������λ��,���û���򷵻� -1����Ҫ���ִ�Сд��.
#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

class CharStatistics
{
public:
	//˼·����char���������룬��ÿ���������д�ӡ��������ĳ�������洢��������hash��Ĵ洢���̣�
	void FirstAppearingOnce(stringstream& input)
	{
		char str;
		string totalStr;
		vector<int> save(256, 0);
		while (input >> str)
		{
			save[str]++;
			totalStr += str;
			for (int i = 0; i < totalStr.size(); i++)
			{
				if (save[totalStr[i]] == 1)
				{
					cout << totalStr[i] << " ";
					break;
				}
			}
		}
	}
};

// ====================���Դ���====================

int main_offer50_2(int argc, char* argv[])
{
	CharStatistics s;
	stringstream input;
	input << "asadf dw w 3 fws 22 ";
	s.FirstAppearingOnce(input);

	return 0;
}