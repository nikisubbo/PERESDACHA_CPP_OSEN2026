#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>
#include "input.h"

int Input_Int() {
    int number;
    while (true) {
        if (std::cin >> number) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return number;
        }
        else {
            std::cout << "Ошибка. Введите число." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}