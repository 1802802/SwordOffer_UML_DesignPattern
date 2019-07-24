#include <iostream>
#include <string>
#include <list>
using namespace std;

class Staff
{
public:
	Staff(string name) : m_name(name) {}
	void Make_Word()
	{
		cout << "Boss command staff " << m_name << " to make a word!" << endl;
	}
	void Make_Excel()
	{
		cout << "Boss command staff " << m_name << " to make a excel!" << endl;
	}
	void Make_Powerpoint()
	{
		cout << "Boss command staff " << m_name << " to make a ppt!" << endl;
	}
private:
	string m_name;
};

class Command
{
public:
	virtual void Make_Office() = 0;
};

class Word_Command : public Command
{
public:
	Word_Command(Staff* staff) : m_staff(staff) {}
	void Make_Office()
	{
		m_staff->Make_Word();
	}
private:
	Staff* m_staff;
};

class Excel_Command : public Command
{
public:
	Excel_Command(Staff* staff) : m_staff(staff) {}
	void Make_Office()
	{
		m_staff->Make_Excel();
	}
private:
	Staff* m_staff;
};

class Powerpoint_Command : public Command
{
public:
	Powerpoint_Command(Staff* staff) : m_staff(staff) {}
	void Make_Office()
	{
		m_staff->Make_Powerpoint();
	}
private:
	Staff* m_staff;
};

class Boss
{
public:
	Boss()
	{
		m_commandlist.clear();
	}
	void AddCommand(Command* command)
	{
		m_commandlist.push_back(command);
	}
	void RemoveCommand(Command* command)
	{
		m_commandlist.remove(command);
	}
	void SubmitCommand()
	{
		for (auto &s : m_commandlist)
		{
			s->Make_Office();
		}
		m_commandlist.clear();
	}
private:
	list<Command*> m_commandlist;
};

int main_Command()
{
	Staff* mike = new Staff("mike");
	Staff* lily = new Staff("lily");
	Word_Command* word1 = new Word_Command(mike);
	Excel_Command* excel1 = new Excel_Command(mike);
	Powerpoint_Command* ppt1 = new Powerpoint_Command(lily);

	Boss* jack = new Boss;
	jack->AddCommand(word1);
	jack->AddCommand(excel1);
	jack->AddCommand(ppt1);
	jack->SubmitCommand();

	jack->AddCommand(word1);
	jack->AddCommand(excel1);
	jack->AddCommand(ppt1);
	jack->RemoveCommand(excel1);
	jack->SubmitCommand();

	delete mike;
	delete lily;
	delete word1;
	delete excel1;
	delete ppt1;
	delete jack;

	return 0;
}