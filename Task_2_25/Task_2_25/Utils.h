#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include "enums/EOperationPriority.h"

using namespace std;


map <string, EOperationPriority> operations = {
    {"cos", EOperationPriority::COS},
    {"sin", EOperationPriority::SIN},
    {"exp", EOperationPriority::EXP},
    {"^",   EOperationPriority::POW},
    {"*",   EOperationPriority::MUL},
    {"/",   EOperationPriority::DIV},
    {"-",   EOperationPriority::MINUS},
    {"+",   EOperationPriority::PLUS},
};

map <string, EOperationPriority> unaryOperations = {
	{"cos", EOperationPriority::COS},
	{"sin", EOperationPriority::SIN},
	{"exp", EOperationPriority::EXP},
};

namespace Utils {
    bool isCalc = false;

	void setIsCalc(bool value) {
		isCalc = value;
	}

	bool getIsCalc() {
		return isCalc;
	}

    bool isFloat(const string &str) {
        istringstream stream(str);
        float value;
        stream >> noskipws >> value;
        return stream.eof() && !stream.fail();
    }

    bool isOperator(const string &str) {
        return operations.find(str) != operations.end();
    }

    bool isUnaryOperation(const string &str) {
        return unaryOperations.find(str) != unaryOperations.end();
    }

    EOperationPriority getOperationPriority(const string &str) {
        auto value = operations.find(str);
        if (value == operations.end()) {
            return EOperationPriority::NONE;
        }
        return value->second;
    }

    float doOperation(float first_operand, float second_operand, const string &operation) {
        if (operation == "+") return first_operand + second_operand;
        if (operation == "-") return first_operand - second_operand;
        if (operation == "*") return first_operand * second_operand;
        if (operation == "/") return first_operand / second_operand;
        if (operation == "^") return powf(first_operand, second_operand);
        if (operation == "exp") return expf(second_operand);
        if (operation == "sin") return sinf(second_operand);
        if (operation == "cos") return cosf(second_operand);
        throw invalid_argument("Unknown operator '" + operation + "'");
    }

	void removeSubstrs(string &str, string pattern) {
		string::size_type n = pattern.length();
		for (string::size_type i = str.find(pattern);
			i != string::npos;
			i = str.find(pattern))
			str.erase(i, n);
	}

	string getUniqueSymbols(string str) {
		removeSubstrs(str, "sin");
		removeSubstrs(str, "cos");
		removeSubstrs(str, "exp");
		str.erase(remove_if(str.begin(), str.end(), [](auto const& c) -> bool { return !isalpha(c); }), str.end());
		sort(begin(str), end(str));
		auto last = unique(begin(str), end(str));
		str.erase(last, end(str));
		return str;
	}

}
