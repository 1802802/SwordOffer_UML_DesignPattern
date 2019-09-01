#pragma once
#include <time.h>
#include <list>
#include <new>
#include <queue>
#include <stack>
using namespace std;

static int count1 = 0;
//void* operator new(size_t size)
//{
//	count1++;
//	return malloc(size);
//}

template<typename T> class Vector
{
private:
	int _size;		//实际大小
	int _capacity;	//当前容量
	T* _elem;		//指向内存首位置的指针（可理解为begin())
public:
	//构造函数与析构函数
	Vector(int capacity = 1, T value = 0);
	Vector(const Vector<T>& vec);
	Vector(Vector<T>&& vec) noexcept;
	Vector<T>& operator=(const Vector<T>& vec);
	Vector<T>& operator=(Vector<T>&& vec) noexcept;
	T& operator[](int rank) const;
	~Vector();
	//动态数组核心函数
	void shrink();
	void expand();
	//常用访问接口
	bool empty() const;
	int size() const;
	int find(T const& v);
	int find(T const& v, int lo, int hi);
	int erase(int rank);
	int erase(int lo, int hi);
	int insert(int rank, T const&v);
	void print(int lo, int hi);

	//排序算法的实现接口（用于sort中的随机调用）
	void unsort();
	void sort();
	void sort(int lo, int hi);

	void bubblesort(int lo, int hi);
	void mergesort(int lo, int hi);
	void merge(int lo, int mi, int hi);
	void insertionsort(int lo, int hi);
	void selectionsort(int lo, int hi);
	void countingsort(int lo, int hi);
	void bucketsort(int lo, int hi);
	void radixsort(int lo, int hi);
	void moveDown(int first, int last);
	void moveUp(int rank);
	void moveDown_reserve(int first, int last);
	void heapsort(int lo, int hi);
	void quicksort(int lo, int hi);
	int partition(int lo, int hi);
	void shellsort(int lo, int hi);
	void quicksort2(int lo, int hi);
};

#include "Vector.h"
#include <random>

//构造函数与析构函数

template<typename T> Vector<T>::Vector(int capacity = 1, T value = 0)
{
	_elem = new T[_capacity = capacity];
	for (_size = 0; _size < _capacity; _size++)
		_elem[_size] = value;
}

template<typename T> Vector<T>::Vector(const Vector& vec)
{
	//拷贝构造函数使用深拷贝，即new出一个新的空间，将_elem指向，然后拷贝赋值
	_elem = new T[_capacity = vec._capacity];
	for (_size = 0; _size < vec._size; _size++)
		_elem[_size] = vec[_size];
}

template<typename T> Vector<T>::Vector(Vector&& vec) noexcept
{
	cout << "移动构造函数" << endl;
	//移动构造函数使用移动赋值，即将vec的内部属性赋值给本对象后，将vec的全部置空
	_elem = vec._elem;
	_size = vec._size;
	_capacity = vec._capacity;
	vec._elem = nullptr;
	vec._size = vec._capacity = 0;
}

template<typename T> Vector<T>& Vector<T>::operator=(const Vector<T>& vec)
{
	//拷贝赋值运算符与移动赋值运算符的三大要素：
	//①将返回值设为该类型的引用（用于连续拷贝赋值）
	//②（只针对拷贝赋值运算符）将传入的形参设为常量引用（避免实参到形参执行一次拷贝构造函数）
	//③确定是否在开始赋值/移动前释放了自身本来有的内存（防止内存泄露）
	//④判断传入的参数是否为自身this，是的话则直接返回自身，否则会导致自身被析构没有元素了
	if (this != &vec)
	{
		delete[] _elem;
		_elem = new T[_capacity = vec._capacity];
		for (_size = 0; _size < vec._size; _size++)
			_elem[_size] = vec[_size];
	}
	return *this;
}

template<typename T> Vector<T>& Vector<T>::operator=(Vector&& vec) noexcept
{
	cout << "移动赋值运算符" << endl;
	if (this != &vec)
	{
		delete[] _elem;
		_elem = vec._elem;
		_size = vec._size;
		_capacity = vec._capacity;
		vec._elem = nullptr;
		vec._size = vec._capacity = 0;
	}
	return *this;
}

