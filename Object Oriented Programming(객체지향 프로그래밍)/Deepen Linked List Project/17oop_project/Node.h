#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

class Node
{
private:
	Node*	pNext;
	Node*	pDown;
	Node*	pUp;

public:
	Node() 
	{
		pNext = NULL;
		pDown = NULL;
		pUp = NULL;
	};
	~Node() {};

	Node* getNext() { return pNext; }	//�� ��带 ��ȯ�ϴ� �Լ�
	Node* getUp()	{ return pUp; }	//�� ��带 ��ȯ�ϴ��Լ�
	Node* getDown() { return pDown; }// �Ʒ� ��带 ��ȯ�ϴ� �Լ�

	void setNext(Node* pN)	{ pNext = pN; }// ����带 �������ִ� �Լ�
	void setUp(Node* pN)	{ pUp = pN; }// �� ��带 �������ִ� �Լ�
	void setDown(Node* pN)	{ pDown = pN; }// �Ʒ� ��带 �������ִ� �Լ�
	//////////////////�������� ����� ���ؼ�///////////
	virtual void setItemName(char* name) = 0;
	virtual void setItemCount(int count) = 0;
	virtual void setItemPrice(int price) = 0;
	virtual char* getItemName() = 0;
	virtual int getItemCount() = 0;
	virtual int getItemPrice() = 0;
	virtual void setCategoryName(char* name) = 0;
	virtual char* getCategoryName() = 0;
	//////////////////////////////////////////////////
};