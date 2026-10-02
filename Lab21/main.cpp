#include <iostream>
#include <Windows.h>
#include "sup.h"
#include "Graf1.h"
#include "Graf4.h"
#include "Graf8.h"

int main() {
    SetConsoleOutputCP(65001); 
    SetConsoleCP(65001);


    int choice = 0;
    std::string menu_message = "Меню:\n1) Граф 1\n2) Граф 4\n3) Граф 8\n4) Выход\nВыберите номер задачи: ";

    while (choice != 4) {
        std::cout << menu_message;
        choice = Input_Int();
        if (choice < 1 || choice > 4) {
            std::cout << "\nОшибка. Пожалуйста, введите число от 1 до 4.\n\n";
            continue;
        }
        switch (choice) {
        case 1:
            Graf1();
            break;
        case 2:
            Graf4();
            break;
        case 3:
            Graf8();
            break;
        }
        std::cout << "\n";
    }

    std::cout << "Завершение работы..." << std::endl;
    return 0;
}