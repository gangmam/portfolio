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

	bool LOAD();// item.txt������ �о�ͼ� ��ũ�帮��Ʈ�� �����ϴ� �Լ� 
	bool ADD(char* arg);// ��ǰ�� ������ �߰��ϰų� ��ǰ�� ��ũ�� ����Ʈ�� �߰��ϴ� �Լ� 
	bool MODIFY(char* arg);//�Է¹��� ��ǰ�� ������ �����ϴ� �Լ�
	bool SELL(char* arg);//�Է¹��� ��ǰ�� count��ŭ �Ǹ��ϴ� �Լ�
	bool DELETE(char* arg);// �Է¹޴� ��ǰ�� �����ϴ� �Լ�
	bool SEARCH(char* arg);// �Է¹��� �ѱ���, �Ѵܾ ������ Ž�� �� ��� �ϴ� �Լ�
	bool PRINT(char* arg);// ��ǰ�� ������ ����ϴ� �Լ�
	bool MANAGE(char* arg);// ��ǰ�� ������ �������� ��ǰ�� ���� ������ ����ϰų� ��ǰ�� ������ ä���ִ� �Լ�
	bool SALES(char* arg);//��ǰ�� �Ǹž� ���� �� �� ������ ����ϴ� �Լ�
	bool SAVE();//��ũ�� ����Ʈ�� item.txt�� �����ϴ� �Լ�
};