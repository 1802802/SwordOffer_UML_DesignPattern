// 面试题63：股票的最大利润
// 题目：假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖交易该股
// 票可能获得的利润是多少？例如一只股票在某些时间节点的价格为{9, 11, 8, 5,
// 7, 12, 16, 14}。如果我们能在价格为5的时候买入并在价格为16时卖出，则能
// 收获最大的利润11。

#include <map>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "BinaryTree.h"
using namespace std;

//股票最大利润问题有六种，需要都好好考虑一下他们的共性

//动态规划实现第一类股票问题，单次买入卖出如果将最低收益设为0，那么初始值为0；如果考虑负收益 ，则初始值为INT_MIN

//思路：动态规划，计算每个位置的卖出价最大值（如果将0作为最小值而不考虑负值时）
/*
dp[i][0]代表第i + 1天没有持股票，dp[i][1]代表第i + 1天持有股票

初始化：
dp[0][0] = 0;         第一天没有持股，这时候相当于没有买入，故为0
dp[0][1] = -prices[0];  第一天持股，相当于买入，这时候为 - pricrs[0]

状态转移方程：
未持股 = max(昨天没有持股今天维持现状, （昨天持股，今天卖出））
	dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);

持股 = max(昨天持股今天维持现状，（之前没有交易，今天买入)）【因为只能完成一笔交易，故今天买入，则前面就相当于一直没有进行交易为利润为0】
	dp[i][1] = max(dp[i - 1][1], -1 * prices[i])（也相当于一直保持所有的dp[i][1]为买入价的最小值）
*/

int MaxDiff1_1(const int* numbers, unsigned length)
{
	if (numbers == nullptr && length < 2)
		return 0;

	vector<vector<int>> dp(length, vector<int>(2));
	dp[0][0] = INT_MIN;
	dp[0][1] = -1 * numbers[0];
	for (int i = 1; i < length; i++)
	{
		dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + numbers[i]);
		dp[i][1] = max(dp[i - 1][1], 0 - numbers[i]);
	}

	return dp[length - 1][0];
}

//思路2：记录前面的最小值，不断地计算最大效益（注意不要只考虑正收益的最大值，还要包括负收益的）
int MaxDiff1_2(const int* numbers, unsigned length)
{
	if (numbers == nullptr && length < 2)
		return 0;

	int minValue = INT_MAX;
	int maxDiff = INT_MIN;

	for (int i = 0; i < length; i++)
	{
		if (numbers[i] < minValue)
		{
			maxDiff = max(maxDiff, numbers[i] - minValue);
			minValue = numbers[i];
		}
		else
			maxDiff = max(maxDiff, numbers[i] - minValue);
	}
	
	return maxDiff;
}

//动态规划实现第二类股票问题，允许多次买入卖出

/*
dp[i][0]代表第i+1天没有持股票，dp[i][1]代表第i+1天持有股票

初始化：
dp[0][0] = 0;         第一天没有持股，这时候相当于没有买入，故为0
dp[0][1] = -prices[0];   第一天持股，相当于买入，这时候为-prices[0]

状态转移方程：
没有持股 =max(昨天没有持股今天维持现状 , 昨天持股，今天卖出）
   dp[i][0] = Math.max(dp[i-1][0],dp[i-1][1] + prices[i]);
持股 = max(昨天持股今天维持现状，（昨天没有持股，今天买入))【相对于之前，这里改变了】（不需要存最小值了）
     dp[i][1] = Math.max(dp[i-1][1], dp[i-1][0] - prices[i])
*/

int MaxDiff2_1(const int* numbers, unsigned length)
{
	if (numbers == nullptr && length < 2)
		return 0;

	vector<vector<int>> dp(length, vector<int>(2));
	dp[0][0] = INT_MIN;
	dp[0][1] = -1 * numbers[0];
	for (int i = 1; i < length; i++)
	{
		dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + numbers[i]);
		dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - numbers[i]);
	}

	return dp[length - 1][0];
}

