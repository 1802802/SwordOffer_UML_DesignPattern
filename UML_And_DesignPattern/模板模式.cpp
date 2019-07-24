#include <iostream>
#include <string>
using namespace std;

class MakeBicycle
{
public:
	void makebicycle()   //模板模式的特点就是这个函数，定义了执行的规则与逻辑
	{
		makeWheel();
		makeBrake();
		makeCushion();
	}
protected:
	virtual void makeWheel() = 0;
	virtual void makeBrake() = 0;
	virtual void makeCushion() = 0;
};

class Make_NormalBicycle : public MakeBicycle
{
public:
	void makeWheel()
	{
		cout << "Make the normal bicycle's wheel!" << endl;
	}
	void makeBrake()
	{
		cout << "Make the normal bicycle's brake!" << endl;
	}
	void makeCushion()
	{
		cout << "Make the normal bicycle's cushion!" << endl;
	}
};

class Make_GreatBicycle : public MakeBicycle
{
public:
	void makeWheel()
	{
		cout << "Make the great bicycle's wheel!" << endl;
	}
	void makeBrake()
	{
		cout << "Make the great bicycle's brake!" << endl;
	}
	void makeCushion()
	{
		cout << "Make the great bicycle's cushion!" << endl;
	}
};

int main_Template()
{
	MakeBicycle* normalbicycle = new Make_NormalBicycle;
	normalbicycle->makebicycle();
	MakeBicycle* greatbicycle = new Make_GreatBicycle;
	greatbicycle->makebicycle();

	delete greatbicycle;
	delete normalbicycle;

	return 0;
}