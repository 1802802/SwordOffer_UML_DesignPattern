#include <iostream>
#include <string>
#include <vector>
using namespace std;

class A
{
public:
	void print() { cout << "A" << endl; }
};
class B : public A
{
public:
	void print() { cout << "B" << endl; }
};

template<typename T> T factory(string &input)
{
	if (input == "A")
		return new A;
	else if (input == "B")
		return new B;
	return nullptr;
}

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
	ap = &bb;
	
	ap->print();

	string s = "A";
	auto t1 = factory<A*>(s);
	t1->print();

	return 0;
}