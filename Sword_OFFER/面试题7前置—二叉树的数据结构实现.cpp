#include <iostream>
#include <stack>
#include <list>
using namespace std;

template<typename T> class BinaryTreeNode
{
public:
	T m_value;
	int m_height;
	BinaryTreeNode() {}
	BinaryTreeNode(T value) : m_value(value) {}
	BinaryTreeNode<T> *m_leftchild;
	BinaryTreeNode<T> *m_rightchild;
	BinaryTreeNode<T> *m_parent;
};

template<typename T> class BinaryTree
{
public:
	BinaryTreeNode<T> *m_root;
	void visit(BinaryTreeNode<T>* node) { cout << node->m_value << " "; }
	//���ֵݹ������ʽ�������򵥲���������⣨���Ӹ��ڵ㿪ʼ����˳��ݹ鼴�ɣ�
	void travPre_Recursion(BinaryTreeNode<T>* node);
	void travMid_Recursion(BinaryTreeNode<T>* node);
	void travPos_Recursion(BinaryTreeNode<T>* node);
	void travPre_Circulate(BinaryTreeNode<T>* node);
	void travMid_Circulate(BinaryTreeNode<T>* node);
	void travPos_Circulate(BinaryTreeNode<T>* node);
	void insert(BinaryTreeNode* &root, int x);
	int m_size;
	void updateHeight(BinaryTreeNode<T>* node);
	BinaryTree() : m_size(0), m_root(NULL) {};
	BinaryTreeNode<T>* insertAsRoot(T const &value);
	int remove(BinaryTreeNode<T>* node);  //�������ڴ˽ڵ㱻ɾ��������ɾ���Ľڵ�����
	int removeAt(BinaryTreeNode<T>* node);
	BinaryTreeNode<T>* insertAsLeftChild(BinaryTreeNode<T>* parent, T const &value);
	BinaryTreeNode<T>* insertAsRightChild(BinaryTreeNode<T>* parent, T const &value);
};

template<typename T> void BinaryTree<T>::travPre_Recursion(BinaryTreeNode<T>* node)
{
	if (node == NULL)
		return;
	visit(node);
	travPre_Recursion(node->m_leftchild);
	travPre_Recursion(node->m_rightchild);
}

template<typename T> void BinaryTree<T>::travMid_Recursion(BinaryTreeNode<T>* node)
{
	if (node == NULL)
		return;
	travMid_Recursion(node->m_leftchild);
	visit(node);
	travMid_Recursion(node->m_rightchild);
}

template<typename T> void BinaryTree<T>::travPos_Recursion(BinaryTreeNode<T>* node)
{
	if (node == NULL)
		return;
	travPos_Recursion(node->m_leftchild);
	travPos_Recursion(node->m_rightchild);
	visit(node);
}

template<typename T> void BinaryTree<T>::travPre_Circulate(BinaryTreeNode<T>* node)
{
	stack<BinaryTreeNode<T>*> sss;
	list<BinaryTreeNode<T>*> slist;

	//1.������������ĸ������ң�������������˳��ֱ�ӽ��б���
	sss.push(node);
	while (!sss.empty())
	{
		node = sss.top(); sss.pop();
		slist.push_back(node);
		if (node->m_rightchild != NULL)
		{
			sss.push(node->m_rightchild);
		}
		if (node->m_leftchild != NULL)
		{
			sss.push(node->m_leftchild);
		}
	}

	for (auto &s : slist)
		cout << s->m_value << " ";

	//while (node != NULL)
	//{
	//	//1.����������Ӹ��㿪ʼ���ʣ�����ڵ��ٵ��ҽڵ�
	//	visit(node);
	//	//2.�����ҽڵ��ȷ���ջ�У��ȴ�������ڵ�͸��ڵ�֮����ʹ��
	//	if(node->m_rightchild != NULL)
	//		sss.push(node->m_rightchild);
	//	//3.���ŵ�ǰ�ڵ������������
	//	if (node->m_leftchild != NULL)
	//		node = node->m_leftchild;
	//	else
	//	{
	//		//4.��ջ��ʱ����ڵ������ϣ��˳��������ʾ��ǰ��֧����ڵ������ϣ�ջ����ջ�����ҽڵ�
	//		if (sss.empty())
	//			return;
	//		node = sss.top();
	//		sss.pop();
	//	}
	//}
}

