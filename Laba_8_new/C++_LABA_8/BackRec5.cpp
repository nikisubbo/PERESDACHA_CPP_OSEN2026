#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Backrec5.h"
#include "input.h"

void Algorithm(std::vector<int> w, std::vector<int> p, int max_weight, int n) {
    std::cout << "Запуск алгоритма...\n";
    std::vector<std::vector<int>> a(n + 1, std::vector<int>(max_weight + 1, 0));
    for (int k = 1; k <= n; k++) {
        for (int s = 1; s <= max_weight; s++) {
            if (s >= w[k]) {
                a[k][s] = std::max(a[k - 1][s], a[k - 1][s - w[k]] + p[k]);
            }
            else {
                a[k][s] = a[k - 1][s];
            }
        }
    }
    int current_weight = max_weight;
    std::vector<int> selected_items;
    for (int k = n; k >= 1; k--) {
        if (current_weight >= w[k] && a[k][current_weight] == a[k - 1][current_weight - w[k]] + p[k]) {
            selected_items.push_back(k);
            current_weight -= w[k];
        }
    }
    std::cout << "Общая ценность: " << a[n][max_weight] << "\n";
    std::cout << "Итоговая масса: " << max_weight - current_weight << "\n";
    std::cout << "Номера выбранных предметов: ";
    for (size_t i = 0; i < selected_items.size(); i++) {
        std::cout << selected_items[i] << " ";
    }
    std::cout << "\n";
}

void BackRec5() {
    std::cout << "Задание: BackRec5\n";
    int choice = 0;
    do {
        std::cout << "\nКак вы хотите ввести данные?\n";
        std::cout << "1) С клавиатуры\n";
        std::cout << "2) Случайно\n";
        std::cout << "3) Из файла\n";
        std::cout << "4) Назад\n";
        std::cout << "Выбор: ";
        choice = Input_Int();
        if (choice < 1 || choice > 4) {
            std::cout << "Ошибка. Введите число от 1 до 4.\n";
            continue;
        }
        int n = 0, max_weight = 0;
        std::vector<int> weight, prices;
        if (choice == 1) {
            std::cout << "Введите количество предметов: ";
            n = Input_Int();
            std::cout << "Введите максимальный вес рюкзака: ";
            max_weight = Input_Int();
            weight.assign(n + 1, 0);
            prices.assign(n + 1, 0);
            std::cout << "Введите веса " << n << " предметов:\n";
            for (int i = 1; i <= n; i++) weight[i] = Input_Int();
            std::cout << "Введите цены " << n << " предметов:\n";
            for (int i = 1; i <= n; i++) prices[i] = Input_Int();
        }
        else if (choice == 2) {
            n = std::rand() % 6 + 5;
            max_weight = std::rand() % 30 + 20;
            weight.assign(n + 1, 0);
            prices.assign(n + 1, 0);
            for (int i = 1; i <= n; i++) {
                weight[i] = std::rand() % 15 + 1;
                prices[i] = std::rand() % 90 + 10;
            }
            std::cout << "\n[Случайные данные] Предметов: " << n << ", Макс. вес: " << max_weight << "\n";
        }
        else if (choice == 3) {
            std::string file_name;
            std::cout << "Введите название файла (без .txt): ";
            std::cin >> file_name;
            file_name += ".txt";
            std::ifstream file(file_name);
            while (!file.is_open()) {
                std::cout << "Файл не найден. Введите название заново: ";
                std::cin >> file_name;
                file_name += ".txt";
                file.open(file_name);
            }
            file >> n >> max_weight;
            weight.assign(n + 1, 0);
            prices.assign(n + 1, 0);
            for (int i = 1; i <= n; i++) file >> weight[i];
            for (int i = 1; i <= n; i++) file >> prices[i];
            file.close();
        }
        else {
            break;
        }
        std::cout << "\nРазмер рюкзака: " << max_weight << "\n";
        std::cout << "Кол-во предметов: " << n << "\n";
        std::cout << "Веса: ";
        for (int i = 1; i <= n; i++) std::cout << weight[i] << " ";
        std::cout << "\nЦены: ";
        for (int i = 1; i <= n; i++) std::cout << prices[i] << " ";
        std::cout << "\n";
        Algorithm(weight, prices, max_weight, n);
    } while (choice != 4);
}