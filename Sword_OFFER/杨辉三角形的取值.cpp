#include <iostream>
using namespace std;

//��������ε��������ǣ�һ��������������֮��
long PascalsTriangle(int x, int y)
{
	//1.�����ж����ݵ�������ȷ
	if( x > 0 && y > 0)
	{
		//2.Ȼ���жϵݹ����ȡ�����εı߾�Ϊ1
		if (x == y || x == 1)
			return 1;
		//3.�����������ִ�ж��ֵݹ飬���������λ�ý��еݹ飨�����ڹ�ʱ��ɽ�����㣩
		return PascalsTriangle(x - 1, y - 1) + PascalsTriangle(x, y - 1);
	}
	return -1;
}

class A
{
public:
	virtual void fun() { cout << "fun A" << endl; }
	A() { fun();  cout << "A" << endl; }
	virtual ~A() { fun(); cout << "A Delete" << endl; }
};

class B : public A
{
public:
	void test() {}
	void fun() override { cout << "fun B" << endl; }
	B() { cout << "B" << endl; }
	~B() { cout << "B Delete" << endl; }
};

class AAA { public: void f1() {} virtual void f2() {} };

int main_PascalsTriangle()
{
	A* a = new B;
	delete a;

	cout << "��������ε�(10,5)λ��Ϊ��" << PascalsTriangle(3, 5) << endl;
	return 0;
}