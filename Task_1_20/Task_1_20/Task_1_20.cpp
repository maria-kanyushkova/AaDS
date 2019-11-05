// ПС-21 Канюшкова М.В.

// 20. Составить программу перевода вещественного числа в форму
//     константы с плавающей  точкой  в строковом формате. Целая часть
//     мантиссы должна состоять из одной цифры (8).

#include <iostream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <iomanip>

using namespace std;

int main()
{
	string str;
	int exp;
	int countSign;
	double value;

	cout << "Input value" << endl;
	cin >> str;
	cout << "Input number of digits after point" << endl;
	cin >> countSign;

	string expon = str.substr(str.find("E") + 1, str.length());
	exp = expon != str ? stoi(expon) : 0;
	value = stod(str.substr(0, str.find("E")));

	cout << endl;

	if (value < 0) {
		value *= -1;
		cout << "-";
	}

	if (value >= 10) {
		while (value >= 10) {
			value = value / 10;
			exp++;
		}
	}
	else if ((1 >= value) && (value >= 0)) {
		while (1 > value) {
			value = value * 10;
			exp--;
		}
	}

	cout << fixed << setprecision(countSign) << value;

	if (exp != 0) {
		string sign = exp > 0 ? "+" : "";
		cout << "E" << sign << exp;
	}

	cout << endl;
}