template<typename T> void BinaryTree<T>::travMid_Circulate(BinaryTreeNode<T>* node)
{
	stack<BinaryTreeNode<T>*> sss;
	list<BinaryTreeNode<T>*> slist;

	//2.������������ص��󡪸����ң������ҵ���ʼ�ڵ�Ϊ����ߵ�ֵ��Ȼ������󡪸����ҿ�ʼ����
	//do while��ԭ�������ʼջһֱΪ��
	do 
	{
		while (node != NULL) 
		{
			sss.push(node);
			node = node->m_leftchild;
		}
		if (!sss.empty()) 
		{
			node = sss.top(); sss.pop();
			slist.push_back(node);
			node = node->m_rightchild;
		}
	} while (!sss.empty() || node != NULL);

	for (auto &s : slist)
		cout << s->m_value << " ";

	//while (node != NULL)
	//{
	//	//1.�������������ڵ㵽���ڵ㵽�ҽڵ㡣���ڸ��ڵ�Ϊ��ʼ�ڵ㣬���Ը��ڵ�����ջ
	//	if (node->m_leftchild != NULL)
	//	{
	//		//1.1һ������ڵ㣬�ͽ���ǰ�ڵ㣨���ڵ���ջ����Ȼ������ڵ����ǰ��
	//		sss.push(node);
	//		node = node->m_leftchild;
	//	}
	//	else
	//	{
	//		//1. 2��ǰ�ڵ���û����ڵ㣬��ʾ�˷�֧�ѵ���ͷ������visit���ʲ���
	//		visit(node);
	//		//1.3 ��ʱ���뵽����������������������Ϊһ����֧��ĩ�˽ڵ���ڣ�������Ϊһ�����ڵ���ڡ�
	//		//1.3.1 ���������ҽڵ���Ϊ֦�ڵ㣬��Ҫ�ص���һ��ջ����Ԫ�ؼ�������
	//		while (node->m_rightchild == NULL)
	//		{
	//			if (sss.empty())
	//				return;
	//			node = sss.top();
	//			sss.pop();
	//			visit(node);
	//		}
	//		//1.3.2 �������ҽڵ�������Ϊ���ڵ㣬��Ҫ�������ҽڵ����
	//		node = node->m_rightchild;
	//	}
	//}
}

template<typename T> void BinaryTree<T>::travPos_Circulate(BinaryTreeNode<T>* node)
{
	stack<BinaryTreeNode<T>*> sss;
	list<BinaryTreeNode<T>*> slist;

	//�������Ϊ���ҡ�����ʵ�ַ�ʽΪ��ת����������Ⱥ�˳��
	sss.push(node);
	while (!sss.empty())
	{
		node = sss.top(); sss.pop();
		slist.push_front(node);
		if (node->m_leftchild != NULL)
		{
			sss.push(node->m_leftchild);
		}
		if (node->m_rightchild != NULL)
		{
			sss.push(node->m_rightchild);
		}
	}

	for (auto &s : slist)
		cout << s->m_value << " ";

	//if (node != NULL)
	//	sss.push(node);
	//while (node != NULL)
	//{
	//	while (node->m_leftchild != NULL)
	//	{
	//		//1.1һ������ڵ㣬�ͽ���ǰ�ڵ㣨���ڵ���ջ����Ȼ������ڵ����ǰ��
	//		sss.push(node);
	//		if (node->m_rightchild != NULL)
	//			sss.push(node->m_rightchild);
	//		node = node->m_leftchild;
	//	}
	//	if (node->m_rightchild != NULL)
	//	{
	//		node = node->m_rightchild;
	//	}
	//	else
	//	{
	//		visit(node);
	//		node = sss.top(); sss.pop();
	//	}
	//}
}

template<typename T> void BinaryTree<T>::updateHeight(BinaryTreeNode<T>* node)
{
	if (node == NULL)
		return;
	int leftHeight = -1;
	if (node->m_leftchild != NULL)
		leftHeight = node->m_leftchild->m_height;
	int rightHeight = -1;
	if (node->m_rightchild != NULL)
		rightHeight = node->m_rightchild->m_height;
	node->m_height = 1 + ((leftHeight > rightHeight) ? (leftHeight) : (rightHeight));
	updateHeight(node->m_parent);
}

