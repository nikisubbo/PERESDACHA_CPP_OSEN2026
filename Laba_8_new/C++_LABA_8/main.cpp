#include <iostream>
#include "BackRec5.h"
#include "HomeDyn3.h"
#include "HomeDyn15.h"
#include "input.h"
int main() {
    setlocale(LC_ALL, "");
    int choice = 0;
    std::string menu_message = "Меню:\n1)BackRec5\n2)HomeDyn3\n3)HomeDyn15\n4)Выход\nВведите номер выбранного пункта меню: ";
    std::cout << menu_message;
    choice = Input_Int();
    while (choice != 4) {
        if (choice < 1 || choice > 4) {
            std::cout << "Ошибка. Некорректный ввод, попробуйте еще раз: " << std::endl;
        }
        else {
            switch (choice) {
            case 1:
                BackRec5();
                break;
            case 2:
                HomeDyn3();
                break;
            case 3:
                HomeDyn15();
                break;
            }
        }
        std::cout << menu_message;
        std::cin >> choice;
    }
    std::cout << "Завершение работы..." << std::endl;
    return 0;
}
