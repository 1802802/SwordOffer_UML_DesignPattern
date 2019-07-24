#include <iostream>
#include <string>
using namespace std;

class AbHouse
{
public:
	virtual void setDoor(string) = 0;
	virtual void setWindow(string) = 0;
	virtual void setWall(string) = 0;
	virtual void getAll() = 0;
};

class AHouse :public AbHouse
{
public:
	AHouse()
	{
		m_door = "";
		m_wall = "";
		m_window = "";
	}
	void setDoor(string door)
	{
		m_door = " A House " + door;
	}
	void setWindow(string window)
	{
		m_window = " A House " + window;
	}
	void setWall(string wall)
	{
		m_wall = " A House " + wall;
	}
	void getAll()
	{
		cout << "m_door: " << m_door << endl
			<< "m_window: " << m_window << endl
			<< "m_wall: " << m_wall << endl;
	}
private:
	string m_door;
	string m_window;
	string m_wall;
};

class BHouse :public AbHouse
{
public:
	BHouse()
	{
		m_door = "";
		m_wall = "";
		m_window = "";
	}
	void setDoor(string door)
	{
		m_door = " B House " + door;
	}
	void setWindow(string window)
	{
		m_window = " B House " + window;
	}
	void setWall(string wall)
	{
		m_wall = " B House " + wall;
	}
	void getAll()
	{
		cout << "m_door: " << m_door << endl
			<< "m_window: " << m_window << endl
			<< "m_wall: " << m_wall << endl;
	}
private:
	string m_door;
	string m_window;
	string m_wall;
};

class Build    //build的抽象基类
{
public:
	virtual void makeDoor() = 0;
	virtual void makeWindow() = 0;
	virtual void makeWall() = 0;
	virtual AbHouse* getHouse() = 0;
};

class normalBuild : public Build
{
public:
	normalBuild(AbHouse* abhouse)
	{
		m_house = abhouse;   //浅拷贝，当前normalbuild的house直接指向了传入的形参所指的house
	}
	void makeDoor()
	{
		m_house->setDoor("normaldoor");
		cout << "make normal door!" << endl;
	}
	void makeWindow()
	{
		m_house->setWindow("normalwindow");
		cout << "make normal window!" << endl;
	}
	void makeWall()
	{
		m_house->setWall("normalwall");
		cout << "make normal wall!" << endl;
	}
	AbHouse* getHouse()
	{
		return m_house;
	}
private:
	AbHouse* m_house;
};

class GreatBuild : public Build
{
public:
	GreatBuild(AbHouse* abhouse)
	{
		house = abhouse;
	}
	void makeDoor()
	{
		house->setDoor("Greatdoor");
		cout << "make Great door!" << endl;
	}
	void makeWindow()
	{
		house->setWindow("Greatwindow");
		cout << "make Great window!" << endl;
	}
	void makeWall()
	{
		house->setWall("Greatwall");
		cout << "make Great wall!" << endl;
	}
	AbHouse* getHouse()
	{
		return house;
	}
private:
	AbHouse *house;
};

class Director  //指挥者，直接调用抽象基类来执行，根据其特性会自动匹配
{
public:
	Director(Build* build)
	{
		m_build = build;     //谨记，这里的指挥者是直接调用的输入形参所指的对象，为浅拷贝，并非深拷贝
	}
	void construct()
	{
		m_build->makeWall();
		m_build->makeDoor();
		m_build->makeWindow();
	}
private:
	Build *m_build;
};

int main_AbBuilder()
{
	Director *director = nullptr;
	Build *first_build = nullptr;
	Build *second_build = nullptr;
	AHouse *first_house = nullptr;
	BHouse *second_house = nullptr;

	first_house = new AHouse;
	first_build = new normalBuild(first_house);
	director = new Director(first_build);
	director->construct();
	first_house->getAll();
	delete first_build;
	delete first_house;

	second_house = new BHouse;
	second_build = new GreatBuild(second_house);
	director = new Director(second_build);
	director->construct();
	second_house->getAll();
	delete second_build;
	delete second_house;

	return 0;
}