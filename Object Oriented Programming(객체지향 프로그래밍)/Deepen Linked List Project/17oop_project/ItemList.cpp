#include "ItemList.h"

ItemList::ItemList(ofstream* fout) //생성자
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

void ItemList::ItemInsert(Node* newNode)//ItemList에 노드를 삽입하는 함수(이름비교를 통해 오름차순으로 노드를 삽입한다.)
{
	Node* pWalker = NULL;
	Node* pPrev = NULL;
	if (iRoot == NULL)//리스트가 비어있을 경우
	{
		iRoot = newNode;
	}
	else if (iRoot->getNext() == NULL)//리스트에 노드가 1개만 있을경우
	{
		if (strcmp(iRoot->getItemName(), newNode->getItemName()) < 0)//이름값의 비교를 통해 새로운 노드에 대한 포인터연결을 수정한다.
		{
			iRoot->setNext(newNode);
		}
		else if (strcmp(iRoot->getItemName(), newNode->getItemName()) > 0)
		{
			newNode->setNext(iRoot);
			iRoot = newNode;
		}
	}
	else//리스트에 여러개의 노드가 존재하는 경우 
	{
		pWalker = iRoot;
		while (pWalker->getNext() != NULL)//마지막 노드까지 가면서 새로운 노드가 들어갈 위치를 탐색한다.
		{
			if (strcmp(pWalker->getItemName(), newNode->getItemName()) < 0)//이름 값의 비교를 실시
			{
				pPrev = pWalker;
				pWalker = pWalker->getNext();
				if (pWalker->getNext() == NULL)//탐색중에 ItemList의 마지막 노드에 도착했을 경우 
				{
					if (strcmp(pWalker->getItemName(), newNode->getItemName()) > 0)//마지막 노드에서의 값의 비교를 실시한뒤 포인터 연결을 수정한다.
					{
						pPrev->setNext(newNode);
						newNode->setNext(pWalker);
					}
					else if (strcmp(pWalker->getItemName(), newNode->getItemName()) < 0)
					{
						pWalker->setNext(newNode);
					}
					break;//노드의 삽입이 끝났으므로 반복문 탈출
				}
			}
			else if(strcmp(pWalker->getItemName(), newNode->getItemName()) > 0)
			{
				if (pPrev == NULL)//pPrev의 값이 지정되지않았을 경우
				{
					newNode->setNext(pWalker);//처음 pWalker 노드의 이름값이 newNode 이름값보다 큰 값을 가졌을 경우 
					iRoot = newNode;//iRoot의 값을 바꿔준다.
				}
				else//pPrev의 값이 지정되었을 경우 포인터 연결을 수정한다.
				{
					pPrev->setNext(newNode);
					newNode->setNext(pWalker);
				}
				break;//노드의 삽입을 완료했으므로 반복문을 탈출한다.
			}
		}	
	}
}
Node* ItemList::ItemSearch(char* name)// 물품의 이름을 전달받아서 해당되는 물품의 이름을 가지는 노드를 반환하는 함수
{
	Node* pWalker = iRoot;
	while (pWalker != NULL)// 모든 ItemList를 돌면서 탐색
	{
		if (strcmp(name, pWalker->getItemName()) == 0)//해당되는 이름을 가지는 물품노드가 존재하는경우
		{
			return pWalker;// 해당되는 노드를 반환
		}
		pWalker = pWalker->getNext();
	}
}
Node* ItemList::ItemPrevSearch(char* name)//해당 되는 이름을 가지는 물품 노드의 이전노드를 반환하는 함수 DELETE 함수 구현시 이용
{
	//알고리즘은 ItemSearch함수와 같습니다.
	Node* pWalker = iRoot;
	Node* pPrev = NULL;
	while (pWalker != NULL)
	{
		if (strcmp(name, pWalker->getItemName()) == 0)
		{
			return pPrev;//이전 노드를 반환
		}
		pPrev = pWalker;//pWalker의 이전 노드를 pPrev로 지정한다.
		pWalker = pWalker->getNext();
	}
}
Node* ItemList::getCategory(char* name)//해당 되는 이름을 가지는 ItemList 노드의 카테고리노드를 반환하는 함수
{
	Node* pWalker = iRoot;
	Node* pPrev = NULL;
	pWalker = ItemSearch(name);
	while (pWalker != NULL)//pWalker가 계속해서 위로 올라가고 pPrev는 pWalker이전의 노드의 위치를 가르키게 된다.
	{
		//pWalker가 NULL이 될때 까지 반복하므로 pPrev는 카테고리 노드를 가르키게 된다.
		pPrev = pWalker;
		pWalker = pWalker->getUp();
	}
	return pPrev;//카테고리노드를 반환
}
Node* ItemList::getItemHead()// iRoot의 값을 반환하는 함수
{
	return iRoot;
}
void ItemList::setItemHead(Node* newNode)//iRoot의 값을 set해주는 함수 
{
	iRoot = newNode;
}