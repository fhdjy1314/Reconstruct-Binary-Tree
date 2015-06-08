/*
	根据先序遍历跟中序遍历重建二叉树，并输出后续遍历的结果
*/
#include <iostream>
using namespace std;

struct BinaryTreeNode
{
	int nodeValue;
	BinaryTreeNode *pLeft;
	BinaryTreeNode *pRight;
};

BinaryTreeNode * BuildRecursivly(int *pPrevOrderStart, int *pPrevOrderEnd, int *pInOrderStart, int *pInOrderEnd)
{
	//在先序遍历序列中取出第一个元素即为根节点元素
	int value = pPrevOrderStart[0];
	//构造根节点
	BinaryTreeNode *root = new BinaryTreeNode;
	root->nodeValue = value;
	root->pLeft = NULL;
	root->pRight = NULL;
	//递归结束的情况，即只剩一个叶子节点
	if (pPrevOrderStart == pPrevOrderEnd)
	{
		if (pInOrderStart == pInOrderEnd && *pPrevOrderStart == *pInOrderStart)
			return root;
		else
			throw std::exception();
	}
	//在中序遍历序列中找出根节点的位置
	int *pInOrderCursor = pInOrderStart;
	while (pInOrderCursor < pInOrderEnd && *pInOrderCursor != value)
	{
		pInOrderCursor++;
	}
	if (pInOrderCursor == pInOrderEnd && *pInOrderCursor != value)
	{
		throw std::exception();
	}
	//取得左子树的长度以及在先序遍历中取得左子树的起始位置
	int leftTreeLen = pInOrderCursor - pInOrderStart;
	int *pPrevOrderLeftTreeEnd = pPrevOrderStart + leftTreeLen;
	//如果左子树存在，则递归左子树
	if (leftTreeLen > 0)
	{
		root->pLeft = BuildRecursivly(pPrevOrderStart + 1, pPrevOrderLeftTreeEnd,
			pInOrderStart, pInOrderCursor - 1);
	}
	//如果右子树存在，则递归右子树
	if ((pPrevOrderEnd - pPrevOrderStart) > leftTreeLen)
	{
		root->pRight = BuildRecursivly(pPrevOrderLeftTreeEnd + 1, pPrevOrderEnd,
			pInOrderCursor + 1, pInOrderEnd);
	}

	return root;
}

BinaryTreeNode * BulidBinaryTree(int *szPrevOrder, int *szInOrder, int nodeNum)
{
	if (szPrevOrder == NULL || szInOrder == NULL)
		return NULL;
	return BuildRecursivly(szPrevOrder, szPrevOrder + nodeNum - 1,
		szInOrder, szInOrder + nodeNum - 1);
}

/*先序遍历*/
void PrevOrder(BinaryTreeNode *root)
{
	if (root == NULL)
		return;
	//根
	cout << root->nodeValue << ' ';
	//左子树
	if (root->pLeft != NULL)
		PrevOrder(root->pLeft);
	//右子树
	if (root->pRight != NULL)
		PrevOrder(root->pRight);
}

/*中序遍历*/
void InOrder(BinaryTreeNode *root)
{
	if (root == NULL)
		return;
	//左子树
	if (root->pLeft != NULL)
		InOrder(root->pLeft);
	//根
	cout << root->nodeValue << ' ';
	//右子树
	if (root->pRight != NULL)
		InOrder(root->pRight);
}

/*后序遍历*/
void PostOrder(BinaryTreeNode *root)
{
	if (root == NULL)
		return;
	//左子树
	if (root->pLeft != NULL)
		PostOrder(root->pLeft);
	//右子树
	if (root->pRight != NULL)
		PostOrder(root->pRight);
	//根
	cout << root->nodeValue << ' ';
}


void main()
{
	int szPrevOrder[] = { 1, 2, 4, 7, 3, 5, 6, 8 };   //二叉树的先序遍历  
	int szInOrder[] = { 4, 7, 2, 1, 5, 3, 8, 6 };     //二叉树的中序遍历  
	int nodeNum = sizeof(szPrevOrder) / sizeof(int);
	BinaryTreeNode *root = BulidBinaryTree(szPrevOrder, szInOrder, nodeNum);
	cout << "PrevOrder: ";
	PrevOrder(root);
	cout << endl << "InOrder:   ";
	InOrder(root);
	cout << endl << "PostOrder: ";
	PostOrder(root);
	cout << endl;

	system("pause");
}
