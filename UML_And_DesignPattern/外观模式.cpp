#include <iostream>
#include <string>
using namespace std;

class Share
{
public:
	void Buy()
	{
		cout << "Buy the Share" << endl;
	}
};

class Futures
{
public:
	void Buy()
	{
		cout << "Buy the Futures" << endl;
	}
};

class Bond
{
public:
	void Buy()
	{
		cout << "Buy the Bond" << endl;
	}
};

class Facade
{
public:
	Facade(string &user)
	{
		m_user = user;
		m_share = new Share;
		m_futures = new Futures;
		m_bond = new Bond;
	}
	void BuyShare()
	{
		cout << m_user << " ";
		m_share->Buy();
	}
	void BuyFutures()
	{
		cout << m_user << " ";
		m_futures->Buy();
	}
	void BuyBond()
	{
		cout << m_user << " ";
		m_bond->Buy();
	}
	~Facade()
	{
		delete m_share;
		delete m_futures;
		delete m_bond;
	}
private:
	string m_user;
	Share* m_share;
	Futures* m_futures;
	Bond *m_bond;
};

int main_Facade()
{
	string user_Mike = "Mike";
	Facade* facade = new Facade(user_Mike);
	facade->BuyBond();
	facade->BuyFutures();
	facade->BuyShare();

	return 0;
}