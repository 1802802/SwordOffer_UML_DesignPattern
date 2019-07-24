#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

int main_experiment2()
{
	STARTUPINFO si = { sizeof(si) };  //STARTUPINFO 用于指定新进程的主窗口特性的一个结构
	PROCESS_INFORMATION pi;

	char* zw = "C:\\Notepad++";
	char* sz = "C:\\new1.txt";

	//system(sz);														//可以单独打开文件
	//WinExec(sz, SW_SHOWMAXIMIZED);									//不能单独打开文件
	ShellExecute(NULL, "open", zw, sz, NULL, SW_SHOWMAXIMIZED);			//可以打开单独文件，也可以指定使用什么软件打开
	//::CreateProcess(zw, sz, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);  //不能单独打开文件

	//ifstream in("Commandlist.txt");
	//string abc;
	//while (in >> abc)
	//	cout << abc << endl;

	return 0;
}