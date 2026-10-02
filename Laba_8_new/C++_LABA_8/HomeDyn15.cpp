#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "HomeDyn15.h"
#include "input.h"

bool isValidDyn15(int k, int n) {
    return (k >= 2 && k <= 10) && (n > 1 && n < 20) && (n + k < 26);
}

void HomeDyn15() {
    std::cout << "Задание: HomeDyn15\n";
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
        int k = 0, n = 0;
        if (choice == 1) {
            bool flag = true;
            do {
                std::cout << "Введите основание системы счисления K (2 <= K <= 10): ";
                k = Input_Int();
                if (k < 2 || k > 10) {
                    std::cout << "Ошибка: K должно быть от 2 до 10.\n";
                    continue;
                }
                std::cout << "Введите разряд N (1 < N < 20 и N + K < 26): ";
                n = Input_Int();
                if (!isValidDyn15(k, n)) {
                    std::cout << "Ошибка: N должно удовлетворять 1 < N < 20 и N + K < 26.\n";
                    flag = false;
                }
                else {
                    flag = true;
                }
            } while (!flag);
        }
        else if (choice == 2) {
            k = std::rand() % 9 + 2;
            int max_n = std::min(19, 25 - k);
            if (max_n <= 1) max_n = 2;
            n = std::rand() % (max_n - 1) + 2;
            std::cout << "\n[Случайные данные] K = " << k << ", N = " << n << "\n";
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
            file >> k >> n;
            file.close();
            if (!isValidDyn15(k, n)) {
                std::cout << "Ошибка: Данные в файле не удовлетворяют условиям (2<=K<=10, 1<N<20, N+K<26).\n";
                continue;
            }
        }
        else {
            break;
        }
        int nz = k - 1;
        int oz = 1;
        int tz = 0;
        for (int i = 2; i <= n; i++) {
            int _nz = nz;
            int _oz = oz;
            int _tz = tz;
            nz = (_nz + _oz + _tz) * (k - 1);
            oz = _nz;
            tz = _oz;
        }
        double result = (double)(nz + oz + tz);
        std::cout << "\nКоличество " << k << "-ичных чисел из " << n << " разрядов, где не содержатся 3 и более идущих подряд 0: " << result << "\n";
    } while (choice != 4);
}