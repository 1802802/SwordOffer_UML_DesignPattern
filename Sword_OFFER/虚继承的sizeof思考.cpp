#include <iostream>
using namespace std;

/*
普通继承与虚函数继承：
（1）普通继承：class A ：public B；A中内存会将B中的所有数据放到前面，
自己的变量内存放到后面（仍符合内存对齐规则），计算内存时按照内存对齐的方式去计算；
（2）虚函数继承：class A ：virtual public B；B的数据相关内存存储在内存的后部（加上了虚基类指针），
而A自己的数据存放在前面（并且最前面的内存为新创建的虚函数指针，指向当前类的虚函数表），
前面的正常继承数据与类A自己的内存自己内存对齐，后面的虚继承的内存自己内存对齐（切记），两者直接相加为总数
*/

//虚函数继承时如class B : public virtual A，B的sizeof为：（B自身数据成员的内存对齐大小 + 虚基类表指针大小（常为4） + A的sizeof大小）
class A
{
	//char a[3];
	
public:
	virtual void aa() {};
};

class B :public virtual A
{
	int aa;
	char b[3];
public:
	//virtual void bb() {};
};

class C :public virtual A
{
	//char c[3];
public:
	virtual void cc() { A::aa(); };
};
//8 20 32

//虚继承的继承的那块变量的内存，都是放在最后的相加而不是对齐（也就是说是虚基类表指针大小4字节+虚继承的类的大小），而虚指针都是放在最前面的
class D : public A  //如果这里不是虚继承，那就是常规套路，如果是虚继承，那么还会多一个指向父类的虚函数指针
{
	//两个继承都是virtual时D才会产生自己的虚函数指针
	char c[3];
public:
	void dd() {};
};

//class A
//{
//	char a[3];
//public:
//	virtual void aa() {};
//};
//
//class B :public A
//{
//	char b[3];
//public:
//	virtual void bb() {};
//};
//
//class C :public A
//{
//	char c[3];
//public:
//	virtual void cc() {};
//};
//
//class D : public B, public C
//{
//	char c[3];
//public:
//	void dd() {};
//};
//8 12 16

int main_virtualpublic()
//int main_virtualsizeof()
{
	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
	cout << sizeof(C) << endl;
	cout << sizeof(D) << endl;
	//D d;

	//if (dynamic_cast<D*>(&d) == NULL)
	//	cout << "NULL" << endl;


	return 0;
}