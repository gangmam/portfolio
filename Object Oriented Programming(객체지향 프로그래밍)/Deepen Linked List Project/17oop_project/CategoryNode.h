#pragma once

#include "Node.h"
#pragma warning(disable:4996)

class CategoryNode : public Node
{
private:
	char	mName[64];
	
public:
	void setCategoryName(char* Category)//ī�װ����� set���ִ� �Լ�
	{
		strcpy(mName, Category);
	}
	char* getCategoryName()//ī�װ����� ��ȯ�ϴ� �Լ�
	{
		return mName;
	}
	//////////�������� ����� ���ؼ�///////////////
	void setItemName(char* name)
	{
	}
	void setItemCount(int count)
	{
	}
	void setItemPrice(int price)
	{
	}
	char* getItemName()
	{
		return 0;
	}
	int getItemCount()
	{
		return 0;
	}
	int getItemPrice()
	{
		return 0;
	}
	/////////////////////////////////
};