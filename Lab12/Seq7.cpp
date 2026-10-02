#include "Seq7.h"
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
#include <cstdlib>      
#define NOMINMAX
#include <windows.h>

void seq7() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int n = get_even_number("Введите чётное количество элементов: ");
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
        for (int i = 0; i < n; ++i) {
            temp_data[i] = rand() % 100;
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
        else {
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
    }
    std::vector<int> V(temp_data.begin(), temp_data.end());
    std::deque<int>  D(temp_data.begin(), temp_data.end());
    std::list<int>   L(temp_data.begin(), temp_data.end());

    std::cout << "\nДо: ";
    print_forward("Вектор V", V);
    print_forward("Дек D", D);
    print_forward("Список L", L);
    std::cout << "\nRbegin/rend: ";
    print_backward("Вектор V", V);
    int mid1 = n / 2 - 1;
    int mid2 = n / 2;
    std::cout << "\nОбмен: \n";
    std::cout << "Обмен позиций " << (mid1 + 1) << " и " << (mid2 + 1) << "\n";
    std::swap(V[mid1], V[mid2]);
    std::swap(D[mid1], D[mid2]);
    auto it1 = std::next(L.begin(), mid1);
    auto it2 = std::next(L.begin(), mid2);
    std::swap(*it1, *it2);
    std::cout << "\nПосле: \n";
    print_forward("Вектор V", V);
    print_forward("Дек D", D);
    print_forward("Список L", L);
}