#include <iostream>
#include "Dynamic26.h"
#include "queue.h"
#include "input.h"

void Dynamic26(Queue& q) {
    std::cout << "\nВведите N: ";
    int n = Input_Int();
    std::cout << "Как вы хотите задать множество чисел?\n1) Случайно\n2) С клавиатуры\n3) Из файла\nВыбор: ";
    int choice;
    while (true) {
        choice = Input_Int();
        if (choice == 1) {
            for (int i = 0; i < n; i++) {
                q.add(rand());
            }
            break;
        }
        else if (choice == 2) {
            for (int i = 0; i < n; i++) {
                q.add(Input_Int());
            }
            break;
        }
        else if (choice == 3) {
            std::cout << "Ввод из файла\n";
            break;
        }
        else {
            std::cout << "Ошибка. Введите число от 1 до 3: ";
            continue;
        }
    }
    std::cout << "Новый адрес начала (P1): " << q.get_top() << "\n";
    std::cout << "Новый адрес конца (P2): " << q.get_bottom() << "\n";
}