//动态规划实现第三类股票问题，允许多次买入卖出，但是含有冷冻期（比如sell之后等一天才能继续交易）

/*
dp[i][0]代表第i+1天没有持股票，dp[i][1]代表第i+1天持有股票

初始化：（由于有了买入冷却期，所以在冷却期k前的所有时间dp[i][1]都应该为-price[i]，下面以k=1为例子）
dp[0][0] = 0;                     //第1天没有持股，这时候相当于没有买入，故为0
dp[1][0] = max(0,prices[1]-prices[0]);		//第2天没有持股，这时候max(第一天没持股，第一天持股第二天卖出)
dp[0][1] = -prices[0];               //第1天持股维持，相当于买入，这时候为-prices[0]
dp[1][1] = max(-prices[0],-prices[1]);		//第2天持股，这时候max(第一天持股维持，第一天没持股第二天买入)

状态转移方程：
没有持股 =max(昨天没有持股今天维持现状 , (昨天持股，今天卖出))
    dp[i][0] = Math.max(dp[i-1][0],dp[i-1][1] + prices[i]);
持股 = max(昨天持股今天维持现状，（前天没有持股，今天买入))即：第i天要买的时候，要从前天的状态进行判断
	  dp[i][1] = Math.max(dp[i-1][1], dp[i-2][0] - prices[i]);
*/

class Solution3
{
public:
	int maxProfit3_1(vector<int>& prices) 
	{
		//1. k充当冷却期间
		int k = 1;
		if (prices.size() < 2)
			return 0;
		vector<vector<int>> dp(prices.size(), vector<int>(2));
		//2. 0位置的初始化
		dp[0][0] = 0;
		dp[0][1] = 0 - prices[0];
		//3. 状态转移方程，注意对初始k冷冻期间的日期特殊处理
		for (int i = 1; i < prices.size(); i++)
		{
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
			if (i <= k)
				dp[i][1] = max(dp[i - 1][1], 0 - prices[i]);
			else
				dp[i][1] = max(dp[i - 1][1], dp[i - k - 1][0] - prices[i]);
		}
		return dp[prices.size() - 1][0];
	}
};

//动态规划实现第四类股票问题，允许多次买入卖出，但是每次的交易含有手续费（可以理解为卖出时多交钱，当然也可以理解为买入时）
//常规思想是继续沿用第二类问题的代码，然后记录每次交易的次数，在交易后减去手续费，但是实际还是可以在DP过程中完成）

/*
dp[i][0]代表第i+1天没有持股票，dp[i][1]代表第i+1天持有股票（思想为在买入时扣除手续费，当然在卖出时计算也是可行的）

初始化：
dp[0][0] = 0;        		   第一天没有持股，这时候相当于没有买入，故为0
dp[0][1] = 0 - prices[0] - fee;   第一天持股，相当于买入，这时候为 - prices[0] - fee ,本次以买入作为交易的开始，每次买入就扣除手续费，卖出的时候就不扣除手续费了。

状态转移方程：
没有持股 = max(昨天没有持股今天维持现状 , 昨天持股，今天卖出）【买入扣除手续费，卖出就不扣除了，因为买卖都完成才扣一次手续费】
    dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
持股 = max(昨天持股今天维持现状，（昨天没有持股，今天买入))
	 dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i] - fee);
*/

class Solution4
{
public:
	int maxProfit4_1(vector<int>& prices, int fee)
	{
		if (prices.size() < 2)
			return 0;
		vector<vector<int>> dp(prices.size(), vector<int>(2));
		//2. 0位置的初始化（思想为在买入时扣除手续费）
		dp[0][0] = 0;
		dp[0][1] = 0 - prices[0] - fee;
		//3. 状态转移方程，基本思路与第二种问题类似，多了手续费
		for (int i = 1; i < prices.size(); i++)
		{
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
			dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i] - fee);
		}
		return dp[prices.size() - 1][0];
	}

	int maxProfit4_2(vector<int>& prices, int fee)
	{
		if (prices.size() < 2)
			return 0;
		vector<vector<int>> dp(prices.size(), vector<int>(2));
		//2. 0位置的初始化（思想为在卖出时扣除手续费）
		dp[0][0] = 0;
		dp[0][1] = 0 - prices[0];
		//3. 状态转移方程，基本思路与第二种问题类似，多了手续费
		for (int i = 1; i < prices.size(); i++)
		{
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i] - fee);
			dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
		}
		return dp[prices.size() - 1][0];
	}
};

