#pragma once

#include <vector>

struct TreeNode
{
	int                       m_nValue;
	TreeNode*				  m_parent;
	std::vector<TreeNode*>    m_vChildren;
};

__declspec(dllexport) TreeNode* CreateTreeNode(int value);
__declspec(dllexport) void ConnectTreeNodes(TreeNode* pParent, TreeNode* pChild);
__declspec(dllexport) void PrintTreeNode(const TreeNode* pNode);
__declspec(dllexport) void PrintTree(const TreeNode* pRoot);
__declspec(dllexport) void DestroyTree(TreeNode* pRoot);