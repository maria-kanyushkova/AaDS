#pragma once

#include "Term.h"

struct BracketedTerm : public Term {
public:
    BracketedTerm(const string &p_first_operand, const string &operation, const string & p_second_operand) : Term(p_first_operand, operation, p_second_operand) {}

    string first_operand() const override {
        return "(" + Term::first_operand();
    }

    string second_operand() const override {
        return Term::second_operand() + ")";
    }

    string toString() const override {
        return "(" + Term::toString() + ")";
    }
};