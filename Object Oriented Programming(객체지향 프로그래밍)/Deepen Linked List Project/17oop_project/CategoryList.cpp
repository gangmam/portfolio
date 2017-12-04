#include "CategoryList.h"

CategoryList::CategoryList(ofstream* fout) //������ 
{
	this->fout = fout;
	cRoot = NULL;
}

CategoryList::~CategoryList()
{
	Node* pWalker = NULL;
	Node* pPrev = NULL;
	if (cRoot == NULL)
	{
		return;
	}
	else
	{
		pWalker = cRoot;
		while (pWalker != NULL)
		{
			pPrev = pWalker;
			pWalker = pWalker->getNext();
			delete pPrev;
		}
	}
}

void CategoryList::CategoryInsert(char* category)
{
	int count = 0;
	Node* newNode = new CategoryNode;
	Node* pWalker = NULL;
	Node* pPrev = NULL;
	newNode->setCategoryName(category);
	//�ش� ī�װ� �̸��� ������ ���ο� ��带 �����Ѵ�.
	// ������������ ī�װ� �̸��� ������ ����Ʈ�� �����ϱ� ���� �˰���
	if(cRoot == NULL)//����Ʈ�� ������� ���
	{
		cRoot = newNode;
	}
	else 
	{
		pWalker = cRoot;
		// �ǳ� ���� ī�װ� �̸��� ������ ��尡 �����ϴ����� �Ǵ��ϴ� �˰���
		while (pWalker != NULL)
		{
			if (strcmp(category, pWalker->getCategoryName()) == 0)// �����ϴ� ��尡 �ִٸ�
			{
				count++;
				delete newNode;
				break;//�ݺ��� Ż��
			}
			pWalker = pWalker->getNext();
		}
		if (count == 0)// ������ ���� ī�װ� �� ���
		{
			///////////////////ItemList�� Insert�Լ��� �˰����� �����ϱ� ������ �ּ� �����߽��ϴ�/////////////////
			if (cRoot->getNext() == NULL)
			{
				if (strcmp(cRoot->getCategoryName(), category) < 0)
				{
					cRoot->setNext(newNode);
				}
				else if (strcmp(cRoot->getCategoryName(), category) > 0)
				{
					newNode->setNext(cRoot);
					cRoot = newNode;
				}
			}
			else
			{
				pWalker = cRoot;
				while (pWalker->getNext() != NULL)
				{
					if (strcmp(pWalker->getCategoryName(), category) < 0)
					{
						pPrev = pWalker;
						pWalker = pWalker->getNext();
						if (pWalker->getNext() == NULL)
						{
							if (strcmp(pWalker->getCategoryName(), category) > 0)
							{
								pPrev->setNext(newNode);
								newNode->setNext(pWalker);
							}
							else if (strcmp(pWalker->getCategoryName(), category) < 0)
							{
								pWalker->setNext(newNode);
							}
							break;
						}
					}
					else if (strcmp(pWalker->getCategoryName(), category) > 0)
					{
						if (pPrev == NULL)
						{
							newNode->setNext(pWalker);
							cRoot = newNode;
						}
						else
						{
							pPrev->setNext(newNode);
							newNode->setNext(pWalker);
						}
						break;
					}
				}
			}
			//////////////////////////////////////////////////////////////////////////
		}
	}
}
Node* CategoryList::getCategoryHead()//category List�� cRoot�� ��ȯ�ϴ� ������
{
	return cRoot;
}
Node* CategoryList::CategorySearch(char* category)//�ش� �Ǵ� ī�װ� ���� ������ ��带 ��ȯ�ϴ� �Լ� 
{
	Node* pWalker = cRoot;
	while (pWalker != NULL)//��� ī�װ� ����Ʈ�� ���鼭
	{
		if (strcmp(pWalker->getCategoryName(), category) == 0)// �Է¹��� ī�װ� ���� ������ ��尡 �ִٸ�
		{
			return pWalker;// �׳�带 ��ȯ�Ѵ�.
		}
		pWalker = pWalker->getNext();
	}
}
Node* CategoryList::CategoryPrevSearch(char* category)// �ش� �Ǵ� ī�װ� ���� ������ ����� ������带 ��ȯ�ϴ� �Լ� DELETE�Լ� ������ �̿�
{
	Node* pWalker = cRoot;
	Node* pPrev = NULL;
	while (pWalker != NULL)
	{
		if (strcmp(pWalker->getCategoryName(), category) == 0)
		{
			return pPrev;//�ش� �Ǵ� ī�װ� ���� ������ ����� ������带 ��ȯ
		}
		pPrev = pWalker;//pPrev�� �ش�Ǵ� ī�װ����� ������ ����� ���� ��带 ����Ŵ
		pWalker = pWalker->getNext();
	}
}
void CategoryList::setCategoryHead(Node* newNode)//cRoot�� ���� set ���ִ� �Լ�
{
	cRoot = newNode;
}