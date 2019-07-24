#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
	virtual Person* Clone() = 0;
	virtual void Printself() = 0;
};

class cppPerson : public Person
{
public:
	cppPerson()
	{
		m_name = "Temp";
		m_age = 18;
	}
	cppPerson(string name,int age)
	{
		m_name = name;
		m_age = age;
	}
	Person* Clone()
	{
		cppPerson* temp = new cppPerson;
		*temp = *this;
		//���д���ȼ����£�Ϊ���
		//temp->m_age = this->m_age;
		//temp->m_name = this->m_name;
		//���д�����Ϊǳ������ָ��ֱ���滻
		//temp = this;
		return temp;
	}
	void Printself()
	{
		cout << "m_name:" << m_name << "  m_age:" << m_age << endl;
	}

	void setName(string name)
	{
		m_name = name;
	}
	void setAge(int age)
	{
		m_age = age;
	}
private:
	string m_name;
	int m_age;
};

int main_Prototype()
{
	Person* people = new cppPerson("mike", 21);
	people->Printself();
	Person* second_people = people->Clone();
	second_people->Printself();

	cppPerson* third_people = new cppPerson("jack", 22);
	third_people->Printself();
	Person* fouth_people = third_people->Clone();
	fouth_people->Printself();

	third_people->setAge(30);    //���������third_people��ֵ������֤�����Clone���������ǳ����
	third_people->Printself();
	fouth_people->Printself();

	return 0;
}