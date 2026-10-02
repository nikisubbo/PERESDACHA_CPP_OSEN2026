#include <iostream>
#include <windows.h>
#include "sup.h"
#include "TreeFun1.h"
#include "TreeFun3.h"
#include "TreeFun13.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice = 0;
    std::string menu_message = "Меню:\n1) Задача 1\n2) Задача 3\n3) Задача 13\n4) Выход\nВыберите номер задачи: ";

    while (choice != 4) {
        std::cout << menu_message;
        choice = Input_Int();
        if (choice < 1 || choice > 4) {
            std::cout << "\nОшибка. Пожалуйста, введите число от 1 до 4.\n\n";
            continue;
        }
        switch (choice) {
        case 1:
            TreeFun1();
            break;
        case 2:
            TreeFun3();
            break;
        case 3:
            TreeFun13();
            break;
        }
        std::cout << "\n";
    }

    std::cout << "Завершение работы..." << std::endl;
    return 0;
}