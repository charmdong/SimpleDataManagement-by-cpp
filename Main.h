#pragma once
#include <fstream>
#include "User.h"
#define FILE "User.txt"

char *menuList[] = { "1. Create Account", "2. Log in", "3. Delete Account" , "4. Edit Info","5. Find PW", "6. Exit"};
char *editList[] = { "1. Change PW", "2. Change Name" };

typedef vector<User> U;
typedef vector<string> I;

void menu(U &uList, I &idList);
void pullData(U &uList, I &idList);
void pushData(U &uList);
void createUser(U &uList, I &lst);
pair<bool, int> checkID(I idList, string id);
void login(U uList, I idList);
void findPW(U uList, I idList);
void delUser(U &uList, I &idList);
void editInfo(U &uList, I &idList);
void prn(U &uList);
void myflush();

void menu(U &uList, I &idList) {
	int choice;
	pullData(uList, idList);
	while (1) {
		for (auto t : menuList)
			cout << t << endl;
		cout << ">> ";
		cin >> choice;

		if (cin.fail())
			myflush();

		switch (choice) {
		case 1: createUser(uList, idList); break;
		case 2: login(uList, idList); break;
		case 3: delUser(uList, idList);  prn(uList); break;
		case 4: editInfo(uList, idList); break;
		case 5: findPW(uList, idList); break;
		case 6: cout << "\n* Exit the program ! *" << endl; return;
		default: cout << "\n* Wrong Selection ! *" << endl;
		}
	}
}

void pullData(U &uList, I &idList) {
	ifstream in(FILE);
	string id, pw, name, birth;
	while (!in.eof()) {
		in >> id >> pw >> name >> birth;
		uList.push_back(User(id, pw, name, birth));
		idList.push_back(id);
	}
	in.close();
}

/*
	수정이 필요합니다.
	데이터를 삭제 후, 파일 덮어쓰기가 안됨
*/
void pushData(U &uList) {
	ofstream out(FILE, ios_base::in);
	out << uList[0].getlogInfo().first << " " <<uList[0].getlogInfo().second << " " << uList[0].getName() << " " << uList[0].getBirth();
	for (auto t : uList)
		out << "\n" << t.getlogInfo().first << " " << t.getlogInfo().second << " " << t.getName() << " " << t.getBirth();
	out.close();
}

void createUser(U &uList, I &lst) {
	string id, pw, name;
	string birth;
	ofstream out(FILE, ios_base::app);
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
	cout << "Enter your Identification Number : ";
	cin >> birth;
	uList.push_back(User(id, pw, name, birth));
	lst.push_back(id);
	myflush();
	out << "\n" << id << " " << pw << " " << name << " " << birth;
	out.close();
}

/*
	이미 존재하는 id일 경우 : true
	존재하는 id가 아닌 경우 : false
*/
pair<bool, int> checkID(I idList, string id) {
	auto iter = find(idList.begin(), idList.end(), id);
	return iter != idList.end() ? pair<bool, int>(true, iter - idList.begin()) : pair<bool, int>(false, -1);
}

void login(U uList, I idList) {
	string id, pw;
	pair<bool, int> check;
	
	while (1) {
		cout << "\nID : ";
		cin >> id;
		check = checkID(idList, id);
		if (check.first)
			break;
		cout << "\n* This id isn't existed ! *" << endl;
		myflush();
	}

	for(int i=0;i<5; i++) {
		cout << "PW : ";
		cin >> pw;
		if (uList[check.second].getlogInfo().second == pw) {
			cout << "* Welcome to Gun's World ! *" << endl;
			return;
		}
		cout << "\n* Passwords do not match ! *" << endl;
		myflush();
	}
	cout << "* You Failed 5 times *" << endl;
}

void findPW(U uList, I idList) {
	string name, id, birth;
	pair<bool, int> check;

	cout << "\nEnter your name : ";
	cin >> name;
	cout << "Enter your ID : ";

	cin >> id;
	cout << "Enter your Identification Number : ";
	cin >> birth;

	check = checkID(idList, id);
	if (!check.first) {
		cout << "\n* No data of this ID *" << endl;
		return;
	}

	if (uList[check.second].getName() == name &&
		uList[check.second].getBirth() == birth)
		cout << "\n<" << uList[check.second].getlogInfo().second << "> is your password !" << endl;
	else 
		cout << "* No Matching information exists *" << endl;
}

void delUser(U &uList, I &idList) {
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
	ofstream out(FILE, ios_base::trunc);
	out.close();
	pushData(uList);
}

void editInfo(U &uList, I &idList) {
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

void prn(U &uList) {
	if (uList.size() == 0) {
		cout << "\n* No data ! *\n" << endl;
		return;
	}
	for (auto t : uList)
		t.info();
}

void myflush() {
	cin.clear();
	while (getchar() != '\n');
}