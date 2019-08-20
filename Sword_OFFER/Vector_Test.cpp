#include <iostream>
#include <list>
#include "Vector.h"
using namespace std;

int main()
{
	Vector<int> a(1, 0);
	for (int i = 0; i < 5; i++)
	{
		a.insert(0, 2);
		a.insert(0, 6);
		a.insert(0, 21);
		a.insert(0, -64);
		a.insert(0, 67);
		a.insert(0, 156);
		a.insert(0, 256);
		a.insert(0, -11);
		a.insert(0, 22);
		a.insert(0, 7);
		a.insert(0, -1);
		a.print(0, a.size());
		a.erase(6);
		a.erase(4);
		a.print(0, a.size());
		a.sort();
		a.print(0, a.size());
		a.unsort();
		a.print(0, a.size());
		cout << endl;
	}

	cout << count1 << endl;
	void *temp = operator new(10);
	cout << temp << endl;
	Vector<int> *v = new(temp) Vector<int>();  
	cout << v << endl;
	Vector<int> *v2 = new Vector<int>();
	cout << v2 << endl;
	cout << count1 << endl;
	v->~Vector();  //这样将会只销毁对象而不会释放内存，但是temp自身内存的释放问题还是没有解决（需要写一个placememt delete来实现）
	delete v2;

	return 0;
}