#include <iostream>
#include <fstream>
#include <string>
#include "Dlist.h"

void ListWork63(DoublyList& list) {
    std::string filename = "ListWork63.txt";
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка. Не удалось открыть файл '" << filename << "'.\n";
        return;
    }
    if (list.is_empty()) {
        std::cout << "Список пуст.\n";
        file.close();
        return;
    }
    std::cout << "Запись списка в файл '" << filename << "'...\n";
    bool first = true;
    while (!list.is_empty()) {
        int value = list.remove_back();
        if (!first) {
            file << " ";
        }
        file << value;
        first = false;
    }
    file.close();
    std::cout << "Список пуст.\n";
    std::cout << "Результат сохранён в '" << filename << "'.\n";
}