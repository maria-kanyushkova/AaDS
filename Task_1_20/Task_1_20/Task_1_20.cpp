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
	cout << "Input value" << endl;
	cin >> str;
	cout << "Input exponent" << endl;
	cin >> exp;
	cout << "Input number of digits after point" << endl;
	cin >> countSign;
	double value = stod(str);

	if (value < 0) {
		value *= -1;
		cout << "-";
	}

	if (value >= 10) {
		while (value >= 10) {
			value = value / 10;
			exp++;
		}
		exp--;
	}
	else if ((1 >= value) && (value >= 0)) {
		while (1 > value) {
			value = value * 10;
			exp--;
		}
	}

	string sign = exp > 0 ? "+" : "";

	cout << fixed << setprecision(countSign) << value << "E" << sign << exp << endl;
}
