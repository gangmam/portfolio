#include "Manager.h"
#include "ItemList.h"
using namespace std;

int main(int argc, char** argv)
{
	if (!argv[1])
	{ 
		argv[1] = "command.txt";
	}
	Manager KW_IMS;
	KW_IMS.run(argv[1]);//Manager�� run�Լ��� �����Ѵ�. command.txt������ ��ɾ� ���Ϸ��Ѵ�.
	
	return 0;
}