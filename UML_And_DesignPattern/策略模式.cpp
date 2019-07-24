#include <iostream>
using namespace std;

namespace Strategy
{
	class AGV_Location
	{
	public:
		virtual void CalculatePosition() = 0;
	};

	class Map_Location : public AGV_Location
	{
	public:
		void CalculatePosition()
		{
			cout << "Using the map to get the position of AGV!" << endl;
		}
	};

	class Lidar_Location : public AGV_Location
	{
	public:
		void CalculatePosition()
		{
			cout << "Using the lidar to get the position of AGV!" << endl;
		}
	};

	class AGV_Move
	{
	public:
		virtual void MoveMethod() = 0;
	};

	class TranslationMove : public AGV_Move
	{
	public:
		void MoveMethod()
		{
			cout << "Using the TranslationMove to move the AGV!" << endl;
		}
	};

	class VehicleMove : public AGV_Move
	{
	public:
		void MoveMethod()
		{
			cout << "Using the VehicleMove to move the AGV!" << endl;
		}
	};

	class AGV_System
	{
	public:
		AGV_System(AGV_Location *agvloaction, AGV_Move *agvmove)
		{
			m_agvloaction = agvloaction;
			m_agvmove = agvmove;
		}
		void SetMethod(AGV_Location *agvloaction, AGV_Move *agvmove)
		{
			m_agvloaction = agvloaction;
			m_agvmove = agvmove;
		}
		void DoAction()
		{
			m_agvloaction->CalculatePosition();
			m_agvmove->MoveMethod();
		}
	private:
		AGV_Location *m_agvloaction;
		AGV_Move *m_agvmove;
	};
}

using namespace Strategy;

int main_Strategy()
{
	//这里的都是预定义的策略Strategy，严格上不属于Client的调用范围
	AGV_Location* maplocation = new Map_Location;
	AGV_Location* lidarlocation = new Lidar_Location;
	AGV_Move* translationmove = new TranslationMove;
	AGV_Move* vehiclemove = new VehicleMove;

	//先在构造函数中定义策略，然后重新定义新的策略
	AGV_System *agvsystem = new AGV_System(maplocation, translationmove);
	agvsystem->DoAction();
	agvsystem->SetMethod(lidarlocation, vehiclemove);
	agvsystem->DoAction();

	delete maplocation;
	delete lidarlocation;
	delete translationmove;
	delete vehiclemove;
	delete agvsystem;

	return 0;
}