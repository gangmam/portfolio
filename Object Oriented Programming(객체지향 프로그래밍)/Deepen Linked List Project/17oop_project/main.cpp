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
	KW_IMS.run(argv[1]);//Manager의 run함수를 실행한다. command.txt파일을 명령어 파일로한다.
	
	return 0;
}