//动态规划实现第五类股票问题，只允许最多两次买入卖出（理解交易次数k在买入还是在卖出时减少1）

/*
（这里的交易k次注意，是指已经进行了交易的次数，本题中将买入的时候当做进行了一次交易）
dp[i][k][0]代表第i+1天交易k次并且没有持股票，dp[i][k][1]代表第i+1天交易k次并且持有股票

dp[i][k][0]代表第i+1天交易k次并且没有持股票，dp[i][k][1]代表第i+1天交易k次并且持有股票

初始化：（在买入的时候算进行一次交易）
dp[0][0][0] = 0				//第一天， 交易次数为0，没持股，相当于啥都没干，没有存在意义
dp[0][1][0] = 0;      	//第一天，交易次数为1，没持股，相当于买入再卖出
dp[0][1][1] = - prices[0];	//第一天，交易次数为1，持股，相当于买入股票未卖出
dp[0][2][0] = 0;     	//第一天, 交易次数为2，没持股，相当于买入卖出买入卖出，没有盈利
dp[0][2][1] = - prices[0];	//第一天，交易次数为2，持股，相当于买入再卖出（交易1次）再买入

状态转移方程：
第(i+1)天交易数为2，没持股 = max(前一天交易数为2没持股维持，前一天交易数为2持股今天卖出)
    dp[i][2][0] = Math.max(dp[i-1][2][0],dp[i-1][2][1] + prices[i]);
第(i+1)天交易数为2，持股 = max(前一天交易数为2持股维持，前一天交易数为1没持股今天买入)[买入之前必须卖出，故之前交易数应该为1而不是为2]
	  dp[i][2][1] = Math.max(dp[i-1][2][1],dp[i-1][1][0] - prices[i]);
第(i+1)天交易数为1，没持股 = max(前一天交易数为1没持股维持，前一天交易数为1持股今天卖出)[卖出之前必须买入，故交易数为1而不是0]
	   dp[i][1][0] = Math.max(dp[i-1][1][0],dp[i-1][1][1] + prices[i]);
第(i+1)天交易数为1，持股 = max(前一天交易数为1持股维持，(没交易，今天买入))
	   dp[i][1][1] = Math.max(dp[i-1][1][1],0 - prices[i]);
*/

class Solution5
{
public:
	int maxProfit5_1(vector<int>& prices)
	{
		//1. 边界条件
		if (prices.size() < 2)
			return 0;
		vector < vector<vector<int>>> dp(prices.size(), vector<vector<int>>(3, vector<int>(2)));
		//2. 0位置的初始化（针对第一天有无持股，交易次数进行的初始化操作）
		dp[0][0][0] = 0;
		dp[0][1][0] = 0;
		dp[0][1][1] = 0 - prices[0];
		dp[0][2][0] = 0;
		dp[0][2][1] = 0 - prices[0];
		//3. 状态转移方程，穷举了k为1和2时的情况
		for (int i = 1; i < prices.size(); i++)
		{
			//通过下面可见，可以通过循环将k穷举，这里只是单纯的全部写出来了
			dp[i][1][0] = max(dp[i - 1][1][0], dp[i - 1][1][1] + prices[i]);
			dp[i][1][1] = max(dp[i - 1][1][1], 0 - prices[i]);
			dp[i][2][0] = max(dp[i - 1][2][0], dp[i - 1][2][1] + prices[i]);
			dp[i][2][1] = max(dp[i - 1][2][1], dp[i - 1][1][0] - prices[i]);
		}
		return dp[prices.size() - 1][2][0];
	}
};

