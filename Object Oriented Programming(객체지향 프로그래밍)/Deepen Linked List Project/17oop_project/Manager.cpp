#include "Manager.h"
#include <cstring>
#pragma warning(disable:4996)

Manager::Manager()//Manager 생성자
{
	fout.open("log.txt", ios::app);
	cList = new CategoryList(&fout);
	iList = new ItemList(&fout);
}

Manager::~Manager()//Manager소멸자
{
	delete cList;
	delete iList;
	fout.close();
}

void Manager::run(const char* fileName)// command.txt를 읽어온대로 각함수를 실행시켜서 프로그램을 동작시키는 함수
{
	ifstream fin;
	fin.open(fileName);

	if (!fin) {
		cout << "[OPEN]" << endl << "error" << endl;
		return;
	}

	char cmd[64] = { 0 };
	char arg[64] = { 0 };

	bool isWork = true;	

	while (!fin.eof())// 읽어온 명령어에대한 각 함수의 실행
	{
		fin >> cmd;
		fin.getline(arg, 64);

		if		(!strcmp(cmd, "LOAD"))		{	isWork = LOAD();		}
		else if (!strcmp(cmd, "ADD"))		{	isWork = ADD(arg);		}
		else if (!strcmp(cmd, "MODIFY"))	{	isWork = MODIFY(arg);	}
		else if (!strcmp(cmd, "SELL"))		{	isWork = SELL(arg);		}
		else if (!strcmp(cmd, "DELETE"))	{	isWork = DELETE(arg);	}
		else if (!strcmp(cmd, "SEARCH"))	{	isWork = SEARCH(arg);	}
		else if (!strcmp(cmd, "PRINT"))		{	isWork = PRINT(arg);	}
		else if (!strcmp(cmd, "MANAGE"))	{	isWork = MANAGE(arg);	}
		else if (!strcmp(cmd, "SALES"))		{	isWork = SALES(arg);	}
		else if (!strcmp(cmd, "SAVE"))		{	isWork = SAVE();		}
		else								{	isWork = false;			}

		cout << "[" << cmd << "]" << endl;

		if (isWork == false) {
			cout << "error" << endl << endl;
		}
	}	
	
	fin.close();
}

