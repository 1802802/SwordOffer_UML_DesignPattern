#include <iostream>
#include <vector>
using namespace std;


void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
{
	nums1.reserve(m + n);
	nums1.resize(m + n, 0);
	for (int i = (m--) + (n--) - 1; i >= 0; i--)
	{
		int maxNum = 0x80000000;
		if (m >= 0 && n < 0)
			maxNum = nums1[m--];
		else if (m < 0 && n >= 0)
			maxNum = nums2[n--];
		else if (m >= 0 && n >= 0 && nums1[m] >= nums2[n])
			maxNum = nums1[m--];
		else
			maxNum = nums2[n--];
		nums1[i] = maxNum;
	}
}

int main_leecode_unknown2()
{
	vector<int> nums1({ 1,2,3,4,7,9 });
	int m = nums1.size();
	vector<int> nums2({ 2,5,6 });
	int n = nums2.size();
	merge(nums1, m, nums2, n);

	return 0;
}