#include "CircularList.h"
#include "input.h"
#include <iostream>

void CircularList::Task3() {
    if (!head) {
        std::cout << "Список пуст.\n";
        return;
    }
    int n = size();
    bool has_negative = false;
    CNode* check = head;
    for (int i = 0; i < n; i++) {
        if (check->data < 0) {
            has_negative = true;
            break;
        }
        check = check->next;
    }
    if (!has_negative) {
        std::cout << "Без отрицательных элементов.\n";
        return;
    }
    CNode* current = head;
    CNode* best_start = nullptr;
    CNode* current_start = nullptr;
    int best_length = 0;
    int current_length = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (current->data < 0) {
            if (current_length == 0) {
                current_start = current;
            }
            current_length++;
            if (current_length > n) {
                current_length = n;
                current_start = current_start->next;
            }
            if (current_length > best_length) {
                best_length = current_length;
                best_start = current_start;
            }
        }
        else {
            current_length = 0;
            current_start = nullptr;
        }
        current = current->next;
    }
    std::cout << "Максимальная длина последовательности: " << best_length << "\n";
    std::cout << "Элементы: ";
    CNode* p = best_start;
    for (int i = 0; i < best_length; i++) {
        std::cout << p->data;
        if (i < best_length - 1) std::cout << ", ";
        p = p->next;
    }
    std::cout << "\n";
}