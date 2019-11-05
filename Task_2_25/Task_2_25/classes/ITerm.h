#pragma once

#include <string>

using namespace std;

class ITerm {
public:
    virtual string first_operand() const = 0;

    virtual string operation() const = 0;

    virtual string second_operand() const = 0;

    virtual string toString() const = 0;
};

