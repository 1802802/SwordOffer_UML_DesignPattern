#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main_experiment4()  //��ϰ3.14 ����
{
	string word;
	vector<string>text;
	while (cin >> word)
		text.push_back(word);
	for (auto a : text)
		cout << a << " ";
	cout << endl;
	return 0;
}