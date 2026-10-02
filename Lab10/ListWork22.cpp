#include <iostream>
#include "input.h"
#include "list.h"

void ListWork22(LinkedList& l) {
    std::cout << "Введите M: ";
    int m = Input_Int();
    ListNode* p2 = l.every_second(m);
    std::cout << "Ссылка на последний элемент (P2): " << p2 << "\n";
}