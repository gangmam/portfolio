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

	Node* getNext() { return pNext; }	//옆 노드를 반환하는 함수
	Node* getUp()	{ return pUp; }	//위 노드를 반환하는함수
	Node* getDown() { return pDown; }// 아래 노드를 반환하는 함수

	void setNext(Node* pN)	{ pNext = pN; }// 옆노드를 지정해주는 함수
	void setUp(Node* pN)	{ pUp = pN; }// 위 노드를 지정해주는 함수
	void setDown(Node* pN)	{ pDown = pN; }// 아래 노드를 지정해주는 함수
	//////////////////다형성의 사용을 위해서///////////
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