#pragma once

#include "ItemNode.h"

class ItemList 
{
private:
	Node*		iRoot;
	ofstream*	fout;

public:
	ItemList(ofstream* fout);//������
	~ItemList();//�Ҹ���
	void ItemInsert(Node* newNode);//�����۸���Ʈ�� ������ �ǽ��ϴ��Լ�
	Node* ItemSearch(char* name);// �ش��̸��� ������ ��带 ��ȯ�ϴ� �Լ�
	Node* ItemPrevSearch(char* name);// �ش��̸��� ������ ����� ������带 ��ȯ�ϴ� �Լ�
	Node* getCategory(char* name);// �ش� �̸��� ������ ����� ī�װ���带 ��ȯ�ϴ� �Լ�
	Node* getItemHead();// �����۸���Ʈ�� iRoot�� ��ȯ�ϴ� �Լ�
	void setItemHead(Node* newNode);// �����۸���Ʈ�� iRoot set���ִ� �Լ�
};