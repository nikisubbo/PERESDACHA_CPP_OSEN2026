#include <iostream>
#include "DoubleClist.h"

void ListWork42(CircularDoublyList& l) {
    Node* original_head = l.get_head();
    Node* original_tail = l.get_tail();

    if (original_head) {
        std::cout << "\nАдрес первого элемента: " << original_head << ", значение: " << original_head->data;
        std::cout << "\nАдрес последнего элемента: " << original_tail << ", значение: " << original_tail->data << "\n";
    }
    else {
        std::cout << "\nСписок пуст.";
        return;
    }

    Node* new_tail = l.listwork42();
    std::cout << "\nПосле удаления:";

    if (l.is_empty()) {
        std::cout << "\nСписок пуст";
    }
    else {
        l.print();
    }

    if (new_tail) {
        std::cout << "\nАдрес последнего элемента после удаления: " << new_tail << ", значение: " << new_tail->data << "\n";
    }
    else {
        std::cout << "\nСписок пуст.";
    }
}