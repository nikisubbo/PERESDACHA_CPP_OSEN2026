#include "alg60.h"
#include "stl_utils.h" 
#include <list>
#include <vector>
#include <algorithm>  
#include <numeric>     
#include <iterator>   
#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <random>
#define NOMINMAX
#include <windows.h>

struct AverageFunctor {
    double operator()(double current, double previous) const {
        return (current + previous) / 2.0;
    }
};

void alg60() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int n;
    std::cout << "Введите количество элементов списка L >= 2: ";
    while (!(std::cin >> n) || n < 2) {
        std::cout << "Ошибка. Введите целое число >= 2: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::list<double> L;
    int method;
    std::cout << "Выберите способ ввода:\n1) С клавиатуры\n2) Случайно\n3) Из файла\nВыбор: ";
    std::cin >> method;
    while (method < 1 || method > 3) {
        std::cout << "Неверный выбор. Введите 1, 2 или 3: ";
        std::cin >> method;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (method == 1) {
        std::cout << "Введите " << n << " чисел:\n";
        for (int i = 0; i < n; ++i) {
            double val;
            std::cin >> val;
            L.push_back(val);
        }
    }
    else if (method == 2) {
        std::cout << "Генерация " << n << " случайных чисел:\n";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(1.0, 100.0);
        for (int i = 0; i < n; ++i) {
            double val = dis(gen);
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
        double val;
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
    std::cout << "\nДо: ";
    std::cout << "Список L: ";
    for (double x : L) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    std::vector<double> V;
    std::adjacent_difference(
        L.begin(),
        L.end(),
        std::back_inserter(V),
        AverageFunctor()
    );
    if (!V.empty()) {
        V.erase(V.begin());
    }
    std::cout << "\nПосле: ";
    std::cout << "Вектор V (средние арифметические пар): ";
    for (double x : V) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}