#include <iostream>
#include <string>
#include <map>
using namespace std;

class Mediator
{
public:
	virtual void NormalWithSport(string) = 0;
	virtual void NormalWithArt(string) = 0;
	virtual void ArtWithSport(string) = 0;
};

class Student
{
public:
	Student(string name, string skill,string shortcoming) 
		: m_name(name), m_skill(skill),m_shortcoming(shortcoming) 
	{
		m_mediator = new map<string, Mediator*>;
	}
	void SetMediator(string name, Mediator* mediator) { m_mediator->insert({ name,mediator }); }
	string getName() { return m_name; }
	string getSkill() { return m_skill; }
	string getShortcoming() { return m_shortcoming; }
	virtual void UseMediator(string, int) = 0;
protected:
	string m_name;
	string m_skill;
	string m_shortcoming;
	map<string, Mediator*>* m_mediator;
};

class NormalStudent : public Student
{
public:
	NormalStudent(string name, string skill, string shortcoming) : Student(name, skill, shortcoming) {}
	void UseMediator(string mediatorname,int num)
	{
		if (num == 1)
			m_mediator->at(mediatorname)->NormalWithSport(m_name);
		if (num == 2)
			m_mediator->at(mediatorname)->NormalWithArt(m_name);
		if (num == 3)
		{
			m_mediator->at(mediatorname)->NormalWithSport(m_name);
			m_mediator->at(mediatorname)->NormalWithArt(m_name);
		}
	}
};

class SportStudent : public Student
{
public:
	SportStudent(string name, string skill, string shortcoming) : Student(name, skill, shortcoming) {}
	void UseMediator(string mediatorname, int num)
	{
		if (num == 1)
			m_mediator->at(mediatorname)->NormalWithSport(m_name);
		if (num == 2)
			m_mediator->at(mediatorname)->ArtWithSport(m_name);
		if (num == 3)
		{
			m_mediator->at(mediatorname)->NormalWithSport(m_name);
			m_mediator->at(mediatorname)->ArtWithSport(m_name);
		}
	}
};

class ArtStudent : public Student
{
public:
	ArtStudent(string name, string skill, string shortcoming) : Student(name, skill, shortcoming) {}
	void UseMediator(string mediatorname, int num)
	{
		if (num == 1)
			m_mediator->at(mediatorname)->NormalWithArt(m_name);
		if (num == 2)
			m_mediator->at(mediatorname)->ArtWithSport(m_name);
		if (num == 3)
		{
			m_mediator->at(mediatorname)->NormalWithArt(m_name);
			m_mediator->at(mediatorname)->ArtWithSport(m_name);
		}
	}
};

