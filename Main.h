#pragma once
#include "User.h"

char *menuList[] = { "1. Create Account", "2. Log in", "3. Delete Account" , "4. Edit Info","5. Exit"};
char *editList[] = { "1. Change PW", "2. Change Name" };

void menu(vector<User> &uList, vector<string> &idList);
void createUser(vector<User> &uList, vector<string> &lst);
pair<bool, int> checkID(vector<string> idList, string id);
void login();
void delUser(vector<User> &uList, vector<string> &idList);
void editInfo(vector<User> &uList, vector<string> &idList);
void prn(vector<User> &uList);
void myflush();

void menu(vector<User> &uList, vector<string> &idList) {
	int choice;

	while (1) {
		for (auto t : menuList)
			cout << t << endl;
		cout << ">> ";
		cin >> choice;

		if (cin.fail())
			myflush();

		switch (choice) {
		case 1: createUser(uList, idList); break;
		case 2: login(); break;
		case 3: delUser(uList, idList);  prn(uList); break;
		case 4: editInfo(uList, idList); break;
		case 5: cout << "\n* Exit the program ! *" << endl; break;
		default: cout << "\n* Wrong Selection ! *" << endl;
		}
		if (choice == 5)
			break;
	}
}

void createUser(vector<User> &uList, vector<string> &lst) {
	string id, pw, name;
	int birth;
	while (1) {
		cout << "Enter the ID to use : ";
		cin >> id;
		if (!(checkID(lst, id).first))
			break;
		cout << "\n* This ID is already existed ! *" << endl;
		myflush();
	}
	
	while (1) {
		cout << "Enter the PW to use : ";
		cin >> pw;
		if (User::checkSecurity(pw))
			break;
		cout << "\n* This password isn't Secure ! Try another PW *" << endl;
		myflush();
	}
	
	cout << "Enter your name : ";
	cin >> name;
	cout << "Enter your Birth year : ";
	cin >> birth;
	uList.push_back(User(id, pw, name, birth));
	lst.push_back(id);
	myflush();
}

/*
	이미 존재하는 id일 경우 : true
	존재하는 id가 아닌 경우 : false
*/
pair<bool, int> checkID(vector<string> idList, string id) {
	auto iter = find(idList.begin(), idList.end(), id);
	return iter != idList.end() ? pair<bool, int>(true, iter - idList.begin()) : pair<bool, int>(false, -1);
}

void login() {
	return;
}

void delUser(vector<User> &uList, vector<string> &idList) {
	string del,choice;
	pair<bool, int> tmp;
	while (1) {
		cout << "Enter the ID to delete : ";
		cin >> del;
		tmp = checkID(idList, del);
		if(tmp.first){
			cout << "\nAre you sure ? ";
			cin >> choice;
			if (choice == "y" || choice == "Y") {
				uList[tmp.second].info();
				uList.erase(uList.begin() + tmp.second, uList.begin() + tmp.second + 1);
				idList.erase(idList.begin() + tmp.second, idList.begin() + tmp.second + 1);
				cout << "\n* Deletion is completed ! *" << endl;
			}
			myflush();
			return;
		}
		cout << "\n* Cannot find the Informations of the ID !*\n" << endl;
		myflush();
	}
}

void editInfo(vector<User> &uList, vector<string> &idList) {
	string id;
	int choice;
	cout << "Enter the ID to Edit : ";
	cin >> id;
	pair<bool, int> tmp = checkID(idList, id);
	if (!tmp.first) {
		cout << "\n* There is no Data of this ID ! *" << endl;
		myflush();
		return;
	}

	cout << "\n< You can do only these 2 tasks >" << endl;
	for (auto t : editList)
		cout << t << endl;
	cout << ">> ";
	cin >> choice;
	
	switch (choice) {
	case 1: uList[tmp.second].changePW(); break;
	case 2: uList[tmp.second].changeName(); break;
	default: cout << "\nWrong Selection !" << endl; myflush();
	}
}

void prn(vector<User> &uList) {
	for (auto t : uList)
		t.info();
}

void myflush() {
	cin.clear();
	while (getchar() != '\n');
}