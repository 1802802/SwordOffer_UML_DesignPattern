#include <iostream>
using namespace std;

//class A
//{
//	char a[3];
//public:
//	virtual void aa() {};
//};
//
//class B :public virtual A
//{
//	char b[3];
//public:
//	virtual void bb() {};
//};
//
//class C :public virtual B
//{
//	char c[3];
//public:
//	virtual void cc() {};
//};
//8 20 32

class A
{
	char a[3];
public:
	virtual void aa() {};
};

class B :public A
{
	char b[3];
public:
	virtual void bb() {};
};

class C :public B
{
	char c[3];
public:
	virtual void cc() {};
};
//8 12 16


int main_virtualsizeof()
{
	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
	cout << sizeof(C) << endl;

	return 0;
}