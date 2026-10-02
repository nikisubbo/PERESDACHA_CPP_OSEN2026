#include <iostream>
#include <fstream>
#include "CircularList.h"

void CircularList::ListWork67(const std::string& filename) {
    if (!head) {
        std::cout << "Список пуст.\n";
        return;
    }
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка. Не удалось открыть файл '" << filename << "'.\n";
        return;
    }
    std::cout << "Запись в файл...\n";
    CNode* current = head;
    while (head != nullptr) {
        file << current->data;
        if (current == current->next) {
            delete current;
            head = nullptr;
            current = nullptr;
        }
        else {
            CNode* next_to_keep = current->next->next;
            CNode* to_delete = current;
            if (current == head) {
                head = next_to_keep;
            }
            CNode* prev = head;
            while (prev->next != to_delete) {
                prev = prev->next;
            }
            prev->next = next_to_keep;
            delete to_delete;
            current = next_to_keep;
        }
        if (head != nullptr) {
            file << " ";
        }
    }
    file.close();
    std::cout << "Успешно. Проверьте файл '" << filename << "'.\n";
    std::cout << "Список пуст.\n";
}