// 面试题60：n个骰子的点数
// 题目：把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s
// 的所有可能的值出现的概率。

/*题解：

《剑指offer》上给出的两种方法，尤其是代码，晦涩难懂且没有注释。而n个骰子的问题实质就是一个动态规划问题。
首先该问题具备DP的两个特征：最优子结构性质和子问题的重叠性。具体的表现在：
(1)n个骰子的点数依赖于n - 1个骰子的点数，相当于在n - 1个骰子点数的基础上再进行投掷。
(2)求父问题的同时，需要多次利用子问题。

由此定义状态转移方程为f(n, k)表示n个骰子，点数和为k时出现的次数；
第一步，确定问题解的表达式。可将f(n, s) 表示n个骰子点数的和为s的排列情况总数。 
第二步，确定状态转移方程。n个骰子点数和为s的种类数只与n-1个骰子的和有关。
因为一个骰子有六个点数，那么第n个骰子可能出现1到6的点数。
所以第n个骰子点数为1的话，f(n,k)=f(n-1,k-1)，当第n个骰子点数为2的话，f(n,s)=f(n-1,k-2)，…，
依次类推。在n-1个骰子的基础上，再增加一个骰子出现点数和为s的结果只有这6种情况！

f(n, k) = f(n−1, k−1) + f(n−1, k−2) + f(n−1, k−3) + f(n−1, k−4) + f(n−1, k−5) + f(n−1, k−6)

其中 n>0且k <= 6n。其中f(n−1, k−i)表示的是第n次掷骰子时，骰子的点数为i对应的情况，
所以从k−1到k−6分别对应第n次掷骰子时骰子正面为1到6的情况。而初始状态可以定义为：

f(1, 1) = f(1, 2) = f(1, 3) = f(1, 4) = f(1, 5) = f(1, 6) = 1

所以根据这两个方程，给出的实现代码如下：
*/

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "BinaryTree.h"
using namespace std;

//思路：刚开始看不懂，其本质是f(n)=f(n-1)+f(n-2)+f(n-3)+f(n-4)+f(n-5)+f(n-6)
list<map<int, double>> PrintProbability_Solution1(int n)
{
	//1.边界条件
	if (n == 0)
		return list<map<int, double>>();

	//2.初始朱，face面和点数总值
	const int face = 6;
	const int pointNum = face * n;

	//3.存储数组，其中 dp[i][j] 表示前 i 个骰子产生点数 j 的次数
	vector<vector<int>> dp(n + 1, vector<int>(pointNum + 1));

	//4.表示第1个骰子产生点数1到6的次数均为1
	for (int i = 1; i <= face; i++)
		dp[1][i] = 1;

	//5.核心代码，f(n, k) = f(n−1, k−1) + f(n−1, k−2) + f(n−1, k−3) + f(n−1, k−4) + f(n−1, k−5) + f(n−1, k−6)
	for (int i = 2; i <= n; i++)
	{
		//比如当i为3时，其点数可能为3到18，所以j的范围为[i, pointNum（face * n）]
		for (int j = i; j <= face*i; j++)
		{
			//实现时，注意j-k值的合法性，同时注意k最大只能到face与j
			for (int k = 1; k <= face && k <= j; k++)
			{
				dp[i][j] += dp[i - 1][j - k];
				//dp[i][j] += (dp[i - 1][j - 1] + dp[i - 1][j - 2] +
				//	dp[i - 1][j - 3] + dp[i - 1][j - 4] + dp[i - 1][j - 5] + dp[i - 1][j - 6]);
			}
		}
	}

	//6.计算所有骰子的点数排列方式，比如两个骰子就是36种
	const double totalNum = pow(6, n);

	//7.计算所有骰子的点数的概率（为n时则输出n时的骰子概率，但是实际上数组中仍然存储了之间的所有概率）
	list<map<int, double>> save;
	//注意i的区间为[n, pointNum（face*n）]
	for (int i = n; i <= pointNum; i++)
		save.push_back(map<int, double>{ { i, dp[n][i] / totalNum }});
	return save;
}

// ====================测试代码====================
static void Test(int n)
{
	printf("Test for %d begins:\n", n);

	printf("Test for solution1\n");
	auto s = PrintProbability_Solution1(n);

	for (auto &s1 : s)
	{
		for (auto &s2 : s1)
			cout << s2.first << " " << s2.second << " ";
		cout << endl;
	}

	//printf("Test for solution2\n");
	//PrintProbability_Solution2(n);

	printf("\n");
}

int main_offer60(int argc, char* argv[])
{
	Test(1);
	Test(2);
	Test(3);
	Test(4);

	Test(11);

	Test(0);

	return 0;
}
