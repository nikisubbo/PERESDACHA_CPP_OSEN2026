#include <iostream>
#include <string>
#include <climits>
#include "Recur15.h"
std::string s;
int cur_pos = 0;
int Reading() { // ф-я для чтения 1 символа (числа)
	return s[cur_pos++] - '0';// -'0' для преобразования символа в число
}
int Term() {
	int number = Reading();
	if (cur_pos < s.size() && s[cur_pos] == '*') {
		cur_pos++;// пропускаем знак умножения
		return number * Term();
	}
	return number;
}

int Expression(int number = 0, bool flag = true) {// flag для проверки на 1ый вызов
	if (flag) {
		number = Term();
	}
	if (cur_pos < s.size() && (s[cur_pos] == '+' || s[cur_pos] == '-')) {
		char operand = s[cur_pos++];// считываем знак
		int new_term = Term();
		int new_number = number;
		if (operand == '+') {
			new_number += new_term;
		}
		else {
			new_number -= new_term;
		}
		return Expression(new_number, false);// рекурсивно вызываем
	}
	return number;
}
void Recur15() {
	std::cout << "Задание Recur15" << std::endl;
	std::cout << "Введите ваше выражение: ";
	std::cin >> s;
	cur_pos = 0;
	std::cout << "Результат: " << Expression() << std::endl;
}