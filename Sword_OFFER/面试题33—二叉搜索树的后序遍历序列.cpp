// 面试题33—二叉搜索树的后序遍历序列
// 题目：输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
// 如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。

#include <iostream>
#include <vector>
#include "BinaryTree.h"
using namespace std;

//基本思路是根据后序遍历（左右根）与二叉搜索树（左小右大）的基本规则，判断所输入的数组序列是否满足这个基本规则

class Solution 
{
public:
	
	//1.第二个版本，参照解析写的，使用函数的递归和长度传参，使空间复杂度降低
	//运行时间：4ms，占用内存：492k
	bool VerifySquenceOfBST(vector<int>& sequence)
	{
		if (sequence.size() < 1)
			return false;
		return Verify(sequence, 0, sequence.size() - 1);
	}

	bool Verify(vector<int>& sequence, int nStart, int nRoot)
	{
		//递归基，当前后点的距离小于1时（当前区间只有一个点或没有点了），返回true
		if (nRoot - nStart <= 1)
			return true;
		//1.根据后序遍历的规则来分辨左子树，右子树和根节点，并在其中判断二叉搜索树的规则
		//这里的nLeft与nRight的意思与第一版本的不同，这里的两者数据为左子树尾节点的下一位，与右子树尾节点的下一位
		int nLeft = nStart;	
		while (sequence[nLeft] < sequence[nRoot] && nLeft < nRoot)
			nLeft++;

		int nRight = nLeft;
		while (sequence[nRight] > sequence[nRoot] && nRight < nRoot)
			nRight++;

		if (nRight != nRoot)
			return false;

		//2.递归实现，从分辨出来的左右子树递归判断
		return Verify(sequence, nStart, nLeft - 1) && Verify(sequence, nLeft, nRight - 1);
	}



	//2.第一个版本，参照书上的基本操作写的，没有考虑到vector的实际情况，能过，但是代码不优雅
	//运行时间：3ms，占用内存：480k
	bool VerifySquenceOfBST2(vector<int>& sequence) 
	{
		if (sequence.size() < 1)
			return false;

		//1.根据后序遍历与二叉搜索树的规则来分辨左子树，右子树和根节点
		int nRoot = sequence.size() - 1;

		//1.1 nLeft最终为左子树的终点，nRight最终为右子树的终点
		int nLeft = -1;	
		while (sequence[nLeft + 1] < sequence[nRoot] && nLeft < static_cast<int>(sequence.size()) - 1)
			nLeft++;

		int nRight = nLeft;
		while (sequence[nRight+ 1] > sequence[nRoot] && nRight < static_cast<int>(sequence.size()) - 1)
			nRight++;

		//1.2 判断最终左右子树是否到达了对应地方，否则不满足规则
		if (nRight != nRoot - 1)
			return false;
		
		//2.递归实现
		vector<int> vLeft;
		vector<int> vRight;
		for (int i = 0; i <= nLeft; i++)
			vLeft.push_back(sequence[i]);
		for (int i = nLeft + 1; i <= nRight; i++)
			vRight.push_back(sequence[i]);
		bool isLeftOK = true;
		bool isRightOK = true;
		if(vLeft.size() > 1)
			isLeftOK = VerifySquenceOfBST(vLeft);
		if (vRight.size() > 1)
			isRightOK = VerifySquenceOfBST(vRight);

		return isLeftOK && isRightOK;
	}
};

// ====================测试代码====================
static void Test(const char* testName, int sequence[], int length, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);
	Solution s;
	vector<int> v;
	for (int i = 0; i < length; i++)
	{
		v.push_back(sequence[i]);
		cout << sequence[i] << " ";
	}
	cout << endl;
	if (s.VerifySquenceOfBST(v) == expected)
		printf("passed.\n");
	else
		printf("failed.\n");
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16
static void Test1()
{
	int data[] = { 4, 8, 6, 12, 16, 14, 10 };
	Test("Test1", data, sizeof(data) / sizeof(int), true);
}

//           5
//          / \
//         4   7
//            /
//           6
static void Test2()
{
	int data[] = { 4, 6, 7, 5 };
	Test("Test2", data, sizeof(data) / sizeof(int), true);
}

//               5
//              /
//             4
//            /
//           3
//          /
//         2
//        /
//       1
static void Test3()
{
	int data[] = { 1, 2, 3, 4, 5 };
	Test("Test3", data, sizeof(data) / sizeof(int), true);
}

// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
static void Test4()
{
	int data[] = { 5, 4, 3, 2, 1 };
	Test("Test4", data, sizeof(data) / sizeof(int), true);
}

// 树中只有1个结点
static void Test5()
{
	int data[] = { 5 };
	Test("Test5", data, sizeof(data) / sizeof(int), true);
}

static void Test6()
{
	int data[] = { 7, 4, 6, 5 };
	Test("Test6", data, sizeof(data) / sizeof(int), false);
}

static void Test7()
{
	int data[] = { 4, 6, 12, 8, 16, 14, 10 };
	Test("Test7", data, sizeof(data) / sizeof(int), false);
}

static void Test8()
{
	Test("Test8", nullptr, 0, false);
}

int main_offer33(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	//Test8();

	return 0;
}