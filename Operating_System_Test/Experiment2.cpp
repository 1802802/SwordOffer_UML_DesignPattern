#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

int main_experiment2()
{
	STARTUPINFO si = { sizeof(si) };  //STARTUPINFO ����ָ���½��̵����������Ե�һ���ṹ
	PROCESS_INFORMATION pi;

	char* zw = "C:\\Notepad++";
	char* sz = "C:\\new1.txt";

	//system(sz);														//���Ե������ļ�
	//WinExec(sz, SW_SHOWMAXIMIZED);									//���ܵ������ļ�
	ShellExecute(NULL, "open", zw, sz, NULL, SW_SHOWMAXIMIZED);			//���Դ򿪵����ļ���Ҳ����ָ��ʹ��ʲô�����
	//::CreateProcess(zw, sz, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);  //���ܵ������ļ�

	//ifstream in("Commandlist.txt");
	//string abc;
	//while (in >> abc)
	//	cout << abc << endl;

	return 0;
}