bool Manager::LOAD()// item.txt파일을 읽어와서 링크드리스트에 삽입하는 함수 
{
	fout << "[LOAD]" << endl;
	char* arr = NULL;
	char buf[100] = { 0 };
	ifstream fin;

	char name[100] = { 0 };
	char category[100] = { 0 };
	int count = 0;
	int price = 0;

	fin.open("item.txt");
	while (fin.getline(buf, 100))// item.txt파일을 한줄씩 읽어와서 Node에 정보를 저장한뒤 링크드리스트에 삽입한다.
	{
		Node* temp = NULL;
		Node* pPrev = NULL;
		Node* pWalker = NULL;
		Node* newNode = new ItemNode;// Item의 정보를 저장할 Node의 동적할당
		arr = strtok(buf, " ");
		strcpy(name, arr);

		arr = strtok(NULL, " ");
		strcpy(category, arr);

		arr = strtok(NULL, " ");
		count = atoi(arr);

		arr = strtok(NULL, " ");
		price = atoi(arr);

		newNode->setItemName(name);
		newNode->setItemPrice(price);
		newNode->setItemCount(count);
		// 새로 동적할당한 노드에 각 정보를 저장한다.
		cList->CategoryInsert(category);//CategoryLIst에 삽입
		iList->ItemInsert(newNode);//ItemList에 삽입
		//////////Up Down 포인터 연결/////////
		temp = cList->CategorySearch(category);// temp = 해당 categoryname을 가지는 노드 
		if (temp->getDown() == NULL)// category에 Item이 들어 있지 않은 경우
		{
			temp->setDown(newNode);
			newNode->setUp(temp);
		}
		else if (temp->getDown()->getDown() == NULL)//category에 Item이 한개만 존재하는 경우
		{
			pWalker = temp->getDown();
			if (strcmp(pWalker->getItemName(), newNode->getItemName()) < 0)// 값의 비교를 통해 오름차순으로 값을 삽입하고 포인터 연결을 수정한다.
			{
				pWalker->setDown(newNode);
				newNode->setUp(pWalker);
			}
			else if (strcmp(pWalker->getItemName(), newNode->getItemName()) > 0)//// 값의 비교를 통해 오름차순으로 값을 삽입하고 포인터 연결을 수정한다.
			{
				newNode->setDown(pWalker);
				newNode->setUp(temp);
				pWalker->setUp(newNode);
				temp->setDown(newNode);
			}
		}
		else//category에 여러개의 Item이 존재하는 경우 
		{
			pWalker = temp->getDown();
			////////////////////////////////
			while (pWalker->getDown() != NULL)//해당카테고리의 마지막 Node로 getDown할때 까지 반복
			{
				if (strcmp(pWalker->getItemName(), newNode->getItemName()) < 0)// 값의 비교를 통해 들어갈 위치를 탐색한다
				{
					pPrev = pWalker;
					pWalker = pWalker->getDown();
					if (pWalker->getDown() == NULL)// pWalker가 해당 카테고리의 마지막 노드에 해당된다면
					{
						if (strcmp(pWalker->getItemName(), newNode->getItemName()) > 0)// 값의 비교를 통해 들어갈 위치를 탐색하고 포인터 연결을 수정한다
						{
							pPrev->setDown(newNode);
							newNode->setUp(pPrev);
							pWalker->setUp(newNode);
							newNode->setDown(pWalker);
							//////////////////////////
						}
						else if (strcmp(pWalker->getItemName(), newNode->getItemName()) < 0)
						{
							pWalker->setDown(newNode);
							newNode->setUp(pWalker);
						}
						break;// 노드의 삽입이 종료되었기 때문의 반복문의 탈출
					}
				}
				else if (strcmp(pWalker->getItemName(), newNode->getItemName()) > 0)
				{
					if (pPrev == NULL)//pPrev의 값이 지정되어있지 않을 경우 => 처음 pWalker의 위치가 새로운 노드의 이름보다 큰 이름을 가지고 있을 경우
					{
						newNode->setDown(pWalker);
						pWalker->setUp(newNode);
						temp->setDown(newNode);
						newNode->setUp(temp);
					}
					else// 해당되는 포인터 연결을 수정한다.(Up, Down)
					{
						pPrev->setDown(newNode);
						newNode->setUp(pPrev);
						newNode->setDown(pWalker);
						pWalker->setUp(newNode);
					}
					break;
				}
			}
		}
	}
	fin.close();// item.txt 파일을 close한다.
	fout << "success" << endl << endl;
	return true;
}
bool Manager::ADD(char * arg)// 물품의 수량을 추가하거나 물품을 링크드 리스트에 추가하는 함수 
{
	fout << "[ADD]" << endl;
	char* arr = NULL;
	char name[100] = { 0 };
	char category[100] = { 0 };
	int count = 0;
	int price = 0;

	arr = strtok(arg, " ");
	strcpy(name, arr);
	arr = strtok(NULL, " ");
	strcpy(category, arr);
	arr = strtok(NULL, " ");
	if (arr == NULL)// 물품의 수량을 추가하는경우
	{
		if (atoi(category) < 1)// 수량이 양의 정수가 아닐경우의 예외처리
		{
			fout << "error" << endl << endl;
			return false;
		}
		if (iList->ItemSearch(name) == NULL)// 해당 되는 물품이 존재하지 않을 경우에 대한 예외처리
		{
			fout << "error" << endl << endl;
			return false;
		}
		iList->ItemSearch(name)->setItemCount(iList->ItemSearch(name)->getItemCount() + atoi(category));
		// 현재수량에 추가한 수량을 더한값을 수량값으로 저장한다.
	}
	else// 물품을 추가하는경우 
	{
		if (iList->ItemSearch(name) != NULL)// 해당되는 물품이 이미 존재하는 경우에 대한 예외처리
		{
			fout << "error" << endl << endl;
			return false;
		}
		count = atoi(arr);
		arr = strtok(NULL, " ");
		price = atoi(arr);
		if (count < 1 || price < 1)// 입력받은 수량과 가격이 양의 정수가 아닐경우에 대한 예외처리
		{
			fout << "error" << endl << endl;
			return false;
		}
		/////////이부분 부터는 LOAD에서의 링크드 리스트 삽입 부분과 동일하기때문에 주석을 생략하겠습니다./////
		Node* newNode = new ItemNode;
		Node* temp = NULL;
		Node* pWalker = NULL;
		Node* pPrev = NULL;
		newNode->setItemName(name);
		newNode->setItemPrice(price);
		newNode->setItemCount(count);

		cList->CategoryInsert(category);
		iList->ItemInsert(newNode);
		//////////updown연결을 시작한다/////////
		temp = cList->CategorySearch(category);
		if (temp->getDown() == NULL)
		{
			temp->setDown(newNode);
			newNode->setUp(temp);//
		}
		else if (temp->getDown()->getDown() == NULL)
		{
			pWalker = temp->getDown();
			if (strcmp(pWalker->getItemName(), newNode->getItemName()) < 0)
			{
				pWalker->setDown(newNode);
				newNode->setUp(pWalker);
			}
			else if (strcmp(pWalker->getItemName(), newNode->getItemName()) > 0)
			{
				newNode->setDown(pWalker);
				newNode->setUp(temp);//
				pWalker->setUp(newNode);//
				temp->setDown(newNode);
			}
		}
		else
		{
			pWalker = temp->getDown();
			////////////////////////////////
			while (pWalker->getDown() != NULL)
			{
				if (strcmp(pWalker->getItemName(), newNode->getItemName()) < 0)
				{
					pPrev = pWalker;
					pWalker = pWalker->getDown();
					if (pWalker->getDown() == NULL)
					{
						if (strcmp(pWalker->getItemName(), newNode->getItemName()) > 0)
						{
							pPrev->setDown(newNode);
							newNode->setUp(pPrev);
							pWalker->setUp(newNode);
							newNode->setDown(pWalker);
							//////////////////////////
						}
						else if (strcmp(pWalker->getItemName(), newNode->getItemName()) < 0)
						{
							pWalker->setDown(newNode);
							newNode->setUp(pWalker);
						}
						break;
					}
				}
				else if (strcmp(pWalker->getItemName(), newNode->getItemName()) > 0)
				{
					if (pPrev == NULL)
					{
						newNode->setDown(pWalker);
						pWalker->setUp(newNode);
						temp->setDown(newNode);
						newNode->setUp(temp);
					}
					else
					{
						pPrev->setDown(newNode);
						newNode->setUp(pPrev);
						newNode->setDown(pWalker);
						pWalker->setUp(newNode);
					}
					break;
				}
			}
		}
	}
	fout << "success" << endl << endl;
	return 1;
}