template<typename T> T& Vector<T>::operator[](int rank) const
{
	return _elem[rank];
}

template<typename T> Vector<T>::~Vector()
{
	delete[] _elem;
}

//动态数组核心函数
template<typename T> void Vector<T>::expand()
{
	if (_size < _capacity)
		return;
	else
	{
		//注意，扩容后_size不变，capacity翻倍，而elem更换了地址
		T* _oldelem = _elem;
		_elem = new T[_capacity <<= 1];
		for (int i = 0; i < _size; i++)
			_elem[i] = _oldelem[i];
		delete[] _oldelem;
	}
	cout << "expand" << endl;
}

template<typename T> void Vector<T>::shrink()
{
	if (_size << 2 > _capacity)
		return;
	else
	{
		//注意，缩容后_size不变，capacity减半，而elem更换了地址
		T* _oldelem = _elem;
		_elem = new T[_capacity >>= 1];
		for (int i = 0; i < _size; i++)
			_elem[i] = _oldelem[i];
		delete[] _oldelem;
	}
}

//常用访问接口

template<typename T> bool Vector<T>::empty() const
{
	return !_size;
}

template<typename T> int Vector<T>::size() const
{
	return _size;
}

template<typename T> int Vector<T>::find(T const& v)
{
	find(v, 0, _size);
}
template<typename T> int Vector<T>::find(T const& v, int lo, int hi)
{
	while (lo < hi && v != _elem[lo])
		lo++;
	return (lo == hi) ? (-1) : (lo);
}

template<typename T> int Vector<T>::erase(int rank)
{
	return erase(rank, rank + 1);
}

template<typename T> int Vector<T>::erase(int lo, int hi)
{
	//erase采用的是直接丢弃的方式
	if (lo == hi)
		return 0;
	//下面代码的的含义是将[hi,size]前移了hi-lo个单元，直接抛弃掉后面的即可
	while (hi < _size)
		_elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return hi - lo;
}

template<typename T> int Vector<T>::insert(int rank, T const&v)
{
	expand();
	//if (rank >= _size)
	//	return -1;
	for (int i = _size; i > rank; i--)
		_elem[i] = _elem[i - 1];
	_elem[rank] = v;
	_size++;

	cout << "当前count1为：" << count1 << endl;
	return rank;
}

template<typename T> void Vector<T>::print(int lo, int hi)
{
	while (lo < hi)
		std::cout << _elem[lo++] << " ";
	std::cout << std::endl;
}

//著名的洗牌算法
template<typename T> void Vector<T>::unsort()
{
	for (int i = _size; i > 0; i--)
	{
		srand((unsigned)time(NULL));
		swap(_elem[i - 1], _elem[rand() % i]);
	}
}

template<typename T> void Vector<T>::sort()
{
	sort(0, _size);
}

template<typename T> void Vector<T>::sort(int lo, int hi)
{
	srand((unsigned)time(NULL));
	int n = 10;
	switch (n)
	{
	case 0: bubblesort(lo, hi); cout << "当前使用bubblesort" << endl; break;
	case 1:	mergesort(lo, hi); cout << "当前使用mergesort" << endl; break;
	case 2:	insertionsort(lo, hi); cout << "当前使用insertionsort" << endl; break;
	case 3:	selectionsort(lo, hi); cout << "当前使用selectionsort" << endl;  break;
	case 4:	countingsort(lo, hi) ; cout << "当前使用countingsort" << endl; break;
	case 5:	bucketsort(lo, hi); cout << "当前使用bucketsort" << endl; break;
	case 6:	radixsort(lo, hi); cout << "当前使用radixsort" << endl;  break;
	case 7:	heapsort(lo, hi); cout << "当前使用heapsort" << endl; break;
	case 8:	quicksort(lo, hi); cout << "当前使用quicksort" << endl; break;
	case 9: shellsort(lo, hi); cout << "当前使用shellsort" << endl; break;
	case 10: quicksort2(lo, hi); cout << "当前使用quicksort2" << endl; break;
	default: break;
	}
}

