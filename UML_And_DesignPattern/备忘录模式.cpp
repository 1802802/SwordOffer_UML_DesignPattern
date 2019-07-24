#include <iostream>
#include <string>
#include <map>
#include <windows.h>
using namespace std;

string GetSystemTime()   //获取当前系统时间
{
	SYSTEMTIME m_time;
	GetLocalTime(&m_time);
	char szDateTime[100] = { 0 };
	sprintf_s(szDateTime, "%02d-%02d-%02d %02d:%02d:%02d", m_time.wYear, m_time.wMonth,
		m_time.wDay, m_time.wHour, m_time.wMinute, m_time.wSecond);
	string time(szDateTime);
	return time;
}

class SaveFile
{
public:
	SaveFile(int level, string mission, map<string, int> package, string savefilname)
	{
		sf_level = level;
		sf_mission = mission;
		sf_package = package;
		sf_savefilname = savefilname;
	}
	void ChangeSaveFile(int level, string mission, map<string, int> package)
	{
		sf_level = level;
		sf_mission = mission;
		sf_package = package;
	}
	string getName() 
	{
		return sf_savefilname;
	}
	map<string, int> getpackage()
	{
		return sf_package;
	}
	string getmission()
	{
		return sf_mission;
	}
	int getlevel()
	{
		return sf_level;
	}
private:
	int sf_level;
	string sf_mission;
	map<string, int> sf_package;
	string sf_savefilname;
};

class RPGgame
{
public:
	RPGgame(int level, string mission, map<string, int> package)
	{ 
		m_level = level;
		m_mission = mission;
		m_package = package;
	}
	SaveFile* CreateSaveFile()
	{
		return new SaveFile(m_level, m_mission, m_package, GetSystemTime());
	}
	void ChangeGame(int level, string mission, map<string, int> package)
	{
		m_level = level;
		m_mission = mission;
		m_package = package;
	}
	void LoadSaveFile(SaveFile* savefile)
	{
		m_level = savefile->getlevel();
		m_mission = savefile->getmission();
		m_package = savefile->getpackage();
	}
	void DisplaySaveFile()
	{
		cout << "m_level is " << m_level << endl;
		cout << "m_mission is " << m_mission << endl;
		for (auto &s : m_package)
			cout << s.first << " have " << s.second << endl;
	}
private:
	int m_level;
	string m_mission;
	map<string, int> m_package;
};

class RPGgameSystem
{
public:
	void InsertSaveFile(SaveFile* savefile)
	{
		m_savefile.insert({ savefile->getName(),savefile });
	}
	SaveFile* useSaveFile(string name)
	{
		return m_savefile.at(name);
	}
	void RemoveaveFile(string name)
	{
		m_savefile.erase(name);
	}
private:
	map<string, SaveFile*> m_savefile;
};

int main_Memento()
{
	RPGgameSystem* TheWitcher3_System = new RPGgameSystem;

	//用户数据的自定义
	map<string, int> Geralt_Package;
	Geralt_Package.insert({ "Memory Rose",1 });
	Geralt_Package.insert({ "Crystal Skulls",1 }); 

	//进入游戏读取默认存档
	RPGgame* TheWitcher3 = new RPGgame(10, "Kill Monster", Geralt_Package);

	//第一次存档
	cout << "***** TheWitcher3第一次存档 *****" << endl;
	SaveFile* savefile1 = TheWitcher3->CreateSaveFile();
	TheWitcher3_System->InsertSaveFile(savefile1);
	TheWitcher3->DisplaySaveFile();

	//第二次存档
	Sleep(1000);
	cout << "***** TheWitcher3第二次存档 *****" << endl;
	TheWitcher3->ChangeGame(12, "Find Child", Geralt_Package);
	SaveFile* savefile2 = TheWitcher3->CreateSaveFile();
	TheWitcher3_System->InsertSaveFile(savefile2);
	TheWitcher3->DisplaySaveFile();

	//第一次读档
	cout << "***** TheWitcher3第一次读档 *****" << endl;
	TheWitcher3->LoadSaveFile(TheWitcher3_System->useSaveFile(savefile1->getName()));
	TheWitcher3->DisplaySaveFile();

	//第二次读档
	cout << "***** TheWitcher3第二次读档 *****" << endl;
	TheWitcher3->LoadSaveFile(TheWitcher3_System->useSaveFile(savefile2->getName()));
	TheWitcher3->DisplaySaveFile();

	delete TheWitcher3_System;
	delete TheWitcher3;
	delete savefile1;
	delete savefile2;

	return 0;
}