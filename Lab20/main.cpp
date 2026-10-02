#define NOMINMAX
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <limits>
#include <windows.h>
#include "Money.h"

int main() {
    SetConsoleOutputCP(65001);  // UTF-8 для вывода
    SetConsoleCP(65001);        // UTF-8 для ввода
    std::cout << "\nКонструкторы: \n";
    Money m1;
    std::cout << "По умолчанию:        " << m1 << "\n";
    Money m2(15, 75);
    std::cout << "С параметрами:       " << m2 << "\n";
    Money m3(10, 150);
    std::cout << "Нормализация:        " << m3 << "\n";
    Money m4(m2);
    std::cout << "Копирование:         " << m4 << "\n";
    std::cout << "\nВвод (формат руб.коп). Выберите способ:\n";
    std::cout << "1. С клавиатуры\n";
    std::cout << "2. Случайно\n";
    std::cout << "3. Из файла (money.txt)\n";

    int choice;
    std::cout << "Ваш выбор: ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Money m5;

    if (choice == 1) {
        std::cout << "Введите сумму: ";
        std::cin >> m5; 
    }
    else if (choice == 2) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distRub(0, 1000);
        std::uniform_int_distribution<> distKop(0, 99);

        unsigned int r = distRub(gen);
        short int k = distKop(gen);

        m5 = Money(r, k);
        std::cout << "Сгенерировано случайно: " << m5 << "\n";
    }
    else if (choice == 3) {
        std::ifstream file("money.txt");
        if (file.is_open()) {
            unsigned int r;
            char dot;
            short int k;
            if (file >> r >> dot >> k && dot == '.' && k >= 0 && k < 100) {
                m5 = Money(r, k);
                std::cout << "Прочитано из файла money.txt: " << m5 << "\n";
            }
            else {
                std::cout << "Ошибка формата в файле. Установлено 0 руб. 0 коп.\n";
                m5 = Money(0, 0);
            }
            file.close();
        }
        else {
            std::cout << "Файл money.txt не найден в папке проекта. Установлено 0 руб. 0 коп.\n";
            m5 = Money(0, 0);
        }
    }
    else {
        std::cout << "Неверный выбор. Установлено 0 руб. 0 коп.\n";
        m5 = Money(0, 0);
    }

    std::cout << "Итоговая введенная сумма:  " << m5 << "\n";

    std::cout << "\nВычитание: \n";
    Money wallet(10, 50);
    std::cout << "Кошелек:             " << wallet << "\n";
    std::cout << "кошелек - 60:        " << (wallet - 60) << "\n";
    std::cout << "кошелек - 2000:      " << (wallet - 2000) << " (недостаточно средств)\n";
    Money debt(4, 25);
    std::cout << "кошелек - долг:      " << (wallet - debt) << "\n";
    Money bigDebt(20, 0);
    std::cout << "кошелек - большой:   " << (wallet - bigDebt) << " (недостаточно средств)\n";

    std::cout << "\nУнарные операции (++ / --)\n";
    Money counter(0, 99);
    std::cout << "Начало:              " << counter << "\n";
    ++counter;
    std::cout << "После ++:            " << counter << "\n";
    counter--;
    std::cout << "После --:            " << counter << "\n";
    counter++;
    std::cout << "После ++:            " << counter << "\n";

    std::cout << "\nПреобразование типов\n";
    Money test(42, 85);
    std::cout << "Сумма:               " << test << "\n";
    unsigned int rublesOnly = static_cast<unsigned int>(test);
    std::cout << "Как int (руб):       " << rublesOnly << "\n";
    std::cout << "Как bool:            " << (test ? "true" : "false") << "\n";
    Money zero;
    std::cout << "Ноль как bool:       " << (zero ? "true" : "false") << "\n";

    std::cout << "\nГотово.\n";
    return 0;
}