bool Manager::MODIFY(char * arg)//입력받은 물품의 가격을 수정하는 함수
{
	fout << "[MODIFY]" << endl;
	char* arr = NULL;
	char name[100] = { 0 };
	int price = 0;

	arr = strtok(arg, " ");
	strcpy(name, arr);
	arr = strtok(NULL, " ");
	price = atoi(arr);
	if (price < 1)// 가격의 양의정수가 아닐경우에 대한 예외처리 
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)//리스트가 존재하지 않을때에 대한 예외처리
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (iList->ItemSearch(name) == NULL)// 입력받은 물품이 존재하지 않을때에 대한 예외처리
	{
		fout << "error" << endl << endl;
		return false;
	}
	else
	{
		iList->ItemSearch(name)->setItemPrice(price);// 입력받은 물품의 가격을 수정
	}
	fout << "success" << endl << endl;
	return true;
}

bool Manager::SELL(char * arg)//입력받은 물품을 count만큼 판매하는 함수
{
	fout << "[SELL]" << endl;
	char* arr = NULL;
	char name[100] = { 0 };
	int new_count = 0;
	ofstream qout;
	qout.open("sell.txt", ios::app);// sell.txt에 판매 목록을 이어서 작성

	arr = strtok(arg, " ");
	strcpy(name, arr);
	arr = strtok(NULL, " ");
	new_count = atoi(arr);
	if (new_count < 1)// 입력받은 count가 양의 정수가 아닐경우에 대한 예외처리
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)// 리스트가 존재 하지 않을때에 대한 예외처리
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (iList->ItemSearch(name)->getItemCount() < new_count)// 입력받은 count수보다 해당 물품의 count가 더 작을 때에 대한 예외처리
	{
		fout << "error" << endl << endl;
		return false;//error
	}
	iList->ItemSearch(name)->setItemCount(iList->ItemSearch(name)->getItemCount() - new_count);// 해당물품의 수량을 입력받은 count수를 뺀 수량으로 수정한다.
	qout << name << " " << new_count * iList->ItemSearch(name)->getItemPrice() << endl;
	// sell.txt에 판매한 물품의 정보를 저장한다.
	qout.close();// sell.txt를 닫는다.
	fout << "success" << endl << endl;
	return true;
}

