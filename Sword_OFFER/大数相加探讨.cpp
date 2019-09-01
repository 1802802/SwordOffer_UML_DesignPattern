#include <iostream>
#include <string>
#include <vector>
using namespace std;

//虚函数重写（覆盖）的实质就是复刻一张父类虚函数表，并根据内部实现修改表中对应虚函数的地址；；
//当父类指针指向子类对象时，可以调用父类的所有东西，因为这些都被继承了；但是对于父类中的虚函数，其仍会调用子类的重载函数，因为此时被继承的虚函数指针指向的虚函数表已经被换成了子类的虚函数表
//当子类指针指向父类对象时，可以调用子类继承父类的东西，但是不能调用子类自身的东西（因为没有，所以通常不允许这种情况发生），对于虚函数同上，此时指向的内存中的虚函数表仍为父类的虚函数表

//dynamic_cast用于实现在上下行转换时，尤其是上行向下行转换时（基类转子类）的检测，这种转换往往是不允许被实现的，对指针，返回NULL，对引用，抛出bad_cast异常
//同时，该转换符在进行转换时（子类转父类）必须要求父类有虚函数，在转换后，那个虚函数仍然为子类的虚函数（由于该内存中的虚函数指针已经被子类改写），但是普通继承的其他函数回归到父类的函数
//具体原因为子类是继承了父类的这些东西的，在将那个指针变为父类的指针后，这些普通函数和变量就指向了父类的那些东西，就这样

namespace zileiyufulei
{
	static class A
	{
	public:
		virtual void print() { cout << "AAAA" << endl; }
		void printA(){ cout << "A" << endl; }
		int m_A = 1;
	};
	static class B : public A
	{
	public:
		void print() { cout << "BBBB" << endl; }
		void printA() { cout << "B" << endl; }
		int m_A = 2;
	};

	template<typename T> T factory(string &input)
	{
		if (input == "A")
			return new A;
		else if (input == "B")
			return new B;
		return nullptr;
	}
}

using namespace zileiyufulei;

int main_dashuxiangjia()
{
	string a = "12123235647568";
	string b = "23412523342353";
	int asize = a.size();
	int bsize = b.size();
	int maxsize = (asize > bsize) ? asize : bsize;
	vector<int> c(maxsize + 1, 0);
	for (int i = 0; i < maxsize; i++)
	{
		int anum = (i < asize) ? (a[i] - '0') : (0);
		int bnum = (i < bsize) ? (b[i] - '0') : (0);
		c[i + 1] = anum + bnum;
	}
	for (int i = maxsize; i > 0; i--)
	{
		if (c[i] >= 10)
		{
			c[i] -= 10;
			c[i - 1]++;
		}
	}
	long long result = 0;
	for (int i = 0; i < maxsize + 1; i++)
	{
		result = ((result * 10) + c[i]);
	}
	cout << result << endl;

	B* bp;
	A* ap;
	B bb;
	A aa;
	ap = &aa;
	bp = &bb;

	ap->print();
	//B* bp_t = dynamic_cast<B*>(ap);
	B* bp_t = (B*)(ap);
	cout << bp_t << endl;
	bp_t->print();
	bp_t->printA();

	bp->print();
	bp->printA();
	//A* ap_t = dynamic_cast<A*>(bp);
	A* ap_t = (A*)(bp);
	ap_t->print();
	ap_t->printA();
	cout << ap_t->m_A << endl;
	

	//string s = "A";
	//auto t1 = factory<A*>(s);
	//t1->print();

	return 0;
}