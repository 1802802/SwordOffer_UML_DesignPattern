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
		cout << "�Ϸ��㽶" << endl;
	}
};

class SouthApple : public AbFruit
{
	void myname()
	{
		cout << "�Ϸ�ƻ��" << endl;
	}
};

class NorthBanana : public AbFruit
{
	void myname()
	{
		cout << "�����㽶" << endl;
	}
};

class NorthApple : public AbFruit
{
	void myname()
	{
		cout << "����ƻ��" << endl;
	}
};

class SouthFactory : public AbFactory
{
public:
	AbFruit* createBanana()
	{
		cout << "�����Ϸ����㽶" << endl;
		return new SouthBanana;
	}
	AbFruit* createApple()
	{
		cout << "�����Ϸ���ƻ��" << endl;
		return new SouthApple;
	}
};

class NorthFactory : public AbFactory
{
public:
	AbFruit* createBanana()
	{
		cout << "���ɱ������㽶" << endl;
		return new NorthBanana;
	}
	AbFruit* createApple()
	{
		cout << "���ɱ�����ƻ��" << endl;
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