#include <iostream>
#include <string>
using namespace std;

class Subject
{
public:
	virtual void KillMonster() = 0;
};

class NormalPlayer : public Subject
{
public:
	void KillMonster()
	{
		cout << "NormalPlayer Kill the Monster By 10 Damage" << endl;
	}
};

class ProxyPlayer : public Subject
{
public:
	ProxyPlayer(Subject* player)
	{
		m_normalplayer = player;
	}
	void ReduceMonsterArmor()
	{
		cout << "ProxyPlayer Reduce the Monster's Armor" << endl;
	}
	void KillMonster1sec()
	{
		cout << "ProxyPlayer Kill the Monster in 1 sec" << endl;
	}
	void KillMonster()
	{
		m_normalplayer = new NormalPlayer;

		ReduceMonsterArmor();
		m_normalplayer->KillMonster();   //����ģʽ�������ñ��������ʵ�ֻ������ܣ�������ʵ��ǰ����Ӷ��ֹ���
		KillMonster1sec();
	}
private:
	Subject* m_normalplayer;
};

int main_Proxy()
{
	Subject* player = new NormalPlayer;
	player->KillMonster();
	Subject* proxyplayer = new ProxyPlayer(player);
	proxyplayer->KillMonster();

	delete player;
	delete proxyplayer;

	return 0;
}