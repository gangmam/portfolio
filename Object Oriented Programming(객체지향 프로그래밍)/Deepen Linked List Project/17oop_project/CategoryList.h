#pragma once

#include "CategoryNode.h"

class CategoryList
{
private:
	Node*		cRoot;
	ofstream*	fout;

public:
	CategoryList(ofstream* fout);//생성자
	~CategoryList();//소멸자
	void CategoryInsert(char* category);// 카테고리 리스트 삽입함수
	Node* CategorySearch(char* category);// 해당카테고리명을 가지는 노드를 반환해주는 함수
	Node* CategoryPrevSearch(char* category);//해당카테고리명을 가지는 노드의 이전 노드를 반환해주는 함수
	Node* getCategoryHead();// 카테고리 리스트의 cRoot를 반환해주는 함수
	void setCategoryHead(Node* newNode);//카테고리 리스트이 cRoot를 set해주는 함수
};