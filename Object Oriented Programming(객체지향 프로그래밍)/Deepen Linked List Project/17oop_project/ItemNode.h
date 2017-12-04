#pragma once

#include "Node.h"
#pragma warning(disable:4996)

class ItemNode : public Node
{
private:
	char	mName[64];
	int		mCount;
	int		mPrice;
public:
	void setItemName(char* name)// 아이템이름을 set해주는 함수
	{
		strcpy(mName, name);
	}
	void setItemCount(int count)// 아이템수량을 set해주는 함수 
	{
		mCount = count;
	}
	void setItemPrice(int price)//아이템 가격을 set해주는 함수
	{
		mPrice = price;
	}
	char* getItemName()//아이템 이름을 반환하는 함수
	{
		return mName;
	}
	int getItemCount()// 아이템 수량을 반환하는 함수
	{
		return mCount;
	}
	int getItemPrice()//아이템 가격을 반환하는 함수
	{
		return mPrice;
	}
	///////////다형성의 사용을 위해
	void setCategoryName(char* name)
	{
	}
	char* getCategoryName()
	{
		return 0;
	}
	/////////////////////////////
};