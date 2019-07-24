#include <iostream>
using namespace std;

class Singleton     //����ģʽ����ʽ�����䱻��ȡ����ʱ��GetInstanceʱ�����Ż�Ե�������NEW����
{
public:
	Singleton() { cout << "�������캯��ִ��" << endl; }
	static Singleton* GetInstance()
	{
		if (m_sig == nullptr)
		{
			m_sig = new Singleton();
			cout << "��������ʵ��" << endl;
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
		cout << "��������ִ��" << endl;
	}
private:
	static Singleton* m_sig;
};

Singleton* Singleton::m_sig = nullptr;    //���ⶨ���ʼֵ

class Singleton_Ehan     //����ģʽ����ʽ�����ڲ���̬�����ڴ���ʱ��NEW��������Ҫ�ڱ���ȡʱ����
{
public:
	Singleton_Ehan() { cout << "�������캯��ִ��" << endl; }
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
		cout << "��������ִ��" << endl; 
	}
private:
	static Singleton_Ehan* m_esig;
};

Singleton_Ehan* Singleton_Ehan::m_esig = new Singleton_Ehan();    //����ֱ�Ӹ�ֵ

int main_singleton()
{
	Singleton* temp1 = Singleton::GetInstance();
	Singleton* temp2 = Singleton::GetInstance();

	Singleton_Ehan* temp3 = Singleton_Ehan::GetInstance();
	Singleton_Ehan* temp4 = Singleton_Ehan::GetInstance();

	if (temp1 == temp2)
		cout << "������ͬ" << endl;
	else
		cout << "��������ͬ" << endl;

	if (temp3 == temp4)
		cout << "������ͬ" << endl;
	else
		cout << "��������ͬ" << endl;

	temp1->Free();
	temp2->Free();
	temp3->Free();
	temp4->Free();

	return 0;
}