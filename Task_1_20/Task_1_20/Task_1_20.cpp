// ПС-21 Канюшкова М.В.

// 20. Составить программу перевода вещественного числа в форму
//     константы с плавающей  точкой  в строковом формате. Целая часть
//     мантиссы должна состоять из одной цифры (8).

#include <iostream>
#include <string>
#include <stdio.h>
#include <regex>

using namespace std;

//      /^(?:\+|\-)?(?:(?:\d+)|(?:\d+\.)|(?:\.\d+)|(?:\d+\.\d+)){1}(?:e(?:\+|\-)?\d+)?$/i регулярка проверяющая на соответствие вещественному числу


int main()
{
	string value;
	cin >> value;
 	// regex r("/^(?:\\+|\\-)?(?:(?:\\d+)|(?:\\d+\\.)|(?:\\.\\d+)|(?:\\d+\\.\\d+)){1}(?:e(?:\\+|\\-)?\\d+)?$/i");
	regex r("\\d");
	cout << "is valid ? " <<  regex_match(value, r);

	// TODO: проверить на соответствие регулярному выражению иначе ошибка ввода
	/*
	long int lengthStr = value.length();
	long int position = 0;
	char delimiter = '.';
	char delimiterExponent = 'E';
	char symbol = value[position];
	char sign, firstDigit = ' ';
	string significantPart, exponent;

	if (symbol == '-') {
		sign = '-';
		position++;
	} else if (symbol == '+') {
		position++;
	}

	long int positionOfDelimiter = value.find(delimiter);
	long int positionOfDelimiterExponent = value.find(delimiterExponent);
	string firstPart = value.substr(position, positionOfDelimiter - 1);
	string secondPart = value.substr(positionOfDelimiter + 1, positionOfDelimiterExponent);
	string thirdPart = value.substr(positionOfDelimiterExponent, lengthStr);
	cout << firstPart << '\n';
	cout << secondPart << '\n';
	cout << thirdPart << '\n';


	cout << sign << firstDigit << "." << significantPart << exponent;
	*/
}
