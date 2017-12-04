#pragma once

#include "CategoryNode.h"

class CategoryList
{
private:
	Node*		cRoot;
	ofstream*	fout;

public:
	CategoryList(ofstream* fout);//������
	~CategoryList();//�Ҹ���
	void CategoryInsert(char* category);// ī�װ� ����Ʈ �����Լ�
	Node* CategorySearch(char* category);// �ش�ī�װ����� ������ ��带 ��ȯ���ִ� �Լ�
	Node* CategoryPrevSearch(char* category);//�ش�ī�װ����� ������ ����� ���� ��带 ��ȯ���ִ� �Լ�
	Node* getCategoryHead();// ī�װ� ����Ʈ�� cRoot�� ��ȯ���ִ� �Լ�
	void setCategoryHead(Node* newNode);//ī�װ� ����Ʈ�� cRoot�� set���ִ� �Լ�
};