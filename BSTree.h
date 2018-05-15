#pragma once
typedef int DataType;
typedef struct BSTreeNode
{
	struct BSTreeNode* _pLeft;
	struct BSTreeNode* _pRight;
	DataType _data;
}BSTNode;

// ��ʼ������������ 
void InitBSTree(BSTNode** pRoot);

// ����ֵΪdata��Ԫ�� 
void InsertBSTree(BSTNode** pRoot, DataType data);

// ɾ��ֵΪdata�Ľ�� 
void DeleteBSTree(BSTNode** pRoot, DataType data);

// �ڶ����������в���ֵΪdata�Ľ�� 
BSTNode* FindBSTree(BSTNode* pRoot, DataType data);

// ����������������� 
void PreOrder(BSTNode* pRoot);

// ���ٶ��������� 
void DestroyBSTree(BSTNode** pRoot);