class Skill2Shortcoming_Mediator : public Mediator
{
public:
	Skill2Shortcoming_Mediator()
	{
		m_normalstudent = new map<string, NormalStudent*>;
		m_sportstudent = new map<string, SportStudent*>;
		m_artstudent = new map<string, ArtStudent*>;
	}
	void AddNormalStudent(NormalStudent* normalstudent)
	{
		m_normalstudent->insert({ normalstudent->getName(), normalstudent });
	}
	void AddSportStudent(SportStudent* sportstudent)
	{
		m_sportstudent->insert({ sportstudent->getName(),sportstudent });
	}
	void AddArtStudent(ArtStudent* artstudent)
	{
		m_artstudent->insert({ artstudent->getName(),artstudent });
	}
	void NormalWithSport(string name)
	{
		if (m_normalstudent->at(name) != NULL)
		{
			auto s1 = m_normalstudent->at(name);
			for (auto &s2 : *m_sportstudent)
			{
				if (s1->getSkill() == s2.second->getShortcoming())
					cout << "NormalStudent " << s1->getName() << " can be mate with SportStudent " << s2.second->getName() << " by Skill " << s2.second->getShortcoming() << endl;
				if (s1->getShortcoming() == s2.second->getSkill())
					cout << "NormalStudent " << s1->getName() << " can be mate with SportStudent " << s2.second->getName() << " by Shortcoming " << s2.second->getSkill() << endl;
			}
		}
		else if (m_sportstudent->at(name) != NULL)
		{
			auto s1 = m_sportstudent->at(name);
			for (auto &s2 : *m_normalstudent)
			{
				if (s1->getSkill() == s2.second->getShortcoming())
					cout << "SportStudent " << s1->getName() << " can be mate with SportStudent " << s2.second->getName() << " by Skill " << s2.second->getShortcoming() << endl;
				if (s1->getShortcoming() == s2.second->getSkill())
					cout << "SportStudent " << s1->getName() << " can be mate with SportStudent " << s2.second->getName() << " by Shortcoming " << s2.second->getSkill() << endl;
			}
		}
		else
		{
			cout << "the student don't belong to NormalStudent or SportStudent" << endl;
		}
	}
	void NormalWithArt(string name)
	{
		if (m_normalstudent->at(name) != NULL)
		{
			auto s1 = m_normalstudent->at(name);
			for (auto &s2 : *m_artstudent)
			{
				if (s1->getSkill() == s2.second->getShortcoming())
					cout << "NormalStudent " << s1->getName() << " can be mate with SportStudent " << s2.second->getName() << " by Skill " << s2.second->getShortcoming() << endl;
				if (s1->getShortcoming() == s2.second->getSkill())
					cout << "NormalStudent " << s1->getName() << " can be mate with SportStudent " << s2.second->getName() << " by Shortcoming " << s2.second->getSkill() << endl;
			}
		}
		else if ((*m_normalstudent)[name] != NULL)
		{
			auto s1 = (*m_normalstudent)[name];
			for (auto &s2 : *m_normalstudent)
			{
				if (s1->getSkill() == s2.second->getShortcoming())
					cout << "ArtStudent " << s1->getName() << " can be mate with ArtStudent " << s2.second->getName() << " by Skill " << s2.second->getShortcoming() << endl;
				if (s1->getShortcoming() == s2.second->getSkill())
					cout << "ArtStudent " << s1->getName() << " can be mate with ArtStudent " << s2.second->getName() << " by Shortcoming " << s2.second->getSkill() << endl;
			}
		}
		else
		{
			cout << "the student don't belong to NormalStudent or ArtStudent" << endl;
		}
	}
	void ArtWithSport(string name)
	{
		if ((*m_normalstudent)[name] != NULL)
		{
			auto s1 = (*m_normalstudent)[name];
			for (auto &s2 : *m_sportstudent)
			{
				if (s1->getSkill() == s2.second->getShortcoming())
					cout << "ArtStudent " << s1->getName() << " can be mate with SportStudent " << s2.second->getName() << " by Skill " << s2.second->getShortcoming() << endl;
				if (s1->getShortcoming() == s2.second->getSkill())
					cout << "ArtStudent " << s1->getName() << " can be mate with SportStudent " << s2.second->getName() << " by Shortcoming " << s2.second->getSkill() << endl;
			}
		}
		else if (m_sportstudent->at(name) != NULL)
		{
			auto s1 = m_sportstudent->at(name);
			for (auto &s2 : *m_artstudent)
			{
				if (s1->getSkill() == s2.second->getShortcoming())
					cout << "SportStudent " << s1->getName() << " can be mate with ArtStudent " << s2.second->getName() << " by Skill " << s2.second->getShortcoming() << endl;
				if (s1->getShortcoming() == s2.second->getSkill())
					cout << "SportStudent " << s1->getName() << " can be mate with ArtStudent " << s2.second->getName() << " by Shortcoming " << s2.second->getSkill() << endl;
			}
		}
		else
		{
			cout << "the student don't belong to SportStudent or ArtStudent" << endl;
		}
	}
private:
	map<string, NormalStudent*>* m_normalstudent;
	map<string, SportStudent*>* m_sportstudent;
	map<string, ArtStudent*>* m_artstudent;
};

