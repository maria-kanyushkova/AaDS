#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Tree.h"


namespace Handler {
	void printTree(ofstream& outFile, Tree tree, const string indent) {
		outFile << indent << tree.toString();

		for (Tree& child : tree.getChildren()) {
			printTree(outFile, child, indent + '*');
		}
	};

	int getMaxWeight(string fileContent, size_t& pointer) {
		string maxWeightStr = "";
		while (fileContent[pointer] != '\n') {
			maxWeightStr += fileContent[pointer];
			pointer++;
		}
		pointer++;

		return stoi(maxWeightStr);
	}

	string readAllFile(ifstream& inFile) {
		stringstream fileContentStream;
		fileContentStream << inFile.rdbuf();

		return fileContentStream.str();
	}
}