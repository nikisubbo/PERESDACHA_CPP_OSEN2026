#include <iostream>
#include "File8.h"
#include "File41.h"
#include "File50.h"
#include "Recur15.h"
#include "WorkWithFiles.h"
int main() {
    setlocale(LC_ALL, "");
    int choice = 0;
    std::string menu_message = "Меню:\n1)File8\n2)File41\n3)File50\n4)Recur15\n5)Создать файл\n6)Вывести содержимое файла\n7)Выход\nВведите номер выбранного пункта меню: ";
    std::cout << menu_message;
    std::cin >> choice;
    while (choice != 7) {
        if (choice < 1 || choice > 7 || !(std::cin >> choice)) {
            std::cin.clear();
			std::cin.ignore();
            std::cout << "Ошибка. Некорректный ввод, попробуйте еще раз: " << std::endl;
        }
        else {
            switch (choice) {
            case 1:
                File8();
                break;
            case 2:
                File41();
                break;
            case 3:
                File50();
                break;
            case 4:
                Recur15();
                break;
            case 5:
                CreateFile();
                break;
            case 6:
                PrintFile();
                break;
            }
        }
        std::cout << menu_message;
        std::cin >> choice;
    }
    std::cout << "Завершение работы..." << std::endl;
    return 0;
}