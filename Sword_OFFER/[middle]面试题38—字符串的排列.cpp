// 面试题38—字符串的排列
// 题目：输入一个字符串,按字典序打印出该字符串中字符的所有排列。
// 例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。
// 输入描述: 输入一个字符串, 长度不超过9(可能有字符重复), 字符只包括大小写字母。

// 基本思路：全排列问题的基本思路就是多叉树递归，set排序（运行时间：4ms，占用内存：632k），sort排序（运行时间：3ms，占用内存：472k）
/*
		   abc
  a bc     b ac     c ba	  其上的枝节点都在过循环
abc acb  bac bca  cba cab   到达递归基的多叉树叶节点

全排列递归的意义：长度为n，固定前[0,i]，全排列[i+1,n]，
所有结果成多叉树结构，整体运行操作就是按序访问所有叶节点（每访问完一个叶节点就要复位）
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
	//针对不能有重复值，进行了set的操作（这里有个很搞的事情，我大可直接用set存然后再将set转成vector输出，可以减少一道操作）
	//所以搞法有两种：使用set存，然后倒入vector输出；使用vector存，中间除首节点外相同数不处理，然后排序后输出（第二种效率更高）
	vector<string> Permutation(string str) 
	{
		if (str.size() < 1)
			return vector<string>();
		vector<string> save;
		Perm(str, save, 0, str.size());
		sort(save.begin(), save.end());
		//set实现去重操作，但是其实可以在函数的运行过程中即可实现
		//set<string> saveSet(save.begin(), save.end());
		//vector<string> tmp;
		//for (auto &s : saveSet)
		//	tmp.push_back(s);
		//return tmp;
		return save;
	}

	void Perm(string str, vector<string>& save, int start, int end)
	{
		//1.递归基
		if (end - start <= 1)
			save.push_back(str);
		else
		{
			//这里的交换包括str[start]和str[start]自身的交换，因为这也是一种
			for (int i = start ; i < end; i++)
			{
				//如果除了首节点之外的数据一样，则不换（实现不了字典序排序，还是需要操作）
				if (str[start] == str[i] && i != start)
					continue;
				//2.这里的实现就是固定前[0,start]，全排列[start+1,n]，start的值随着深入逐渐递增，end不变
				swap(str[start], str[i]);
				Perm(str, save, start + 1, str.size());
				//在完成一次交换的所有分支后，记得要换回来，
				swap(str[start], str[i]);
			}
		}
	}
};

// ====================测试代码====================
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