#include <iostream>
using namespace std;

//1.基本的节点类
template<typename T> class ListNode
{
public:
	T m_value;
	ListNode<T>* m_pred;
	ListNode<T>* m_succ;
};

//2.双向链表类
template<typename T> class List
{
private:
	int m_size;
	ListNode<T>* m_header;
	ListNode<T>* m_laster;
public:
	List() { init(); }
	int getSize() { return m_size; }
	void init();
	T& operator[] (int rank) const;  //const放在最后表const成员函数，无法修改类的成员变量
	ListNode<T>* find(const T& value) const;
	T erase(const T &value);
	T erase(ListNode<T>* node);
	ListNode<T>* insertAsPred(const T &value, ListNode<T>* node);
	ListNode<T>* insertAsSucc(const T &value, ListNode<T>* node);
	ListNode<T>* insertAsHead(const T &value);
	ListNode<T>* insertAsLast(const T &value);
	~List();
};

template<typename T> void List<T>::init()
{
	m_header = new ListNode<T>;
	m_laster = new ListNode<T>;
	m_header->m_pred = NULL;
	m_header->m_succ = m_laster;
	m_laster->m_pred = m_header;
	m_laster->m_succ = NULL;
	m_size = 0;
}

template<typename T> T& List<T>::operator[](int rank) const
{
	ListNode<T>* temp = m_header->m_succ;
	while (rank--)
		temp = temp->m_succ;
	return temp->m_value;
}

template<typename T> ListNode<T>* List<T>::find(const T& value) const
{
	ListNode<T>* temp = m_header->m_succ;
	int size = m_size;
	while (size--)
	{
		if (temp->m_value == value)
			return temp;
		temp = temp->m_succ;
	}
	return NULL;
}

template<typename T> T List<T>::erase(const T &value)
{
	ListNode<T>* temp = find(value);
	if (temp == NULL)
		return NULL;
	T temp_value = temp->m_value;
	//1.temp的后继的pred变为temp的前继
	temp->m_succ->m_pred = temp->m_pred;
	//2.temp的前继的succ变为temp的后继
	temp->m_pred->m_succ = temp->m_succ;
	//3.delete当前temp，然后返回被删除的值
	delete temp;
	m_size--;
	return temp_value;
}

template<typename T> T List<T>::erase(ListNode<T>* node)
{
	if (node == NULL)
		return NULL;
	T node_value = node->m_value;
	//1.node的后继的pred变为node的前继
	node->m_succ->m_pred = node->m_pred;
	//2.node的前继的succ变为node的后继
	node->m_pred->m_succ = node->m_succ;
	//3.delete当前node，然后返回被删除的值
	delete node;
	m_size--;
	return node_value;
}

template<typename T> ListNode<T>* List<T>::insertAsPred(const T &value, ListNode<T>* node)
{
	if (node == NULL)
		return NULL;
	ListNode<T>* temp = new ListNode<T>;
	temp->m_value = value;
	//1.原node的前继对象的succ变为temp，原node的前继对象变为temp的pred
	node->m_pred->m_succ = temp;
	temp->m_pred = node->m_pred;
	//2.原node的pred变为temp，原node变为temp的succ
	node->m_pred = temp;
	temp->m_succ = node;
	//3.前继插入完成，返回插入后的node
	m_size++;
	return temp;
}

template<typename T> ListNode<T>* List<T>::insertAsSucc(const T &value, ListNode<T>* node)
{
	if (node == NULL)
		return NULL;
	ListNode<T>* temp = new ListNode<T>;
	temp->m_value = value;
	//1.原node的后继对象的pred变为temp，原node的后继对象变为temp的succ
	node->m_succ->m_pred = temp;
	temp->m_succ = node->m_succ;
	//2.原node的succ变为temp，原node变为temp的pred
	node->m_succ = temp;
	temp->m_pred = node;
	//3.后继插入完成，返回插入后的node
	m_size++;
	return temp;
}

template<typename T> ListNode<T>* List<T>::insertAsHead(const T &value)
{
	ListNode<T>* temp = new ListNode<T>;
	temp->m_value = value;

	m_header->m_succ->m_pred = temp;
	temp->m_succ = m_header->m_succ;

	m_header->m_succ = temp;
	temp->m_pred = m_header;

	m_size++;
	return temp;
}
template<typename T> ListNode<T>* List<T>::insertAsLast(const T &value)
{
	ListNode<T>* temp = new ListNode<T>;
	temp->m_value = value;

	m_laster->m_pred->m_succ = temp;
	temp->m_pred = m_laster->m_pred;

	m_laster->m_pred = temp;
	temp->m_succ = m_laster;

	m_size++;
	return temp;
}

template<typename T> List<T>::~List()
{
	while (m_size--)
		erase(m_header->m_succ);
	delete m_laster;
	delete m_header;
}

int main_offer601()
{
	List<int> test;
	for (int i = 0; i < 10; i++)
	{
		test.insertAsHead(i);
		test.insertAsLast(i);
	}
	cout << "test[5]:" << test[5] << endl;
	cout << "test[15]:" << test[15] << endl;
	cout << "test.find(8)->m_value:" << test.find(8)->m_value << endl;
	cout << "test.erase(test.find(4)):" << test.erase(test.find(4)) << endl;
	cout << "test.erase(8)->m_value:" << test.erase(8) << endl;
	cout << "test.insertAsPred(11, test.find(8))->m_value:" << test.insertAsPred(11, test.find(8))->m_value << endl;
	cout << "test.insertAsSucc(13, test.find(5))->m_value:" << test.insertAsSucc(13, test.find(5))->m_value << endl;

	int size = test.getSize();
	for (int i = 0; i < size; i++)
		cout << test[i] << " ";
	cout << endl;

	return 0;
}