bool Manager::DELETE(char * arg)// 입력받는 물품을 삭제하는 함수
{
	fout << "[DELETE]" << endl;
	char* arr = NULL;
	arr = strtok(arg, " ");
	Node* temp = iList->ItemSearch(arr);
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)//리스트가 존재 하지 않는 경우에 대한 예외처리
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (iList->ItemSearch(arr) == NULL)//입력받은 물품이 존재하지 않는 경우에 대한 예외처리
	{
		fout << "error" << endl << endl;
		return false;
	}
	Node* pCate = iList->getCategory(arr);//입력받은 물품의 카테고리 노드
	Node* pPrev = temp->getUp();
	if (temp == iList->getItemHead())// 삭제하려는 노드가 ItempList의 head일경우
	{
		iList->setItemHead(temp->getNext());
	}
	else if (temp->getNext() == NULL)// 삭제하려는 노드가 ItemList의 마지막노드일경우
	{
		iList->ItemPrevSearch(arr)->setNext(NULL);
	}
	else// 삭제하려는 노드가 ItemList의 중간에 있을 경우 
	{
		iList->ItemPrevSearch(arr)->setNext(temp->getNext());
	}
	if (temp->getDown() == NULL)////카테고리에서 제일 마지막 노드일경우
	{
		temp->getUp()->setDown(NULL);
		delete temp;
		///////////////////////////////////
		if (pCate->getDown() == NULL)// 카테고리가 비어 있을 경우
		{
			if (pCate == cList->getCategoryHead())//category List에서 head일경우
			{
				cList->setCategoryHead(pCate->getNext());
				delete pCate;
			}
			else if (pCate->getNext() == NULL)// category List에서 마지막 노드일 경우
			{
				cList->CategoryPrevSearch(pCate->getCategoryName())->setNext(NULL);
				delete pCate;
			}
			else// category List에서 중간에 있을 경우
			{
				cList->CategoryPrevSearch(pCate->getCategoryName())->setNext(pCate->getNext());
				delete pCate;
			}
		}
		///////////////////////////////////
	}
	else if (pCate->getDown() == temp)//카테고리 바로 밑 노드일 경우
	{
		pCate->setDown(temp->getDown());
		temp->getDown()->setUp(pCate);
		delete temp;
	}
	else//해당 카테고리에서 중간의 노드일 경우
	{
		pPrev->setDown(temp->getDown());
		temp->getDown()->setUp(pPrev);
		delete temp;
	}
	fout << "success" << endl << endl;
	return true;
}

