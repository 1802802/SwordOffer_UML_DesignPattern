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

class green : public color
{
public:
	void mycolor() { cout << "green" << endl; }
};

class factory
{
public:
	color* create(string c)
	{
		if (c == "blue")
			return new blue;
		else if (c == "red")
			return new red;
		else if (c == "green")
			return new green;
		else
			cout << "error input" << endl;
	}
};

int main_simplyFactory()
{
	factory *f = new factory;

	color* r = f->create("red");
	r->mycolor();

	color* b = f->create("blue");
	b->mycolor();

	color* g = f->create("green");
	g->mycolor();

	delete r, b, g;
	delete f;
	return 0;
}