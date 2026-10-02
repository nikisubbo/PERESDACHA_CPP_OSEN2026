#define NOMINMAX
#include <iostream>
#include <windows.h>
#include <limits> 
#include "stack.h"
#include "queue.h"
#include "list.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    int choice = 0;
    std::string menu_message = "Меню:\n1) Меню стека\n2) Меню очереди\n3) Меню списка\n4) ListWork22\n5) ListWork60\n6) Выход\nВыберите номер задачи: ";

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
            stack_menu();
            break;
        case 2:
            queue_menu();
            break;
        case 3:
            list_menu();
            break;
        }
        std::cout << "\n";
    }

    std::cout << "Завершение работы..." << std::endl;
    return 0;
}