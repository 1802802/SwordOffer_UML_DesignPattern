/*
输入描述:
第一行包含2个整数 N、K，分别表示手机号码数字个数以及靓号至少有 K 个数字相同。
第二行包含 N 个字符，每个字符都是一个数字('0'-'9')，数字之间没有任何其他空白符。表示小多的手机号码。
数据范围：2 <= K <= N <= 10000

输出描述:
第一行包含一个整数，表示修改成一个靓号，最少需要的金额。
第二行包含 N 个数字字符，表示最少花费修改的新手机号。若有多个靓号花费都最少，则输出字典序最小的靓号。

*/

//这个题做对了是最骚的。。。。

//思路：以0到9为最佳数字n，循环10次，每次循环中寻找当数字为n时达到K个数字相同时的最小代价（首先是代价，其次才是字典序）
//算法：从数字n开始向外扩散，采用贪心算法思想（代价为先），首先寻找相同的数字，然后寻找比该数字大1或者小1的数字
//（先从头向尾找大于n的数，再从尾向头找小于n的数，之后以此类推，直到到达K个相同）

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main_pinduoduo2019_1()
{
	double N, K;
	string phoneNumber;
	while (cin >> N >> K >> phoneNumber)
	{
		//1.初始化阶段，用于定义各类数值与原始数据存储

		//1.1 存储初始值
		string phoneNumber_back = phoneNumber;
		double K_back = K;
		//1.2 用于存储数据
		map<int, string> save;
		//1.3 各种计数
		int sameNum2CurrentNum = 0;      //存储与当前num相同的数据数
		int currentValue = 0;
		//1.4 用于存储最优解是否已经被找到
		bool isBestResultFind = false;

		//2.大循环，实现0-9的全部查找
		for (int currentNum = 0; currentNum <= 9; currentNum++)
		{
			//2.1 如果最优解已经被找到，直接跳出循环，执行第3步输出结果
			if (isBestResultFind)
				break;

			//2.2 先遍历所有数值，如果相同数目已经超过了K，则将最优值赋值给save后跳出；
			for (int i = 0; i < N; i++)
			{
				if (phoneNumber[i] - '0' == currentNum)
					sameNum2CurrentNum++;
			}
			if (sameNum2CurrentNum >= K)
			{
				save.insert({ 0,phoneNumber });
				isBestResultFind = true;
				break;
			}

			//2.3 如果2.2未满足，则根据sameNum2CurrentNum将K减小，并定义贪心算法的两个变量
			int maxcurrentNum = currentNum;		//currentNum向上扩张的数
			int mincurrentNum = currentNum;		//currentNum向下扩张的数
			K = K - sameNum2CurrentNum;

			//2.4 贪心算法实现，currentNum同时向上下匀速扩张1，上下边界为9和0。当边界都达到，或者K被使用完后，跳出循环
			while ( K || (maxcurrentNum > 9 && mincurrentNum < 0))
			{
				if (!K)
					break;

				maxcurrentNum++;
				mincurrentNum--;
				//2.4.1 先从最大位数向最小位数查找能替换的值
				if (maxcurrentNum <= 9)
				{
					for (int i = 0; i < N; i++)
					{
						if (!K)
							break;
						if (phoneNumber[i] - '0' == maxcurrentNum)
						{
							currentValue += phoneNumber[i] - '0' - currentNum;
							phoneNumber[i] = currentNum + '0';
							K--;
						}
					}
				}
				//2.4.2 然后再从最小位数向最大位数查找能替换的值（2.4.1与2.4.2的先后顺序是为了保证字典序最小）
				if (mincurrentNum >= 0)
				{
					for (int i = N - 1; i >= 0; i--)
					{
						if (!K)
							break;
						if (phoneNumber[i] - '0' == mincurrentNum)
						{
							currentValue += currentNum - (phoneNumber[i] - '0');
							phoneNumber[i] = currentNum + '0';
							K--;
						}
					}
				}
			}

			//2.5 当贪心算法流程结束后，进行数据的存储，与数据的还原工作。
			save.insert({ currentValue, phoneNumber });
			phoneNumber = phoneNumber_back;
			K = K_back;
			sameNum2CurrentNum = 0;
			currentValue = 0;
		}
		//3.所有循环完成，或者最优解被查找出来后，输出结果
		cout << save.begin()->first << endl;
		cout << save.begin()->second << endl;	
	}
	return 0;
}

//	最开始的尝试，将最小字典序作为第一优先级，然而并没必要这样

//	//2.再以最小序列号算一遍
//	//如果数值>=currentNum，则从大往小
//	for (int i = 0; i < N; i++)
//	{
//		if (!K)
//			break;

//		if ((phoneNumber[i] - '0' - currentNum) >= 0)
//		{
//			int tmp = phoneNumber[i] - '0' - currentNum;
//			sum += tmp;
//			phoneNumber[i] = currentNum + '0';
//			K--;
//		}
//	}
//	//如果数值<currentNum，则从小往大
//	for (int i = N - 1; i >= 0; i--)
//	{
//		if (!K)
//			break;

//		if ((phoneNumber[i] - '0' - currentNum) < 0)
//		{
//			int tmp = currentNum - (phoneNumber[i] - '0');
//			sum += tmp;
//			phoneNumber[i] = currentNum + '0';
//			K--;
//		}
//	}
//	save.insert({ sum, phoneNumber });
//	phoneNumber = back;
//	K = K_back;
//	sum = 0;