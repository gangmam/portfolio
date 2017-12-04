#pragma once

#include "Node.h"
#pragma warning(disable:4996)

class CategoryNode : public Node
{
private:
	char	mName[64];
	
public:
	void setCategoryName(char* Category)//카테고리명을 set해주는 함수
	{
		strcpy(mName, Category);
	}
	char* getCategoryName()//카테고리명을 반환하는 함수
	{
		return mName;
	}
	//////////다형성의 사용을 위해서///////////////
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