template<typename T> void Vector<T>::bubblesort(int lo, int hi)
{
	bool flag = false;
	while (!flag)
	{
		flag = true;
		for (int i = lo; i < hi - 1; i++)
		{
			if (_elem[i] > _elem[i + 1])
			{
				swap(_elem[i], _elem[i + 1]);
				flag = false;
			}
		}
		hi--;
	}
}

template<typename T> void Vector<T>::mergesort(int lo, int hi)
{
	if (hi - lo < 2)
		return;
	int mi = (hi + lo) >> 1;
	mergesort(lo, mi);
	mergesort(mi, hi);
	merge(lo, mi, hi);
}

template<typename T> void Vector<T>::merge(int lo, int mi, int hi)
{
	int i1 = 0, i2 = lo, i3 = mi;
	int *temp = new int[hi - lo];

	while (i2 < mi && i3 < hi)
	{
		if (_elem[i2] <= _elem[i3])
			temp[i1++] = _elem[i2++];
		else
			temp[i1++] = _elem[i3++];
	}

	while (i2 < mi)
		temp[i1++] = _elem[i2++];
	while (i3 < hi)
		temp[i1++] = _elem[i3++];

	for (int i = 0; i < hi - lo; i++)
		_elem[i + lo] = temp[i];

	delete[] temp;
}

//特点为不断地将之后的数据插入前缀，只管前缀，不管后缀
template<typename T> void Vector<T>::insertionsort(int lo, int hi)
{
	for (int i = lo + 1, j; i < hi; i++)
	{
		for (j = i; j > lo && _elem[j] < _elem[j - 1]; j--)
			swap(_elem[j], _elem[j - 1]);
	}
}

template<typename T> void Vector<T>::selectionsort(int lo, int hi)
{
	for (int i = hi - 1, j, max; i > lo; i--)
	{
		//判断比当前i位置大的数，有则换，没有则不换，无论换不换i都递减
		for (j = lo, max = i; j <= i; j++)
			if (_elem[j] > _elem[max])
				max = j;
		if (i != max)
			swap(_elem[i], _elem[max]);
	}
}

//这里其实为计数排序，实现的是对所有出现的数进行出现次数的计数过程
//（可见计数排序为一种特殊的桶排序，当桶的个数最大的时候，也就是一个数对一个桶，就是计数排序）
template<typename T> void Vector<T>::countingsort(int lo, int hi)
{
	int largest = _elem[lo];
	int minest = _elem[lo];
	for (int i = lo; i < hi; i++)
	{
		if (_elem[i] > largest)
			largest = _elem[i];
		if (_elem[i] < minest)
			minest = _elem[i];
	}
	int size = largest - minest + 1;
	int *bucket = new int[size];
	for (int i = 0; i < size; i++)
		bucket[i] = 0;
	for (int i = lo; i < hi; i++)
		bucket[_elem[i] - minest]++;
	for (int i = 0; i < size;)
	{
		if (bucket[i]-- > 0)
			_elem[lo++] = i + minest;
		else
			i++;
	}
	delete[] bucket;
}

//桶排序即为计数排序的升级版，计数排序是一数一桶，而桶排序是多数一桶（一个范围内的在一桶），
//然后在桶内进行单独排序（如插入排序），最后再将各个桶合并起来
template<typename T> void Vector<T>::bucketsort(int lo, int hi)
{
	int largest = _elem[lo];
	int minest = _elem[lo];
	for (int i = lo; i < hi; i++)
	{
		if (_elem[i] > largest)
			largest = _elem[i];
		if (_elem[i] < minest)
			minest = _elem[i];
	}
	//表示桶的数目，暂且定为5（bucket数组默认弄的很大）
	int n = 5;
	vector<vector<int>> bucket(n + 1);
	int range = (largest - minest) / n;
	if (range < 1) range = 1;
	//先把数据全部插入到对应的桶中，每插入一个桶就进行一个插排
	for (int i = lo; i < hi; i++)
	{
		int index = (_elem[i] - minest) / range;
		bucket[index].push_back(_elem[i]);
		for (int j = bucket[index].size() - 1; j > 0 && bucket[index][j] < bucket[index][j - 1]; j--)
			swap(bucket[index][j], bucket[index][j - 1]);
	}
	//最后将桶中数据对原数组进行全部覆盖
	int cur = lo;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j < bucket[i].size(); j++)
			_elem[cur++] = bucket[i][j];
}

