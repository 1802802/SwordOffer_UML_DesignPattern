//#include <iostream>
//#include <list>
//#include <algorithm>
//#include <string>
//#include <vector>    
//using namespace std;
//
//#define MAX_NUM 100
//
//int solution(int boxs[], int N)
//{
//	vector<vector<int>> dp(N, vector<int>(3, 0));   //第一位为数量，第二位1为存在0为消失，第三位为相同的个数累计
//	dp[0][0] = 0;
//	dp[0][1] = 0;
//	dp[0][2] = 1;
//	for (int i = 1; i <= N; i++)
//	{
//		//while (boxs[i] != boxs[i - 1])
//		//{
//		//	if (boxs[i - 1][1] == 0)
//		//		i--;
//		//}
//		//{
//		//	dp[0][0] = 0;
//		//	dp[i][1] = dp[i - 1][0];
//		//}
//		//else
//		//{
//		//	dp[i][2] = dp[i - 1][2] + 1;
//		//	dp[i - 1][1] = 0;
//		//	dp[i][0] = max(dp[i][0], dp[i][2] * dp[i][2]);
//		//	dp[i][1] = 0;
//		//}
//	}
//
//	return 1;
//}
//
//int main_vivo333()
//{
//	string str("");
//	getline(cin, str);
//	int boxs[MAX_NUM];
//	int i = 0;
//	char *p;
//	int count = 0;
//
//	const char* strs = str.c_str();
//	p = strtok((char *)strs, " ");
//	while (p)
//	{
//		boxs[i] = atoi(p);
//		count++;
//		p = strtok(NULL, " ");
//		i++;
//		if (i >= MAX_NUM)
//			break;
//	}
//
//	int num = solution(boxs, count);
//	cout << num << endl;
//	return 0;
//}