#include <iostream>
#include <string>
using namespace std;

namespace jianzaozhemoshi
{
	class House		//产品类，根据实际情况对其进行更改
	{
	public:
		void setDoor(string door)
		{
			m_door = door;
		}
		void setWindow(string window)
		{
			m_window = window;
		}
		void setWall(string wall)
		{
			m_wall = wall;
		}
		string getDoor()
		{
			return m_door;
		}
		string getWindow()
		{
			return m_window;
		}
		string getWall()
		{
			return m_wall;
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
		virtual House* getHouse() = 0;
	};

	class normalBuild : public Build
	{
	public:
		normalBuild()
		{
			house = new House;
		}
		void makeDoor()
		{
			house->setDoor("normaldoor");
			cout << "make normal door!" << endl;
		}
		void makeWindow()
		{
			house->setWindow("normalwindow");
			cout << "make normal window!" << endl;
		}
		void makeWall()
		{
			house->setWall("normalwall");
			cout << "make normal wall!" << endl;
		}
		House* getHouse()
		{
			return house;
		}
	private:
		House *house;
	};

	class GreatBuild : public Build
	{
	public:
		GreatBuild()
		{
			house = new House;
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
		House* getHouse()
		{
			return house;
		}
	private:
		House *house;
	};

	class Director  //指挥者，直接调用抽象基类来执行，根据其特性会自动匹配
	{
	public:
		Director(Build* build)
		{
			m_build = build;
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
}

using namespace jianzaozhemoshi;

int main_Builder()
{
	Director *director = nullptr;

	Build *first_build = new normalBuild;
	director = new Director(first_build);
	director->construct();
	House *first_house = new House;
	first_house = first_build->getHouse();
	cout << first_house->getDoor() << endl << first_house->getWindow() << endl << first_house->getWall() << endl;
	delete first_build;
	delete first_house;

	Build *second_build = new GreatBuild;
	director = new Director(second_build);
	director->construct();
	House *second_house = new House;
	second_house = second_build->getHouse();
	cout << second_house->getDoor() << endl << second_house->getWindow() << endl << second_house->getWall() << endl;
	delete second_build;
	delete second_house;

	return 0;
}