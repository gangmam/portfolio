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
	void setItemName(char* name)// �������̸��� set���ִ� �Լ�
	{
		strcpy(mName, name);
	}
	void setItemCount(int count)// �����ۼ����� set���ִ� �Լ� 
	{
		mCount = count;
	}
	void setItemPrice(int price)//������ ������ set���ִ� �Լ�
	{
		mPrice = price;
	}
	char* getItemName()//������ �̸��� ��ȯ�ϴ� �Լ�
	{
		return mName;
	}
	int getItemCount()// ������ ������ ��ȯ�ϴ� �Լ�
	{
		return mCount;
	}
	int getItemPrice()//������ ������ ��ȯ�ϴ� �Լ�
	{
		return mPrice;
	}
	///////////�������� ����� ����
	void setCategoryName(char* name)
	{
	}
	char* getCategoryName()
	{
		return 0;
	}
	/////////////////////////////
};