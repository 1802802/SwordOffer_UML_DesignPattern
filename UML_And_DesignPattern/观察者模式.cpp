#include <iostream>
#include <string>
#include <list>
using namespace std;

class Observer
{
public:
	virtual void Update() = 0;
};

class World
{
public:
	World() { m_observerlist.clear(); }
	virtual void Attach(Observer *observer) = 0;
	virtual void Delete(Observer *observer) = 0;
	virtual void Notify() = 0;
protected:
	list<Observer*> m_observerlist;
};

class WorldLine : public World
{
public:
	void Attach(Observer *observer) override { m_observerlist.push_back(observer); }
	void Delete(Observer *observer) override { m_observerlist.remove(observer); }
	void Notify() override
	{
		for (auto &s : m_observerlist)
			s->Update();
	}
	WorldLine(string currentworldline) : m_worldline(currentworldline)
	{
		cout << "CurrentWorldLine is " << currentworldline << endl;
	}
	string getWorldLine() { return m_worldline; }
	void setWorldLine(string worldline) { m_worldline = worldline; }
private:
	string m_worldline;
};

class WorldLine_Observer : public Observer
{
public:
	WorldLine_Observer(string name, WorldLine* world) : m_name(name), m_world(world) {};
	void Update()
	{
		cout << m_name << " feel that! The WorldLine now change to " << m_world->getWorldLine() << endl;
	}
private:
	string m_name;
	WorldLine* m_world;
};

int main_Observer()
{
	WorldLine* alpha_worldline = new WorldLine("1.02412");
	WorldLine* beta_worldline = new WorldLine("2.45672");

	WorldLine_Observer* Makise_Kurisu = new WorldLine_Observer("Makise_Kurisu", alpha_worldline);
	WorldLine_Observer* Okabe_Rintaro = new WorldLine_Observer("Okabe_Rintaro", beta_worldline);

	alpha_worldline->Attach(Makise_Kurisu);
	beta_worldline->Attach(Okabe_Rintaro);

	alpha_worldline->setWorldLine("1.45321");
	alpha_worldline->Notify();
	beta_worldline->setWorldLine("2.86712");
	beta_worldline->Notify();

	delete alpha_worldline;
	delete beta_worldline;
	delete Makise_Kurisu;
	delete Okabe_Rintaro;

	return 0;
}