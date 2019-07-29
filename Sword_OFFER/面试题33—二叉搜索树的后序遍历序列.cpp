// ������33�������������ĺ����������
// ��Ŀ������һ���������飬�жϸ������ǲ���ĳ�����������ĺ�������Ľ����
// ����������Yes,�������No���������������������������ֶ�������ͬ��

#include <iostream>
#include <vector>
#include "BinaryTree.h"
using namespace std;

//����˼·�Ǹ��ݺ�����������Ҹ������������������С�Ҵ󣩵Ļ��������ж�����������������Ƿ����������������

class Solution 
{
public:
	
	//1.�ڶ����汾�����ս���д�ģ�ʹ�ú����ĵݹ�ͳ��ȴ��Σ�ʹ�ռ临�ӶȽ���
	//����ʱ�䣺4ms��ռ���ڴ棺492k
	bool VerifySquenceOfBST(vector<int>& sequence)
	{
		if (sequence.size() < 1)
			return false;
		return Verify(sequence, 0, sequence.size() - 1);
	}

	bool Verify(vector<int>& sequence, int nStart, int nRoot)
	{
		//�ݹ������ǰ���ľ���С��1ʱ����ǰ����ֻ��һ�����û�е��ˣ�������true
		if (nRoot - nStart <= 1)
			return true;
		//1.���ݺ�������Ĺ������ֱ����������������͸��ڵ㣬���������ж϶����������Ĺ���
		//�����nLeft��nRight����˼���һ�汾�Ĳ�ͬ���������������Ϊ������β�ڵ����һλ����������β�ڵ����һλ
		int nLeft = nStart;	
		while (sequence[nLeft] < sequence[nRoot] && nLeft < nRoot)
			nLeft++;

		int nRight = nLeft;
		while (sequence[nRight] > sequence[nRoot] && nRight < nRoot)
			nRight++;

		if (nRight != nRoot)
			return false;

		//2.�ݹ�ʵ�֣��ӷֱ���������������ݹ��ж�
		return Verify(sequence, nStart, nLeft - 1) && Verify(sequence, nLeft, nRight - 1);
	}



	//2.��һ���汾���������ϵĻ�������д�ģ�û�п��ǵ�vector��ʵ��������ܹ������Ǵ��벻����
	//����ʱ�䣺3ms��ռ���ڴ棺480k
	bool VerifySquenceOfBST2(vector<int>& sequence) 
	{
		if (sequence.size() < 1)
			return false;

		//1.���ݺ������������������Ĺ������ֱ����������������͸��ڵ�
		int nRoot = sequence.size() - 1;

		//1.1 nLeft����Ϊ���������յ㣬nRight����Ϊ���������յ�
		int nLeft = -1;	
		while (sequence[nLeft + 1] < sequence[nRoot] && nLeft < static_cast<int>(sequence.size()) - 1)
			nLeft++;

		int nRight = nLeft;
		while (sequence[nRight+ 1] > sequence[nRoot] && nRight < static_cast<int>(sequence.size()) - 1)
			nRight++;

		//1.2 �ж��������������Ƿ񵽴��˶�Ӧ�ط��������������
		if (nRight != nRoot - 1)
			return false;
		
		//2.�ݹ�ʵ��
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

// ====================���Դ���====================
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

// ����ֻ��1�����
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