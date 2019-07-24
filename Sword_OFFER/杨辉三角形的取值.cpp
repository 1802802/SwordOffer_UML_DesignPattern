#include <iostream>
using namespace std;

//杨辉三角形的特征就是，一个数等于两肩数之和
long PascalsTriangle(int x, int y)
{
	//1.首先判断数据的输入正确
	if( x > 0 && y > 0)
	{
		//2.然后判断递归基，取三角形的边均为1
		if (x == y || x == 1)
			return 1;
		//3.如果都可以则执行二分递归，按照两肩的位置进行递归（属于在归时完成结果计算）
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

	cout << "杨辉三角形的(10,5)位置为：" << PascalsTriangle(3, 5) << endl;
	return 0;
}