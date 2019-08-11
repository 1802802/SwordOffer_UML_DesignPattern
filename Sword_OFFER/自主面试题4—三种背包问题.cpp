//背包问题每种物品都有一个价值w、体积c与数量i，你现在有一个背包容积为V, 你想用一些物品装背包使得物品总价值最大.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//1.01背包问题：
//我们有n种物品，物品i的重量为weight[i]，价格为value[i]。我们假定所有物品的重量和价格都是非负的。
//背包所能承受的最大重量为v。如果限定每种物品只能选择0个或1个，求背包里面能放的最大价格。
static int ZeroOnePackge(vector<int> &weight, vector<int> &value, vector<int> &f, int n, int v)
{
	for (int i = 1; i <= n; i++) //每件物品遍历
		for (int j = v; j >= weight[i]; j--)  //从背包的最大重量到当前物品的重量逆序查找（这样后面的f[i]不会被前面的f[i-1]之类的干扰，新更新的状态也不会影响其他）
			f[j] = max(f[j], f[j - weight[i]] + value[i]);  //后面的式子表示，装上第i件物品前背包内物品的价值+第i件物品的价值
	return f[v];  //返回的为最大容量时的数值
}

//2.完全背包问题
//有n种物品和一个容量为v的背包，每种物品都有无限件可用。第i种物品的体重量是weight[i]，价值是value[i]。
//将哪些物品装入背包可使这些物品的体积总和不超过背包容量，且价值总和最大。
static int ZeroMorePackge(vector<int> &weight, vector<int> &value, vector<int> &f, int n, int v)
{
	for (int i = 1; i <= n; i++) //每件物品遍历
		for (int j = weight[i]; j <= v; j++)  //从背包的当前物品到最大重量的重量顺序查找（顺序查找的原因在于考虑之前物品的贡献）
			f[j] = max(f[j], f[j - weight[i]] + value[i]);  //后面的式子表示，装上第i件物品前背包内物品的价值+第i件物品的价值
	return f[v];  //返回的为最大容量时的数值
}

//3.多重背包问题
//有n种物品和一个容量为v的背包。第i种物品最多有eachNum[i]件可用，每件体积是weight[i]，价值是value[i]。
//求解将哪些物品装入背包可使这些物品的体积总和不超过背包容量v，且价值总和最大。
static int MorePackge(vector<int> &weight, vector<int> &value, vector<int> &f, vector<int> &eachNum, int n, int v)
{
	for (int i = 1; i <= n; i++)
		for (int k = 1; k <= eachNum[i]; k++)
			for (int j = v; j >= weight[i]; j--)  //从背包的最大重量到当前物品的重量逆序查找（可通过画图理解）
				f[j] = max(f[j], f[j - weight[i]] + value[i]);  //后面的式子表示，装上第i件物品前背包内物品的价值+第i件物品的价值
	return f[v];  //返回的为最大容量时的数值
}

int main_zizhu4()
{
	vector<int> weight({ 0,26,5,5 });
	vector<int> value({ 0,100,1,2 });
	vector<int> eachNum({ 0,4,4,2 });
	int n = 3;
	int v = 100;
	vector<int> f(v + 1);
	cout << MorePackge(weight, value, f, eachNum, n, v) << endl;
	for (auto &s : f)
		cout << s << " ";
	cout << endl;
	return 0;
}