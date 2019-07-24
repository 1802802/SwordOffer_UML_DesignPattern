#include <iostream>
#include <vector>
using namespace std;

//���ֲ��ң����ַ�ʽ��mi����ѡȡ���м�ֵ������ʱ�临�Ӷȶ���O(logn)
//�汾A��ԭʼ��˼�룬Ϊ������������У����е����λ�ô��ж��е�ϴ��ǽ�С���ϴ���ȡ�����䣬��С��ȡС����
//���ڶ����ͬ������ֻ�ܸ��ݴ���˳���ҵ������һ����ʱ�临�ӶȾ���ΪO(1.50logn)
template<typename T> static int binSearch_A(const vector<T>& A, T const& e, int lo, int hi)
{
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		//����1��[lo,mi)
		if (e < A[mi])
			hi = mi;
		//����2��[mi+1,hi)
		else if (e > A[mi])
			lo = mi + 1;
		//����3��ֱ������mi
		else
			return mi;
	}
	return -1;
}

//B�汾����ɫ���ڳɹ����в���ֱ�ӷ��أ���Ҫ��������ѭ����returnʱ�����ж�
//���ڶ����ͬ������ֻ�ܸ��ݴ���˳���ҵ������һ�������Ǹ���֧�Ĳ��ҳ��ȸ��ӽӽ������������ܸ����ȶ�
template<typename T> static int binSearch_B(const vector<T>& A, T const& e, int lo, int hi)
{
	while (lo + 1 < hi)
	{
		int mi = (lo + hi) >> 1;
		//����1��[lo,mi)
		if (e < A[mi])
			hi = mi;
		//����2��[mi,hi)
		else
			lo = mi;
	}
	//����ʱhi = lo + 1����hiΪ�����䣬ֻ��ѡ��lo
	return (e == A[lo]) ? lo : -1;
}

//C�汾����B������ͬ��������ɫ�����ܹ��������ʧ�ܵ�λ��
//���ڶ����ͬ���������Է����������
template<typename T> static int binSearch_C(const vector<T>& A, T const& e, int lo, int hi)
{
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		//����1��[lo,mi)
		if (e < A[mi])
			hi = mi;
		//����2��[mi + 1,hi)
		else
			lo = mi + 1;
	}
	//�˰汾����ɫ������ҵ������䣬lo�Ǵ���Ԫ��e����С�ȣ�����--loΪ������e������ȣ�����ֵҪô������ֵ��Ҫô��ʧ�ܵ�����λ��
	return --lo;
}

class Fib
{
public:
	vector<int> m_fib;

	Fib(int n)
	{
		int f = 1;
		int s = 0;
		while (n > s)
		{
			s = f + s;
			f = s - f;
			m_fib.push_back(s);
		}
	}
	
};

//fibonacci���ң�Ҳ�ƻƽ�ָ���ң�����ȡmiֵ�ķ�ʽ���ˣ�����fibnocci�����ߣ�Ϊlo+fib-1��
//ʱ�临�Ӷ�O(1.44logn)
template<typename T> static int fibonacciSearch_A(const vector<T>& A, T const& e, int lo, int hi)
{
	Fib fib(hi - lo);
	int place = fib.m_fib.size() - 1;
	while (lo < hi)
	{
		while (hi - lo < fib.m_fib[place--]);
		int mi = lo + fib.m_fib[place] - 1;
		//����1��[lo,mi)
		if (e < A[mi])
			hi = mi;
		//����2��[mi+1,hi)
		else if (e > A[mi])
			lo = mi + 1;
		//����3��ֱ������mi
		else
			return mi;
	}
	return -1;
}

//�����㷨��˼�����ȡ��λ�㣬ʹ�ÿ��ٻ����㷨��һ�������б����С�����Ƶ�����ߣ����Ƶ��ұߣ�ֱ�����ݶδ�СС��2
template<typename T> void quickSort(vector<T>& A, int lo, int hi)
{
	//���С��2�ܾ��䣬����˼��Ļ�����Ӧ����<1������ʵ����<2�Ϳ����ˣ��ܹ��ӿ����Ч��
	if (hi - lo < 2)
		return;
	int mi = partition(A, lo, hi - 1);
	quickSort(A, lo, mi);
	quickSort(A, mi + 1, hi);
}

//���ٻ����㷨��������ѡȡ��㣬Ȼ����������л��֣���󷵻����λ�ã��ȣ�
template<typename T> int partition(vector<T>& A, int lo, int hi)
{
	//1.�������ѡȡ���ݶ��е�һ��λ�ã�����Ϊ���pivot������λ�õ���ֵ��lo������ֵ���н���
	//�����������������������ֱ��ע�͵�����
	swap(A[lo], A[lo + rand() % (hi - lo + 1)]);
	//2.��ȡ��������ֵpivot����λ����lo���������ֵ����Ҫ����ϵ���������е����ݽ�����
	T pivot = A[lo];
	//3.��������Ϊǰ��˫ָ�룬ǰָ�����ڽ��Ƚڵ�С��������ȥ����ָ�����ڽ��Ƚڵ���������ȥ
	//����������⣬�������ֵ�տ�ʼ�ͳ�����ֵ���������ΪA[lo]λ��ֱ��Ϊ�գ���ֱ�����Ż�Ż�ȥ
	while (lo < hi)
	{
		//3.1�������ĳ�ʼλΪlo�����Դ�hi��ʼ������ֵ���������������С��ֵ�򻻹���
		while ((lo < hi) && (pivot <= A[hi]))
			hi--;
		A[lo] = A[hi];
		//3.2Ȼ���ǰ������lo
		while ((lo < hi) && (pivot >= A[lo]))
			lo++;
		A[hi] = A[lo];
	}
	//���һ��ΪA[hi] = A[lo]�����������������lo����λ�����ڡ����һ�������ĵ㡱�����Խ��������λ��
	A[lo] = pivot;
	return lo;
}

int main_offer11_search_quicksort()
{
	vector<int> a = { 1,1,23,124,143,3252454,543,634,12,312,312,12,1,1,2,3,4,6,7,13,89,124,134 };
	for (auto &s : a)
		cout << s << " ";
	cout << endl;
	quickSort(a, 0, a.size());
	for (auto &s : a)
		cout << s << " ";
	cout << endl;
	cout << "place is: " << binSearch_A<int>(a, 89, 0, a.size()) << endl;
	cout << "place is: " << binSearch_B<int>(a, 89, 0, a.size()) << endl;
	cout << "place is: " << binSearch_C<int>(a, 89, 0, a.size()) << endl;
	cout << "place is: " << fibonacciSearch_A<int>(a, 89, 0, a.size()) << endl;

	return 0;
}