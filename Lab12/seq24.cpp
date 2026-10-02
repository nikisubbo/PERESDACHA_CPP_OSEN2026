#include "seq24.h"
#include "stl_utils.h"
#include <vector>
#include <list>
#include <iterator> 
#include <iostream>  
#include <string>       
#include <fstream>      
#include <limits>      
#include <random>       
#define NOMINMAX
#include <windows.h>

void seq24() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int n1 = get_odd_number("Введите нечётное количество элементов для L1 (>= 1): ", 1);
    std::vector<int> temp1(n1);
    std::cout << "\nВыберите способ ввода для L1:\n";
    std::cout << "1) С клавиатуры\n2) Случайные числа\n3) Из файла\n";
    std::cout << "Ваш выбор (1-3): ";
    int method1 = 0;
    std::cin >> method1;
    while (method1 < 1 || method1 > 3) {
        std::cout << "Неверный выбор. Пожалуйста, введите 1, 2 или 3: ";
        std::cin >> method1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (method1 == 1) {
        std::cout << "Введите " << n1 << " целых чисел для L1:\n";
        for (int i = 0; i < n1; ++i) {
            std::cin >> temp1[i];
        }
    }
    else if (method1 == 2) {
        std::cout << "Генерация " << n1 << " случайных чисел для L1:\n";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        for (int i = 0; i < n1; ++i) {
            temp1[i] = dis(gen);
            std::cout << temp1[i] << " ";
        }
        std::cout << "\n";
    }
    else if (method1 == 3) {
        std::string filename;
        std::cout << "Введите имя файла для L1 (например, data1.txt): ";
        std::cin >> filename;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка. Файл не открыт: " << filename << "\n";
            return;
        }
        int count = 0;
        while (count < n1 && file >> temp1[count]) {
            count++;
        }
        file.close();
        if (count < n1) {
            std::cout << "Внимание: Файл содержал только " << count << " элементов для L1.\n";
        }
    }
    int n2 = get_min_number("Введите количество элементов для L2 (>= 0): ", 0);
    std::vector<int> temp2(n2);

    if (n2 > 0) {
        std::cout << "\nВыберите способ ввода для L2:\n";
        std::cout << "1) С клавиатуры\n2) Случайные числа\n3) Из файла\n";
        std::cout << "Ваш выбор (1-3): ";
        int method2 = 0;
        std::cin >> method2;
        while (method2 < 1 || method2 > 3) {
            std::cout << "Неверный выбор. Пожалуйста, введите 1, 2 или 3: ";
            std::cin >> method2;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (method2 == 1) {
            std::cout << "Введите " << n2 << " целых чисел для L2:\n";
            for (int i = 0; i < n2; ++i) {
                std::cin >> temp2[i];
            }
        }
        else if (method2 == 2) {
            std::cout << "Генерация " << n2 << " случайных чисел для L2:\n";
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 100);
            for (int i = 0; i < n2; ++i) {
                temp2[i] = dis(gen);
                std::cout << temp2[i] << " ";
            }
            std::cout << "\n";
        }
        else if (method2 == 3) {
            std::string filename;
            std::cout << "Введите имя файла для L2 (например, data2.txt): ";
            std::cin >> filename;
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Ошибка. Файл не открыт: " << filename << "\n";
                return;
            }
            int count = 0;
            while (count < n2 && file >> temp2[count]) {
                count++;
            }
            file.close();
            if (count < n2) {
                std::cout << "Внимание: Файл содержал только " << count << " элементов для L2.\n";
            }
        }
    }
    std::list<int> L1(temp1.begin(), temp1.end());
    std::list<int> L2(temp2.begin(), temp2.end());
    std::cout << "\nДо: ";
    print_forward("Список L1", L1);
    print_forward("Список L2", L2);
    std::cout << "\nВыполнение задания: ";
    int mid_index = L1.size() / 2;
    auto mid_it = std::next(L1.begin(), mid_index);
    L2.splice(L2.end(), L1, mid_it);
    std::cout << "\nПосле: ";
    print_forward("Список L1", L1);
    print_forward("Список L2", L2);
    std::cout << "\nВ обратном порядке: ";
    print_backward("Список L2", L2);
}