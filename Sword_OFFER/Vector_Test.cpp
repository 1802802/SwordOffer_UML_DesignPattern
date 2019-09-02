#include <iostream>
#include <list>
#include <string>
#include "Vector.h"
#include <stdio.h>                                                                                                                                                                                                                                                            
#include <stdlib.h>
#include <time.h>    
//#define  _CRTDBG_MAP_ALLOC
//#include "crtdbg.h"
//#include <string.h>
//#ifdef _DEBUG
//#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
//#define new DEBUG_CLIENTBLOCK
//#else
//#define DEBUG_CLIENTBLOCK
//#endif

using namespace std;

class s
{
public:
	s() { cout << "main函数之前执行" << endl; }
};

//s sss;

//使用C的定义方式可以实现某些函数在main函数之前与之后执行的情况
//__attribute((destructor))
//__attribute((constructor))

static int temp = 1;

int main_d3e1()
{
	cout << "main函数开始执行" << endl;
	//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
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

	time_t myt = time(NULL);
	cout << myt << endl;

	string s;
	s.substr(0, 3);

	int t1 = 3;
	int *t2 = &t1;
	double *t3 = (double*)t2;
	cout << t2 << endl;
	cout << *t2 << endl;
	cout << t3 << endl;
	cout << *t3 << endl;
	
	string aaa = "a";
	string bbb = "b";
	string ccc = aaa + bbb;
	cout << ccc << endl;

	_CrtDumpMemoryLeaks();//注意这条语句的摆放位置，因为这会直接影响到你的判断结果

	return 0;
}