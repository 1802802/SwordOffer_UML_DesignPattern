//��������ÿ����Ʒ����һ����ֵw�����c������i����������һ�������ݻ�ΪV, ������һЩ��Ʒװ����ʹ����Ʒ�ܼ�ֵ���.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//1.01�������⣺
//������n����Ʒ����Ʒi������Ϊweight[i]���۸�Ϊvalue[i]�����Ǽٶ�������Ʒ�������ͼ۸��ǷǸ��ġ�
//�������ܳ��ܵ��������Ϊv������޶�ÿ����Ʒֻ��ѡ��0����1�����󱳰������ܷŵ����۸�
static int ZeroOnePackge(vector<int> &weight, vector<int> &value, vector<int> &f, int n, int v)
{
	for (int i = 1; i <= n; i++) //ÿ����Ʒ����
		for (int j = v; j >= weight[i]; j--)  //�ӱ����������������ǰ��Ʒ������������ң����������f[i]���ᱻǰ���f[i-1]֮��ĸ��ţ��¸��µ�״̬Ҳ����Ӱ��������
			f[j] = max(f[j], f[j - weight[i]] + value[i]);  //�����ʽ�ӱ�ʾ��װ�ϵ�i����Ʒǰ��������Ʒ�ļ�ֵ+��i����Ʒ�ļ�ֵ
	return f[v];  //���ص�Ϊ�������ʱ����ֵ
}

//2.��ȫ��������
//��n����Ʒ��һ������Ϊv�ı�����ÿ����Ʒ�������޼����á���i����Ʒ����������weight[i]����ֵ��value[i]��
//����Щ��Ʒװ�뱳����ʹ��Щ��Ʒ������ܺͲ����������������Ҽ�ֵ�ܺ����
static int ZeroMorePackge(vector<int> &weight, vector<int> &value, vector<int> &f, int n, int v)
{
	for (int i = 1; i <= n; i++) //ÿ����Ʒ����
		for (int j = weight[i]; j <= v; j++)  //�ӱ����ĵ�ǰ��Ʒ���������������˳����ң�˳����ҵ�ԭ�����ڿ���֮ǰ��Ʒ�Ĺ��ף�
			f[j] = max(f[j], f[j - weight[i]] + value[i]);  //�����ʽ�ӱ�ʾ��װ�ϵ�i����Ʒǰ��������Ʒ�ļ�ֵ+��i����Ʒ�ļ�ֵ
	return f[v];  //���ص�Ϊ�������ʱ����ֵ
}

//3.���ر�������
//��n����Ʒ��һ������Ϊv�ı�������i����Ʒ�����eachNum[i]�����ã�ÿ�������weight[i]����ֵ��value[i]��
//��⽫��Щ��Ʒװ�뱳����ʹ��Щ��Ʒ������ܺͲ�������������v���Ҽ�ֵ�ܺ����
static int MorePackge(vector<int> &weight, vector<int> &value, vector<int> &f, vector<int> &eachNum, int n, int v)
{
	for (int i = 1; i <= n; i++)
		for (int k = 1; k <= eachNum[i]; k++)
			for (int j = v; j >= weight[i]; j--)  //�ӱ����������������ǰ��Ʒ������������ң���ͨ����ͼ��⣩
				f[j] = max(f[j], f[j - weight[i]] + value[i]);  //�����ʽ�ӱ�ʾ��װ�ϵ�i����Ʒǰ��������Ʒ�ļ�ֵ+��i����Ʒ�ļ�ֵ
	return f[v];  //���ص�Ϊ�������ʱ����ֵ
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