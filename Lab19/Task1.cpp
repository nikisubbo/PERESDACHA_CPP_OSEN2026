#include <iostream>
#include "Hemming.h"
#include "sup.h"

void Task1() {
    std::cout << "Задача 1. Код Хэмминга.\n";
    std::string message;
    HowToFillHemming(message);
    HemmingCode h(message);
    h.printEmpty();
    std::cout << "\nПосле вычисления контрольных битов: ";
    h.run();
    h.printFull();
    std::cout << "Введите номер бита для ошибки: ";
    int error;
    error = Input_Int();
    while (error < 1 || error > h.get_n()) {
        std::cout << "\nОшибка. Введите число от 1 до " << h.get_n() << ": ";
        error = Input_Int();
    }
    h.insertError(error);
    std::cout << "\nПосле внесения ошибки: ";
    h.printSyndrome();
    std::cin.get();
}