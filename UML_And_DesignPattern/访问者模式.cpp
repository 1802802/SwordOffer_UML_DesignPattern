#include <iostream>
#include <map>
#include <string>
using namespace std;

class Visitor;
class Hall;
class Kitchen;
class Office;

class RestaurantPart
{
public:
	RestaurantPart(string name) : m_name(name) {}
	string getName() { return m_name; }
	virtual void Accept(Visitor *) = 0;
protected:
	string m_name;
};

class Visitor
{
public:
	Visitor(string name) : m_name(name) {}
	virtual void VisitHall(Hall* systempart) = 0;
	virtual void VisitKitchen(Kitchen* systempart) = 0;
	virtual void VisitOffice(Office* systempart) = 0;
	string getName() { return m_name; }
protected:
	string m_name;
};

class Hall : public RestaurantPart
{
public:
	Hall(string name) : RestaurantPart(name){}
	void Accept(Visitor *visitor)
	{
		cout << "visitor " << visitor->getName() << " trying to visit the Hall named " << m_name << endl;
		visitor->VisitHall(this);
	}
};

class Kitchen : public RestaurantPart
{
public:
	Kitchen(string name) : RestaurantPart(name) {}
	void Accept(Visitor *visitor)
	{
		cout << "visitor " << visitor->getName() << " trying to visit the Kitchen named " << m_name << endl;
		visitor->VisitKitchen(this);
	}
};

class Office : public RestaurantPart
{
public:
	Office(string name) : RestaurantPart(name) {}
	void Accept(Visitor *visitor)
	{
		cout << "visitor " << visitor->getName() << " trying to visit the Office named " << m_name << endl;
		visitor->VisitOffice(this);
	}
};

class Guest : public Visitor
{
public:
	Guest(string name) : Visitor(name) {}
	void VisitHall(Hall* systempart) override
	{
		cout << "Welcome to visit the Hall named " << systempart->getName() << endl;
	}
	void VisitKitchen(Kitchen* systempart) override
	{
		cout << "Sorry! " << m_name << " can't enter the Kitchen named " << systempart->getName() << endl;
	}
	void VisitOffice(Office* systempart) override
	{
		cout << "Sorry! " << m_name << " can't enter the Office named " << systempart->getName() << endl;
	}
};

class Cook : public Visitor
{
public:
	Cook(string name) : Visitor(name) {}
	void VisitHall(Hall* systempart) override
	{
		cout << "Welcome to visit the Hall named " << systempart->getName() << endl;
	}
	void VisitKitchen(Kitchen* systempart) override
	{
		cout << "Welcome to visit the Kitchen named " << systempart->getName() << endl;
	}
	void VisitOffice(Office* systempart) override
	{
		cout << "Sorry! " << m_name << " can't enter the Office named " << systempart->getName() << endl;
	}
};

class Manager : public Visitor
{
public:
	Manager(string name) : Visitor(name) {}
	void VisitHall(Hall* systempart) override
	{
		cout << "Welcome to visit the Hall named " << systempart->getName() << endl;
	}
	void VisitKitchen(Kitchen* systempart) override
	{
		cout << "Welcome to visit the Kitchen named " << systempart->getName() << endl;
	}
	void VisitOffice(Office* systempart) override
	{
		cout << "Welcome to visit the Office named " << systempart->getName() << endl;
	}
};

class Restaurant
{
public:
	Restaurant() { m_restaurantpart_list.clear(); }
	void insert(RestaurantPart* restaurantpart)
	{
		m_restaurantpart_list.insert({ restaurantpart->getName(),restaurantpart });
	}
	void remove(RestaurantPart* restaurantpart)
	{
		m_restaurantpart_list.erase(restaurantpart->getName());
	}
	RestaurantPart* use(string name)
	{
		return m_restaurantpart_list.at(name);
	}
	void AcceptAll(Visitor* vistor)
	{
		for (auto &s : m_restaurantpart_list)
			s.second->Accept(vistor);
	}
private:
	map<string, RestaurantPart*> m_restaurantpart_list;
};

int main_Visitor()
{
	//1.Visitor，饭店部门，饭店的定义与赋值
	Visitor* GuestMike = new Guest("GuestMike");
	Visitor* CookJack = new Cook("CookJack");
	Visitor* ManagerLinda = new Manager("ManagerLinda");

	RestaurantPart* FirstHall = new Hall("FirstHall");
	RestaurantPart* SecondHall = new Hall("SecondHall");
	RestaurantPart* FirstKitchen = new Kitchen("FirstKitchen");
	RestaurantPart* SecondKitchen = new Kitchen("SecondKitchen");
	RestaurantPart* BossOffice = new Office("BossOffice");

	Restaurant* CrisCloseDoor = new Restaurant;
	CrisCloseDoor->insert(FirstHall);
	CrisCloseDoor->insert(SecondHall);
	CrisCloseDoor->insert(FirstKitchen);
	CrisCloseDoor->insert(SecondKitchen);
	CrisCloseDoor->insert(BossOffice);

	//2.测试
	cout << "***** GuestMike 全部访问 *****" << endl;
	CrisCloseDoor->AcceptAll(GuestMike);
	cout << "***** CookJack 全部访问 *****" << endl;
	CrisCloseDoor->AcceptAll(CookJack);
	cout << "***** ManagerLinda 全部访问 *****" << endl;
	CrisCloseDoor->AcceptAll(ManagerLinda);

	delete GuestMike;
	delete CookJack;
	delete ManagerLinda;
	delete FirstHall;
	delete SecondHall;
	delete FirstKitchen;
	delete SecondKitchen;
	delete BossOffice;

	return 0;
}