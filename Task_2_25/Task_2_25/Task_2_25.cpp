/*
   25. Имеется  выражение  в  постфиксной  форме,   включающее
обращение к функциям SIN, COS, EXP.  Переменные  заданы  одной
строчной латинской буквой.  Запросить  значения  переменных  и
вычислить выражение. Представить  его  в  инфиксной  форме  со
скобками. Лишние скобки присутствовать не должны (11).

Канюшкова Мария ПС-21

*/

#include "pch.h"
#include <iomanip>
#include <iostream>
#include "lib/Reader.h"
#include "RPN.h"

using namespace std;

int main() {
	CReader reader = CReader();
	reader.read();
	
	try {
		RPN::setTokens(reader.tokenize());

		string convertedNotation = RPN::getConvertedNotation();

		RPN::setVariables(reader.getStream());

		cout << convertedNotation;

		if (!RPN::canCalculate()) {
			cout << endl;
			throw runtime_error("variables not");
		}
		cout << " = " << fixed << setprecision(3) << RPN::calculate() << endl;
	}
	catch (const exception & ex) {
		cerr << ex.what() << endl;
	}
}