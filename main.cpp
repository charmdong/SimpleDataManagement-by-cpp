#include "User.h"
#include "Main.h"

void fileTest();

int main()
{
	vector<User> uList;
	vector<string> idList;
	
	menu(uList, idList);
	prn(uList);
	//fileTest();
	return 0;
}

void fileTest() {
	ofstream out(FILE, ios_base::app);
	string n;

	cin >> n;
	out << "\n" << n;
}