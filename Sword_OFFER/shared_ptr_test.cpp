#include <iostream>
#include "shared_ptr.h"

using namespace std;
class MyClass
{
public:
	~MyClass()
	{
		cout << "释放MyClass(" << _id << ")\n";
	}

	MyClass(int i) :_id(i)
	{

	}

	void Print() const
	{
		cout << "MyClass(" << _id << ")" << endl;
	}
private:
	int _id;
};

int main_sharedptr_test()
{
	MyClass* px = new MyClass(1);

	weak_ptr<MyClass> ap(px);
	weak_ptr<MyClass> bp = ap;
	weak_ptr<MyClass> cp;

	cout << "ap的引用计数(2): "
		<< ap.getCount() << endl;
	cout << "ap的弱计数(2): "
		<< ap.getWeakCount() << endl;

	cout << "将ap赋值给cp\n";
	cp = ap;

	cout << "ap的引用计数(3): "
		<< ap.getCount() << endl;
	cout << "ap的弱计数(3): "
		<< ap.getWeakCount() << endl;


	MyClass* qx = new MyClass(5);

	weak_ptr<MyClass> dp(qx);
	ap = dp;

	//if (ap.expired())
	//	ap = ap.lock();
	//if (bp.expired())
	//	bp = ap.lock();
	//if (cp.expired())
	//	cp = ap.lock();
	//if (dp.expired())
	//	dp = ap.lock();

	cout << "ap的引用计数(2): "
		<< ap.getCount() << endl;
	cout << "ap的弱计数(2): "
		<< ap.getWeakCount() << endl;

	cout << "dp的引用计数(2): "
		<< dp.getCount() << endl;

	//"像指针一样使用智能指针"
	//dp->Print();
	//(*cp).Print();

	//注意这里的栈的析构，栈中的顺序为dp(指向qx)，cp(指向px)，bp(指向px)，ap(指向qx)，根据智能指针的析构特性，先析构了px，再析构了qx

	return 0;
}