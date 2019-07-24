#include <iostream>
using namespace std;

class Computer18V
{
public:
	virtual void use18V() = 0;
};

class Source220V
{
public:
	void use_tansform18V()
	{
		cout << "transform the source to 18V" << endl;
	}
	void use220V()
	{
		cout << "use the 220V source" << endl;
	}
};

class Adapter : public Computer18V
{
public:
	Adapter(Source220V* source)
	{
		m_voltage = source;
	}
	void use18V()
	{
		m_voltage->use_tansform18V();
	}
private:
	Source220V* m_voltage;
};

int main_Adapter()
{
	Source220V* source220v = new Source220V;
	//这里注意new的类型和变量类型不同
	Computer18V* sourcr18V = new Adapter(source220v);
	sourcr18V->use18V();

	delete source220v;
	delete sourcr18V;

	return  0;
}