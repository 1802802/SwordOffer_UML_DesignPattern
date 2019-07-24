#include <iostream>
#include <string>
using namespace std;

class AGV_Car
{
public: 
	virtual void Component() = 0;
};

class Normal_AGV_Car : public AGV_Car
{
public:
	void Component() override
	{
		cout << "I can achieve AGV_Car normal work!" << endl;
	}
};

class Location_Component4AGV_Car : public AGV_Car
{
public:
	Location_Component4AGV_Car(AGV_Car* agvcar)
	{
		m_agvcar = agvcar;
	}
	virtual void Location_Component() = 0;
	virtual void Component() = 0;
protected:
	AGV_Car* m_agvcar;
};

class Move_Component4AGV_Car : public AGV_Car
{
public:
	Move_Component4AGV_Car(AGV_Car* agvcar)
	{
		m_agvcar = agvcar;
	}
	virtual void Move_Component() = 0;
	virtual void Component() = 0;
protected:
	AGV_Car* m_agvcar;
};

class Map_Location : public Location_Component4AGV_Car
{
public:
	Map_Location(AGV_Car* agvcar) : Location_Component4AGV_Car(agvcar) {}
	void Location_Component() override
	{
		cout << "New Location_Component: I can use the Map Location!" << endl;
	}
	void Component() override
	{
		m_agvcar->Component();
		Location_Component();
	}
};

class QR_Location : public Location_Component4AGV_Car
{
public:
	QR_Location(AGV_Car* agvcar) : Location_Component4AGV_Car(agvcar) {}
	void Location_Component() override
	{
		cout << "New Location_Component: I can use the QR Location!" << endl;
	}
	void Component() override
	{
		m_agvcar->Component();
		Location_Component();
	}
};

class Auto_Move : public Move_Component4AGV_Car
{
public:
	Auto_Move(AGV_Car* agvcar) : Move_Component4AGV_Car(agvcar) {}
	void Move_Component() override
	{
		cout << "New Move_Component: I can use the Auto Move!" << endl;
	}
	void Component() override
	{
		m_agvcar->Component();
		Move_Component();
	}
};

class Hand_Move : public Move_Component4AGV_Car
{
public:
	Hand_Move(AGV_Car* agvcar) : Move_Component4AGV_Car(agvcar) {}
	void Move_Component() override
	{
		cout << "New Move_Component: I can use the Hand Move!" << endl;
	}
	void Component() override
	{
		m_agvcar->Component();
		Move_Component();
	}
};

int main_Decorator()
{
	Normal_AGV_Car* agvcar = new Normal_AGV_Car;
	agvcar->Component();

	Map_Location* maploc_agvcar = new Map_Location(agvcar);        //值得一提的是，这里的Map和QR都使用的是同一个agvcar，根据其构造函数为浅拷贝，可知这里的两个函数使用的是同一个内存的变量
	maploc_agvcar->Component();

	QR_Location* qr_agvcar = new QR_Location(agvcar);
	qr_agvcar->Component();

	Auto_Move* automove_agvcar = new Auto_Move(maploc_agvcar);
	automove_agvcar->Component();

	Hand_Move* handmove_agvcar = new Hand_Move(qr_agvcar);
	handmove_agvcar->Component();

	return 0;
}