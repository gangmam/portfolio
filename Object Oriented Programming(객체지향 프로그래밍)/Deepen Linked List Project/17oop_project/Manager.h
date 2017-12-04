#pragma once

#include "CategoryList.h"
#include "ItemList.h"

class Manager
{
private:
	CategoryList		*cList;
	ItemList			*iList;
	ofstream			fout;
	vector<ItemNode*>	vItem;

public:
	Manager();
	~Manager();

	void run(const char* fileName);

	bool LOAD();// item.txt파일을 읽어와서 링크드리스트에 삽입하는 함수 
	bool ADD(char* arg);// 물품의 수량을 추가하거나 물품을 링크드 리스트에 추가하는 함수 
	bool MODIFY(char* arg);//입력받은 물품의 가격을 수정하는 함수
	bool SELL(char* arg);//입력받은 물품을 count만큼 판매하는 함수
	bool DELETE(char* arg);// 입력받는 물품을 삭제하는 함수
	bool SEARCH(char* arg);// 입력받은 한글자, 한단어를 가지는 탐색 및 출력 하는 함수
	bool PRINT(char* arg);// 물품의 정보를 출력하는 함수
	bool MANAGE(char* arg);// 물품의 수량을 기준으로 물품에 대한 정보를 출력하거나 물품의 수량을 채워주는 함수
	bool SALES(char* arg);//물품별 판매액 순위 및 총 수익일 출력하는 함수
	bool SAVE();//링크드 리스트를 item.txt에 저장하는 함수
};