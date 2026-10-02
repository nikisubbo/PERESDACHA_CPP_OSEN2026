#include <iostream>
#include <limits>
#define NOMINMAX
#include <windows.h>
#include "Alg1.h"
#include "Alg28.h"
#include "Alg38.h"
#include "Alg60.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice = 0;
    std::string menu_message = "Меню:\n1) Alg1\n2) Alg28\n3) Alg38\n4) Alg60\n5) Выход\nВыберите номер задачи: ";

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
            alg1();
            break;
        case 2:
            alg28();
            break;
        case 3:
            alg38();
            break;
        case 4:
            alg60();
            break;
        }
        std::cout << "\n";
    }

    std::cout << "Завершение работы..." << std::endl;
    return 0;
}