//#define new new(__FILE__, __LINE__)    
/*�궨��,��new�滻�����Ƕ����
operator new (size_t size,char *m_file,int m_line)����
�õ���__FILE__,__LINE__������ȡ��ǰ�ļ����͵�ǰ����*/

#include <iostream>
#include <list>
#include <string>
#include "Vector.h"
#include <stdio.h>                                                                                                                                                                                                                                                            
#include <stdlib.h>
#include <time.h>    
//#define  _CRTDBG_MAP_ALLOC
//#include "crtdbg.h"
//#include <string.h>
//#ifdef _DEBUG
//#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
//#define new DEBUG_CLIENTBLOCK
//#else
//#define DEBUG_CLIENTBLOCK
//#endif

using namespace std;

class s
{
public:
	s() { cout << "main����֮ǰִ��" << endl; }
};

void test_fun1()
{
	//�����еľ�̬��Ա�����ڴ���֮�󲻻ᱻС���٣�֮��ÿ�ε��ú���������������������ִ�к���Ĳ���
	//�������ڼ�¼�ϴ����д˺����õ���ֵ�����Ǽ�¼���д���֮���
	static int temp_fun1 = 0;
	temp_fun1++;
	cout << "temp_fun1��" << temp_fun1 << endl;
}

struct testfortem
{
	int a;
};


//s sss;

//ʹ��C�Ķ��巽ʽ����ʵ��ĳЩ������main����֮ǰ��֮��ִ�е����
//__attribute((destructor))
//__attribute((constructor))

static int temp = 1;

class parafile
{
public:
	virtual void fun1() = 0;
	virtual void fun2() = 0;
};

class xmlparafile : public parafile
{
public:
	void fun1() { cout << 1 << endl; }
	void fun2() { cout << m_index << endl; }
private:
	virtual void fun3() {}
	int m_index = 1;
};

template<typename T, class A> void fun_test()
{
	T a;
	cout << sizeof(a) << endl;
}

int main_vectortest()
{
	cout << "main������ʼִ��" << endl;
	fun_test<testfortem, xmlparafile>();

	cout << __FILE__ << endl;
	cout << __LINE__ << endl;
	
	//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	Vector<int> a(1, 0);
	for (int i = 0; i < 5; i++)
	{
		test_fun1();
		a.insert(0, 2);
		a.insert(0, 6);
		a.insert(0, 21);
		a.insert(0, -64);
		a.insert(0, 67);
		a.insert(0, 156);
		a.insert(0, 256);
		a.insert(0, -11);
		a.insert(0, 22);
		a.insert(0, 7);
		a.insert(0, -1);
		a.print(0, a.size());
		a.erase(6);
		a.erase(4);
		a.print(0, a.size());
		a.sort();
		a.print(0, a.size());
		a.unsort();
		a.print(0, a.size());
		cout << endl;
	}

	cout << count1 << endl;
	void *temp = operator new(10);
	cout << temp << endl;
	Vector<int> *v = new(temp) Vector<int>();  
	cout << v << endl;
	Vector<int> *v2 = new Vector<int>();
	cout << v2 << endl;
	cout << count1 << endl;
	v->~Vector();  //��������ֻ���ٶ���������ͷ��ڴ棬����temp�����ڴ���ͷ����⻹��û�н������Ҫдһ��placememt delete��ʵ�֣�
	delete v2;

	time_t myt = time(NULL);
	cout << myt << endl;

	string s;
	s.substr(0, 3);

	int t1 = 3;
	int *t2 = &t1;
	double *t3 = (double*)t2;
	cout << t2 << endl;
	cout << *t2 << endl;
	cout << t3 << endl;
	cout << *t3 << endl;
	
	string aaa = "a";
	string bbb = "b";
	string ccc = aaa + bbb;
	cout << ccc << endl;

	char* tmp1 = new char[10];
	memset(tmp1, '0', 9);
	cout << tmp1 << endl;
	tmp1[2] = '2';
	tmp1[9] = '\0';
	cout << tmp1 << endl;

	char* s_test = "1234562ed";
	char sa_test[] = "afsdggsd";
	//sa_test = s_test;  //�����������ɳ���������ֱ�Ӹ�ֵ

	//char a1 = 'aaaa';
	//char *str = &a1;
	//strcpy(str, "a");
	//printf("%s", str);

	//char *str = "abcde";
	////str[0] = 'x';
	//printf("%s", str);

	vector<int> vec_temp1(100, 0);
	for (vector<int>::iterator beg = vec_temp1.begin(); beg < vec_temp1.end(); )
	{
		if (*beg == 0)
			beg = vec_temp1.erase(beg);
		else
			beg++;
	}
	cout << "sizeof(vec_temp1):" << sizeof(vec_temp1) << endl;
	cout << "sizeof(vector<int>):" << sizeof(vector<int>) << endl;

	parafile* tmp2 = new xmlparafile();
	tmp2->fun2();

	_CrtDumpMemoryLeaks();//ע���������İڷ�λ�ã���Ϊ���ֱ��Ӱ�쵽����жϽ��

	return 0;
}