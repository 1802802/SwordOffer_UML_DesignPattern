/*
题目：
你在玩一个回合制角色扮演的游戏。现在你在准备一个策略，以便在最短的回合内击败敌方角色。在战斗开始时，敌人拥有HP格血量。当血量小于等于0时，敌人死去。一个缺乏经验的玩家可能简单地尝试每个回合都攻击。但是你知道辅助技能的重要性。
在你的每个回合开始时你可以选择以下两个动作之一：聚力或者攻击。
聚力会提高你下个回合攻击的伤害。
攻击会对敌人造成一定量的伤害。如果你上个回合使用了聚力，那这次攻击会对敌人造成buffedAttack点伤害。否则，会造成normalAttack点伤害。
给出血量HP和不同攻击的伤害，buffedAttack和normalAttack，返回你能杀死敌人的最小回合数。

输入描述:
第一行是一个数字HP
第二行是一个数字normalAttack
第三行是一个数字buffedAttack
1 <= HP,buffedAttack,normalAttack <= 10^9

输出描述:
输出一个数字表示最小回合数
*/

#include <iostream>
using namespace std;

//思路：贪心算法，两种情况，NA>=BA/2,NA<ba/2，即选择一直使用normal或者一直使用buffed，其中使用buffed要判断下最后的值怎么选
//有个小坑就是(normalAttack * 2 >= buffedAttack)这里，最开始用的是>>1，这样会损失精度导致结果失效

int main_pinduoduo2019_4()
{
	//分两种情况：NA>=BA/2,NA<ba/2
	int hp, normalAttack, buffedAttack;
	while (cin >> hp >> normalAttack >> buffedAttack)
	{
		int round = 0;

		if (normalAttack * 2 >= buffedAttack)
		{
			if (hp % normalAttack)
				round = (hp / normalAttack) + 1;
			else
				round = (hp / normalAttack);
			cout << round << endl;
			continue;
		}

		if (normalAttack * 2 < buffedAttack)
		{
			if (hp % buffedAttack)
			{
				if (hp % buffedAttack > normalAttack)
					round = (hp / buffedAttack) * 2 + 2;
				else
					round = (hp / buffedAttack) * 2 + 1;
				cout << round << endl;
				continue;
			}
			else
			{
				round = (hp / buffedAttack) * 2;
				cout << round << endl;
				continue;
			}
		}
	}
	return 0;
}