class Skill2Skill_Mediator : public Mediator
{
public:
	Skill2Skill_Mediator()
	{
		m_normalstudent = new map<string, NormalStudent*>;
		m_sportstudent = new map<string, SportStudent*>;
		m_artstudent = new map<string, ArtStudent*>;
	}
	void AddNormalStudent(NormalStudent* normalstudent)
	{
		m_normalstudent->insert({ normalstudent->getName(),normalstudent });
	}
	void AddSportStudent(SportStudent* sportstudent)
	{
		m_sportstudent->insert({ sportstudent->getName(),sportstudent });
	}
	void AddArtStudent(ArtStudent* artstudent)
	{
		m_artstudent->insert({ artstudent->getName(),artstudent });
	}
	void NormalWithSport(string name)
	{
		if (m_normalstudent->find(name) != m_normalstudent->end())
		{
			auto s1 = m_normalstudent->at(name);
			for (auto &s2 : *m_sportstudent)
			{
				if (s1->getSkill() == s2.second->getSkill())
					cout << "NormalStudent " << s1->getName() << " can be mate with SportStudent " << s2.second->getName() << " by Skill " << s2.second->getSkill() << endl;
			}
		}
		else if (m_sportstudent->find(name) != m_sportstudent->end())
		{
			auto s1 = m_sportstudent->at(name);
			for (auto &s2 : *m_normalstudent)
			{
				if (s1->getSkill() == s2.second->getSkill())
					cout << "SportStudent " << s1->getName() << " can be mate with NormalStudent " << s2.second->getName() << " by Skill " << s2.second->getSkill() << endl;
			}
		}
		else
		{
			cout << "the student don't belong to SportStudent or NormalStudent" << endl;
		}
	}
	void NormalWithArt(string name)
	{
		if (m_normalstudent->find(name) != m_normalstudent->end())
		{
			auto s1 = m_normalstudent->at(name);
			for (auto &s2 : *m_artstudent)
			{
				if (s1->getSkill() == s2.second->getSkill())
					cout << "NormalStudent " << s1->getName() << " can be mate with ArtStudent " << s2.second->getName() << " by Skill " << s2.second->getSkill() << endl;
			}
		}
		else if (m_artstudent->find(name) != m_artstudent->end())
		{
			auto s1 = m_artstudent->at(name);
			for (auto &s2 : *m_normalstudent)
			{
				if (s1->getSkill() == s2.second->getSkill())
					cout << "ArtStudent " << s1->getName() << " can be mate with NormalStudent " << s2.second->getName() << " by Skill " << s2.second->getSkill() << endl;
			}
		}
		else
		{
			cout << "the student don't belong to ArtStudent or NormalStudent" << endl;
		}
	}
	void ArtWithSport(string name)
	{
		if (m_artstudent->find(name) != m_artstudent->end())
		{
			auto s1 = (*m_artstudent)[name];
			for (auto &s2 : *m_sportstudent)
			{
				if (s1->getSkill() == s2.second->getSkill())
					cout << "ArtStudent " << s1->getName() << " can be mate with SportStudent " << s2.second->getName() << " by Skill " << s2.second->getSkill() << endl;
			}
		}
		else if (m_sportstudent->find(name) != m_sportstudent->end())
		{
			auto s1 = m_sportstudent->at(name);
			for (auto &s2 : *m_artstudent)
			{
				if (s1->getSkill() == s2.second->getSkill())
					cout << "SportStudent " << s1->getName() << " can be mate with NormalStudent " << s2.second->getName() << " by Skill " << s2.second->getSkill() << endl;
			}
		}
		else
		{
			cout << "the student don't belong to ArtStudent or SportStudent" << endl;
		}
	}
private:
	map<string, NormalStudent*>* m_normalstudent;
	map<string, SportStudent*>* m_sportstudent;
	map<string, ArtStudent*>* m_artstudent;
};

