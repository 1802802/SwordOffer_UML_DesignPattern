/*
��Ŀ��
������һ���غ��ƽ�ɫ���ݵ���Ϸ����������׼��һ�����ԣ��Ա�����̵Ļغ��ڻ��ܵз���ɫ����ս����ʼʱ������ӵ��HP��Ѫ������Ѫ��С�ڵ���0ʱ��������ȥ��һ��ȱ���������ҿ��ܼ򵥵س���ÿ���غ϶�������������֪���������ܵ���Ҫ�ԡ�
�����ÿ���غϿ�ʼʱ�����ѡ��������������֮һ���������߹�����
������������¸��غϹ������˺���
������Ե������һ�������˺���������ϸ��غ�ʹ���˾���������ι�����Ե������buffedAttack���˺������򣬻����normalAttack���˺���
����Ѫ��HP�Ͳ�ͬ�������˺���buffedAttack��normalAttack����������ɱ�����˵���С�غ�����

��������:
��һ����һ������HP
�ڶ�����һ������normalAttack
��������һ������buffedAttack
1 <= HP,buffedAttack,normalAttack <= 10^9

�������:
���һ�����ֱ�ʾ��С�غ���
*/

#include <iostream>
using namespace std;

//˼·��̰���㷨�����������NA>=BA/2,NA<ba/2����ѡ��һֱʹ��normal����һֱʹ��buffed������ʹ��buffedҪ�ж�������ֵ��ôѡ
//�и�С�Ӿ���(normalAttack * 2 >= buffedAttack)����ʼ�õ���>>1����������ʧ���ȵ��½��ʧЧ

int main_pinduoduo2019_4()
{
	//�����������NA>=BA/2,NA<ba/2
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