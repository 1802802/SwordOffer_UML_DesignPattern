#include <iostream>
#include <vector>
using namespace std;

//二分查找，三种方式的mi都是选取的中间值，所以时间复杂度都是O(logn)
//版本A最原始的思想，为在排序的数组中，从中点二分位置处判断中点较大还是较小，较大则取大区间，较小则取小区间
//对于多个相同的数，只能根据代码顺序找到最近的一个，时间复杂度具体为O(1.50logn)
template<typename T> static int binSearch_A(const vector<T>& A, T const& e, int lo, int hi)
{
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		//区间1：[lo,mi)
		if (e < A[mi])
			hi = mi;
		//区间2：[mi+1,hi)
		else if (e > A[mi])
			lo = mi + 1;
		//区间3：直接命中mi
		else
			return mi;
	}
	return -1;
}

//B版本，特色在于成功命中不能直接返回，需要在最后结束循环后return时进行判断
//对于多个相同的数，只能根据代码顺序找到最近的一个，但是各分支的查找长度更加接近，故整体性能更趋稳定
template<typename T> static int binSearch_B(const vector<T>& A, T const& e, int lo, int hi)
{
	while (lo + 1 < hi)
	{
		int mi = (lo + hi) >> 1;
		//区间1：[lo,mi)
		if (e < A[mi])
			hi = mi;
		//区间2：[mi,hi)
		else
			lo = mi;
	}
	//出口时hi = lo + 1，且hi为开区间，只能选择lo
	return (e == A[lo]) ? lo : -1;
}

//C版本，与B基本相同，但是特色在于能够返回最后失败的位置
//对于多个相同的数，可以返回秩最大者
template<typename T> static int binSearch_C(const vector<T>& A, T const& e, int lo, int hi)
{
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		//区间1：[lo,mi)
		if (e < A[mi])
			hi = mi;
		//区间2：[mi + 1,hi)
		else
			lo = mi + 1;
	}
	//此版本的特色，最后找到的区间，lo是大于元素e的最小秩，所以--lo为不大于e的最大秩，即此值要么是命中值，要么是失败的所处位置
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

//fibonacci查找，也称黄金分割查找（就是取mi值的方式改了，随着fibnocci数列走，为lo+fib-1）
//时间复杂度O(1.44logn)
template<typename T> static int fibonacciSearch_A(const vector<T>& A, T const& e, int lo, int hi)
{
	Fib fib(hi - lo);
	int place = fib.m_fib.size() - 1;
	while (lo < hi)
	{
		while (hi - lo < fib.m_fib[place--]);
		int mi = lo + fib.m_fib[place] - 1;
		//区间1：[lo,mi)
		if (e < A[mi])
			hi = mi;
		//区间2：[mi+1,hi)
		else if (e > A[mi])
			lo = mi + 1;
		//区间3：直接命中mi
		else
			return mi;
	}
	return -1;
}

//快排算法，思想就是取中位点，使用快速划分算法将一组数据中比轴点小的数移到其左边，大移到右边，直到数据段大小小于2
template<typename T> void quickSort(vector<T>& A, int lo, int hi)
{
	//这个小于2很经典，常规思想的话这里应该是<1，但是实际上<2就可以了，能够加快计算效率
	if (hi - lo < 2)
		return;
	int mi = partition(A, lo, hi - 1);
	quickSort(A, lo, mi);
	quickSort(A, mi + 1, hi);
}

//快速划分算法，首先是选取轴点，然后根据轴点进行划分，最后返回轴点位置（秩）
template<typename T> int partition(vector<T>& A, int lo, int hi)
{
	//1.首先随机选取数据段中的一个位置（设其为轴点pivot，将该位置的数值与lo处的数值进行交换
	//这里想随机就随机，不想随机直接注释掉都行
	swap(A[lo], A[lo + rand() % (hi - lo + 1)]);
	//2.获取轴点的数据值pivot（其位置在lo处，这里的值很重要，关系到后面所有的数据交换）
	T pivot = A[lo];
	//3.交换过程为前后双指针，前指针用于将比节点小的数换过去，后指针用于将比节点大的数换过去
	//对于轴点的理解，就是这个值刚开始就成了虚值（可以理解为A[lo]位置直接为空），直到最后才会放回去
	while (lo < hi)
	{
		//3.1由于轴点的初始位为lo，所以从hi开始搜索大值，当搜索到比轴点小的值则换过来
		while ((lo < hi) && (pivot <= A[hi]))
			hi--;
		A[lo] = A[hi];
		//3.2然后从前往后搜lo
		while ((lo < hi) && (pivot >= A[lo]))
			lo++;
		A[hi] = A[lo];
	}
	//最后一步为A[hi] = A[lo]，在完成上述搜索后，lo处的位置属于“最后一个被换的点”，所以将轴点放入此位置
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