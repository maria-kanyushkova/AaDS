 // В листьях И-ИЛИ дерева, соответствующего некоторому
 // множеству конструкций, заданы значения массы. Известно
 // максимально допустимое значение массы изделия. Требуется усечь
 // дерево так, чтобы дерево включало все элементы, соответствующие
 // допустимым значениям массы, но не содержало "лишних" вершин.
 // Конечное дерево выдать на экран в  наглядном виде.

 // Канюшкова Мария ПС-21 Вариант 22
 
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "lib/Reader.h"
#include "enum/EErrorMessage.h"
#include "Handler.h"
#include "Utils.h"
#include "Tree.h"

using namespace std;

int main() {
	CReader reader = CReader();
	reader.read();
	vector<string> tokens = reader.tokenize();

	try {
		Utils::checkFileName(tokens);

		ifstream inFile(tokens[0]);
		ofstream outFile(tokens[1]);

		Utils::checkOpenFile(inFile.is_open(), outFile.is_open());

		string fileContent = Handler::readAllFile(inFile);
		size_t pointer = 0;

		int maxWeight = Handler::getMaxWeight(fileContent, pointer);

		Tree root(fileContent, pointer, 0);
		inFile.close();

		root.calculateTree();

		if (root.trimTree(maxWeight)) {
			Handler::printTree(outFile, root, "");
		}
		else {
			outFile << Utils::getErrorMessage(EErrorMessage::CANT_TRIM);
		}

		outFile.close();
	}
	catch (const exception& ex) {
		cerr << ex.what() << endl;
	}
};

