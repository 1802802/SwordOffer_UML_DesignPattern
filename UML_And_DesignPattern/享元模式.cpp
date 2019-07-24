#include <iostream>
#include <string>
#include <map>
using namespace std;

class Person
{
public:
	Person(string name, int age) : m_name(name), m_age(age) {}
	virtual void Display() = 0;
protected:
	string m_name;
	int m_age;
};

class Teacher : public Person
{
public:
	Teacher(string id, string name, int age) : Person(name, age), m_id(id) {}
	void Display()
	{
		cout << "Teacher's ID is " << m_id << endl
			<< "Teacher's Name is " << m_name << endl
			<< "Teacher's Age is " << m_age << endl;
		cout << endl;	//此处再分一行用于错开Debug
	}
private:
	string m_id;
};

class Student: public Person
{
public:
	Student(string id, string school, string name, int age) : Person(name, age), m_id(id), m_school(school) {}
	void Display()
	{
		cout << "Student's ID is " << m_id << endl
			<< "Student's school is " << m_school << endl
			<< "Student's Name is " << m_name << endl
			<< "Student's Age is " << m_age << endl;
		cout << endl;	//此处再分一行用于错开Debug
	}
private:
	string m_id;
	string m_school;
};

class PersonFactory
{
public:
	PersonFactory()
	{
		m_person.clear();
	}
	Person* GetTeacher(string id)    //map中如果有则直接输出，没有则输入数据读入
	{
		auto id2person = m_person.find(id);
		if (id2person == m_person.end())
		{
			cout << "There is no Teacher match this id!" << endl;
			cout << "Now you should cin the data to install this id!" << endl;
			cout << "cin the Teacher's name: "; string tempname;
			cin >> tempname;
			cout << "cin the Teacher's age: "; int tempage;
			cin >> tempage;

			Teacher* tempTeacher = new Teacher(id, tempname, tempage);
			m_person.insert({ id,tempTeacher });
			return tempTeacher;
		}
		else
		{
			cout << "The ID already have a Teacher data!" << endl;
			return id2person->second;
		}
	}
	Person* GetStudent(string id)    //map中如果有则直接输出，没有则输入数据读入
	{
		auto id2person = m_person.find(id);
		if (id2person == m_person.end())
		{
			cout << "There is no Student match this id!" << endl;
			cout << "Now you should cin the data to install this id!" << endl;
			cout << "cin the Student's school: "; string tempschool;
			cin >> tempschool;
			cout << "cin the Student's name: "; string tempname;
			cin >> tempname;
			cout << "cin the Student's age: "; int tempage;
			cin >> tempage;

			Student* tempStudent = new Student(id, tempschool, tempname, tempage);
			m_person.insert({ id,tempStudent });
			return tempStudent;
		}
		else
		{
			cout << "The ID already have a Student data!" << endl;
			return id2person->second;
		}
	}
private:
	map<string, Person*> m_person;
};

int main_FlyWeight()
{
	PersonFactory* personfactory = new PersonFactory;

	personfactory->GetTeacher("t001")->Display();
	personfactory->GetTeacher("t002")->Display();
	personfactory->GetTeacher("t001")->Display();

	personfactory->GetStudent("s001")->Display();
	personfactory->GetStudent("s003")->Display();
	personfactory->GetStudent("s001")->Display();

	return 0;
}