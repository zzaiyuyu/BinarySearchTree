#include "BSTree.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
// ��ʼ������������ 
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
// ����ֵΪdata��Ԫ�� 
void InsertBSTree(BSTNode** pRoot, DataType data)
{
	assert(pRoot);
	if (NULL == *pRoot) {
		//�������ı�ͷ���
		*pRoot = BuyNode(data);
	}
	else {
		//�����գ��ҵ�����λ�ò���
		BSTNode *parent = NULL;
		BSTNode *child = *pRoot;
		//�������λ��һ����childΪ�գ�����ǣ���������м����
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
		//�ҵ���child�ĺ���λ��
		if (parent->_data > data) {
			parent->_pLeft = BuyNode(data);
		}
		else {
			parent->_pRight = BuyNode(data);
		}
	}
}

// ɾ��ֵΪdata�Ľ�� 
void DeleteBSTree(BSTNode** pRoot, DataType data)
{
	assert(pRoot);
	if (*pRoot) {
			//�ҵ�Ҫɾ���Ľ��
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
			//�����ɾ��,������Ϊ�գ�������Ϊ�գ����Ҿ�����
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
					//ɾ���ڵ�
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
					//ɾ���ڵ�
					*pRoot = pDel->_pLeft;
				}
			}
			else {
				//��������������С�Ľ��
				BSTNode *pOrg = pDel; //��¼��ɾ���Ľ��
				parent = pDel;
				pDel = pDel->_pRight;
				while (pDel->_pLeft) {
					parent = pDel;
					pDel = pDel->_pLeft;
				}
				//������ɾ������������ɾ���Ľ��ֵ
				pOrg->_data = pDel->_data;
				//ɾ���ҵ�����С�ڵ�
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

// �ڶ����������в���ֵΪdata�Ľ�� 
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

// ����������������� 
void PreOrder(BSTNode* pRoot)
{
	if (pRoot) {
		PreOrder(pRoot->_pLeft);
		printf("%d ", pRoot->_data);
		PreOrder(pRoot->_pRight);
	}
}

// ���ٶ��������� 
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