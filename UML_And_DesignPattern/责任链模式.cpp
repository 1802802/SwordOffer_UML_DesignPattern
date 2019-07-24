#include <iostream>
using namespace std;

class MakeBicycle
{
public:
	virtual void makebicycle() = 0;
	void SetNextWork(MakeBicycle *nextwork)
	{
		m_nextwork = nextwork;
	}
protected:
	MakeBicycle *m_nextwork;
};

class MakeBrake : public MakeBicycle
{
public:
	void makebicycle()
	{
		cout << "Make the brake for bicycle!" << endl;
		if (m_nextwork != NULL)
			m_nextwork->makebicycle();
	}
};

class MakeWheel : public MakeBicycle
{
public:
	void makebicycle()
	{
		cout << "Make the wheel for bicycle!" << endl;
		if (m_nextwork != NULL)
			m_nextwork->makebicycle();
	}
};

class MakeCushion: public MakeBicycle
{
public:
	void makebicycle()
	{
		cout << "Make the cushion for bicycle!" << endl;
		if (m_nextwork != NULL)
			m_nextwork->makebicycle();
	}
};

int main_COR()
{
	//Chains of Responsibility
	MakeBicycle *makebrake = new MakeBrake;
	MakeBicycle *makewheel = new MakeWheel;
	MakeBicycle *makecushion = new MakeCushion;

	makewheel->SetNextWork(makebrake);
	makebrake->SetNextWork(makecushion);
	makecushion->SetNextWork(NULL);

	//根据责任链中起始位置的不同，所执行的步骤数也不同
	cout << "first make the wheel" << endl;
	makewheel->makebicycle();
	cout << "first make the brake" << endl;
	makebrake->makebicycle();
	cout << "first make the cushion" << endl;
	makecushion->makebicycle();

	delete makebrake;
	delete makewheel;
	delete makecushion;

	return 0;
}