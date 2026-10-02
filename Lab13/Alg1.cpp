#include "Alg1.h"
#include "stl_utils.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <limits>
#include <random>
#include <fstream>
#include <string>
#define NOMINMAX
#include <windows.h>

void alg1() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int n;
    std::cout << "Введите размер списка L: ";
    std::cin >> n;
    while (n < 0) {
        std::cout << "Ошибка: размер должен быть >= 0. Введите снова: ";
        std::cin >> n;
    }
    std::list<int> L;
    int method;
    std::cout << "Выберите способ ввода:\n1) С клавиатуры\n2) Случайно\n3) Из файла\nВыбор: ";
    std::cin >> method;
    while (method < 1 || method > 3) {
        std::cout << "Неверный выбор. Введите 1, 2 или 3: ";
        std::cin >> method;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (method == 1) {
        std::cout << "Введите " << n << " целых чисел:\n";
        for (int i = 0; i < n; ++i) {
            int val;
            std::cin >> val;
            L.push_back(val);
        }
    }
    else if (method == 2) {
        std::cout << "Генерация " << n << " случайных чисел:\n";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(-10, 10);
        for (int i = 0; i < n; ++i) {
            int val = dis(gen);
            L.push_back(val);
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
    else if (method == 3) {
        std::string filename;
        std::cout << "Введите имя исходного файла: ";
        std::cin >> filename;
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Ошибка. Исходный файл не открыт: " << filename << "\n";
            return;
        }
        int val;
        int count = 0;
        while (count < n && infile >> val) {
            L.push_back(val);
            count++;
        }
        infile.close();
        if (count < n) {
            std::cout << "Внимание: Файл содержал только " << count << " элементов.\n";
        }
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nДо:\n";
    print_list("Список L", L);

    auto first_zero = std::find(L.begin(), L.end(), 0);
    if (first_zero == L.end()) {
        std::cout << "\nНулевых элементов нет. Список не изменён.\n";
        return;
    }

    auto last_zero_rev = std::find(L.rbegin(), L.rend(), 0);
    auto last_zero = --(last_zero_rev.base());

    if (first_zero == last_zero) {
        L.erase(first_zero);
        std::cout << "\nНайден только один нулевой элемент. Он удалён.\n";
    }
    else {
        L.erase(last_zero);
        L.erase(first_zero);
        std::cout << "\nУдалены первый и последний нулевые элементы.\n";
    }

    std::cout << "\nПосле:\n";
    print_list("Список L", L);
}