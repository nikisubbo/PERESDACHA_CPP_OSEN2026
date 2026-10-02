#include "seq12.h"
#include "stl_utils.h"
#include <iostream>   
#include <string>      
#include <vector>
#include <deque>
#include <list>
#include <iterator>   
#include <utility>   
#include <fstream>      
#include <limits>      
#include <random>       
#define NOMINMAX
#include <windows.h>

void seq12() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int n = get_min_number("Введите количество элементов >= 5: ", 5);
    std::cout << "\nВыберите способ ввода:\n";
    std::cout << "1) С клавиатуры\n";
    std::cout << "2) Случайные числа\n";
    std::cout << "3) Из файла\n";
    std::cout << "Ваш выбор (1-3): ";
    int method = 0;
    std::cin >> method;
    while (method < 1 || method > 3) {
        std::cout << "Неверный выбор. Пожалуйста, введите 1, 2 или 3: ";
        std::cin >> method;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::vector<int> temp_data(n);

    if (method == 1) {
        std::cout << "Введите " << n << " целых чисел через пробел:\n";
        for (int i = 0; i < n; ++i) {
            std::cin >> temp_data[i];
        }
    }
    else if (method == 2) {
        std::cout << "Генерация " << n << " случайных чисел:\n";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        for (int i = 0; i < n; ++i) {
            temp_data[i] = dis(gen);
            std::cout << temp_data[i] << " ";
        }
        std::cout << "\n";
    }
    else if (method == 3) {
        std::string filename;
        std::cout << "Введите имя файла (например, data.txt): ";
        std::cin >> filename;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка. Файл не открыт: " << filename << "\n";
            return;
        }
        int count = 0;
        std::cout << "Чтение из файла...\n";
        while (count < n && file >> temp_data[count]) {
            count++;
        }
        file.close();
        if (count < n) {
            std::cout << "Внимание: Файл содержал только " << count << " элементов.\n";
        }
    }
    std::deque<int> D(temp_data.begin(), temp_data.end());
    std::list<int>  L(temp_data.begin(), temp_data.end());
    std::cout << "\nДо: ";
    print_forward("Дек D", D);
    print_forward("Список L", L);
    std::cout << "\nВ обратном порядке: ";
    print_backward("Дек D", D);
    print_backward("Список L", L);
    std::cout << "\nВыполнение задания: ";
    auto insert_pos = std::prev(L.end(), 5);
    auto d_first = D.rbegin();
    auto d_last = D.rbegin() + 5;
    L.insert(insert_pos, d_first, d_last);
    std::cout << "\nПосле: ";
    print_forward("Дек D", D);
    print_forward("Список L", L);
}