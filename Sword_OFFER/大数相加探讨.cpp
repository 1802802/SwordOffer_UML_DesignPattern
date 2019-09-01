#include <iostream>
#include <string>
#include <vector>
using namespace std;

//�麯����д�����ǣ���ʵ�ʾ��Ǹ���һ�Ÿ����麯�����������ڲ�ʵ���޸ı��ж�Ӧ�麯���ĵ�ַ����
//������ָ��ָ���������ʱ�����Ե��ø�������ж�������Ϊ��Щ�����̳��ˣ����Ƕ��ڸ����е��麯�������Ի������������غ�������Ϊ��ʱ���̳е��麯��ָ��ָ����麯�����Ѿ���������������麯����
//������ָ��ָ�������ʱ�����Ե�������̳и���Ķ��������ǲ��ܵ�����������Ķ�������Ϊû�У�����ͨ����������������������������麯��ͬ�ϣ���ʱָ����ڴ��е��麯������Ϊ������麯����

//dynamic_cast����ʵ����������ת��ʱ������������������ת��ʱ������ת���ࣩ�ļ�⣬����ת�������ǲ�����ʵ�ֵģ���ָ�룬����NULL�������ã��׳�bad_cast�쳣
//ͬʱ����ת�����ڽ���ת��ʱ������ת���ࣩ����Ҫ�������麯������ת�����Ǹ��麯����ȻΪ������麯�������ڸ��ڴ��е��麯��ָ���Ѿ��������д����������ͨ�̳е����������ع鵽����ĺ���
//����ԭ��Ϊ�����Ǽ̳��˸������Щ�����ģ��ڽ��Ǹ�ָ���Ϊ�����ָ�����Щ��ͨ�����ͱ�����ָ���˸������Щ������������

namespace zileiyufulei
{
	static class A
	{
	public:
		virtual void print() { cout << "AAAA" << endl; }
		void printA(){ cout << "A" << endl; }
		int m_A = 1;
	};
	static class B : public A
	{
	public:
		void print() { cout << "BBBB" << endl; }
		void printA() { cout << "B" << endl; }
		int m_A = 2;
	};

	template<typename T> T factory(string &input)
	{
		if (input == "A")
			return new A;
		else if (input == "B")
			return new B;
		return nullptr;
	}
}

using namespace zileiyufulei;

int main_dashuxiangjia()
{
	string a = "12123235647568";
	string b = "23412523342353";
	int asize = a.size();
	int bsize = b.size();
	int maxsize = (asize > bsize) ? asize : bsize;
	vector<int> c(maxsize + 1, 0);
	for (int i = 0; i < maxsize; i++)
	{
		int anum = (i < asize) ? (a[i] - '0') : (0);
		int bnum = (i < bsize) ? (b[i] - '0') : (0);
		c[i + 1] = anum + bnum;
	}
	for (int i = maxsize; i > 0; i--)
	{
		if (c[i] >= 10)
		{
			c[i] -= 10;
			c[i - 1]++;
		}
	}
	long long result = 0;
	for (int i = 0; i < maxsize + 1; i++)
	{
		result = ((result * 10) + c[i]);
	}
	cout << result << endl;

	B* bp;
	A* ap;
	B bb;
	A aa;
	ap = &aa;
	bp = &bb;

	ap->print();
	//B* bp_t = dynamic_cast<B*>(ap);
	B* bp_t = (B*)(ap);
	cout << bp_t << endl;
	bp_t->print();
	bp_t->printA();

	bp->print();
	bp->printA();
	//A* ap_t = dynamic_cast<A*>(bp);
	A* ap_t = (A*)(bp);
	ap_t->print();
	ap_t->printA();
	cout << ap_t->m_A << endl;
	

	//string s = "A";
	//auto t1 = factory<A*>(s);
	//t1->print();

	return 0;
}