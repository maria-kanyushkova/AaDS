#include <string>
#include <vector>
#include <memory>
#include <stack>
#include "classes/ITerm.h"
#include "classes/Term.h"
#include "classes/BracketedTerm.h"
#include "Utils.h"

using namespace std;

namespace Handler {
    void binaryOperation(stack <shared_ptr<ITerm>> &h_stack, const string &h_operation, int i) {
        if (h_stack.size() < 2) {
			string error = "operands problem in " + to_string(i);
            throw runtime_error(error);
        }
        auto lFirstExpression = h_stack.top();
        h_stack.pop();
        auto lSecondExpression = h_stack.top();
        h_stack.pop();

        const auto firstOperationPriority = Utils::getOperationPriority(lFirstExpression->operation());
        const auto firstCondForFirstOperation = firstOperationPriority < Utils::getOperationPriority(h_operation);
        const auto secondCondForFirstOperation = firstOperationPriority != 0;
        if (firstCondForFirstOperation && secondCondForFirstOperation) {
            lFirstExpression = make_shared<BracketedTerm>(
                    lFirstExpression->first_operand(),
                    lFirstExpression->operation(),
                    lFirstExpression->second_operand()
            );
        }
        const auto secondOperationPriority = Utils::getOperationPriority(lSecondExpression->operation());
        const auto firstCondForSecondOperation = secondOperationPriority < Utils::getOperationPriority(h_operation);
        const auto secondCondForSecondOperation = secondOperationPriority != 0;
        if (firstCondForSecondOperation && secondCondForSecondOperation) {
            lSecondExpression = make_shared<BracketedTerm>(
                    lSecondExpression->first_operand(),
                    lSecondExpression->operation(),
                    lSecondExpression->second_operand()
            );
        }

        h_stack.push(make_shared<Term>(
                (lSecondExpression->operation() == "^")
                ?
                "(" + lSecondExpression->first_operand() + lSecondExpression->operation() + lSecondExpression->second_operand() + ")"
                :
                lSecondExpression->first_operand() + lSecondExpression->operation() + lSecondExpression->second_operand(),
                h_operation,
                lFirstExpression->first_operand() + lFirstExpression->operation() + lFirstExpression->second_operand()
        ));
    }

    void unaryOperation(stack <shared_ptr<ITerm>> &h_stack, const string &operation, int i) {
        if (h_stack.empty()) {
			string error = "operands problem in " + to_string(i);
			throw runtime_error(error);
        }
        auto expression = h_stack.top();
        h_stack.pop();

        const auto operationPriority = Utils::getOperationPriority(expression->operation());
        const auto firstCondition = operationPriority < Utils::getOperationPriority(operation);
        const auto secondCondition = operationPriority != 0;
        if (firstCondition && secondCondition) {
            expression = make_shared<BracketedTerm>(
                    expression->first_operand(),
                    expression->operation(),
                    expression->second_operand()
            );
        }

        h_stack.push(make_shared<Term>(
                "",
                operation,
                expression->first_operand() + expression->operation() + expression->second_operand()
        ));
    }
}