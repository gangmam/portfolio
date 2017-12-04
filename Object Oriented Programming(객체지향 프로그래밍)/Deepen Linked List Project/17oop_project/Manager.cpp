#include "Manager.h"
#include <cstring>
#pragma warning(disable:4996)

Manager::Manager()//Manager ������
{
	fout.open("log.txt", ios::app);
	cList = new CategoryList(&fout);
	iList = new ItemList(&fout);
}

Manager::~Manager()//Manager�Ҹ���
{
	delete cList;
	delete iList;
	fout.close();
}

void Manager::run(const char* fileName)// command.txt�� �о�´�� ���Լ��� ������Ѽ� ���α׷��� ���۽�Ű�� �Լ�
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

	while (!fin.eof())// �о�� ��ɾ���� �� �Լ��� ����
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

bool Manager::LOAD()// item.txt������ �о�ͼ� ��ũ�帮��Ʈ�� �����ϴ� �Լ� 
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
	while (fin.getline(buf, 100))// item.txt������ ���پ� �о�ͼ� Node�� ������ �����ѵ� ��ũ�帮��Ʈ�� �����Ѵ�.
	{
		Node* temp = NULL;
		Node* pPrev = NULL;
		Node* pWalker = NULL;
		Node* newNode = new ItemNode;// Item�� ������ ������ Node�� �����Ҵ�
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
		// ���� �����Ҵ��� ��忡 �� ������ �����Ѵ�.
		cList->CategoryInsert(category);//CategoryLIst�� ����
		iList->ItemInsert(newNode);//ItemList�� ����
		//////////Up Down ������ ����/////////
		temp = cList->CategorySearch(category);// temp = �ش� categoryname�� ������ ��� 
		if (temp->getDown() == NULL)// category�� Item�� ��� ���� ���� ���
		{
			temp->setDown(newNode);
			newNode->setUp(temp);
		}
		else if (temp->getDown()->getDown() == NULL)//category�� Item�� �Ѱ��� �����ϴ� ���
		{
			pWalker = temp->getDown();
			if (strcmp(pWalker->getItemName(), newNode->getItemName()) < 0)// ���� �񱳸� ���� ������������ ���� �����ϰ� ������ ������ �����Ѵ�.
			{
				pWalker->setDown(newNode);
				newNode->setUp(pWalker);
			}
			else if (strcmp(pWalker->getItemName(), newNode->getItemName()) > 0)//// ���� �񱳸� ���� ������������ ���� �����ϰ� ������ ������ �����Ѵ�.
			{
				newNode->setDown(pWalker);
				newNode->setUp(temp);
				pWalker->setUp(newNode);
				temp->setDown(newNode);
			}
		}
		else//category�� �������� Item�� �����ϴ� ��� 
		{
			pWalker = temp->getDown();
			////////////////////////////////
			while (pWalker->getDown() != NULL)//�ش�ī�װ��� ������ Node�� getDown�Ҷ� ���� �ݺ�
			{
				if (strcmp(pWalker->getItemName(), newNode->getItemName()) < 0)// ���� �񱳸� ���� �� ��ġ�� Ž���Ѵ�
				{
					pPrev = pWalker;
					pWalker = pWalker->getDown();
					if (pWalker->getDown() == NULL)// pWalker�� �ش� ī�װ��� ������ ��忡 �ش�ȴٸ�
					{
						if (strcmp(pWalker->getItemName(), newNode->getItemName()) > 0)// ���� �񱳸� ���� �� ��ġ�� Ž���ϰ� ������ ������ �����Ѵ�
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
						break;// ����� ������ ����Ǿ��� ������ �ݺ����� Ż��
					}
				}
				else if (strcmp(pWalker->getItemName(), newNode->getItemName()) > 0)
				{
					if (pPrev == NULL)//pPrev�� ���� �����Ǿ����� ���� ��� => ó�� pWalker�� ��ġ�� ���ο� ����� �̸����� ū �̸��� ������ ���� ���
					{
						newNode->setDown(pWalker);
						pWalker->setUp(newNode);
						temp->setDown(newNode);
						newNode->setUp(temp);
					}
					else// �ش�Ǵ� ������ ������ �����Ѵ�.(Up, Down)
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
	fin.close();// item.txt ������ close�Ѵ�.
	fout << "success" << endl << endl;
	return true;
}
bool Manager::ADD(char * arg)// ��ǰ�� ������ �߰��ϰų� ��ǰ�� ��ũ�� ����Ʈ�� �߰��ϴ� �Լ� 
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
	if (arr == NULL)// ��ǰ�� ������ �߰��ϴ°��
	{
		if (atoi(category) < 1)// ������ ���� ������ �ƴҰ���� ����ó��
		{
			fout << "error" << endl << endl;
			return false;
		}
		if (iList->ItemSearch(name) == NULL)// �ش� �Ǵ� ��ǰ�� �������� ���� ��쿡 ���� ����ó��
		{
			fout << "error" << endl << endl;
			return false;
		}
		iList->ItemSearch(name)->setItemCount(iList->ItemSearch(name)->getItemCount() + atoi(category));
		// ��������� �߰��� ������ ���Ѱ��� ���������� �����Ѵ�.
	}
	else// ��ǰ�� �߰��ϴ°�� 
	{
		if (iList->ItemSearch(name) != NULL)// �ش�Ǵ� ��ǰ�� �̹� �����ϴ� ��쿡 ���� ����ó��
		{
			fout << "error" << endl << endl;
			return false;
		}
		count = atoi(arr);
		arr = strtok(NULL, " ");
		price = atoi(arr);
		if (count < 1 || price < 1)// �Է¹��� ������ ������ ���� ������ �ƴҰ�쿡 ���� ����ó��
		{
			fout << "error" << endl << endl;
			return false;
		}
		/////////�̺κ� ���ʹ� LOAD������ ��ũ�� ����Ʈ ���� �κа� �����ϱ⶧���� �ּ��� �����ϰڽ��ϴ�./////
		Node* newNode = new ItemNode;
		Node* temp = NULL;
		Node* pWalker = NULL;
		Node* pPrev = NULL;
		newNode->setItemName(name);
		newNode->setItemPrice(price);
		newNode->setItemCount(count);

		cList->CategoryInsert(category);
		iList->ItemInsert(newNode);
		//////////updown������ �����Ѵ�/////////
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

bool Manager::MODIFY(char * arg)//�Է¹��� ��ǰ�� ������ �����ϴ� �Լ�
{
	fout << "[MODIFY]" << endl;
	char* arr = NULL;
	char name[100] = { 0 };
	int price = 0;

	arr = strtok(arg, " ");
	strcpy(name, arr);
	arr = strtok(NULL, " ");
	price = atoi(arr);
	if (price < 1)// ������ ���������� �ƴҰ�쿡 ���� ����ó�� 
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)//����Ʈ�� �������� �������� ���� ����ó��
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (iList->ItemSearch(name) == NULL)// �Է¹��� ��ǰ�� �������� �������� ���� ����ó��
	{
		fout << "error" << endl << endl;
		return false;
	}
	else
	{
		iList->ItemSearch(name)->setItemPrice(price);// �Է¹��� ��ǰ�� ������ ����
	}
	fout << "success" << endl << endl;
	return true;
}

bool Manager::SELL(char * arg)//�Է¹��� ��ǰ�� count��ŭ �Ǹ��ϴ� �Լ�
{
	fout << "[SELL]" << endl;
	char* arr = NULL;
	char name[100] = { 0 };
	int new_count = 0;
	ofstream qout;
	qout.open("sell.txt", ios::app);// sell.txt�� �Ǹ� ����� �̾ �ۼ�

	arr = strtok(arg, " ");
	strcpy(name, arr);
	arr = strtok(NULL, " ");
	new_count = atoi(arr);
	if (new_count < 1)// �Է¹��� count�� ���� ������ �ƴҰ�쿡 ���� ����ó��
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)// ����Ʈ�� ���� ���� �������� ���� ����ó��
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (iList->ItemSearch(name)->getItemCount() < new_count)// �Է¹��� count������ �ش� ��ǰ�� count�� �� ���� ���� ���� ����ó��
	{
		fout << "error" << endl << endl;
		return false;//error
	}
	iList->ItemSearch(name)->setItemCount(iList->ItemSearch(name)->getItemCount() - new_count);// �ش繰ǰ�� ������ �Է¹��� count���� �� �������� �����Ѵ�.
	qout << name << " " << new_count * iList->ItemSearch(name)->getItemPrice() << endl;
	// sell.txt�� �Ǹ��� ��ǰ�� ������ �����Ѵ�.
	qout.close();// sell.txt�� �ݴ´�.
	fout << "success" << endl << endl;
	return true;
}

bool Manager::DELETE(char * arg)// �Է¹޴� ��ǰ�� �����ϴ� �Լ�
{
	fout << "[DELETE]" << endl;
	char* arr = NULL;
	arr = strtok(arg, " ");
	Node* temp = iList->ItemSearch(arr);
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)//����Ʈ�� ���� ���� �ʴ� ��쿡 ���� ����ó��
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (iList->ItemSearch(arr) == NULL)//�Է¹��� ��ǰ�� �������� �ʴ� ��쿡 ���� ����ó��
	{
		fout << "error" << endl << endl;
		return false;
	}
	Node* pCate = iList->getCategory(arr);//�Է¹��� ��ǰ�� ī�װ� ���
	Node* pPrev = temp->getUp();
	if (temp == iList->getItemHead())// �����Ϸ��� ��尡 ItempList�� head�ϰ��
	{
		iList->setItemHead(temp->getNext());
	}
	else if (temp->getNext() == NULL)// �����Ϸ��� ��尡 ItemList�� ����������ϰ��
	{
		iList->ItemPrevSearch(arr)->setNext(NULL);
	}
	else// �����Ϸ��� ��尡 ItemList�� �߰��� ���� ��� 
	{
		iList->ItemPrevSearch(arr)->setNext(temp->getNext());
	}
	if (temp->getDown() == NULL)////ī�װ����� ���� ������ ����ϰ��
	{
		temp->getUp()->setDown(NULL);
		delete temp;
		///////////////////////////////////
		if (pCate->getDown() == NULL)// ī�װ��� ��� ���� ���
		{
			if (pCate == cList->getCategoryHead())//category List���� head�ϰ��
			{
				cList->setCategoryHead(pCate->getNext());
				delete pCate;
			}
			else if (pCate->getNext() == NULL)// category List���� ������ ����� ���
			{
				cList->CategoryPrevSearch(pCate->getCategoryName())->setNext(NULL);
				delete pCate;
			}
			else// category List���� �߰��� ���� ���
			{
				cList->CategoryPrevSearch(pCate->getCategoryName())->setNext(pCate->getNext());
				delete pCate;
			}
		}
		///////////////////////////////////
	}
	else if (pCate->getDown() == temp)//ī�װ� �ٷ� �� ����� ���
	{
		pCate->setDown(temp->getDown());
		temp->getDown()->setUp(pCate);
		delete temp;
	}
	else//�ش� ī�װ����� �߰��� ����� ���
	{
		pPrev->setDown(temp->getDown());
		temp->getDown()->setUp(pPrev);
		delete temp;
	}
	fout << "success" << endl << endl;
	return true;
}

bool Manager::SEARCH(char * arg)// �Է¹��� �ѱ���, �Ѵܾ ������ Ž�� �� ��� �ϴ� �Լ�
{
	fout << "[SEARCH]" << endl;
	int pc = 0;
	char* arr = NULL;
	char initial[100] = { 0 };
	char word[100] = { 0 };
	arr = strtok(arg, " ");
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)//����Ʈ�� �������� ������쿡 ���� ����ó��
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (arr[1] == NULL)//�ѱ��ڸ� ���°��
	{
		Node* pWalker = iList->getItemHead();//pWalker�� ��ġ�� ItemLsit�� head�� ��ġ�� �����Ѵ�.
		while (pWalker != NULL)//ItemList�� head���� ����Ʈ�� ������ ���� �ݺ�Ž��
		{
			if (pWalker->getItemName()[0] == arr[0])//���� �� ���ڷ� �����ϴ� �ܾ �����ϴ°��
			{
				// �� ����� ������ ���
				cout << pWalker->getItemName() << " " << iList->getCategory(pWalker->getItemName())->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				fout << pWalker->getItemName() << " " << iList->getCategory(pWalker->getItemName())->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				pc++;
			}
			pWalker = pWalker->getNext();
		}
	}
	else//�ܾ ���������
	{
		int count = 0;
		int length = 0;
		Node* pWalker = iList->getItemHead();
		while (pWalker != NULL)
		{
			length = strlen(arr);
			for (int q = 0 ; q < strlen(pWalker->getItemName()) ; q++)//�ش� ��忡�� �ܾ �����ϴ� ���� �Ǵ��ϴ� �˰���
			{
				count = 0;
				for (int a = 0; a < length && q+a < strlen(pWalker->getItemName()) ; a++)//pWalker����� �̸��� �ѱ��ھ� ��ȯ�ϸ鼭 �ش� �ܾ �ִ����� Ž��
				{
					if (arr[a] == pWalker->getItemName()[q + a])
					{
						count++;//������ ���ڰ� �����ϴ°�� ++
					}
					if (count == length)//������ �ܾ �����ϴ°��
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
	if (pc == 0)//����ϴ� ������� ������ ���
	{
		cout << "No Result" << endl << endl;
		fout << "No Result" << endl << endl;
	}
	cout << endl;
	fout << endl;
	return true;
}

bool Manager::PRINT(char* arg)// ��ǰ�� ������ ����ϴ� �Լ�
{
	fout << "[PRINT]" << endl;
	int pc = 0;
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)// ����Ʈ�� �������� �ʴ°���� ����ó��
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (strcmp(arg, "\0") == 0) // PRINT�� �������ڰ� ������ ī�װ����� ��� ��ǰ�� ���
	{
		Node* temp = NULL;
		Node* pWalker = NULL;
		temp = cList->getCategoryHead();// temp => Category Node�� �ش��Ѵ�
		while (temp->getNext() != NULL)// ī�װ� ��带 ��ȯ�ϸ鼭 �ش� ī�װ��� ItemList�� ������ ���
		{
			cout << "<" << temp->getCategoryName() << ">" << endl;
			fout << "<" << temp->getCategoryName() << ">" << endl;
			pWalker = temp->getDown();
			while (pWalker != NULL)//�ش� category�� ��� ItemList�� ���
			{
				cout << pWalker->getItemName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				fout << pWalker->getItemName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				pc++;
				pWalker = pWalker->getDown();
			}
			temp = temp->getNext();
		}
		// ������ category Node������ ItemList�� ���
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
	else //PRINT�� �������ڷ� category�� �Է¹޾��� �� �ش� category�� ItemList���� ���
	{
		char* arr = NULL;
		arr = strtok(arg, " ");
		Node* temp = NULL;
		Node* pWalker = NULL;
		temp = cList->CategorySearch(arr);
		pWalker = temp->getDown();
		// �ش� ī�װ��� ItemList���� ����Ѵ�
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
	if (pc == 0)//��µǴ� ������� ������ ��� 
	{
		cout << "No Result" << endl;
	}
	cout << endl;
	fout << endl;
	return true;
}
bool Manager::MANAGE(char * arg)
{
	//MANAGE ������� ä�����
	//�������ڰ� �ϳ��� ������� ������ ��ǰ���� �̸��� �������� �������� ���
	// �������ڰ� 2���� ���� ���������� ��ǰ�鿡 ä�� ������ ������ �߰��ϰ� �װ�����
	fout << "[MANAGE]" << endl;
	int pc = 0;
	char* arr = NULL;
	int cur_count = 0;
	int fill_count = 0;
	arr = strtok(arg, " ");
	cur_count = atoi(arr);
	arr = strtok(NULL, " ");
	if (cur_count < 1)// �Է¹��� �������ڰ� ���� ������ �ƴҶ��� ���� ����ó��
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)//����Ʈ�� ���� ���� ���� ���� ���� ����ó��
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (arr == NULL)//�������ڰ� �Ѱ��ΰ��
	{
		Node* pWalker = NULL;
		//ItemList�� ó������ ������ ���鼭 Ž���� �ǽ��Ѵ�
		for(pWalker = iList->getItemHead() ; pWalker != NULL ; pWalker = pWalker -> getNext())
		{
			if (pWalker->getItemCount() <= cur_count)// �Է¹��� ���������� ��ǰ�� ���� ��� �� ��ǰ�� ������ ���
			{
				cout << pWalker->getItemName() << " " << iList->getCategory(pWalker->getItemName())->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				fout << pWalker->getItemName() << " " << iList->getCategory(pWalker->getItemName())->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				pc++;
			}
		}
	}
	else// �������ڰ� 2���ΰ��
	{
		fill_count = atoi(arr);
		if (fill_count < 1)// �Է¹��� �������ڰ� ���� ������ �ƴҶ��� ���� ����ó��
		{
			fout << "error" << endl << endl;
			return false;
		}
		Node* pWalker = NULL;
		//ItemList�� ó������ ������ ���鼭 Ž���� �ǽ��Ѵ�
		for (pWalker = iList->getItemHead(); pWalker != NULL; pWalker = pWalker->getNext())
		{
			if (pWalker->getItemCount() <= cur_count)// �Է¹��� ���������� ��ǰ�� ���� ��� �� ��ǰ�� ������ �߰��Ѵ�
			{
				pWalker->setItemCount(pWalker->getItemCount() + fill_count);// ��������� ä�� ������ �߰�
				cout << pWalker->getItemName() << " " << iList->getCategory(pWalker->getItemName())->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				fout << pWalker->getItemName() << " " << iList->getCategory(pWalker->getItemName())->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
				pc++;
			}
		}
	}
	if (pc == 0)// ����� ������� ���� ��� 
	{
		cout << "No Result" << endl;
	}
	cout << endl;
	fout << endl;
	return true;
}

bool Manager::SALES(char * arg)//��ǰ�� �Ǹž� ���� �� �� ������ ����ϴ� �Լ�
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
	if (rank < 1)//�Է� ���� ������ ���� ������ �ƴҶ��� ���� ����ó��
	{
		fout << "error" << endl << endl;
		return false;
	}
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)//����Ʈ�� �������� �������� ���� ����ó��
	{
		fout << "error" << endl << endl;
		return false;
	}
	ifstream fin;
	fin.open("sell.txt");//sell.txt�� �����Ѵ�.
	while (fin.getline(buf, 100))// sell.txt�� ����� ������ ���پ� �о vector�� �����Ѵ�.
	{
		ItemNode* newNode = new ItemNode;
		arr = strtok(buf, " ");
		strcpy(name, arr);
		arr = strtok(NULL, " ");
		price = atoi(arr);
		newNode->setItemName(name);
		newNode->setItemPrice(price);
		//��带 ���Ӱ� �����ؼ� vector�� �����Ѵ�.
		vector<ItemNode*>::iterator it;
		// �Ǹž� �������� ��������, �Ǹž��� �ٸ� �̸����� ������������ ����ϱ� ���� �˰���
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
		if (vItem.size() == 0)//���Ͱ� ������� ���
		{
			vItem.push_back(newNode);
		}
		else// ���Ͱ� ������� ���� ��� 
		{
			it = vItem.begin();// ���ͷ������� ��ġ�� vItem�� ������ġ�� �д�.
			while (1)
			{
				if (it == vItem.end())//newNode�� ������ �������� ���ԵǾ� �Ǵ� ���
				{
					vItem.push_back(newNode);
					break;
				}
				if ((*it)->getItemPrice() < newNode->getItemPrice())// ���ο� ����� ������ ��ū ������ ���  newNode, it ������ ���Ϳ� ����ǰ� �ȴ�.��
				{
					vItem.insert(it, newNode);
					break;
				}
				else if ((*it)->getItemPrice() == newNode->getItemPrice())// �Ǹž��� ������� �̸����� �񱳸� �ǽ�
				{
					if (strcmp((*it)->getItemName(), newNode->getItemName()) > 0)//it�� �̸��� �� Ŭ��� newNode. it ������ ���Ϳ� ����ȴ�.
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
	if (vItem.size() == 0)// ���Ͱ� ��� �ִٸ� 
	{
		cout << "No Result" << endl;
		fout << "No Result" << endl;
	}
	// ���Ͱ� ������ ���� Ȥ�� �Է¹��� rank�� ����ŭ ������ ������ ó������ ����Ѵ�
	for (it = vItem.begin(); it != vItem.end() && count < rank ; it++)
	{
		cout << (*it)->getItemName() << " - " << (*it)->getItemPrice() << endl;
		fout << (*it)->getItemName() << " - " << (*it)->getItemPrice() << endl;
		count++;
	}
	for (it = vItem.begin(); it != vItem.end() ; it++)
	{
		total += (*it)->getItemPrice();// �Ѿ��� ����ϱ� ���ؼ�
	}
	cout << "Total - " << total << endl;
	fout << "Total - " << total << endl;
	for (it = vItem.begin(); it != vItem.end() ; it++)
	{
		delete (*it);
	}
	vItem.clear();//������ �ʱ�ȭ
	cout << endl;
	fout << endl;
	return true;
}

bool Manager::SAVE()//��ũ�� ����Ʈ�� item.txt�� �����ϴ� �Լ�
{
	fout << "[SAVE]" << endl;
	ofstream qout;
	qout.open("item.txt");
	Node* temp = NULL;
	Node* pWalker = NULL;
	if (iList->getItemHead() == NULL || cList->getCategoryHead() == NULL)//����Ʈ�� ���� ���� �ʴ� ��쿡 ���� ����ó��
	{
		fout << "error" << endl << endl;
		return false;
	}
	temp = cList->getCategoryHead();
	while (temp->getNext() != NULL)//ī�װ��� ó������ ���鼭 �ش� ī�װ��� ItemList�� ������ ���
	{
		pWalker = temp->getDown();
		while (pWalker != NULL)// �ش� ī�װ��� ��� ItemList�� ������ ���
		{
			qout << pWalker->getItemName() << " " << temp->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
			pWalker = pWalker->getDown();
		}
		temp = temp->getNext();
	}
	pWalker = temp->getDown();
	while (pWalker != NULL)//������ ī�װ���忡���� ItemList�� ������ ����Ѵ�.
	{
		qout << pWalker->getItemName() << " " << temp->getCategoryName() << " " << pWalker->getItemCount() << " " << pWalker->getItemPrice() << endl;
		pWalker = pWalker->getDown();
	}
	qout.close();
	cout << "success" << endl << endl;
	fout << "success" << endl << endl;
	return true;
}