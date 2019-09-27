//上面分布着许多小球。小球位置p［i］小球速度v［i］，速度方向也知道 - 号表示，两球碰撞之后会消失，求所有碰撞时间。

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
		//1.循环开始，建立存储当前趟循环的map，用于存储每组（两点）的相遇时间，以及是哪两个点
		map<double, vector<double>> crash;
		for (double i = 0; i < p.size(); i++)
		{
			//2.如果当其点已经被标记为删除，则跳过
			if (isGone[i] == true)
				continue;
			for (double j = i + 1; j < p.size(); j++)
			{
				//3.如果当其点已经被标记为删除，则跳过
				if (isGone[j] == true)
					continue;
				//4.如果两点速度大小与方向完全相同，表示两者永不相遇，跳过
				if (v[i] - v[j] == 0)
					continue;
				//5.如果有两个点可以计算相遇时间，则计算，计算完成后跳出，因为一次只算两个点的
				double time = abs((p[i] - p[j]) / (v[i] - v[j]));
				crash.insert({ time,vector<double>({ i,j }) });
				break;
			}
		}
		//6.查看每趟计算中的相遇情况
		for (auto &s : crash)
			cout << s.first << " " << s.second[0] << " " << s.second[1] << endl;
		//7.当当前数据中无法再计算出相遇点时，返回
		if (crash.empty())
			return totalTime;
		else
		{
			//8.否则，懒惰删除时间最小的点，然后重新进入循环计算
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