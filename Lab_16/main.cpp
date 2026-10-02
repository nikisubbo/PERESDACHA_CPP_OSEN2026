#include <iostream>
#include <windows.h>
#include "sup.h"
#include "TreeWork4.h"
#include "TreeWork15.h"
#include "TreeWork17.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice = 0;
    std::string menu_message = "Меню:\n1) TreeWork4\n2) TreeWork15\n3) TreeWork17\n4) Проверки\n5) Выход\nВыберите номер задачи: ";

    while (choice != 5) {
        std::cout << menu_message;
        choice = Input_Int();
        if (choice < 1 || choice > 5) {
            std::cout << "\nОшибка. Пожалуйста, введите число от 1 до 5.\n\n";
            continue;
        }
        switch (choice) {
        case 1: TreeWork4Task(); break;
        case 2: TreeWork15Task(); break;
        case 3: TreeWork17Task(); break;
        case 4:
            TestTreeWork4::run();
            TestTreeWork15::run();
            TestTreeWork17::run();
            break;
        }
        std::cout << "\n";
    }

    std::cout << "Завершение работы..." << std::endl;
    return 0;
}