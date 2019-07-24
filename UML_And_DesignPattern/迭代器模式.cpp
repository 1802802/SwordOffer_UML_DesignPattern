#include <iostream>
#include <string>
using namespace std;

#define object string
#define QueueSize 10

class Aggregate;

class Iterator
{
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual object CurrentItem() = 0;
};

class Aggregate
{
public:
	virtual Iterator* CreateIterator() = 0;
	virtual int getSize() = 0;
	virtual object &getCurrentItem(int index) = 0;
};

class TickerCheck : public Iterator
{
public:
	TickerCheck(Aggregate *ag) : aggregate(ag) { m_index = 0; }
	void First()
	{
		m_index = 0;
	}
	void Next()
	{
		++m_index;
	}
	bool IsDone()
	{
		return (m_index == aggregate->getSize());
	}
	object CurrentItem()
	{
		object currentman = aggregate->getCurrentItem(m_index);
		cout << "当前位置为:" << m_index << "号，";
		if (currentman.size())
			cout << "现在是" << aggregate->getCurrentItem(m_index) << "需要买票" << endl;
		else
			cout << "此号为空" << endl;
		return aggregate->getCurrentItem(m_index);
	}
private:
	int m_index;
	Aggregate *aggregate;
};

class TicketQueue : public Aggregate
{
public:
	Iterator* CreateIterator()
	{
		return new TickerCheck(this);
	}
	int getSize()
	{
		return QueueSize;
	}
	object& getCurrentItem(int index)
	{
		return m_length[index];
	}
private:
	object m_length[QueueSize];
};

int main_Iterator()
{
	Aggregate* ticketqueue = new TicketQueue;
	ticketqueue->getCurrentItem(0) = "mike";
	ticketqueue->getCurrentItem(1) = "jack";
	ticketqueue->getCurrentItem(2) = "linda";
	ticketqueue->getCurrentItem(3) = "lily";

	Iterator* tickercheck = ticketqueue->CreateIterator();

	for (tickercheck->First(); !(tickercheck->IsDone()); tickercheck->Next())
		tickercheck->CurrentItem();

	delete ticketqueue;
	delete tickercheck;

	return 0;
}