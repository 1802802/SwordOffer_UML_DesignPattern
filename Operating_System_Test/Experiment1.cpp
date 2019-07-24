#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

int main_experiment1()
{
	string path1 = "start C:\\Users\\FYD\\Downloads\\Ñ¸À×Ó°Òô+5.4.0.6254\\XMP\\XMP\\XMP.exe";
	string path2 = " \"D:\\Program Files\\Notepad++\\notepad++.exe\" ";
	string path3 = " \"C:\\Program Files\\UrgBenriPlus\\UrgBenriPlus.exe\" ";
	system(path1.c_str());
	system(path2.c_str());
	system(path3.c_str());
	system("start calc");
	system("pause");

	return 0;
}