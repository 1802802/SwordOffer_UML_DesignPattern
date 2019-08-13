#include <iostream>
#include "Vector.h"

int main_testvector()
{
	Vector<int> a(1, 0);
	a.insert(0, 2);
	a.insert(0, 6);
	a.insert(0, 21);
	a.insert(0, 2);
	a.insert(0, 256);
	a.insert(0, 224);
	a.insert(0, 22);
	a.insert(0, 7);
	a.insert(0, -1);
	a.erase(6);
	a.erase(4);
	a.print(0, a.size());
	a.sort();
	a.print(0, a.size());
	a.unsort();
	a.print(0, a.size());

	return 0;
}