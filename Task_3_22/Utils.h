#pragma once

#include <string>
#include "enum/EErrorMessage.h"
#include "enum/ESymbol.h"

using namespace std;

namespace Utils {
	string getErrorMessage(EErrorMessage type) {
		switch (type) {
		case EErrorMessage::NOT_ENOUGH_FILES:
			return "There are not enough files.";
		case EErrorMessage::EQUAL_FILE_NAME:
			return "Files is equal.";
		case EErrorMessage::NOT_OPEN_FILES:
			return "File does not open.";
		case EErrorMessage::CANT_TRIM:
			return "Can't trim tree";
		default:
			return "";
		}
	}

	char getSymbol(ESymbol symbol) {
		switch (symbol) {
		case ESymbol::LINE_BREAK:
			return '\n';
		case ESymbol::LEVEL:
			return '*';
		case ESymbol::AND_TREE:
			return '&';
		case ESymbol::OR_TREE:
			return '|';
		case ESymbol::SPACE:
			return ' ';
		default:
			return ' ';
		}
	}

	void checkFileName(vector<string> tokens) {
		if (tokens.size() < 2) {
			throw runtime_error(Utils::getErrorMessage(EErrorMessage::NOT_ENOUGH_FILES));
		}

		if (static_cast<string>(tokens[0]) == static_cast<string>(tokens[1])) {
			throw runtime_error(Utils::getErrorMessage(EErrorMessage::EQUAL_FILE_NAME));
		}
	}

	void checkOpenFile(bool inFile, bool outFile) {
		if (!inFile|| !outFile) {
			throw runtime_error(Utils::getErrorMessage(EErrorMessage::NOT_OPEN_FILES));
		}
	}
}
