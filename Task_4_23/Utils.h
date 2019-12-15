#pragma once

#include <string>
#include <vector>
#include "enum/EErrorMessage.h"

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
		default:
			return "";
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
		if (!inFile || !outFile) {
			throw runtime_error(Utils::getErrorMessage(EErrorMessage::NOT_OPEN_FILES));
		}
	}

	bool pathIsCyclic = false;

	void setPathIsCyclic(bool value) {
		pathIsCyclic = value;
	}

	bool getPathIsCyclic() {
		return pathIsCyclic;
	}
}