//基数排序，从个位开始排序（暂时不能使用负数）
template<typename T> void Vector<T>::radixsort(int lo, int hi)
{
	int i, j, k, factor;
	const int radix = 10;
	const int digits = 10;
	queue<T> queues[radix];                                        //一组队列，用于存储不同基数的数据（每一级基数都仅且对应9个数）
	for (i = 0, factor = 1; i < digits; factor *= radix, i++)      //digits表示最大位数，默认为10位，此处遍历10遍。也可以优化算法为当前数据中最大的数的那一位
	{
		for (j = lo; j < hi; j++)
			queues[(_elem[j] / factor) % radix].push(_elem[j]);	   //每个数据，根据当前位数取余得到其基数，存入对应的队列中（对列恒定为0-9）
		for (j = 0, k = lo; j < radix; j++)
			while (!queues[j].empty())							   //按基数顺序遍历每个队列，重新将数据覆盖原数组data的同时，清空所有队列
			{
				_elem[k++] = queues[j].front();
				queues[j].pop();
			}
	}
}

template<typename T> void Vector<T>::moveDown(int first, int last)  //堆的下滤算法，first为当前节点（数组的第一位），last为堆尾位置（数组的最后一位）
{													   //从堆的最底层开始，反层次遍历的顺序遍历每个有孩子的节点（自下而上，由浅至深），孩子比自己大就交换，继续按着孩子原来的位置下滤
	int largest = 2 * first + 1;                       //这里的largest计算的是first节点对应的左孩子位置
	while (largest <= last)							   //判断first节点对应的左孩子是否还在区间内
	{
		if (largest < last && _elem[largest] < _elem[largest + 1])   //此处判断largest是否刚好为末节点，或者查看first的左孩子右孩子哪边大，largest取大边
			largest++;
		if (_elem[first] < _elem[largest])               //first作为父节点，与其最大的孩子比较，如果孩子大就换上来；如果不是，代表该节点稳健，跳出
		{
			swap(_elem[first], _elem[largest]);          //大的子节点largest和父节点first交换，继续判断first的两个孩子与其的大小关系
			first = largest;						   //交换后，对交换过去的first节点继续进行下滤（循环实现，递归也行）
			largest = 2 * first + 1;
		}
		else
			//largest = last + 1;
			break;
	}
}

//堆的上滤，说穿了就是不断判断当前节点与其父节点的堆序性
template<typename T> void Vector<T>::moveUp(int rank)  
{
	int parent_rank = (rank >> 1) - 1;
	while (parent_rank >= 0)
	{
		if (_elem[rank] <= _elem[parent_rank])
			break;
		swap(_elem[rank], _elem[parent_rank]);
		rank = parent_rank;
		parent_rank = (rank >> 1) - 1;
	}
}

//小顶堆的建立，换了下movedown的符号
template<typename T> void Vector<T>::moveDown_reserve(int first, int last)  //堆的下滤算法，first为当前节点（数组的第一位），last为堆尾位置（数组的最后一位）
{													   //从堆的最底层开始，反层次遍历的顺序遍历每个有孩子的节点（自下而上，由浅至深），孩子比自己大就交换，继续按着孩子原来的位置下滤
	int largest = 2 * first + 1;                       //这里的largest计算的是first节点对应的左孩子位置
	while (largest <= last)							   //判断first节点对应的左孩子是否还在区间内
	{
		if (largest < last && _elem[largest] > _elem[largest + 1])   //此处判断largest是否刚好为末节点，或者查看first的左孩子右孩子哪边大，largest取大边
			largest++;
		if (_elem[first] > _elem[largest])               //first作为父节点，与其最大的孩子比较，如果孩子大就换上来；如果不是，代表该节点稳健，跳出
		{
			swap(_elem[first], _elem[largest]);          //大的子节点largest和父节点first交换，继续判断first的两个孩子与其的大小关系
			first = largest;						   //交换后，对交换过去的first节点继续进行下滤（循环实现，递归也行）
			largest = 2 * first + 1;
		}
		else
			//largest = last + 1;
			break;
	}
}