class Shortcoming2Shortcoming_Mediator : public Mediator
{
public:
	Shortcoming2Shortcoming_Mediator()
	{
		m_normalstudent = new map<string, NormalStudent*>;
		m_sportstudent = new map<string, SportStudent*>;
		m_artstudent = new map<string, ArtStudent*>;
	}
	void AddNormalStudent(NormalStudent* normalstudent)
	{
		m_normalstudent->insert({ normalstudent->getName(),normalstudent });
	}
	void AddSportStudent(SportStudent* sportstudent)
	{
		m_sportstudent->insert({ sportstudent->getName(),sportstudent });
	}
	void AddArtStudent(ArtStudent* artstudent)
	{
		m_artstudent->insert({ artstudent->getName(),artstudent });
	}
	void NormalWithSport(string name)
	{
		if (m_normalstudent->find(name) != m_normalstudent->end())
		{
			auto s1 = m_normalstudent->at(name);
			for (auto &s2 : *m_sportstudent)
			{
				if (s1->getShortcoming() == s2.second->getShortcoming())
					cout << "NormalStudent " << s1->getName() << " can be mate with SportStudent " << s2.second->getName() << " by Shortcoming " << s2.second->getShortcoming() << endl;
			}
		}
		else if (m_sportstudent->find(name) != m_sportstudent->end())
		{
			auto s1 = m_sportstudent->at(name);
			for (auto &s2 : *m_normalstudent)
			{
				if (s1->getShortcoming() == s2.second->getShortcoming())
					cout << "SportStudent " << s1->getName() << " can be mate with NormalStudent " << s2.second->getName() << " by Shortcoming " << s2.second->getShortcoming() << endl;
			}
		}
		else
		{
			cout << "the student don't belong to SportStudent or NormalStudent" << endl;
		}
	}
	void NormalWithArt(string name)
	{
		if (m_normalstudent->find(name) != m_normalstudent->end())
		{
			auto s1 = m_normalstudent->at(name);
			for (auto &s2 : *m_artstudent)
			{
				if (s1->getShortcoming() == s2.second->getShortcoming())
					cout << "NormalStudent " << s1->getName() << " can be mate with ArtStudent " << s2.second->getName() << " by Shortcoming " << s2.second->getShortcoming() << endl;
			}
		}
		else if (m_artstudent->find(name) != m_artstudent->end())
		{
			auto s1 = (*m_artstudent)[name];
			for (auto &s2 : *m_normalstudent)
			{
				if (s1->getShortcoming() == s2.second->getShortcoming())
					cout << "ArtStudent " << s1->getName() << " can be mate with NormalStudent " << s2.second->getName() << " by Shortcoming " << s2.second->getShortcoming() << endl;
			}
		}
		else
		{
			cout << "the student don't belong to ArtStudent or NormalStudent" << endl;
		}
	}
	void ArtWithSport(string name)
	{
		if (m_artstudent->find(name) != m_artstudent->end())
		{
			auto s1 = (*m_artstudent)[name];
			for (auto &s2 : *m_sportstudent)
			{
				if (s1->getShortcoming() == s2.second->getShortcoming())
					cout << "ArtStudent " << s1->getName() << " can be mate with SportStudent " << s2.second->getName() << " by Shortcoming " << s2.second->getShortcoming() << endl;
			}
		}
		else if (m_sportstudent->find(name) != m_sportstudent->end())
		{
			auto s1 = m_sportstudent->at(name);
			for (auto &s2 : *m_artstudent)
			{
				if (s1->getShortcoming() == s2.second->getShortcoming())
					cout << "SportStudent " << s1->getName() << " can be mate with NormalStudent " << s2.second->getName() << " by Shortcoming " << s2.second->getShortcoming() << endl;
			}
		}
		else
		{
			cout << "the student don't belong to ArtStudent or SportStudent" << endl;
		}
	}
private:
	map<string, NormalStudent*>* m_normalstudent;
	map<string, SportStudent*>* m_sportstudent;
	map<string, ArtStudent*>* m_artstudent;
};


