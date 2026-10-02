#include <iostream>
#include <limits>
#define NOMINMAX
#include <windows.h>
#include "Dlist.h"
#include "DoubleClist.h"
#include "CircularList.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice = 0;
    std::string menu_message = "Меню:\n1) Меню кольцевого списка\n2) Меню кольцевого двусвязного списка\n3) Меню двусвязного списка\n4) ListWork22\n5) ListWork60\n6) Выход\nВыберите номер задачи: ";

    while (true) {
        std::cout << menu_message;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nОшибка. Пожалуйста, введите число от 1 до 6.\n\n";
            continue;
        }

        if (choice < 1 || choice > 6) {
            std::cout << "\nОшибка. Пожалуйста, введите число от 1 до 6.\n\n";
            continue;
        }
        if (choice == 6) {
            break;
        }
        switch (choice) {
        case 1:
            clist_menu();
            break;
        case 2:
            Dclist_menu();
            break;
        case 3:
            Dlist_menu();
            break;
        }
        std::cout << "\n";
    }

    std::cout << "Завершение работы..." << std::endl;
    return 0;
}