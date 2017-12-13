#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

class User {
private:
	pair<string, string> logInfo;
	string name;
	int birth;
public:
	User(string id, string pw, string name, int birth) :name(name), birth(birth) {
		logInfo.first = id;
		logInfo.second = pw;
	}
	virtual ~User(){}
	bool static checkSecurity(string np);
	pair<string,string> getlogInfo() { return logInfo; }
	void changePW();
	void changeName();
	void info();
};

bool User::checkSecurity(string np) {
	if (np.size() < 10)
		return false;
	set<char> check;
	for (int i = 0; i < np.size(); i++)
		check.insert(np[i]);
	return check.size() >= 7;
}

void User::changePW() {
	string np;
	while (1) {
		cout << "Enter the new PW : ";
		cin >> np;
		if (checkSecurity(np)) {
			logInfo.second = np;
			cout << "\n* Password changed successfully ! *\n" << endl;
			return;
		}
		cout << "\n* This password isn't secure ! Try another Password *\n" << endl;
		while (getchar() != '\n');
	}
}

void User::changeName() {
	string newName;
	cout << "Enter the new Name : ";
	cin >> newName;
	name = newName;
}

void User::info() {
	cout << "ID : " << logInfo.first << endl;
	cout << "PW : " << logInfo.second << endl;
	cout << "Name : " << name << endl;
	cout << "Age : " << birth << "\n" << endl;
}