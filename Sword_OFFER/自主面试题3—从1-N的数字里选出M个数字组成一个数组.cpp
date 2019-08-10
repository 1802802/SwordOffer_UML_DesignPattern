//��Ŀ����1-N��������ѡ��M���������һ�����飬Ҫ��ÿ��������ÿ��λ�õ�������ͬ
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
using namespace std;

//1.˼·Ϊ����ϴ���㷨����ȫ����ԣ�ѡ���е�M�γ�����
vector<int> NewArray(int n, int m)
{
	if (n < m)
		return vector<int>();

	vector<int> base(n);
	for (int i = 1; i <= n; i++)
		base[i - 1] = i;
	//����Ϊ������Knuth-Durstenfeld Shuffle ϴ���㷨��ע��ȡ��Ϊ%(i+1)
	for (int i = n - 1; i >= n - m; i--)
	{
		srand((unsigned)time(NULL));
		swap(base[i], base[rand() % (i + 1)]);
	}
	vector<int> save(m);
	for (int i = n - m, j = 0; i <= n - 1; i++, j++)
		save[j] = base[i];
	return save;
}

int main_zizhu3()
{
	int n = 10;
	int a = 10, b = 5;
	while (n--)
	{
		auto t = NewArray(a, b);
		for (auto &s : t)
			cout << s << " ";
		cout << endl;
	}
	return 0;
}