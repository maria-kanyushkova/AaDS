#pragma once

#include <string>

using namespace std;

const size_t maxNameSize = 30; // max длина фамилии

// структура имени, хранит массив символов
struct Name {
	char data[maxNameSize + 1];

	Name() {
		memset(data, '\0', maxNameSize);
	}

	Name(string const& str) : Name() {
		if (str.size() > maxNameSize) {
			throw invalid_argument("Name is too long \n");
		}

		strncpy_s(data, str.c_str(), _TRUNCATE);
	}

	bool operator==(Name const& other) const {
		return string(data) == string(other.data);
	}
};