#pragma once

#include <string>

using namespace std;

const size_t maxNumberSize = 6; // max длина номера

// структура номера, хранит массив символов
struct Number {
	char data[maxNumberSize + 1];

	Number() {
		memset(data, '\0', maxNumberSize);
	}

	Number(string const& str) : Number() {
		if (str.size() > maxNumberSize) {
			throw invalid_argument("Number is too long \n");
		}

		strncpy_s(data, str.c_str(), _TRUNCATE);
	}

	bool operator==(Number const& other) const {
		return string(data) == string(other.data);
	}
};