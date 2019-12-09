
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