bool Manager::SEARCH(char * arg)// 입력받은 한글자, 한단어를 가지는 탐색 및 출력 하는 함수
{
	fout << "[SEARCH]" << endl;
	int pc = 0;
	char* arr = NULL;
	char initial[100] = { 0 };
	char word[100] = { 0 };
	arr = strtok(arg, " ");
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)//리스트가 존재하지 않을경우에 대한 예외처리
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (arr[1] == NULL)//한글자만 들어온경우
	{
		Node* pWalker = iList->getItemHead();//pWalker의 위치를 ItemLsit의 head의 위치로 지정한다.
		while (pWalker != NULL)//ItemList의 head부터 리스트가 끝날때 까지 반복탐색
		{
			if (pWalker->getItemName()[0] == arr[0])//들어온 한 글자로 시작하는 단어가 존재하는경우
			{
				// 그 노드의 정보를 출력
				cout << pWalker->getItemName() << " " << iList->getCategory(pWalker->getItemName())->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				fout << pWalker->getItemName() << " " << iList->getCategory(pWalker->getItemName())->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				pc++;
			}
			pWalker = pWalker->getNext();
		}
	}
	else//단어가 들어왓을경우
	{
		int count = 0;
		int length = 0;
		Node* pWalker = iList->getItemHead();
		while (pWalker != NULL)
		{
			length = strlen(arr);
			for (int q = 0 ; q < strlen(pWalker->getItemName()) ; q++)//해당 노드에서 단어가 존재하는 지를 판단하는 알고리즘
			{
				count = 0;
				for (int a = 0; a < length && q+a < strlen(pWalker->getItemName()) ; a++)//pWalker노드의 이름을 한글자씩 순환하면서 해당 단어가 있는지를 탐색
				{
					if (arr[a] == pWalker->getItemName()[q + a])
					{
						count++;//동일한 글자가 존재하는경우 ++
					}
					if (count == length)//동일한 단어가 존재하는경우
					{
						cout << pWalker->getItemName() << " " << iList->getCategory(pWalker->getItemName())->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
						fout << pWalker->getItemName() << " " << iList->getCategory(pWalker->getItemName())->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
						pc++;
					}
				}
			}
			pWalker = pWalker->getNext();
		}
	}
	if (pc == 0)//출력하는 결과물이 없었을 경우
	{
		cout << "No Result" << endl << endl;
		fout << "No Result" << endl << endl;
	}
	cout << endl;
	fout << endl;
	return true;
}

