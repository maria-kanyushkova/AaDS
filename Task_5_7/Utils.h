#pragma once

#include <iostream>
#include "classes/PhoneBook.h"

using namespace std;

namespace Utils {
	optional<PhoneBook> dictionary;

	void printMenu() {
		cout << "1. New\n";
		cout << "2. Open\n";
		cout << "3. Find\n";
		cout << "4. Add\n";
		cout << "5. Remove\n";
		cout << "6. Save\n";
		cout << "7. Exit\n";
		cout << ">";
	}

	int readCommand() {
		int cmd;
		cin >> cmd;
		return cmd;
	}
}