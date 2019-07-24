#include <iostream>
using namespace std;

class Singleton     //单例模式懒汉式，当其被获取单例时（GetInstance时），才会对单例进行NEW操作
{
public:
	Singleton() { cout << "懒汉构造函数执行" << endl; }
	static Singleton* GetInstance()
	{
		if (m_sig == nullptr)
		{
			m_sig = new Singleton();
			cout << "懒汉单例实现" << endl;
		}
		return m_sig;
	}
	void Free()
	{
		if (m_sig != nullptr)
		{
			delete m_sig;
			m_sig = nullptr;
		}
		cout << "懒汉析构执行" << endl;
	}
private:
	static Singleton* m_sig;
};

Singleton* Singleton::m_sig = nullptr;    //类外定义初始值

class Singleton_Ehan     //单例模式饿汉式，其内部静态变量在创建时即NEW出，不需要在被获取时创建
{
public:
	Singleton_Ehan() { cout << "饿汉构造函数执行" << endl; }
	static Singleton_Ehan* GetInstance()
	{
		return m_esig;
	}
	void Free()
	{ 
		if (m_esig != nullptr)
		{
			delete m_esig;
			m_esig = nullptr;
		}
		cout << "饿汉析构执行" << endl; 
	}
private:
	static Singleton_Ehan* m_esig;
};

Singleton_Ehan* Singleton_Ehan::m_esig = new Singleton_Ehan();    //类外直接赋值

int main_singleton()
{
	Singleton* temp1 = Singleton::GetInstance();
	Singleton* temp2 = Singleton::GetInstance();

	Singleton_Ehan* temp3 = Singleton_Ehan::GetInstance();
	Singleton_Ehan* temp4 = Singleton_Ehan::GetInstance();

	if (temp1 == temp2)
		cout << "懒汉相同" << endl;
	else
		cout << "懒汉不相同" << endl;

	if (temp3 == temp4)
		cout << "饿汉相同" << endl;
	else
		cout << "饿汉不相同" << endl;

	temp1->Free();
	temp2->Free();
	temp3->Free();
	temp4->Free();

	return 0;
}