bool Manager::PRINT(char* arg)// 물품의 정보를 출력하는 함수
{
	fout << "[PRINT]" << endl;
	int pc = 0;
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)// 리스트가 존재하지 않는경우의 예외처리
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (strcmp(arg, "\0") == 0) // PRINT에 전달인자가 없을때 카테고리별로 모든 물품을 출력
	{
		Node* temp = NULL;
		Node* pWalker = NULL;
		temp = cList->getCategoryHead();// temp => Category Node에 해당한다
		while (temp->getNext() != NULL)// 카테고리 노드를 순환하면서 해당 카테고리의 ItemList의 정보를 출력
		{
			cout << "<" << temp->getCategoryName() << ">" << endl;
			fout << "<" << temp->getCategoryName() << ">" << endl;
			pWalker = temp->getDown();
			while (pWalker != NULL)//해당 category의 모든 ItemList를 출력
			{
				cout << pWalker->getItemName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				fout << pWalker->getItemName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				pc++;
				pWalker = pWalker->getDown();
			}
			temp = temp->getNext();
		}
		// 마지막 category Node에서의 ItemList의 출력
		cout << "<" << temp->getCategoryName() << ">" << endl;
		fout << "<" << temp->getCategoryName() << ">" << endl;
		pWalker = temp->getDown();
		while (pWalker != NULL)
		{
			cout << pWalker->getItemName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
			fout << pWalker->getItemName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
			pc++;
			pWalker = pWalker->getDown();
		}
	}
	else //PRINT의 전달인자로 category를 입력받았을 때 해당 category의 ItemList만을 출력
	{
		char* arr = NULL;
		arr = strtok(arg, " ");
		Node* temp = NULL;
		Node* pWalker = NULL;
		temp = cList->CategorySearch(arr);
		pWalker = temp->getDown();
		// 해당 카테고리의 ItemList만을 출력한다
		cout << "<" << temp->getCategoryName() << ">" << endl;
		fout << "<" << temp->getCategoryName() << ">" << endl;
		while (pWalker != NULL)
		{
			cout << pWalker->getItemName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
			fout << pWalker->getItemName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
			pc++;
			pWalker = pWalker->getDown();
		}
	}
	if (pc == 0)//출력되는 결과물이 없었을 경우 
	{
		cout << "No Result" << endl;
	}
	cout << endl;
	fout << endl;
	return true;
}
bool Manager::MANAGE(char * arg)
{
	//MANAGE 현재수량 채울수량
	//전달인자가 하나면 현재수량 이하의 물품들의 이름을 기준으로 오름차순 출력
	// 전달인자가 2개면 현재 수량이하의 물품들에 채울 수량을 실제로 추가하고 그결과출력
	fout << "[MANAGE]" << endl;
	int pc = 0;
	char* arr = NULL;
	int cur_count = 0;
	int fill_count = 0;
	arr = strtok(arg, " ");
	cur_count = atoi(arr);
	arr = strtok(NULL, " ");
	if (cur_count < 1)// 입력받은 전달인자가 양의 정수가 아닐때에 대한 예외처리
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)//리스트가 존재 하지 않을 때에 대한 예외처리
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (arr == NULL)//전달인자가 한개인경우
	{
		Node* pWalker = NULL;
		//ItemList를 처음부터 끝까지 돌면서 탐색을 실시한다
		for(pWalker = iList->getItemHead() ; pWalker != NULL ; pWalker = pWalker -> getNext())
		{
			if (pWalker->getItemCount() <= cur_count)// 입력받은 수량이하의 물품이 있을 경우 그 물품의 정보를 출력
			{
				cout << pWalker->getItemName() << " " << iList->getCategory(pWalker->getItemName())->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				fout << pWalker->getItemName() << " " << iList->getCategory(pWalker->getItemName())->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				pc++;
			}
		}
	}
	else// 전달인자가 2개인경우
	{
		fill_count = atoi(arr);
		if (fill_count < 1)// 입력받은 전달인자가 양의 정수가 아닐때에 대한 예외처리
		{
			fout << "error" << endl << endl;
			return false;
		}
		Node* pWalker = NULL;
		//ItemList를 처음부터 끝까지 돌면서 탐색을 실시한다
		for (pWalker = iList->getItemHead(); pWalker != NULL; pWalker = pWalker->getNext())
		{
			if (pWalker->getItemCount() <= cur_count)// 입력받은 수량이하의 물품이 있을 경우 그 물품의 수량을 추가한다
			{
				pWalker->setItemCount(pWalker->getItemCount() + fill_count);// 현재수량에 채울 수량을 추가
				cout << pWalker->getItemName() << " " << iList->getCategory(pWalker->getItemName())->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				fout << pWalker->getItemName() << " " << iList->getCategory(pWalker->getItemName())->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				pc++;
			}
		}
	}
	if (pc == 0)// 출력한 결과물이 없을 경우 
	{
		cout << "No Result" << endl;
	}
	cout << endl;
	fout << endl;
	return true;
}

