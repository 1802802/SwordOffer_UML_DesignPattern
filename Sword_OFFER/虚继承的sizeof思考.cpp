#include <iostream>
using namespace std;

/*
��ͨ�̳����麯���̳У�
��1����ͨ�̳У�class A ��public B��A���ڴ�ὫB�е��������ݷŵ�ǰ�棬
�Լ��ı����ڴ�ŵ����棨�Է����ڴ������򣩣������ڴ�ʱ�����ڴ����ķ�ʽȥ���㣻
��2���麯���̳У�class A ��virtual public B��B����������ڴ�洢���ڴ�ĺ󲿣������������ָ�룩��
��A�Լ������ݴ����ǰ�棨������ǰ����ڴ�Ϊ�´������麯��ָ�룬ָ��ǰ����麯������
ǰ��������̳���������A�Լ����ڴ��Լ��ڴ���룬�������̳е��ڴ��Լ��ڴ���루�мǣ�������ֱ�����Ϊ����
*/

//�麯���̳�ʱ��class B : public virtual A��B��sizeofΪ����B�������ݳ�Ա���ڴ�����С + ������ָ���С����Ϊ4�� + A��sizeof��С��
class A
{
	//char a[3];
	
public:
	virtual void aa() {};
};

class B :public virtual A
{
	int aa;
	char b[3];
public:
	//virtual void bb() {};
};

class C :public virtual A
{
	//char c[3];
public:
	virtual void cc() { A::aa(); };
};
//8 20 32

//��̳еļ̳е��ǿ�������ڴ棬���Ƿ���������Ӷ����Ƕ��루Ҳ����˵��������ָ���С4�ֽ�+��̳е���Ĵ�С��������ָ�붼�Ƿ�����ǰ���
class D : public A  //������ﲻ����̳У��Ǿ��ǳ�����·���������̳У���ô�����һ��ָ������麯��ָ��
{
	//�����̳ж���virtualʱD�Ż�����Լ����麯��ָ��
	char c[3];
public:
	void dd() {};
};

//class A
//{
//	char a[3];
//public:
//	virtual void aa() {};
//};
//
//class B :public A
//{
//	char b[3];
//public:
//	virtual void bb() {};
//};
//
//class C :public A
//{
//	char c[3];
//public:
//	virtual void cc() {};
//};
//
//class D : public B, public C
//{
//	char c[3];
//public:
//	void dd() {};
//};
//8 12 16

int main_virtualpublic()
//int main_virtualsizeof()
{
	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
	cout << sizeof(C) << endl;
	cout << sizeof(D) << endl;
	//D d;

	//if (dynamic_cast<D*>(&d) == NULL)
	//	cout << "NULL" << endl;


	return 0;
}