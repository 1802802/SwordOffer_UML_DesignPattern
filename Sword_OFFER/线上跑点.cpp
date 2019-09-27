//����ֲ������С��С��λ��p��i��С���ٶ�v��i�ݣ��ٶȷ���Ҳ֪�� - �ű�ʾ��������ײ֮�����ʧ����������ײʱ�䡣

#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<double> calculateTime(vector<double> &p, vector<double> &v)
{
	vector<double> isGone(p.size(), false);
	vector<double> totalTime;

	while (true)
	{
		map<double, vector<double>> crash;
		for (double i = 0; i < p.size(); i++)
		{
			if (isGone[i] == true)
				continue;
			for (double j = i + 1; j < p.size(); j++)
			{
				if (isGone[j] == true)
					continue;
				if (v[i] - v[j] == 0)
					continue;
				double time = abs((p[i] - p[j]) / (v[i] - v[j]));
				crash.insert({ time,vector<double>({ i,j }) });
			}
		}
		if (crash.empty())
			return totalTime;
		else
		{
			double time = (*crash.begin()).first;
			totalTime.push_back(time);
			int a = (*crash.begin()).second[0];
			int b = (*crash.begin()).second[1];
			isGone[a] = true;
			isGone[b] = true;
		}
	}
}

vector<double> calculateTime2(vector<double> &p, vector<double> &v)
{
	vector<double> isGone(p.size(), false);
	vector<double> totalTime;

	while (true)
	{
		//1.ѭ����ʼ�������洢��ǰ��ѭ����map�����ڴ洢ÿ�飨���㣩������ʱ�䣬�Լ�����������
		map<double, vector<double>> crash;
		for (double i = 0; i < p.size(); i++)
		{
			//2.���������Ѿ������Ϊɾ����������
			if (isGone[i] == true)
				continue;
			for (double j = i + 1; j < p.size(); j++)
			{
				//3.���������Ѿ������Ϊɾ����������
				if (isGone[j] == true)
					continue;
				//4.��������ٶȴ�С�뷽����ȫ��ͬ����ʾ������������������
				if (v[i] - v[j] == 0)
					continue;
				//5.�������������Լ�������ʱ�䣬����㣬������ɺ���������Ϊһ��ֻ���������
				double time = abs((p[i] - p[j]) / (v[i] - v[j]));
				crash.insert({ time,vector<double>({ i,j }) });
				break;
			}
		}
		//6.�鿴ÿ�˼����е��������
		for (auto &s : crash)
			cout << s.first << " " << s.second[0] << " " << s.second[1] << endl;
		//7.����ǰ�������޷��ټ����������ʱ������
		if (crash.empty())
			return totalTime;
		else
		{
			//8.��������ɾ��ʱ����С�ĵ㣬Ȼ�����½���ѭ������
			double time = (*crash.begin()).first;
			totalTime.push_back(time);
			int a = (*crash.begin()).second[0];
			int b = (*crash.begin()).second[1];
			cout << a << " " << b << endl;
			isGone[a] = true;
			isGone[b] = true;
		}
	}
}

int main_xianshangpaodian()
{
	vector<double> p({ 1.2,23.9,2.023,13.212,6.13,-100.12,122 });
	vector<double> v({ 2.56,30.345,-10.234,23.121,100.111,-50.08,-1000.8 });
	vector<double> temp = calculateTime2(p, v);
	return 0;
}