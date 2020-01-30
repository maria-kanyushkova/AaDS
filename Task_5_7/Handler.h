#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <map>
#include <optional>
#include <vector>
#include <sstream>
#include <ctime>
#include "Utils.h"
#include "struct/Name.h"
#include "struct/Number.h"
#include "classes/PhoneBook.h"

using namespace std;

namespace Handler {
	vector <pair<Number, Name>> readDictionary(istream& in) {
		vector <pair<Number, Name>> result;

		while (in) {
			string number;
			string name;
			in >> number >> name >> ws;

			result.push_back({ number, name });
		}

		return move(result);
	}

	void verifyDictionary(optional < PhoneBook > const& dict) {
		if (!dict) {
			throw logic_error("Open dictionary first");
		}
	}

	clock_t start;

	bool commandProcces(int cmd) {
		switch (cmd) {
		case 1: {
			string inputFileName;
			cout << "Enter txt file name\n>";
			cin >> inputFileName;

			string dictFileName;
			cout << "Enter dictionary file name\n>";
			cin >> dictFileName;

			start = clock();

			ifstream inputFile(inputFileName);
			if (!inputFile) {
				cout << "Error in input file!";
				break;
			}

			auto data = readDictionary(inputFile);
			Utils::dictionary.emplace(dictFileName, true);
			Utils::dictionary->add(data);
			cout << "Created dictionary with " << Utils::dictionary->getSize() << " numbers\n";
			break;
		}
		case 2: {
			string dictFileName;
			cout << "Enter dictionary file name\n>";
			cin >> dictFileName;

			start = clock();

			Utils::dictionary.emplace(dictFileName, false);
			cout << "Opened dictionary with " << Utils::dictionary->getSize() << " numbers\n";
			break;
		}
		case 3: {
			verifyDictionary(Utils::dictionary);

			string number;
			cout << "Enter number\n>";
			cin >> number;

			start = clock();

			auto result = Utils::dictionary->find(number);
			if (result) {
				cout << result->data << endl;
			}
			else {
				cout << "Not found\n";
			}
			break;
		}
		case 4: {
			verifyDictionary(Utils::dictionary);

			string number;
			cout << "Enter number\n>";
			cin >> number;

			string name;
			cout << "Enter name\n>";
			cin >> name;

			start = clock();

			Utils::dictionary->set(number, name);
			break;
		}
		case 5: {
			verifyDictionary(Utils::dictionary);

			string number;
			cout << "Enter number\n>";
			cin >> number;

			start = clock();

			Utils::dictionary->remove(number);
			break;
		}
		case 6: {
			verifyDictionary(Utils::dictionary);

			string dictFileName;
			cout << "Enter output file\n>";
			cin >> dictFileName;

			start = clock();

			if (!Utils::dictionary->save(dictFileName)) {
				cout << "Error!\n";
			}
			break;
		}
		case 7: {
			cout << "Good bye!\n";
			return false;
		}
		default:
			cout << "Invalid command: " << cmd << "\n";
		}
	}
}