bool Manager::SALES(char * arg)//물품별 판매액 순위 및 총 수익을 출력하는 함수
{
	fout << "[SALES]" << endl;
	char* arr = NULL;
	int control_value = 0;
	char name[100] = { 0 };
	char category[100] = { 0 };
	int price = 0;
	char buf[100] = { 0 };
	arr = strtok(arg, " ");
	int count = 0;
	int rank = atoi(arr);
	int total = 0;
	///////////////////////////////
	if (rank < 1)//입력 받은 순위가 양의 정수가 아닐때에 대한 예외처리
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)//리스트가 존재하지 않을때에 대한 예외처리
	{
		fout << "error" << endl << endl;
		return false;
	}
	ifstream fin;
	fin.open("sell.txt");//sell.txt를 오픈한다.
	while (fin.getline(buf, 100))// sell.txt에 저장된 정보를 한줄씩 읽어서 vector에 저장한다.
	{
		ItemNode* newNode = new ItemNode;
		arr = strtok(buf, " ");
		strcpy(name, arr);
		arr = strtok(NULL, " ");
		price = atoi(arr);
		newNode->setItemName(name);
		newNode->setItemPrice(price);
		//노드를 새롭게 생성해서 vector에 저장한다.
		vector<ItemNode*>::iterator it;
		// 판매액 기준으로 내림차순, 판매액이 다면 이름기준 오름차순으로 출력하기 위한 알고리즘
		//////////////////////////////////////////////////////////////////////////
		for (it = vItem.begin(); it != vItem.end(); it++)
		{
			if (strcmp((*it)->getItemName(), name) == 0)
			{
				//control_value++;
				newNode->setItemPrice(price + (*it)->getItemPrice());
				vItem.erase(it);
				break;
			}
		}
		/////////////////////////////////////////////////////////////////////////
		if (vItem.size() == 0)//백터가 비어있을 경우
		{
			vItem.push_back(newNode);
		}
		else// 벡터가 비어있지 않을 경우 
		{
			it = vItem.begin();// 이터레이터의 위치를 vItem의 시작위치로 둔다.
			while (1)
			{
				if (it == vItem.end())//newNode가 백터의 마지막에 삽입되야 되는 경우
				{
					vItem.push_back(newNode);
					break;
				}
				if ((*it)->getItemPrice() < newNode->getItemPrice())// 새로운 노드의 가격이 더큰 가격일 경우  newNode, it 순으로 벡터에 저장되게 된다.ㅏ
				{
					vItem.insert(it, newNode);
					break;
				}
				else if ((*it)->getItemPrice() == newNode->getItemPrice())// 판매액이 같은경우 이름으로 비교를 실시
				{
					if (strcmp((*it)->getItemName(), newNode->getItemName()) > 0)//it의 이름이 더 클경우 newNode. it 순으로 벡터에 저장된다.
					{
						vItem.insert(it, newNode);
						break;
					}
				}
				it++;

			}
		}
	}
	///////////////////////////////
	vector<ItemNode*>::iterator it;
	if (vItem.size() == 0)// 벡터가 비어 있다면 
	{
		cout << "No Result" << endl;
		fout << "No Result" << endl;
	}
	// 벡터가 끝날때 까지 혹은 입력받은 rank의 수만큼 벡터의 정보를 처음부터 출력한다
	for (it = vItem.begin(); it != vItem.end() && count < rank ; it++)
	{
		cout << (*it)->getItemName() << " - " << (*it)->getItemPrice() << endl;
		fout << (*it)->getItemName() << " - " << (*it)->getItemPrice() << endl;
		count++;
	}
	for (it = vItem.begin(); it != vItem.end() ; it++)
	{
		total += (*it)->getItemPrice();// 총액을 계산하기 위해서
	}
	cout << "Total - " << total << endl;
	fout << "Total - " << total << endl;
	for (it = vItem.begin(); it != vItem.end() ; it++)
	{
		delete (*it);
	}
	vItem.clear();//벡터의 초기화
	cout << endl;
	fout << endl;
	return true;
}

bool Manager::SAVE()//링크드 리스트를 item.txt에 저장하는 함수
{
	fout << "[SAVE]" << endl;
	ofstream qout;
	qout.open("item.txt");
	Node* temp = NULL;
	Node* pWalker = NULL;
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)//리스트가 존재 하지 않는 경우에 대한 예외처리
	{
		fout << "error" << endl << endl;
		return false;
	}
	temp = cList->getCategoryHead();
	while (temp->getNext() != NULL)//카테고리를 처음부터 돌면서 해당 카테고리의 ItemList의 정보를 출력
	{
		pWalker = temp->getDown();
		while (pWalker != NULL)// 해당 카테고리의 모든 ItemList의 정보를 출력
		{
			qout << pWalker->getItemName() << " " << temp->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
			pWalker = pWalker->getDown();
		}
		temp = temp->getNext();
	}
	pWalker = temp->getDown();
	while (pWalker != NULL)//마지막 카테고리노드에서의 ItemList의 정보를 출력한다.
	{
		qout << pWalker->getItemName() << " " << temp->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
		pWalker = pWalker->getDown();
	}
	qout.close();
	cout << "success" << endl << endl;
	fout << "success" << endl << endl;
	return true;
}