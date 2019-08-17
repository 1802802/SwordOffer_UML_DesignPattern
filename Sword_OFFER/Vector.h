#pragma once
#include<time.h>
#include <vector>
#include <queue>
using namespace std;

template<typename T> class Vector
{
private:
	int _size;		//ʵ�ʴ�С
	int _capacity;	//��ǰ����
	T* _elem;		//ָ���ڴ���λ�õ�ָ�루�����Ϊbegin())
public:
	//���캯������������
	Vector(int capacity = 1, T value = 0);
	Vector(const Vector<T>& vec);
	Vector(Vector<T>&& vec) noexcept;
	Vector<T>& operator=(const Vector<T>& vec);
	Vector<T>& operator=(Vector<T>&& vec) noexcept;
	T& operator[](int rank) const;
	~Vector();
	//��̬������ĺ���
	void shrink();
	void expand();
	//���÷��ʽӿ�
	bool empty() const;
	int size() const;
	int find(T const& v);
	int find(T const& v, int lo, int hi);
	int erase(int rank);
	int erase(int lo, int hi);
	int insert(int rank, T const&v);
	void print(int lo, int hi);

	//�����㷨��ʵ�ֽӿڣ�����sort�е�������ã�
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
};

#include "Vector.h"
#include <random>

//���캯������������

template<typename T> Vector<T>::Vector(int capacity = 1, T value = 0)
{
	_elem = new T[_capacity = capacity];
	for (_size = 0; _size < _capacity; _size++)
		_elem[_size] = value;
}

template<typename T> Vector<T>::Vector(const Vector& vec)
{
	//�������캯��ʹ���������new��һ���µĿռ䣬��_elemָ��Ȼ�󿽱���ֵ
	_elem = new T[_capacity = vec._capacity];
	for (_size = 0; _size < vec._size; _size++)
		_elem[_size] = vec[_size];
}

template<typename T> Vector<T>::Vector(Vector&& vec) noexcept
{
	//�ƶ����캯��ʹ���ƶ���ֵ������vec���ڲ����Ը�ֵ��������󣬽�vec��ȫ���ÿ�
	_elem = vec._elem;
	_size = vec._size;
	_capacity = vec._capacity;
	vec._elem = nullptr;
	vec._size = vec._capacity = 0;
}

template<typename T> Vector<T>& Vector<T>::operator=(const Vector<T>& vec)
{
	//������ֵ��������ƶ���ֵ�����������Ҫ�أ�
	//�ٽ�����ֵ��Ϊ�����͵����ã���������������ֵ��
	//�ڣ�ֻ��Կ�����ֵ���������������β���Ϊ�������ã�����ʵ�ε��β�ִ��һ�ο������캯����
	//��ȷ���Ƿ��ڿ�ʼ��ֵ/�ƶ�ǰ�ͷ����������е��ڴ棨��ֹ�ڴ�й¶��
	//���жϴ���Ĳ����Ƿ�Ϊ����this���ǵĻ���ֱ�ӷ�����������ᵼ����������û��Ԫ����
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

//��̬������ĺ���
template<typename T> void Vector<T>::expand()
{
	if (_size < _capacity)
		return;
	else
	{
		//ע�⣬���ݺ�_size���䣬capacity��������elem�����˵�ַ
		T* _oldelem = _elem;
		_elem = new T[_capacity <<= 1];
		for (int i = 0; i < _size; i++)
			_elem[i] = _oldelem[i];
		delete[] _oldelem;
	}
}

template<typename T> void Vector<T>::shrink()
{
	if (_size << 2 > _capacity)
		return;
	else
	{
		//ע�⣬���ݺ�_size���䣬capacity���룬��elem�����˵�ַ
		T* _oldelem = _elem;
		_elem = new T[_capacity >>= 1];
		for (int i = 0; i < _size; i++)
			_elem[i] = _oldelem[i];
		delete[] _oldelem;
	}
}

//���÷��ʽӿ�

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
	//erase���õ���ֱ�Ӷ����ķ�ʽ
	if (lo == hi)
		return 0;
	//�������ĵĺ����ǽ�[hi,size]ǰ����hi-lo����Ԫ��ֱ������������ļ���
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
	return rank;
}

