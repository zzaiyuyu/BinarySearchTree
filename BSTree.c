#include "BSTree.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
// 初始化二叉搜索树 
void InitBSTree(BSTNode** pRoot)
{
	assert(pRoot);
	*pRoot = NULL;
}
BSTNode * BuyNode(DataType data)
{
	BSTNode *pNew = (BSTNode*)malloc(sizeof(BSTNode));
	if(NULL == pNew){
		exit(EXIT_FAILURE);
	}
	pNew->_data = data;
	pNew->_pLeft = NULL;
	pNew->_pRight = NULL;
	return pNew;
}
// 插入值为data的元素 
void InsertBSTree(BSTNode** pRoot, DataType data)
{
	assert(pRoot);
	if (NULL == *pRoot) {
		//空树，改变头结点
		*pRoot = BuyNode(data);
	}
	else {
		//树不空，找到合适位置插入
		BSTNode *parent = NULL;
		BSTNode *child = *pRoot;
		//最后插入的位置一定是child为空，而不牵扯在两数中间插入
		while (child) {
			if (child->_data > data) {
				parent = child;
				child = child->_pLeft;
			}
			else {
				parent = child;
				child = child->_pRight;
			}
		}
		//找到了child的合适位置
		if (parent->_data > data) {
			parent->_pLeft = BuyNode(data);
		}
		else {
			parent->_pRight = BuyNode(data);
		}
	}
}

// 删除值为data的结点 
void DeleteBSTree(BSTNode** pRoot, DataType data)
{
	assert(pRoot);
	if (*pRoot) {
			//找到要删除的结点
			BSTNode *parent = NULL;
			BSTNode *pDel = *pRoot;
			while (pDel) {
				if (pDel->_data == data) {
					break;
				}
				else if (pDel->_data > data) {
					parent = pDel;
					pDel = pDel->_pLeft;
				}
				else {
					parent = pDel;
					pDel = pDel->_pRight;
				}
			}
			//分情况删除,右子树为空，左子树为空，左右均存在
			if (NULL == pDel) {
				return;
			}
			if (NULL == pDel->_pLeft ) {
				if (parent) {
					if (parent->_data > pDel->_data) {
						parent->_pLeft = pDel->_pRight;
					}
					else {
						parent->_pRight = pDel->_pRight;
					}

				}
				else {
					//删根节点
					*pRoot = pDel->_pRight;
				}
			}
			else if (pDel->_pRight == NULL) {
				if (parent) {
					if (parent->_data > pDel->_data) {
						parent->_pLeft = pDel->_pLeft;
					}
					else {
						parent->_pRight = pDel->_pLeft;
					}
				}
				else {
					//删根节点
					*pRoot = pDel->_pLeft;
				}
			}
			else {
				//在右子树中找最小的结点
				BSTNode *pOrg = pDel; //记录被删除的结点
				parent = pDel;
				pDel = pDel->_pRight;
				while (pDel->_pLeft) {
					parent = pDel;
					pDel = pDel->_pLeft;
				}
				//交换被删除结点和真正被删除的结点值
				pOrg->_data = pDel->_data;
				//删除找到的最小节点
				if (parent == pOrg) {
					parent->_pRight = pDel->_pRight;
				}
				else {
					parent->_pLeft = pDel->_pRight;
				}
			}
			free(pDel);
	}
}

// 在二叉搜索树中查找值为data的结点 
BSTNode* FindBSTree(BSTNode* pRoot, DataType data)
{
	BSTNode *pCur = pRoot;
	while (pCur) {
		if (pCur->_data == data) {
			break;
		}
		else if (pCur->_data > data) {
			pCur = pCur->_pLeft;
		}
		else {
			pCur = pCur->_pRight;
		}
	}
	return pCur;
}

// 中序遍历二叉搜索树 
void PreOrder(BSTNode* pRoot)
{
	if (pRoot) {
		PreOrder(pRoot->_pLeft);
		printf("%d ", pRoot->_data);
		PreOrder(pRoot->_pRight);
	}
}

// 销毁二叉搜索树 
void DestroyBSTree(BSTNode** pRoot)
{
	if (*pRoot) {
		DestroyBSTree(&(*pRoot)->_pLeft);
		DestroyBSTree(&(*pRoot)->_pRight);
		free(*pRoot);
		*pRoot = NULL;
	}
}

void testBSTree()
{
	BSTNode *pRoot;
	InitBSTree(&pRoot);
	int arr[] = { 5,3,4,1,7,8,2,6,0,9 };
	int len = sizeof(arr) / sizeof(arr[0]);
	int i = 0;
	for (i = 0; i < len; i++) {
		InsertBSTree(&pRoot, arr[i]);
	}
	BSTNode *pFind = FindBSTree(pRoot, 6);
	DeleteBSTree(&pRoot, 0);
	PreOrder(pRoot);
	printf("\n");
	DeleteBSTree(&pRoot, 8);
	PreOrder(pRoot);
	printf("\n");
	DeleteBSTree(&pRoot, 5);
	DeleteBSTree(&pRoot, 1);
	DeleteBSTree(&pRoot, 4);
	DeleteBSTree(&pRoot, 3);
	PreOrder(pRoot);
	printf("\n");
	DeleteBSTree(&pRoot, 7);
	DeleteBSTree(&pRoot, 6);
	DeleteBSTree(&pRoot, 9);
	PreOrder(pRoot);
	printf("\n");
}