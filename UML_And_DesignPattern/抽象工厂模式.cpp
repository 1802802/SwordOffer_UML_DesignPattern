#include <iostream>
using namespace std;

class AbFruit
{
public:
	virtual void myname() {}
};

class AbFactory
{
public:
	virtual AbFruit* createBanana() = 0;
	virtual AbFruit* createApple() = 0;
};

class SouthBanana : public AbFruit
{
	void myname()
	{
		cout << "南方香蕉" << endl;
	}
};

class SouthApple : public AbFruit
{
	void myname()
	{
		cout << "南方苹果" << endl;
	}
};

class NorthBanana : public AbFruit
{
	void myname()
	{
		cout << "北方香蕉" << endl;
	}
};

class NorthApple : public AbFruit
{
	void myname()
	{
		cout << "北方苹果" << endl;
	}
};

class SouthFactory : public AbFactory
{
public:
	AbFruit* createBanana()
	{
		cout << "生成南方的香蕉" << endl;
		return new SouthBanana;
	}
	AbFruit* createApple()
	{
		cout << "生成南方的苹果" << endl;
		return new SouthApple;
	}
};

class NorthFactory : public AbFactory
{
public:
	AbFruit* createBanana()
	{
		cout << "生成北方的香蕉" << endl;
		return new NorthBanana;
	}
	AbFruit* createApple()
	{
		cout << "生成北方的苹果" << endl;
		return new NorthApple;
	}
};


int main_AbFactory()
{
	AbFruit* fruit;
	AbFactory* southfa = new SouthFactory;
	AbFactory* northfa = new NorthFactory;
	fruit = southfa->createApple();
	fruit->myname();
	delete fruit;

	fruit = southfa->createBanana();
	fruit->myname();
	delete fruit;

	fruit = northfa->createBanana();
	fruit->myname();
	delete fruit;

	fruit = northfa->createApple();
	fruit->myname();
	delete fruit;

	return 0;
}