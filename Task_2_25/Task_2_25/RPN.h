#include <string>
#include <vector>
#include <map>
#include <stack>
#include <memory>
#include "classes/ITerm.h"
#include "classes/Term.h"
#include "Handler.h"

using namespace std;

namespace RPN {
    vector <string> n_tokens;
    stack <shared_ptr<ITerm>> n_stack;
    map <string, string> n_variables;

    void setTokens(vector<string> h_tokens)
    {
		n_tokens = h_tokens;
    }

	void convert() {
		const vector <string>& tokens = n_tokens;
		auto l_stack = n_stack;
		while (!l_stack.empty()) {
			l_stack.pop();
		}
		string operation;
		int i = 0;
		for (const auto& token : tokens) {
			i++;
			if (!Utils::isOperator(token)) {
				l_stack.push(make_shared<Term>("", "", token));
			}
			else {
				operation = token;
				Utils::isUnaryOperation(operation) ? Handler::unaryOperation(l_stack, operation, i) : Handler::binaryOperation(l_stack, operation, i);
			}
		}
		if (l_stack.size() != 1) {
			throw runtime_error("Invalid stack state: should contains only one element");
		}
		n_stack = l_stack;
	}

	string getConvertedNotation() {
		convert();
		auto stack = n_stack;
		return stack.top()->toString();
	}

	float calculate() {
		Utils::setIsCalc(true);
		return stof(getConvertedNotation());
	}

	bool canCalculate() {
		vector <string> tokens = n_tokens;
		map <string, string> variables = n_variables;

		for (const auto& variable : variables) {
			replace(tokens.begin(), tokens.end(), variable.first, variable.second);
		}

		n_tokens = tokens;

		return all_of(tokens.cbegin(), tokens.cend(), [](const auto& token) {
			return Utils::isOperator(token) || Utils::isFloat(token);
		});
	}

	void setVariables(string sream) {
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
		n_variables = variables;
	}
}