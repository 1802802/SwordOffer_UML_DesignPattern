#pragma once

template<typename T> class Vector
{
private:
	int _size;		//ʵ�ʴ�С
	int _capacity;	//��ǰ����
	T* _elem;		//ָ���ڴ���λ�õ�ָ�루������Ϊbegin())
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
	//��ȷ���Ƿ��ڿ�ʼ��ֵ/�ƶ�ǰ�ͷ������������е��ڴ棨��ֹ�ڴ�й¶��
	//���жϴ���Ĳ����Ƿ�Ϊ����this���ǵĻ���ֱ�ӷ�������������ᵼ������������û��Ԫ����
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
		swap(_elem[i - 1], _elem[rand() % i]);
}

template<typename T> void Vector<T>::sort()
{
	sort(0, _size);
}

template<typename T> void Vector<T>::sort(int lo, int hi)
{
	int n = rand() % 1;
	switch (n)
	{
	case 0: bubblesort(lo, hi); break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	default: bubblesort(lo, hi); break;
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
			if (_elem[lo] < _elem[lo + 1])
			{
				T temp = _elem[lo];
				_elem[lo] = _elem[lo + 1];
				_elem[lo + 1] = temp;
				flag = false;
			}
		}
		hi--;
	}
}