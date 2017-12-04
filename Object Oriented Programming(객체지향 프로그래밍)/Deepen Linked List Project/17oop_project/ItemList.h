#pragma once

#include "ItemNode.h"

class ItemList 
{
private:
	Node*		iRoot;
	ofstream*	fout;

public:
	ItemList(ofstream* fout);//생성자
	~ItemList();//소멸자
	void ItemInsert(Node* newNode);//아이템리스트로 삽입을 실시하는함수
	Node* ItemSearch(char* name);// 해당이름을 가지는 노드를 반환하는 함수
	Node* ItemPrevSearch(char* name);// 해당이름을 가지는 노드의 이전노드를 반환하는 함수
	Node* getCategory(char* name);// 해당 이름을 가지는 노드의 카테고리노드를 반환하는 함수
	Node* getItemHead();// 아이템리스트의 iRoot를 반환하는 함수
	void setItemHead(Node* newNode);// 아이템리스트의 iRoot set해주는 함수
};