template<typename T> BinaryTreeNode<T>* BinaryTree<T>::insertAsRoot(T const &value)
{
	BinaryTreeNode<T>* node = new BinaryTreeNode<T>;
	node->m_value = value;
	if (m_root == NULL)
	{
		m_root = node;
	}
	else
	{
		m_root->m_parent = node;
		node->m_leftchild = m_root;
		m_root = node;
	}
	m_size++;
	return node;
}

//template<typename T> int BinaryTree<T>::remove(BinaryTreeNode<T>* node)
//{
//	//�������Ѿ�ɾ�����Ľڵ���м���ʱ����ʱnodeָ����ڴ��Ѿ�������������������nodeȴ��Ȼָ����ڴ�
//	if (node == nullptr)
//		return 0;
//	if (node->m_parent != NULL)
//	{
//		if (node->m_parent->m_leftchild == node)
//			node->m_parent->m_leftchild = NULL;
//		if (node->m_parent->m_rightchild == node)
//			node->m_parent->m_rightchild = NULL;
//	}
//	updateHeight(node->m_parent);
//
//	int n = removeAt(node);
//	return n;
//}
//
//template<typename T> int BinaryTree<T>::removeAt(BinaryTreeNode<T>* node)
//{
//	if (node == NULL)
//		return 0;
//	int n = 1 + removeAt(node->m_leftchild) + removeAt(node->m_rightchild);
//	return n;
//}

template<typename T> BinaryTreeNode<T>* BinaryTree<T>::insertAsLeftChild(BinaryTreeNode<T>* parent, T const &value)
{
	BinaryTreeNode<T>* node = new BinaryTreeNode<T>;
	node->m_value = value;
	node->m_parent = parent;
	parent->m_leftchild = node;
	m_size++;
	updateHeight(node->m_parent);
	return node;
}

template<typename T> BinaryTreeNode<T>* BinaryTree<T>::insertAsRightChild(BinaryTreeNode<T>* parent, T const &value)
{
	BinaryTreeNode<T>* node = new BinaryTreeNode<T>;
	node->m_value = value;
	node->m_parent = parent;
	parent->m_rightchild = node;
	m_size++;
	updateHeight(node->m_parent);
	return node;
}

int main_offer701()
{
	BinaryTree<int>* tree = new BinaryTree<int>;
	BinaryTreeNode<int>* node0 = tree->insertAsRoot(0);
	BinaryTreeNode<int>* node1 = tree->insertAsLeftChild(node0, 1);
	BinaryTreeNode<int>* node2 = tree->insertAsRightChild(node0, 2);
	BinaryTreeNode<int>* node3 = tree->insertAsLeftChild(node1, 3);
	BinaryTreeNode<int>* node4 = tree->insertAsRightChild(node1, 4);
	BinaryTreeNode<int>* node5 = tree->insertAsLeftChild(node2, 5);
	BinaryTreeNode<int>* node6 = tree->insertAsRightChild(node2, 6);

	cout << "����ǰ�������";
	tree->travPre_Recursion(tree->m_root);
	cout << endl;
	cout << "�������������";
	tree->travMid_Recursion(tree->m_root);
	cout << endl;
	cout << "�������������";
	tree->travPos_Recursion(tree->m_root);
	cout << endl; 
	cout << "ѭ��ǰ�������";
	tree->travPre_Circulate(tree->m_root);
	cout << endl;
	cout << "ѭ�����������";
	tree->travMid_Circulate(tree->m_root);
	cout << endl;
	cout << "ѭ�����������";
	tree->travPos_Circulate(tree->m_root);
	cout << endl;

	cout << "node0 height:" << node0->m_height << endl;
	cout << "node1 height:" << node1->m_height << endl;
	cout << "node2 height:" << node2->m_height << endl;
	cout << "node3 height:" << node3->m_height << endl;
	//�����漰����delete���ͷŵ�ʱ��Ӧ���ǡ�˭���룬˭�ͷš���
	//cout << "tree->remove(node1):" << tree->remove(node1) << endl;
	//cout << "tree->remove(node2):" << tree->remove(node2) << endl;
	//cout << "tree->remove(node3):" << tree->remove(node3) << endl;
	//cout << "tree->remove(node0):" << tree->remove(node0) << endl;

	delete node3;
	delete node2;
	delete node1;
	delete node0;

	return 0;
}

//����ĳ��ԭ��һ�������������������ڵ��Ԫ�ر��������ڲ��ı����Ľṹ������»ָ���ö���������