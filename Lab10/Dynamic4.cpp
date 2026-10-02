#include "Dynamic4.h"
#include "stack.h"
#include "input.h"
#include <iostream>

void Dynamic4(Stack& s) {
    std::cout << "Начало задания Dynamic 4\n";
    s.print();
    Node* ad = s.get_top();
    std::cout << "Вершина: " << ad;
    std::cout << "\nКонец задания Dynamic 4" << std::endl;
}