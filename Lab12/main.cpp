#include <iostream>
#include <limits>
#define NOMINMAX
#include <windows.h>
#include "Seq7.h"
#include "Seq12.h"
#include "Seq24.h"
#include "iter15.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice = 0;
    std::string menu_message = "Меню:\n1) Seq7\n2) Seq12\n3) Seq24\n4) Iter15\n5) Выход\nВыберите номер задачи: ";

    while (true) {
        std::cout << menu_message;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nОшибка. Пожалуйста, введите число от 1 до 5.\n\n";
            continue;
        }

        if (choice < 1 || choice > 5) {
            std::cout << "\nОшибка. Пожалуйста, введите число от 1 до 5.\n\n";
            continue;
        }
        if (choice == 5) {
            break;
        }
        switch (choice) {
        case 1:
            seq7();
            break;
        case 2:
            seq12();
            break;
        case 3:
            seq24();
            break;
        case 4:
            iter15();
            break;
        }
        std::cout << "\n";
    }

    std::cout << "Завершение работы..." << std::endl;
    return 0;
}