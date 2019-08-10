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
	//三种递归遍历方式，究极简单并且易于理解（均从根节点开始，按顺序递归即可）
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
	int remove(BinaryTreeNode<T>* node);  //返回由于此节点被删除而导致删除的节点总数
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

	//1.先序遍历，灵魂的根—左—右，按照所经过的顺序直接进行遍历
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
	//	//1.先序遍历，从根点开始访问，到左节点再到右节点
	//	visit(node);
	//	//2.对于右节点先放入栈中，等待访问左节点和根节点之后再使用
	//	if(node->m_rightchild != NULL)
	//		sss.push(node->m_rightchild);
	//	//3.沿着当前节点的左侧继续访问
	//	if (node->m_leftchild != NULL)
	//		node = node->m_leftchild;
	//	else
	//	{
	//		//4.在栈空时代表节点访问完毕，退出；否则表示当前分支的左节点访问完毕，栈顶出栈访问右节点
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

	//2.中序遍历，独特的左—根—右，首先找到初始节点为最左边的值，然后根据左—根—右开始遍历
	//do while的原因在于最开始栈一直为空
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
	//	//1.中序遍历，从左节点到根节点到右节点。由于根节点为初始节点，所以根节点先入栈
	//	if (node->m_leftchild != NULL)
	//	{
	//		//1.1一旦有左节点，就将当前节点（根节点入栈），然后变成左节点继续前进
	//		sss.push(node);
	//		node = node->m_leftchild;
	//	}
	//	else
	//	{
	//		//1. 2当前节点若没有左节点，表示此分支已到尽头，进行visit访问操作
	//		visit(node);
	//		//1.3 此时进入到中序遍历的两种情况，是作为一个分支的末端节点存在，还是作为一个根节点存在。
	//		//1.3.1 若不存在右节点则为枝节点，需要回到上一个栈顶的元素继续访问
	//		while (node->m_rightchild == NULL)
	//		{
	//			if (sss.empty())
	//				return;
	//			node = sss.top();
	//			sss.pop();
	//			visit(node);
	//		}
	//		//1.3.2 若存在右节点则自身为根节点，需要继续沿右节点访问
	//		node = node->m_rightchild;
	//	}
	//}
}

template<typename T> void BinaryTree<T>::travPos_Circulate(BinaryTreeNode<T>* node)
{
	stack<BinaryTreeNode<T>*> sss;
	list<BinaryTreeNode<T>*> slist;

	//后序遍历为左—右—根，实现方式为反转后调整左右先后顺序
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
	//		//1.1一旦有左节点，就将当前节点（根节点入栈），然后变成左节点继续前进
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
//	//当对于已经删除掉的节点进行计算时，此时node指向的内存已经被析构，而传进来的node却仍然指向此内存
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

	cout << "迭代前序遍历：";
	tree->travPre_Recursion(tree->m_root);
	cout << endl;
	cout << "迭代中序遍历：";
	tree->travMid_Recursion(tree->m_root);
	cout << endl;
	cout << "迭代后序遍历：";
	tree->travPos_Recursion(tree->m_root);
	cout << endl; 
	cout << "循环前序遍历：";
	tree->travPre_Circulate(tree->m_root);
	cout << endl;
	cout << "循环中序遍历：";
	tree->travMid_Circulate(tree->m_root);
	cout << endl;
	cout << "循环后序遍历：";
	tree->travPos_Circulate(tree->m_root);
	cout << endl;

	cout << "node0 height:" << node0->m_height << endl;
	cout << "node1 height:" << node1->m_height << endl;
	cout << "node2 height:" << node2->m_height << endl;
	cout << "node3 height:" << node3->m_height << endl;
	//这里涉及到的delete，释放的时机应该是“谁申请，谁释放”；
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

//由于某种原因一个二叉排序树的两个节点的元素被交换，在不改变树的结构的情况下恢复这棵二叉排序树