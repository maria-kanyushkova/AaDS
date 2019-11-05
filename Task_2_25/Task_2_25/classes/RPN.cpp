#include "RPN.h"
#include "Expression.h"
#include "../Handler.h"

using namespace std;

RPN::RPN() {}


void RPN::convert() {
	const vector <string>& tokens = this->tokens;
	auto stack = this->stack;
	while (!stack.empty()) {
		stack.pop();
	}
	string oper;
	for (const auto& token : tokens) {
		if (!Utils::isOperator(token)) {
			stack.push(make_shared<Expression>("", "", token));
		}
		else {
			oper = token;
			Utils::isUnaryOperation(oper) ? Handler::unaryOperation(stack, oper) : Handler::binaryOperation(stack, oper);
		}
	}
	if (stack.size() != 1) {
		throw runtime_error("Invalid stack state: should contains only one element");
	}
	this->stack = stack;
}


void RPN::setTokens(vector<string> tokens)
{
	this->tokens = tokens;
}

string RPN::getConvertedNotation() {
	this->convert();
	auto stack = this->stack;
	return stack.top()->toString();
}

float RPN::calculate() {
	Utils::setIsCalc(true);
	return stof(this->getConvertedNotation());
}

bool RPN::canCalculate() {
	vector <string> tokens = this->tokens;
	map <string, string> variables = this->variables;

	for (const auto& variable : variables) {
		replace(tokens.begin(), tokens.end(), variable.first, variable.second);
	}

	this->tokens = tokens;

	return all_of(tokens.cbegin(), tokens.cend(), [](const auto& token) {
		return Utils::isOperator(token) || Utils::isFloat(token);
		});
}

void RPN::setVariables(string sream) {
	string symbols = Utils::getUniqueSymbols(sream);

	map <string, string> variables;

	for (int i = 0; i < symbols.length(); i++) {
		string alpha;
		string tmp;
		alpha.push_back(symbols[i]);
		cout << alpha << " = ";
		getline(cin, tmp);

		if (!Utils::isFloat(tmp)) {
			throw exception("value is not float");
		}

		variables[alpha] = tmp;
	}
	this->variables = variables;
}