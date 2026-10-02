#include "Alg28.h"
#include "stl_utils.h"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <limits>
#include <random>
#include <fstream>
#define NOMINMAX
#include <windows.h>

void alg28() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int n;
    std::cout << "Введите чётное количество элементов в списке L: ";
    std::cin >> n;
    while (n < 0 || n % 2 != 0) {
        std::cout << "Ошибка: число должно быть чётным и >= 0. Введите снова: ";
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
        std::uniform_int_distribution<> dis(-50, 100);
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

    if (L.empty()) {
        std::cout << "\nСписок пуст\n";
        return;
    }

    auto mid = L.begin();
    std::advance(mid, L.size() / 2);

    auto is_not_positive = [](int x) { return x <= 0; };
    std::remove_copy_if(
        L.rbegin(),
        std::make_reverse_iterator(mid),
        std::front_inserter(L),
        is_not_positive
    );

    std::cout << "\nПосле:\n";
    print_list("Список L", L);
}