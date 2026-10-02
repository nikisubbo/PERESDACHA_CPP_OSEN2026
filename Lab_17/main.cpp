#include <iostream>
#include <windows.h>
#include "sup.h"
#include "Tree23.h"
#include "Tree6.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice = 0;
    std::string menu_message = "Меню:\n1) Задача 5\n2) Задача 23\n3) Выход\nВыберите номер задачи: ";

    while (choice != 3) {
        std::cout << menu_message;
        choice = Input_Int();
        if (choice < 1 || choice > 3) {
            std::cout << "\nОшибка. Пожалуйста, введите число от 1 до 3.\n\n";
            continue;
        }
        switch (choice) {
        case 1:
            CalcTree5Task();
            break;
        case 2:
            Tree23();
            break;
        }
        std::cout << "\n";
    }

    std::cout << "Завершение работы..." << std::endl;
    return 0;
}