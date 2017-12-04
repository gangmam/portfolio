#include "CategoryList.h"

CategoryList::CategoryList(ofstream* fout) //생성자 
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
	//해당 카테고리 이름을 가지는 새로운 노드를 생성한다.
	// 오름차순으로 카테고리 이름을 가지는 리스트를 구성하기 위한 알고리즘
	if(cRoot == NULL)//리스트가 비어있을 경우
	{
		cRoot = newNode;
	}
	else 
	{
		pWalker = cRoot;
		// 건네 받은 카테고리 이름을 가지는 노드가 존재하는지를 판단하는 알고리즘
		while (pWalker != NULL)
		{
			if (strcmp(category, pWalker->getCategoryName()) == 0)// 존재하는 노드가 있다면
			{
				count++;
				delete newNode;
				break;//반복문 탈출
			}
			pWalker = pWalker->getNext();
		}
		if (count == 0)// 기존에 없던 카테고리 일 경우
		{
			///////////////////ItemList의 Insert함수와 알고리즘이 동일하기 때문에 주석 생략했습니다/////////////////
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
Node* CategoryList::getCategoryHead()//category List의 cRoot를 반환하는 ㅎ마수
{
	return cRoot;
}
Node* CategoryList::CategorySearch(char* category)//해당 되는 카테고리 명을 가지는 노드를 반환하는 함수 
{
	Node* pWalker = cRoot;
	while (pWalker != NULL)//모든 카테고리 리스트를 돌면서
	{
		if (strcmp(pWalker->getCategoryName(), category) == 0)// 입력받은 카테고리 명을 가지는 노드가 있다면
		{
			return pWalker;// 그노드를 반환한다.
		}
		pWalker = pWalker->getNext();
	}
}
Node* CategoryList::CategoryPrevSearch(char* category)// 해당 되는 카테고리 명을 가지는 노드의 이전노드를 반환하는 함수 DELETE함수 구현시 이용
{
	Node* pWalker = cRoot;
	Node* pPrev = NULL;
	while (pWalker != NULL)
	{
		if (strcmp(pWalker->getCategoryName(), category) == 0)
		{
			return pPrev;//해당 되는 카테고리 명을 가지는 노드의 이전노드를 반환
		}
		pPrev = pWalker;//pPrev는 해당되는 카테고리명을 가지는 노드의 이전 노드를 가르킴
		pWalker = pWalker->getNext();
	}
}
void CategoryList::setCategoryHead(Node* newNode)//cRoot의 값을 set 해주는 함수
{
	cRoot = newNode;
}