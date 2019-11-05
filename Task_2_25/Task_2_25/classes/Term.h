#pragma once

#include "ITerm.h"
#include "../Utils.h"

class Term : public ITerm {
public:
	Term() = delete;

	Term(string l_first_operand, string l_operation, string l_second_operand) {
		m_first_operand = l_first_operand;
		m_second_operand = l_second_operand;
		m_operation = l_operation;

        float p_first_operand = 0;
        float p_second_operand = 0;

        if (!m_operation.empty()) {
            try {
                if (!m_first_operand.empty() && !m_second_operand.empty()) {
					p_first_operand = stof(m_first_operand);
					p_second_operand = stof(m_second_operand);
                } else if (!m_first_operand.empty()) {
					p_first_operand = stof(m_first_operand);
                } else if (!m_second_operand.empty()) {
					p_second_operand = stof(m_second_operand);
                }
            }
            catch (...) {}
        } else {
            try {
				p_second_operand = stof(m_second_operand);
            }
            catch (...) {}
        }

        try {
            if (Utils::getIsCalc()) {
				if (!m_operation.empty()) {
					m_result = to_string(Utils::doOperation(p_first_operand, p_second_operand, m_operation));
				} else {
					m_result = to_string(p_second_operand);
				}
				m_first_operand = "";
				m_operation = "";
				m_second_operand = m_result;
            }
        }
        catch (...) {}
    }

    string first_operand() const override { 
		return m_first_operand;
	}

    string operation() const override {
		return m_operation;
	}

    string second_operand() const override {
		return m_second_operand;
	}

    virtual string toString() const override {
        return m_first_operand + m_operation + m_second_operand;
    }

private:
    string m_first_operand;
    string m_second_operand;
    string m_operation;
    string m_result = "not";
};