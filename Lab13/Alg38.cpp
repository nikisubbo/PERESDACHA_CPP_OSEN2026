#include "alg38.h"
#include "stl_utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <limits>
#include <random>
#include <fstream>
#define NOMINMAX
#include <windows.h>

void alg38() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int n;
    std::cout << "Введите размер вектора >= 3: ";
    std::cin >> n;
    while (n < 3) {
        std::cout << "Ошибка: размер должен быть >= 3. Введите снова: ";
        std::cin >> n;
    }
    std::vector<int> V;
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
            V.push_back(val);
        }
    }
    else if (method == 2) {
        std::cout << "Генерация " << n << " случайных чисел:\n";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        for (int i = 0; i < n; ++i) {
            int val = dis(gen);
            V.push_back(val);
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
            V.push_back(val);
            count++;
        }
        infile.close();
        if (count < n) {
            std::cout << "Внимание: Файл содержал только " << count << " элементов.\n";
        }
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nДо: ";
    print_vector("Вектор V", V);
    std::partial_sort(V.begin(), V.begin() + 3, V.end(), std::greater<int>());
    std::cout << "\nПосле: ";
    std::copy(
        V.begin(),
        V.begin() + 3,
        std::ostream_iterator<int>(std::cout, " ")
    );
    std::cout << "\n";
}