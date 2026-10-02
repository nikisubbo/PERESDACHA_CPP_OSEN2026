#include "stl_utils.h"
#include <limits>
#include <list>
#define NOMINMAX
#include <windows.h>

std::vector<int> get_vector_from_input(const std::string& prompt) {
    std::vector<int> vec;
    int n;
    std::cout << prompt;
    if (!(std::cin >> n) || n < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return vec;
    }
    std::cout << "Введите " << n << " целых чисел:\n";
    for (int i = 0; i < n; ++i) {
        int val;
        std::cin >> val;
        vec.push_back(val);
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return vec;
}

void print_vector(const std::string& name, const std::vector<int>& v) {
    std::cout << name << ": ";
    if (v.empty()) {
        std::cout << "Пуст";
    }
    else {
        for (int x : v) {
            std::cout << x << " ";
        }
    }
    std::cout << "\n";
}

std::list<int> get_even_list_from_input(const std::string& prompt) {
    std::list<int> lst;
    int n;
    while (true) {
        std::cout << prompt;
        if (std::cin >> n) {
            if (n >= 0 && n % 2 == 0) {
                break;
            }
            std::cout << "Ошибка. Количество элементов должно быть чётным и >= 0\n";
        }
        else {
            std::cout << "Ошибка. Введите корректное число\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::cout << "Введите " << n << " целых чисел:\n";
    for (int i = 0; i < n; ++i) {
        int val;
        std::cin >> val;
        lst.push_back(val);
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return lst;
}

std::vector<int> get_vector_min_size(const std::string& prompt, int min_size) {
    std::vector<int> vec;
    int n;
    while (true) {
        std::cout << prompt;
        if (std::cin >> n) {
            if (n >= min_size) {
                break;
            }
            std::cout << "Ошибка: размер должен быть >= " << min_size << "\n";
        }
        else {
            std::cout << "Ошибка. Введите корректное число\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::cout << "Введите " << n << " целых чисел:\n";
    for (int i = 0; i < n; ++i) {
        int val;
        std::cin >> val;
        vec.push_back(val);
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return vec;
}