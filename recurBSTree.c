#include "BSTree.h"
#include <stdio.h>
//�ݹ����ֵΪdata���
BSTNode* FindBSTreeR(BSTNode* pRoot, DataType data)
{
	if (pRoot) {
		if (data == pRoot->_data) {
			return pRoot;
		}
		else if (pRoot->_data > data) {
			return FindBSTreeR(pRoot->_pLeft, data);
		}
		else {
			return FindBSTreeR(pRoot->_pRight, data);
		}
	}
	return NULL;
}
//������ݹ���ʽ
int InsertBSTreeR(BSTNode** pRoot, DataType data)
{
	if (NULL == *pRoot) {
		*pRoot = BuyNode(data);
		return 1;
	}
	else if ((*pRoot)->_data > data) {
		return InsertBSTreeR(&(*pRoot)->_pLeft, data);
	}
	else if ((*pRoot)->_data < data) {
		return InsertBSTreeR(&(*pRoot)->_pRight, data);
	}
	return 0;
}

//ɾ�����ݹ���ʽ
int DeleteBSTreeR(BSTNode** pRoot, DataType data)
{
	if (NULL == *pRoot) {
		return 0;
	}
	if ((*pRoot)->_data > data) {
		return DeleteBSTreeR(&(*pRoot)->_pLeft, data);
	}
	else if((*pRoot)->_data < data) {
		return DeleteBSTreeR(&(*pRoot)->_pRight, data);
	}
	else {
		//�ҵ���ɾ�����
		BSTNode *pDel = *pRoot;
		BSTNode *parent = NULL;
		if (NULL == pDel->_pLeft) {
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
	return 1;
}

void testRecur()
{
	BSTNode *pRoot;
	InitBSTree(&pRoot);
	int arr[] = { 5,3,4,1,7,8,2,6,0,9 };
	int len = sizeof(arr) / sizeof(arr[0]);
	int i = 0;
	for (i = 0; i < len; i++) {
		InsertBSTreeR(&pRoot, arr[i]);
	}
	DeleteBSTreeR(&pRoot, 9);
	DeleteBSTreeR(&pRoot, 8);
	DeleteBSTreeR(&pRoot, 7);
	PreOrder(pRoot);
	printf("\n");
	DeleteBSTreeR(&pRoot, 1);
	DeleteBSTreeR(&pRoot, 4);
	DeleteBSTreeR(&pRoot, 5);
	DeleteBSTreeR(&pRoot, 3);
	PreOrder(pRoot);
	printf("\n");
	DeleteBSTreeR(&pRoot, 7);
	DeleteBSTreeR(&pRoot, 6);
	DeleteBSTreeR(&pRoot, 0);
	DeleteBSTreeR(&pRoot, 2);
	PreOrder(pRoot);
	printf("\n");
}
