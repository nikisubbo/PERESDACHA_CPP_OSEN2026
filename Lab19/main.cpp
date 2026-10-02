#include <iostream>
#include <windows.h>
#include "sup.h"
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice = 0;
    std::string menu_message = "Меню:\n1) Задача 1\n2) Задача 2\n3) Задача 3\n4) Выход\nВыберите номер задачи: ";

    while (choice != 4) {
        std::cout << menu_message;
        choice = Input_Int();
        if (choice < 1 || choice > 4) {
            std::cout << "\nОшибка. Пожалуйста, введите число от 1 до 4.\n\n";
            continue;
        }
        switch (choice) {
        case 1:
            Task1();
            break;
        case 2:
            Task2();
            break;
        case 3:
            Task3();
            break;
        }
        std::cout << "\n";
    }

    std::cout << "Завершение работы..." << std::endl;
    return 0;
}