//动态规划实现第六类股票问题，只允许最多k次买入卖出（理解交易次数k在买入还是在卖出时减少1）

/*
（这里的交易k次注意，是指已经进行了交易的次数，本题中将买入的时候当做进行了一次交易）
dp[i][k][0]代表第i+1天已经交易了k次并且没有持股票，dp[i][k][1]代表第i+1天已经交易了k次并且持有股票

初始化：
dp[0][k][0] = 0; 【k为交易成交的笔数】即第一天,持续的买入卖出买入卖出最后没有留股票，没收益
dp[0][k][1] = 0 - prices[0]; 【k为交易成交的笔数】即第一天,持续的买入卖出买入最后留了股票，收益为买入的 -prices[0]

状态转移方程：
第(i+1)天交易数为j，没持股 = max(前一天交易数为j没持股维持，前一天交易数为j持股今天卖出)
    dp[i][j][0] = Math.max(dp[i-1][j][0], dp[i-1][j][1] + prices[i]);
第(i+1)天交易数为j，持股 = max(前一天交易数为j持股维持，前一天交易数为j-1没持股今天买入)
	  dp[i][j][1] = Math.max(dp[i-1][j][1], dp[i-1][j-1][0] - prices[i]);
*/

//关于第六题有个核心问题，在于当k大于了prices大小的一半之后，就没有存在的意义了，所以要处理否则会超时

class Solution6
{
public:
	int maxProfit6_1(int k, vector<int>& prices)
	{
		//1. 边界条件
		if (prices.size() < 2 || k <= 0)
			return 0;
		//由于k大小对于数据的影响，这里将根据k的大小进行第二种股票问题加第六种股票问题的实现

		//1.1第六种股票问题实现
		if (k < prices.size() >> 1)
		{
			vector < vector<vector<int>>> dp(prices.size(), vector<vector<int>>(k + 1, vector<int>(2)));
			//2. 0位置的初始化（针对第一天有无持股，交易次数进行的初始化操作）
			for (int i = 0; i <= k; i++)
			{
				dp[0][i][0] = 0;
				dp[0][i][1] = 0 - prices[0];
			}
			//3. 状态转移方程，具体为循环穷举不同k时的情况
			for (int i = 1; i < prices.size(); i++)
			{
				for (int j = 1; j <= k; j++)
				{
					dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
					dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
				}
			}
			return dp[prices.size() - 1][k][0];
		}
		//1.2 当k足够大时，第二种股票问题实现
		else
		{
			vector<vector<int>> dp(prices.size(), vector<int>(2));
			dp[0][0] = 0;
			dp[0][1] = 0 - prices[0];
			for (int i = 1; i < prices.size(); i++)
			{
				dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
				dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
			}
			return dp[prices.size() - 1][0];
		}
	}
};


// ==================== Test Code ====================
static void Test(const char* testName, const int* numbers, unsigned int length, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (MaxDiff1_1(numbers, length) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

static void Test1()
{
	int numbers[] = { 4, 1, 3, 2, 5 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), 4);
}

// 价格递增
static void Test2()
{
	int numbers[] = { 1, 2, 4, 7, 11, 16 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), 15);
}

// 价格递减
static void Test3()
{
	int numbers[] = { 16, 11, 7, 4, 2, 1 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), -1);
}

// 价格全部相同
static void Test4()
{
	int numbers[] = { 16, 16, 16, 16, 16 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), 0);
}

static void Test5()
{
	int numbers[] = { 9, 11, 5, 7, 16, 1, 4, 2 };
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), 11);
}

static void Test6()
{
	int numbers[] = { 2, 4 };
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), 2);
}

static void Test7()
{
	int numbers[] = { 4, 2 };
	Test("Test7", numbers, sizeof(numbers) / sizeof(int), -2);
}

static void Test8()
{
	Test("Test8", nullptr, 0, 0);
}

int main_offer63(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	Test8();

	return 0;
}