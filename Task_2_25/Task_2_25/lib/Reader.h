#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class IReader {
public:
    virtual bool read() = 0;

    virtual string getStream() const = 0;

    virtual vector<string> tokenize() = 0;
};

class CReader : public IReader
{
public:
    CReader();

    bool read();

    string getStream() const;

    vector<string> tokenize();

private:
    string m_stream;
};
