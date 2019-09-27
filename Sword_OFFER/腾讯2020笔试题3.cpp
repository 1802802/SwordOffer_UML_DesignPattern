#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

int main_tencent3()
{
	int n, m, x1, x2, y1, y2;
	int ui, li, xi, yi;
	while (cin >> n >> m >> x1 >> y1 >> x2 >> y2)
	{
		vector<pair<int, int>> geban(n, pair<int, int>());
		vector<int> sum(n + 1, 0);
		for (int i = 0; i < n; i++)
		{
			cin >> ui >> li;
			geban[i] = pair<int, int>({ ui,li });
		}
		geban.push_back(pair<int, int>({ x2,x2 }));

		for (int i = 0; i < m; i++)
		{
			cin >> xi >> yi;

			if (xi > x2 || yi > y1 || xi < x1 || yi < y2)
				continue;

			for (int j = 0; j < geban.size(); j++)
			{
				int ui = geban[j].first; int li = geban[j].second;
				if (xi*(y2 - y1) >= ((li - ui) *yi + ui*(y2 - y1) - (li - ui)*y1))
				{
					sum[j]++;
					break;
				}
			}
		}
		for (int j = 0; j < sum.size(); j++)
		{
			cout << j << ": " << sum[j] << endl;
		}
	}

	return 0;
}