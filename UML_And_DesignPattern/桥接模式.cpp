#include <iostream>
#include <string>
using namespace std;

class Wheel
{
public:
	virtual void setsize() = 0;
	int getsize() { return m_size; }
protected:
	int m_size;
};

class Wheel_40 : public Wheel
{
public:
	void setsize() override
	{
		m_size = 40;
		cout << "The bicycle's Wheel size is " << m_size << endl;
	}
};

class Wheel_50 : public Wheel
{
public:
	void setsize() override
	{
		m_size = 50;
		cout << "The bicycle's Wheel size is " << m_size << endl;
	}
};

class Brake
{
public:
	virtual void settype() = 0;
	string gettype() { return m_type; }
protected:
	string m_type;
};

class D_Brake : public Brake
{
	void settype() override
	{
		m_type = "Disc Brake";
		cout<< "The bicycle's Brake type is " << m_type << endl;
	}
};

class V_Brake : public Brake
{
	void settype() override
	{
		m_type = "V Brake";
		cout << "The bicycle's Brake type is " << m_type << endl;
	}
};

class Bicycle
{
public:
	Bicycle(Wheel* wheel, Brake* brake) : m_wheel(wheel), m_brake(brake) {}
	virtual void installBicycle() = 0;
protected:
	Wheel* m_wheel;
	Brake* m_brake;
};

class BSJ_Bicycle : public Bicycle
{
public:
	BSJ_Bicycle(Wheel* wheel, Brake* brake) : Bicycle(wheel, brake) {}
	void installBicycle() override
	{
		m_wheel->setsize();
		m_brake->settype();
		cout << "BSJ Bicycle" << endl;
	}
};

class STN_Bicycle : public Bicycle
{
public:
	STN_Bicycle(Wheel* wheel, Brake* brake) : Bicycle(wheel, brake) {}
	void installBicycle() override
	{
		m_wheel->setsize();
		m_brake->settype();
		cout << "STN Bicycle" << endl;
	}
};

int main_Bridge()
{
	Wheel_40* w40 = new Wheel_40;
	Wheel_50* w50 = new Wheel_50;
	D_Brake* dbrake = new D_Brake;
	V_Brake* vbrake = new V_Brake;

	Bicycle* Abike = new BSJ_Bicycle(w40, dbrake);
	Abike->installBicycle();
	Bicycle* Bbike = new STN_Bicycle(w50, vbrake);
	Bbike->installBicycle();

	return 0;
}