#include <iostream>
#include <mutex>
using namespace std;

class Singleton
{
public:
	void Free() {};
};

//1.��ͨ������ʽ����Singleton1�������ʼ��
class Singleton1 : public Singleton
{
public:
	static Singleton1* getInstance()
	{
		if (m_self == nullptr)
			m_self = new Singleton1();
		return m_self;
	}
	void Free()
	{
		if (m_self != nullptr)
		{
			delete m_self;
			m_self = nullptr;
		}
	}
private:
	static Singleton1* m_self;
};

Singleton1* Singleton1::m_self = nullptr;

//2.��ͨ�Ķ���ʽSingleton2�������ʼ��
class Singleton2 : public Singleton
{
public:
	static Singleton2* getInstance()
	{
		return m_self;
	}
	void Free()
	{
		if (m_self != nullptr)
		{
			delete m_self;
			m_self = nullptr;
		}
	}
private:
	static Singleton2* m_self;
};

Singleton2* Singleton2::m_self = new Singleton2();

//3.�Ľ�������ʽ����Singleton3�������ʼ����getInstance���������ж��Ƿ����
mutex g3_lock;
class Singleton3 : public Singleton
{
public:
	static void test() { cout << "test" << endl; }
	static Singleton3* getInstance()
	{
		if (m_self == nullptr)
		{
			g3_lock.lock();
			if (m_self == nullptr)
				m_self = new Singleton3();
			g3_lock.unlock();
		}
		return m_self;
	}
	void Free()
	{
		if (m_self != nullptr)
		{
			delete m_self;
			m_self = nullptr;
		}
	}
private:
	static Singleton3* m_self;
};

Singleton3* Singleton3::m_self = nullptr;

//4.�߼�������ʽ����Singleton4�������ʼ����getInstance���������ж��Ƿ��������������ʵ��������ࣩ
mutex g4_lock;
class Singleton4 : public Singleton
{
public:
	static void test() { cout << "test" << endl; }
	static Singleton4* getInstance()
	{
		return innerSingleton::getInstance();
	}

	class innerSingleton
	{
	public:
		static Singleton4* getInstance()
		{
			if (m_self == nullptr)
			{
				g4_lock.lock();
				if (m_self == nullptr)
					m_self = new Singleton4();
				g4_lock.unlock();
			}
			return m_self;
		}
		static Singleton4* m_self;
	};

	void Free()
	{
		if (innerSingleton::m_self != nullptr)
		{
			delete innerSingleton::m_self;
			innerSingleton::m_self = nullptr;
		}
	}
};

Singleton4* Singleton4::innerSingleton::m_self = nullptr;

int main_offer2()
{
	Singleton* temp1;
	Singleton* temp2;
	int num = 1;
	switch (num)
	{
	case 1:
	{
		temp1 = Singleton1::getInstance();
		temp2 = Singleton1::getInstance();
		break;
	}
	case 2:
	{
		temp1 = Singleton2::getInstance();
		temp2 = Singleton2::getInstance();
		break;
	}
	case 3:
	{
		temp1 = Singleton3::getInstance();
		temp2 = Singleton3::getInstance();
		break;
	}
	case 4:
	{
		temp1 = Singleton4::getInstance();
		temp2 = Singleton4::getInstance();
		break;
	}
	default:
	{
		temp1 = Singleton1::getInstance();
		temp2 = Singleton1::getInstance();
		break;
	}
	}

	if(temp1 == nullptr && temp2 == nullptr)
		cout << "temp1��temp2��ʱ��δ��ʼ��" << endl;
	if(temp1 != nullptr && temp2 != nullptr)
		cout << "temp1��temp2��ʱ���ѱ���ʼ��" << endl;

	if (temp1 == temp2)
		cout << "Singleton" << num << "��ͬ" << endl;
	else
		cout << "Singleton" << num << "����ͬ" << endl;

	temp1->Free();
	temp2->Free();

	return 0;
}