template<typename T> void Vector<T>::print(int lo, int hi)
{
	while (lo < hi)
		std::cout << _elem[lo++] << " ";
	std::cout << std::endl;
}

//������ϴ���㷨
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
	int n = 6;
	switch (n)
	{
	case 0: bubblesort(lo, hi); cout << "��ǰʹ��bubblesort" << endl; break;
	case 1:	mergesort(lo, hi); cout << "��ǰʹ��mergesort" << endl; break;
	case 2:	insertionsort(lo, hi); cout << "��ǰʹ��insertionsort" << endl; break;
	case 3:	selectionsort(lo, hi); cout << "��ǰʹ��selectionsort" << endl;  break;
	case 4:	countingsort(lo, hi) ; cout << "��ǰʹ��countingsort" << endl; break;
	case 5:	bucketsort(lo, hi); cout << "��ǰʹ��bucketsort" << endl; break;
	case 6:	radixsort(lo, hi); cout << "��ǰʹ��radixsort" << endl;  break;
	case 7:	break;
	case 8:	break;
	case 9: break;
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

//�ص�Ϊ���ϵؽ�֮������ݲ���ǰ׺��ֻ��ǰ׺�����ܺ�׺
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
		//�жϱȵ�ǰiλ�ô���������򻻣�û���򲻻������ۻ�����i���ݼ�
		for (j = lo, max = i; j <= i; j++)
			if (_elem[j] > _elem[max])
				max = j;
		if (i != max)
			swap(_elem[i], _elem[max]);
	}
}

//������ʵΪ��������ʵ�ֵ��Ƕ����г��ֵ������г��ִ����ļ�������
//���ɼ���������Ϊһ�������Ͱ���򣬵�Ͱ�ĸ�������ʱ��Ҳ����һ������һ��Ͱ�����Ǽ�������
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

//Ͱ����Ϊ��������������棬����������һ��һͰ����Ͱ�����Ƕ���һͰ��һ����Χ�ڵ���һͰ����
//Ȼ����Ͱ�ڽ��е���������������򣩣�����ٽ�����Ͱ�ϲ�����
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
	//��ʾͰ����Ŀ�����Ҷ�Ϊ5��bucket����Ĭ��Ū�ĺܴ�
	int n = 5;
	vector<vector<int>> bucket(n + 1);
	int range = (largest - minest) / n;
	if (range < 1) range = 1;
	//�Ȱ�����ȫ�����뵽��Ӧ��Ͱ�У�ÿ����һ��Ͱ�ͽ���һ������
	for (int i = lo; i < hi; i++)
	{
		int index = (_elem[i] - minest) / range;
		bucket[index].push_back(_elem[i]);
		for (int j = bucket[index].size() - 1; j > 0 && bucket[index][j] < bucket[index][j - 1]; j--)
			swap(bucket[index][j], bucket[index][j - 1]);
	}
	//���Ͱ�����ݶ�ԭ�������ȫ������
	int cur = lo;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j < bucket[i].size(); j++)
			_elem[cur++] = bucket[i][j];
}

//�������򣬴Ӹ�λ��ʼ������ʱ����ʹ�ø�����
template<typename T> void Vector<T>::radixsort(int lo, int hi)
{
	int i, j, k, factor;
	const int radix = 10;
	const int digits = 10;
	queue<T> queues[radix];                                        //һ����У����ڴ洢��ͬ���������ݣ�ÿһ�����������Ҷ�Ӧ9������
	for (i = 0, factor = 1; i < digits; factor *= radix, i++)      //digits��ʾ���λ����Ĭ��Ϊ10λ���˴�����10�顣Ҳ�����Ż��㷨Ϊ��ǰ����������������һλ
	{
		for (j = lo; j < hi; j++)
			queues[(_elem[j] / factor) % radix].push(_elem[j]);	   //ÿ�����ݣ����ݵ�ǰλ��ȡ��õ�������������Ӧ�Ķ����У����к㶨Ϊ0-9��
		for (j = 0, k = lo; j < radix; j++)
			while (!queues[j].empty())							   //������˳�����ÿ�����У����½����ݸ���ԭ����data��ͬʱ��������ж���
			{
				_elem[k++] = queues[j].front();
				queues[j].pop();
			}
	}
	bool *pf = bucketsort;
}