#include <iostream>
#include <limits>
#define NOMINMAX
#include <windows.h>
#include "Assoc2.h"
#include "Assoc17.h"
#include "Assoc21.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice = 0;
    std::string menu_message = "Меню:\n1) Assoc2\n2) Assoc17\n3) Assoc21\n4) Выход\nВыберите номер задачи: ";

    while (true) {
        std::cout << menu_message;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nОшибка. Пожалуйста, введите число от 1 до 4.\n\n";
            continue;
        }

        if (choice < 1 || choice > 4) {
            std::cout << "\nОшибка. Пожалуйста, введите число от 1 до 4.\n\n";
            continue;
        }
        if (choice == 4) {
            break;
        }
        switch (choice) {
        case 1:
            Assoc2();
            break;
        case 2:
            Assoc17();
            break;
        case 3:
            Assoc21();
            break;
        }
        std::cout << "\n";
    }

    std::cout << "Завершение работы..." << std::endl;
    return 0;
}