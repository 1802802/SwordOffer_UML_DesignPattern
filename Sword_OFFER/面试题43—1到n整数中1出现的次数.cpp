// 面试题43—1到n整数中1出现的个数
// 题目：求出1~13的整数中1出现的次数,并算出100~1300的整数中1出现的次数？
// 为此他特别数了一下1~13中包含1的数字有1、10、11、12、13因此共出现6次,但是对于后面问题他就没辙了。
// ACMer希望你们帮帮他,并把问题更加普遍化,可以很快的求出任意非负整数区间中1出现的次数
// （从1 到 n 中1出现的次数）

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution 
{
public:
	//1.一种策略的思路（看不懂，脑壳疼）运行时间：3ms，占用内存：480k

	//主要思路：设定整数点（如1、10、100等等）作为位置点i（对应n的各位、十位、百位等等），分别对每个数位上有多少包含1的点进行分析
	//根据设定的整数位置，对n进行分割，分为两部分，高位n/i，低位n%i
	//当i表示百位，且百位对应的数>=2,如n=31456,i=100，则a=314,b=56，此时百位为1的次数有a/10+1=32（最高两位0~31），每一次都包含100个连续的点，即共有(a%10+1)*100个点的百位为1
	//当i表示百位，且百位对应的数为1，如n=31156,i=100，则a=311,b=56，此时百位对应的就是1，则共有a%10(最高两位0-30)次是包含100个连续点，当最高两位为31（即a=311），本次只对应局部点00~56，共b+1次，所有点加起来共有（a%10*100）+(b+1)，这些点百位对应为1
	//当i表示百位，且百位对应的数为0,如n=31056,i=100，则a=310,b=56，此时百位为1的次数有a/10=31（最高两位0~30）
	//综合以上三种情况，当百位对应0或>=2时，有(a+8)/10次包含所有100个点，还有当百位为1(a%10==1)，需要增加局部点b+1
	//之所以补8，是因为当百位为0，则a/10==(a+8)/10，当百位>=2，补8会产生进位位，效果等同于(a/10+1)
	int NumberOf1Between1AndN_Solution(int n)
	{
		int cnt = 0;
		for (int m = 1; m <= n; m *= 10)
		{
			//设定整数点（如1、10、100等等）作为位置点i（对应n的各位、十位、百位等等），分别对每个数位上有多少包含1的点进行分析
			int a = n / m, b = n % m;
			//前面的为当前位为0与>=2时的包含点，后面的为当前位为1时的补偿点
			cnt += (a + 8) / 10 * m + (a % 10 == 1 ? b + 1 : 0);
		}
		return cnt;
	}
};

// ====================测试代码====================
static void Test(const char* testName, int n, int expected)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);
	Solution s;
	if (s.NumberOf1Between1AndN_Solution(n) == expected)
		printf("Solution1 passed.\n");
	else
		printf("Solution1 failed.\n");

	printf("\n");
}

static void Test()
{
	Test("Test1", 1, 1);
	Test("Test2", 5, 1);
	Test("Test3", 10, 2);
	Test("Test4", 55, 16);
	Test("Test5", 99, 20);
	Test("Test6", 10000, 4001);
	Test("Test7", 21345, 18821);
	Test("Test8", 0, 0);
	Test("Test9", 235, 154);
}

int main_offer43(int argc, char* argv[])
{
	Test();

	return 0;
}