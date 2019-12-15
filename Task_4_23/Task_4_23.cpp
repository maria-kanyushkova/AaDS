/*
		23. Имеются  расписания вылетов самолетов в  ряде  аэропортов. 
	Некоторые города могут быть связаны несколькими  рейсами.
	Требуется по начальному и конечному пунктам методом  поиска в
	ширину найти все возможные маршруты в порядке  возрастания ко-
	личества пересадок. Множество путей  сохранять в виде  дерева.
	Выдать дерево возможных путей. Проиллюстрировать  этапы поиска. (11).

	Канюшкова Мария ПС-21 
*/


#include <iostream>
#include "Utils.h"
#include "Handler.h"
#include "lib/Reader.h"

using namespace std;

int main() {
    CReader reader = CReader();
    reader.read();
    vector <string> tokens = reader.tokenize();

    try {
        Utils::checkFileName(tokens);

        ifstream fcities("cities.txt");
        ifstream inFile(tokens[0]);
        ofstream outFile(tokens[1]);

        Utils::checkOpenFile(inFile.is_open(), outFile.is_open());

        Handler::solve(fcities, inFile, outFile);
    }
    catch (const exception &ex) {
        cerr << ex.what() << endl;
    }
}