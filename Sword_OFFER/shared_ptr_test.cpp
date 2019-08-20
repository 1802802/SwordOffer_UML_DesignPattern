#include <iostream>
#include "shared_ptr.h"

using namespace std;
class MyClass
{
public:
	~MyClass()
	{
		cout << "�ͷ�MyClass(" << _id << ")\n";
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

	cout << "ap�����ü���(2): "
		<< ap.getCount() << endl;
	cout << "ap��������(2): "
		<< ap.getWeakCount() << endl;

	cout << "��ap��ֵ��cp\n";
	cp = ap;

	cout << "ap�����ü���(3): "
		<< ap.getCount() << endl;
	cout << "ap��������(3): "
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

	cout << "ap�����ü���(2): "
		<< ap.getCount() << endl;
	cout << "ap��������(2): "
		<< ap.getWeakCount() << endl;

	cout << "dp�����ü���(2): "
		<< dp.getCount() << endl;

	//"��ָ��һ��ʹ������ָ��"
	//dp->Print();
	//(*cp).Print();

	//ע�������ջ��������ջ�е�˳��Ϊdp(ָ��qx)��cp(ָ��px)��bp(ָ��px)��ap(ָ��qx)����������ָ����������ԣ���������px����������qx

	return 0;
}