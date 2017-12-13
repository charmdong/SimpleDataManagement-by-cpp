#include "User.h"
#include "Main.h"

int main()
{
	vector<User> uList;
	vector<string> idList;
	
	menu(uList, idList);
	prn(uList);
	return 0;
}