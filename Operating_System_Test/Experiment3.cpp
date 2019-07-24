#include <iostream> 
#include <thread>
using namespace std;

void print1()
{
	for (int i = 0; i < 100; i++)
		cout << "print1:" << i << endl;
}

void print2()
{
	for (int i = 0; i < 100; i++)
		cout << "print2:" << i << endl;
}

int main_ex3()
{
	thread a(print1);
	thread b(print2);
	cout << "thread a pid:" << a.get_id() << endl;
	cout << "thread b pid:" << b.get_id() << endl;
	a.join();
	b.join();
	
	return 0;
}