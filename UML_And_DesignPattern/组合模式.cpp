#include <iostream>
#include <string>
#include <list>
using namespace std;

class AbFile
{
public:
	virtual void display() = 0;
	virtual int add(AbFile* abfile) = 0;
	virtual int remove(AbFile* abfile) = 0;
	virtual list<AbFile*>* getChild() = 0;
};

class File : public AbFile
{
public:
	File(string name, string type) : m_name(name), m_type(type) {}
	void display() override
	{
		cout << "File is " << m_name << m_type << endl;
	}
	int add(AbFile* abfile) override { return -1; }
	int remove(AbFile* abfile) override { return -1; }
	list<AbFile*>* getChild() override { return NULL; }
private:
	string m_name;
	string m_type;
};

class Folder : public AbFile
{
public:
	Folder(string name)
	{
		m_name = name;
		m_child = new list<AbFile*>;
		m_child->clear();
	}
	void display()
	{
		cout << "Folder name is " << m_name << endl;
	}
	int add(AbFile* abfile)
	{
		m_child->push_back(abfile);
		return 1;
	}
	int remove(AbFile* abfile)
	{
		m_child->remove(abfile);
		return 1;
	}
	list<AbFile*>* getChild()
	{
		return m_child;
	}
private:
	string m_name;
	list<AbFile*>* m_child;
};

void ShowAllFile(AbFile* abfile)
{
	if (abfile == NULL)
	{
		return;
	}
	list<AbFile*>* templist = abfile->getChild();
	if (templist != NULL)
	{
		cout << " ";
		abfile->display();
		for (auto &s : *templist)
		{
			ShowAllFile(s);
		}
	}
	else
	{
		abfile->display();
	}
}

int main_Composite()
{
	File* image1 = new File("foteball", ".jpg");
	File* image2 = new File("basketball", ".jpg");
	File* text1 = new File("Messi", ".txt");
	File* text2 = new File("James", ".txt");
	Folder* Person = new Folder("Person");
	Folder* Person1 = new Folder("Person1");
	Folder* Person2 = new Folder("Person2");

	Person->add(Person1);
	Person->add(Person2);
	Person1->add(image1);
	Person1->add(text1);
	Person2->add(image2);
	Person2->add(text2);

	cout << "*****Person's Place*****" << endl;
	ShowAllFile(Person);
	cout << "*****Person1's Place*****" << endl;
	ShowAllFile(Person1);
	cout << "*****Person2's Place*****" << endl;
	ShowAllFile(Person2);

	return 0;
}