#include <iostream>
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
		//a.insert(0, -64);
		a.insert(0, 67);
		a.insert(0, 156);
		a.insert(0, 256);
		//a.insert(0, -11);
		a.insert(0, 22);
		a.insert(0, 7);
		//a.insert(0, -1);
		a.print(0, a.size());
		//a.erase(6);
		//a.erase(4);
		a.print(0, a.size());
		a.sort();
		a.print(0, a.size());
		a.unsort();
		a.print(0, a.size());
		cout << endl;
	}

	return 0;
}