//大顶堆的下滤实现升序，小顶堆的下滤实现降序
template<typename T> void Vector<T>::heapsort(int lo, int hi)
{
	//默认当前数组为树结构的层次遍历序列，从所有的非叶节点进行操作（前size/2 - 1均为非叶节点）
	for (int i = ((hi - lo) >> 1) - 1; i >= lo; --i)    //建堆，floyid建堆法，即自下而上地下滤每个节点。从size的中部选值，保持所取值都是有孩子的节点，避免无关计算
		moveDown(i, hi - lo - 1);

	cout << "建堆后数组为：   ";
	for (int i = lo; i < hi - lo; i++)
		cout << _elem[i] << " ";
	cout << endl;

	for (int i = hi - lo - 1; i >= lo + 1; --i)        //开始实质的堆排序，即不断地将data[0]（当前的最大数）交换到数组的区间末尾
	{
		swap(_elem[lo], _elem[i]);
		moveDown(lo, i - 1);			   //通过每次交换之后的下滤，保证数组的首元素一直都是最大值
	}
}

template<typename T> void Vector<T>::quicksort(int lo, int hi)
{
	if (hi - lo < 2 || lo < 0 || hi <= 0)
		return;
	int mi = partition(lo, hi - 1);
	quicksort(lo, mi);			//区间[lo,mi)
	quicksort(mi + 1, hi);		//区间[mi+1,hi)
}

template<typename T> int Vector<T>::partition(int lo, int hi)
{
	int pivot = _elem[lo];
	while (lo < hi)
	{
		while (lo < hi && pivot <= _elem[hi])
			hi--;
		_elem[lo] = _elem[hi];
		while (lo < hi && pivot >= _elem[lo])
			lo++;
		_elem[hi] = _elem[lo];
	}
	_elem[lo] = pivot;
	return lo;
}

//shell排序为将整个数组分割成固定步长h间距的序列，对不同步长位置的数据排列，最后的增量序列为1即为全部排列（可理解为高级的插入排序）
template<typename T> void Vector<T>::shellsort(int lo, int hi)
{
	list<T> increment;
	int size = hi - lo;
	int temp = 0;
	while (temp < (size / 3))
		increment.push_front(temp = (temp * 3 + 1));
	for (auto &h : increment)
	{
		//这里的h是递增序列的步长，而hh为所使用的i的初始值定义（插排的i初始值为lo+1）
		for (int hh = lo + h; hh < lo + 2 * h; hh++)	//如h=4，n=17，则在h=4时j所选取的值为4,8,12,16，而i自己所选取的初始值为4,5,6,7
		{
			for (int i = hh; i < hi; i += h)			//说穿了，就是将插入排序的递增变成了变步长的递增方式（所有的hh换为1即为传统插排）
			{
				for (int j = i; j >= lo + h && _elem[j] < _elem[j - h]; j -= h)
					swap(_elem[j], _elem[j - h]);
			}
		}
	}
}

//快排的非递归实现，partition函数仍然选择原来的（就是使用栈来存区间[lo,mi)与[mi+1,hi)
template<typename T> void Vector<T>::quicksort2(int lo, int hi)
{
	if (lo < 0 || hi <= 0 || lo >= hi)
		return;
	stack<int> save;
	save.push(hi);
	save.push(lo);
	while (!save.empty())
	{
		lo = save.top(); save.pop();
		hi = save.top(); save.pop();
		if (hi - lo >= 2)
		{
			int pivot = partition(lo, hi - 1);
			if (hi - pivot >= 2)
			{
				save.push(hi);
				save.push(pivot + 1);
			}
			if (pivot - lo >= 2)
			{
				save.push(pivot);
				save.push(lo);
			}
		}

	}
}