int main_Mediator()
{
	//1.学生的定义过程
	NormalStudent* normal_mike = new NormalStudent("mike", "math", "soccer");
	NormalStudent* normal_jack = new NormalStudent("jack", "english", "basketball");
	NormalStudent* normal_wide = new NormalStudent("wide", "run", "physical");

	SportStudent* sport_liuxiang = new SportStudent("liuxiang", "run", "math");
	SportStudent* sport_yaoming = new SportStudent("yaoming", "basketball", "english");
	SportStudent* sport_zhengzhi = new SportStudent("zhengzhi", "soccer", "paint");
	SportStudent* sport_sunyang = new SportStudent("sunyang", "swim", "sing");

	ArtStudent* art_linda = new ArtStudent("linda", "paint", "english");
	ArtStudent* art_lily = new ArtStudent("lily", "sing", "swim");
	ArtStudent* art_sam = new ArtStudent("sam", "dance", "physical");

	//2.配对班的定义过程
	Skill2Shortcoming_Mediator* skill2shortcoming_1 = new Skill2Shortcoming_Mediator;
	Skill2Skill_Mediator* skill2skill_1 = new Skill2Skill_Mediator;
	Shortcoming2Shortcoming_Mediator* shortcoming2shortcoming_1 = new Shortcoming2Shortcoming_Mediator;

	//3.配对班的信息添加过程（每个配对班根据学生档案得到所有学生信息）
	skill2shortcoming_1->AddNormalStudent(normal_mike);
	skill2shortcoming_1->AddNormalStudent(normal_jack);
	skill2shortcoming_1->AddNormalStudent(normal_wide);
	skill2shortcoming_1->AddSportStudent(sport_liuxiang);
	skill2shortcoming_1->AddSportStudent(sport_yaoming);
	skill2shortcoming_1->AddSportStudent(sport_zhengzhi);
	skill2shortcoming_1->AddSportStudent(sport_sunyang);
	skill2shortcoming_1->AddArtStudent(art_linda);
	skill2shortcoming_1->AddArtStudent(art_lily);
	skill2shortcoming_1->AddArtStudent(art_sam);

	skill2skill_1->AddNormalStudent(normal_mike);
	skill2skill_1->AddNormalStudent(normal_jack);
	skill2skill_1->AddNormalStudent(normal_wide);
	skill2skill_1->AddSportStudent(sport_liuxiang);
	skill2skill_1->AddSportStudent(sport_yaoming);
	skill2skill_1->AddSportStudent(sport_zhengzhi);
	skill2skill_1->AddSportStudent(sport_sunyang);
	skill2skill_1->AddArtStudent(art_linda);
	skill2skill_1->AddArtStudent(art_lily);
	skill2skill_1->AddArtStudent(art_sam);

	shortcoming2shortcoming_1->AddNormalStudent(normal_mike);
	shortcoming2shortcoming_1->AddNormalStudent(normal_jack);
	shortcoming2shortcoming_1->AddNormalStudent(normal_wide);
	shortcoming2shortcoming_1->AddSportStudent(sport_liuxiang);
	shortcoming2shortcoming_1->AddSportStudent(sport_yaoming);
	shortcoming2shortcoming_1->AddSportStudent(sport_zhengzhi);
	shortcoming2shortcoming_1->AddSportStudent(sport_sunyang);
	shortcoming2shortcoming_1->AddArtStudent(art_linda);
	shortcoming2shortcoming_1->AddArtStudent(art_lily);
	shortcoming2shortcoming_1->AddArtStudent(art_sam);

	//4.学生自己选择加入配对班的过程（此处只选用几位同学）
	normal_mike->SetMediator("skill2shortcoming_1", skill2shortcoming_1);
	normal_mike->SetMediator("skill2skill_1", skill2skill_1);
	normal_mike->SetMediator("shortcoming2shortcoming_1", shortcoming2shortcoming_1);

	sport_liuxiang->SetMediator("skill2shortcoming_1", skill2shortcoming_1);
	sport_liuxiang->SetMediator("skill2skill_1", skill2skill_1);
	sport_liuxiang->SetMediator("shortcoming2shortcoming_1", shortcoming2shortcoming_1);

	art_linda->SetMediator("skill2shortcoming_1", skill2shortcoming_1);
	art_linda->SetMediator("skill2skill_1", skill2skill_1);
	art_linda->SetMediator("shortcoming2shortcoming_1", shortcoming2shortcoming_1);

	//5.学生在自己加入的配对班中选择配对方式，完成上课（中介不同功能不同，但是配对的都是非自己类型的学生）
	//中介者的功能数字123，1和2指和另外两种不同的类型学生配对，3是对所有学生配对
	cout << normal_mike->getName() << "'s match process!" << endl;
	normal_mike->UseMediator("skill2shortcoming_1", 1);
	normal_mike->UseMediator("skill2shortcoming_1", 2);
	normal_mike->UseMediator("skill2shortcoming_1", 3);
	cout << sport_liuxiang->getName() << "'s match process!" << endl;
	sport_liuxiang->UseMediator("skill2skill_1", 1);
	sport_liuxiang->UseMediator("skill2skill_1", 2);
	sport_liuxiang->UseMediator("skill2skill_1", 3);
	cout << art_linda->getName() << "'s match process!" << endl;
	art_linda->UseMediator("shortcoming2shortcoming_1", 1);
	art_linda->UseMediator("shortcoming2shortcoming_1", 2);
	art_linda->UseMediator("shortcoming2shortcoming_1", 3);

	return 0;
}