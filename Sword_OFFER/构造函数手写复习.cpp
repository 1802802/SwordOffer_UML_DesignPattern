#include <iostream>
#include <mutex>
using namespace std;

class class_test1
{
public:
	class_test1();
	class_test1(const class_test1 &a);
	class_test1(class_test1 &&a)noexcept;
	class_test1& operator=(const class_test1 &a);
	class_test1& operator=(class_test1 &&a) noexcept;
private:
	int* m_val = nullptr;
};

class_test1::class_test1()
{
	m_val = new int(0);
}

class_test1::class_test1(const class_test1 & a)
{
	m_val = new int(*a.m_val);
}

class_test1::class_test1(class_test1 &&a)noexcept
{
	m_val = a.m_val;
	a.m_val = nullptr;
}

class_test1& class_test1::operator=(const class_test1& a)
{
	if (this != &a)
	{
		delete m_val;
		m_val = new int(*a.m_val);
	}
	return *this;
}

class_test1& class_test1::operator=(class_test1&& a) noexcept
{
	if (this != &a)
	{
		delete m_val;
		m_val = a.m_val;
		a.m_val = nullptr;
	}
	return *this;
}

mutex m_lock;
class singleton
{
public:
	singleton() {}
	singleton(const singleton& s) = delete;
	singleton& operator=(const singleton& s) = delete;
	static singleton* getInstance()
	{
		if (m_self == nullptr)
		{
			m_lock.lock();
			if (m_self == nullptr)
				m_self = new singleton();  //问题在于在new中的三个函数操作的执行顺序会因为CPU的乱序性而变化
			m_lock.unlock();
		}
		return m_self;
	}
	void free()
	{
		if (m_self != nullptr)
		{
			delete m_self;
			m_self = nullptr;
		}
	}
private:
	static singleton* m_self;
};
singleton* singleton::m_self = nullptr;

//局部静态变量实现线程安全单例模式，仅C++11以上能够使用（形式简便且易于书写）
class Singleton 
{
public:
	static Singleton* GetInstance() 
	{
		//局部静态成员变量特性，当其被创建一次后不会再次创建（必须C++11以上）
		static Singleton intance;
		return &intance;
	}

	~Singleton() = default;

private:
	Singleton() = default;
	//禁用拷贝
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};

int main_gouzaotest()
{
	//singleton *temp1 = singleton::getInstance();
	//singleton *temp2 = singleton::getInstance();

	Singleton *temp1 = Singleton::GetInstance();
	Singleton *temp2 = Singleton::GetInstance();

	cout << temp1 << endl;
	cout << temp2 << endl;

	return 0;
}