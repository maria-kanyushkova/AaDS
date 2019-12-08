#include "Reader.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

CReader::CReader() {}

bool CReader::read() {
    string buffer;
    getline(cin, buffer);
    this->m_stream = buffer;
    return !buffer.empty();
}

string CReader::getStream() const
{
    return this->m_stream;
}

vector<string> CReader::tokenize()
{
    char delimeter = ' ';

    vector<string> tokens;
    stringstream stream(this->m_stream);
    string buffer;

    while (getline(stream, buffer, delimeter))
    {
        tokens.push_back(buffer);
    }
    return tokens;
}
