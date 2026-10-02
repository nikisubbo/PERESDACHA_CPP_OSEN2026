#include "stl_utils.h"
#include <limits>

int get_even_number(const std::string& prompt) {
    int n;
    while (true) {
        std::cout << prompt;
        if (std::cin >> n) {
            if (n >= 2 && n % 2 == 0) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return n;
            }
            std::cout << "Ошибка: число должно быть чётным и не меньше 2\n";
        }
        else {
            std::cout << "Ошибка. Введите корректное число\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int get_min_number(const std::string& prompt, int min_val) {
    int n;
    while (true) {
        std::cout << prompt;
        if (std::cin >> n) {
            if (n >= min_val) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return n;
            }
            std::cout << "Ошибка. Число должно быть >= " << min_val << "!\n";
        }
        else {
            std::cout << "Ошибка. Введите корректное целое число\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int get_odd_number(const std::string& prompt, int min_val) {
    int n;
    while (true) {
        std::cout << prompt;
        if (std::cin >> n) {
            if (n >= min_val && n % 2 != 0) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return n;
            }
            std::cout << "Ошибка. Число должно быть >= " << min_val << " и нечётным\n";
        }
        else {
            std::cout << "Ошибка. Введите корректное целое число\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}