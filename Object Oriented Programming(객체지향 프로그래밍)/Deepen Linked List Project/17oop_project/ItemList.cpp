#include "ItemList.h"

ItemList::ItemList(ofstream* fout) //������
{
	this->fout = fout;
	iRoot = NULL;
}

ItemList::~ItemList()
{
	Node* pWalker = NULL;
	Node* pPrev = NULL;
	if (iRoot == NULL)
	{
		return;
	}
	else
	{
		pWalker = iRoot;
		while (pWalker != NULL)
		{
			pPrev = pWalker;
			pWalker = pWalker->getNext();
			delete pPrev;
		}
	}
}

void ItemList::ItemInsert(Node* newNode)//ItemList�� ��带 �����ϴ� �Լ�(�̸��񱳸� ���� ������������ ��带 �����Ѵ�.)
{
	Node* pWalker = NULL;
	Node* pPrev = NULL;
	if (iRoot == NULL)//����Ʈ�� ������� ���
	{
		iRoot = newNode;
	}
	else if (iRoot->getNext() == NULL)//����Ʈ�� ��尡 1���� �������
	{
		if (strcmp(iRoot->getItemName(), newNode->getItemName()) < 0)//�̸����� �񱳸� ���� ���ο� ��忡 ���� �����Ϳ����� �����Ѵ�.
		{
			iRoot->setNext(newNode);
		}
		else if (strcmp(iRoot->getItemName(), newNode->getItemName()) > 0)
		{
			newNode->setNext(iRoot);
			iRoot = newNode;
		}
	}
	else//����Ʈ�� �������� ��尡 �����ϴ� ��� 
	{
		pWalker = iRoot;
		while (pWalker->getNext() != NULL)//������ ������ ���鼭 ���ο� ��尡 �� ��ġ�� Ž���Ѵ�.
		{
			if (strcmp(pWalker->getItemName(), newNode->getItemName()) < 0)//�̸� ���� �񱳸� �ǽ�
			{
				pPrev = pWalker;
				pWalker = pWalker->getNext();
				if (pWalker->getNext() == NULL)//Ž���߿� ItemList�� ������ ��忡 �������� ��� 
				{
					if (strcmp(pWalker->getItemName(), newNode->getItemName()) > 0)//������ ��忡���� ���� �񱳸� �ǽ��ѵ� ������ ������ �����Ѵ�.
					{
						pPrev->setNext(newNode);
						newNode->setNext(pWalker);
					}
					else if (strcmp(pWalker->getItemName(), newNode->getItemName()) < 0)
					{
						pWalker->setNext(newNode);
					}
					break;//����� ������ �������Ƿ� �ݺ��� Ż��
				}
			}
			else if(strcmp(pWalker->getItemName(), newNode->getItemName()) > 0)
			{
				if (pPrev == NULL)//pPrev�� ���� ���������ʾ��� ���
				{
					newNode->setNext(pWalker);//ó�� pWalker ����� �̸����� newNode �̸������� ū ���� ������ ��� 
					iRoot = newNode;//iRoot�� ���� �ٲ��ش�.
				}
				else//pPrev�� ���� �����Ǿ��� ��� ������ ������ �����Ѵ�.
				{
					pPrev->setNext(newNode);
					newNode->setNext(pWalker);
				}
				break;//����� ������ �Ϸ������Ƿ� �ݺ����� Ż���Ѵ�.
			}
		}	
	}
}
Node* ItemList::ItemSearch(char* name)// ��ǰ�� �̸��� ���޹޾Ƽ� �ش�Ǵ� ��ǰ�� �̸��� ������ ��带 ��ȯ�ϴ� �Լ�
{
	Node* pWalker = iRoot;
	while (pWalker != NULL)// ��� ItemList�� ���鼭 Ž��
	{
		if (strcmp(name, pWalker->getItemName()) == 0)//�ش�Ǵ� �̸��� ������ ��ǰ��尡 �����ϴ°��
		{
			return pWalker;// �ش�Ǵ� ��带 ��ȯ
		}
		pWalker = pWalker->getNext();
	}
}
Node* ItemList::ItemPrevSearch(char* name)//�ش� �Ǵ� �̸��� ������ ��ǰ ����� ������带 ��ȯ�ϴ� �Լ� DELETE �Լ� ������ �̿�
{
	//�˰����� ItemSearch�Լ��� �����ϴ�.
	Node* pWalker = iRoot;
	Node* pPrev = NULL;
	while (pWalker != NULL)
	{
		if (strcmp(name, pWalker->getItemName()) == 0)
		{
			return pPrev;//���� ��带 ��ȯ
		}
		pPrev = pWalker;//pWalker�� ���� ��带 pPrev�� �����Ѵ�.
		pWalker = pWalker->getNext();
	}
}
Node* ItemList::getCategory(char* name)//�ش� �Ǵ� �̸��� ������ ItemList ����� ī�װ���带 ��ȯ�ϴ� �Լ�
{
	Node* pWalker = iRoot;
	Node* pPrev = NULL;
	pWalker = ItemSearch(name);
	while (pWalker != NULL)//pWalker�� ����ؼ� ���� �ö󰡰� pPrev�� pWalker������ ����� ��ġ�� ����Ű�� �ȴ�.
	{
		//pWalker�� NULL�� �ɶ� ���� �ݺ��ϹǷ� pPrev�� ī�װ� ��带 ����Ű�� �ȴ�.
		pPrev = pWalker;
		pWalker = pWalker->getUp();
	}
	return pPrev;//ī�װ���带 ��ȯ
}
Node* ItemList::getItemHead()// iRoot�� ���� ��ȯ�ϴ� �Լ�
{
	return iRoot;
}
void ItemList::setItemHead(Node* newNode)//iRoot�� ���� set���ִ� �Լ� 
{
	iRoot = newNode;
}