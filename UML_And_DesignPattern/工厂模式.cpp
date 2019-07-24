#include <iostream>
using namespace std;

class color
{
public:
	virtual void mycolor() {}
};

class blue : public color
{
public:
	void mycolor() { cout << "blue" << endl; }
};

class red : public color
{
public:
	void mycolor() { cout << "red" << endl; }
};

class ABfactory
{
public:
	virtual color* create() { return NULL; }
};

class RedFactory : public ABfactory
{
public:
	color* create()
	{
		return new red;
	}
};

class BlueFactory : public ABfactory
{
public:
	color* create()
	{
		return new blue;
	}
};

int main_Factory()
{
	ABfactory *abf;

	abf = new BlueFactory;
	color* b = abf->create();
	b->mycolor();
	delete abf, b;

	abf = new RedFactory;
	color* r = abf->create();
	r->mycolor();
	delete abf, r;

	return 0;
}