#include <iostream>
#include <string>
using namespace std;

class File
{
public:
	File(string name) : m_name(name) {}
	void setname(string name)
	{
		m_name = name;
	}
	string getname()
	{
		return m_name;
	}
private:
	string m_name;
};

class Add
{
public:
	virtual void add(File* file) = 0;
};

class AddPrefix_mike : public Add
{
public:
	void add(File* file) override
	{
		string addprefix = "[Mike]" + file->getname();
		file->setname(addprefix);
	}
};

class AddSuffix_jpg : public Add
{
public:
	void add(File* file) override
	{
		string addsuffix = file->getname() + ".jpg";
		file->setname(addsuffix);
	}
};

int main_Interpreter()
{
	File* picture1 = new File("Messi");
	File* picture2 = new File("James");

	Add* addprefix1 = new AddPrefix_mike;
	Add* addsuffix1 = new AddSuffix_jpg;

	cout << "picture1's name is " << picture1->getname() << endl;
	cout << "picture2's name is " << picture2->getname() << endl;
	addprefix1->add(picture1);
	addprefix1->add(picture2);
	cout << "picture1's name is " << picture1->getname() << endl;
	cout << "picture2's name is " << picture2->getname() << endl;
	addsuffix1->add(picture1);
	addsuffix1->add(picture2);
	cout << "picture1's name is " << picture1->getname() << endl;
	cout << "picture2's name is " << picture2->getname() << endl;

	delete picture1;
	delete picture2;
	delete addprefix1;
	delete addsuffix1;

	return 0;
}