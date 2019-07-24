#include <iostream>
using namespace std;

class Worker;

class State
{
public:
	virtual void work(Worker *worker) = 0;
};

class ForenoonState : public State
{
	void work(Worker* worker) override;
};

class Worker
{
public:
	Worker() { m_state = new ForenoonState; m_taskfinished = false; }
	double getHour() { return m_hour; }
	void setHour(double hour) { m_hour = hour; }
	void getState() { return m_state->work(this); }
	void setState(State *state) { m_state = state; }
	bool m_taskfinished;
private:
	double m_hour;
	State *m_state;
};

class RestState : public State
{
public:
	void work(Worker* worker) override
	{
		cout << worker->getHour() << "点，我已经完成任务下班啦！" << endl;
	}
};

class NightState : public State
{
public:
	void work(Worker* worker) override
	{
		if (worker->m_taskfinished)
		{
			worker->setState(new RestState);
			worker->getState();
		}
		else
		{
			if (worker->getHour() <= 21 && worker->getHour() > 17.5)
			{
				cout << worker->getHour() << "点，正在晚上加班！" << endl;
			}
			else
			{
				cout << worker->getHour() << "点，任务虽然没完成，但是我还是下班了！" << endl;
			}
		}
	}
};

class AfternoonState : public State
{
public:
	void work(Worker* worker) override
	{
		if (worker->getHour() <= 17.5 && worker->getHour() > 14)
		{
			cout << worker->getHour() << "点，进行下午的工作" << endl;
		}
		else
		{
			worker->setState(new NightState);
			worker->getState();
		}
	}
};

class NoonState : public State
{
public:
	void work(Worker* worker) override
	{
		if (worker->getHour() <= 13.5 && worker->getHour() > 12)
		{
			cout << worker->getHour() << "点，正在午休，请勿打扰！" << endl;
		}
		else
		{
			worker->setState(new AfternoonState);
			worker->getState();
		}
	}
};

void ForenoonState::work(Worker* worker)
{
	if (worker->getHour() <= 9 && worker->getHour() >= 8)
	{
		cout << worker->getHour() << "点，刚进入工作，整理昨天的材料，准备今天的任务" << endl;
	}
	else
	{
		if (worker->getHour() <= 12 && worker->getHour() > 9)
		{
			cout << worker->getHour() << "点，进行上午的工作" << endl;
		}
		else
		{
			worker->setState(new NoonState);
			worker->getState();
		}
	}
}

int main_State()
{
	Worker* mike = new Worker;
	mike->setHour(8.2);
	mike->getState();
	mike->setHour(11.2);
	mike->getState();
	mike->setHour(13.2);
	mike->getState();
	mike->setHour(16.2);
	mike->getState();
	//mike->m_taskfinished = true;
	mike->setHour(19.2);
	mike->getState();
	mike->m_taskfinished = true;
	mike->setHour(22.2);
	mike->getState();
	//mike->m_taskfinished = true;

	delete mike;

	return 0;
}