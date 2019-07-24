#include <iostream>
using namespace std;

//1.�����Ľڵ���
template<typename T> class ListNode
{
public:
	T m_value;
	ListNode<T>* m_pred;
	ListNode<T>* m_succ;
};

//2.˫��������
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
	T& operator[] (int rank) const;  //const��������const��Ա�������޷��޸���ĳ�Ա����
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
	//1.temp�ĺ�̵�pred��Ϊtemp��ǰ��
	temp->m_succ->m_pred = temp->m_pred;
	//2.temp��ǰ�̵�succ��Ϊtemp�ĺ��
	temp->m_pred->m_succ = temp->m_succ;
	//3.delete��ǰtemp��Ȼ�󷵻ر�ɾ����ֵ
	delete temp;
	m_size--;
	return temp_value;
}

template<typename T> T List<T>::erase(ListNode<T>* node)
{
	if (node == NULL)
		return NULL;
	T node_value = node->m_value;
	//1.node�ĺ�̵�pred��Ϊnode��ǰ��
	node->m_succ->m_pred = node->m_pred;
	//2.node��ǰ�̵�succ��Ϊnode�ĺ��
	node->m_pred->m_succ = node->m_succ;
	//3.delete��ǰnode��Ȼ�󷵻ر�ɾ����ֵ
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
	//1.ԭnode��ǰ�̶����succ��Ϊtemp��ԭnode��ǰ�̶����Ϊtemp��pred
	node->m_pred->m_succ = temp;
	temp->m_pred = node->m_pred;
	//2.ԭnode��pred��Ϊtemp��ԭnode��Ϊtemp��succ
	node->m_pred = temp;
	temp->m_succ = node;
	//3.ǰ�̲�����ɣ����ز�����node
	m_size++;
	return temp;
}

template<typename T> ListNode<T>* List<T>::insertAsSucc(const T &value, ListNode<T>* node)
{
	if (node == NULL)
		return NULL;
	ListNode<T>* temp = new ListNode<T>;
	temp->m_value = value;
	//1.ԭnode�ĺ�̶����pred��Ϊtemp��ԭnode�ĺ�̶����Ϊtemp��succ
	node->m_succ->m_pred = temp;
	temp->m_succ = node->m_succ;
	//2.ԭnode��succ��Ϊtemp��ԭnode��Ϊtemp��pred
	node->m_succ = temp;
	temp->m_pred = node;
	//3.��̲�����ɣ����ز�����node
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