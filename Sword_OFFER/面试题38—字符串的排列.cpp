// ������38���ַ���������
// ��Ŀ������һ���ַ���,���ֵ����ӡ�����ַ������ַ����������С�
// ���������ַ���abc,���ӡ�����ַ�a,b,c�������г����������ַ���abc,acb,bac,bca,cab��cba��
// ��������: ����һ���ַ���, ���Ȳ�����9(�������ַ��ظ�), �ַ�ֻ������Сд��ĸ��

// ����˼·��ȫ��������Ļ���˼·���Ƕ�����ݹ飬set��������ʱ�䣺4ms��ռ���ڴ棺632k����sort��������ʱ�䣺3ms��ռ���ڴ棺472k��
/*
		   abc
  a bc     b ac     c ba	  ���ϵ�֦�ڵ㶼�ڹ�ѭ��
abc acb  bac bca  cba cab   ����ݹ���Ķ����Ҷ�ڵ�

ȫ���еݹ�����壺����Ϊn���̶�ǰ[0,i]��ȫ����[i+1,n]��
���н���ɶ�����ṹ���������в������ǰ����������Ҷ�ڵ㣨ÿ������һ��Ҷ�ڵ��Ҫ��λ��
*/

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

class Solution 
{
public:
	//��Բ������ظ�ֵ��������set�Ĳ����������и��ܸ�����飬�Ҵ��ֱ����set��Ȼ���ٽ�setת��vector��������Լ���һ��������
	//���Ը㷨�����֣�ʹ��set�棬Ȼ����vector�����ʹ��vector�棬�м���׽ڵ�����ͬ��������Ȼ�������������ڶ���Ч�ʸ��ߣ�
	vector<string> Permutation(string str) 
	{
		if (str.size() < 1)
			return vector<string>();
		vector<string> save;
		Perm(str, save, 0, str.size());
		sort(save.begin(), save.end());
		//setʵ��ȥ�ز�����������ʵ�����ں��������й����м���ʵ��
		//set<string> saveSet(save.begin(), save.end());
		//vector<string> tmp;
		//for (auto &s : saveSet)
		//	tmp.push_back(s);
		//return tmp;
		return save;
	}

	void Perm(string str, vector<string>& save, int start, int end)
	{
		//1.�ݹ��
		if (end - start <= 1)
			save.push_back(str);
		else
		{
			//����Ľ�������str[start]��str[start]����Ľ�������Ϊ��Ҳ��һ��
			for (int i = start ; i < end; i++)
			{
				//��������׽ڵ�֮�������һ�����򲻻���ʵ�ֲ����ֵ������򣬻�����Ҫ������
				if (str[start] == str[i] && i != start)
					continue;
				//2.�����ʵ�־��ǹ̶�ǰ[0,start]��ȫ����[start+1,n]��start��ֵ���������𽥵�����end����
				swap(str[start], str[i]);
				Perm(str, save, start + 1, str.size());
				//�����һ�ν��������з�֧�󣬼ǵ�Ҫ��������
				swap(str[start], str[i]);
			}
		}
	}
};

// ====================���Դ���====================
void Test(string pStr)
{
	if (pStr.size() == 0)
		printf("Test for nullptr begins:\n");
	else
		cout << "Test for " << pStr << " begins:" << endl;

	Solution s;
	auto tmp = s.Permutation(pStr);
	for (auto &s : tmp)
		cout << s << endl;

	printf("\n");
}

int main_offer38(int argc, char* argv[])
{
	//Test(nullptr);

	string string1 = "";
	Test(string1);

	string string2 = "aa";
	Test(string2);

	string string3 = "ab";
	Test(string3);

	string string4 = "abc";
	Test(string4);

	string string5 = "abcd";
	Test(string5);

	return 0;
}