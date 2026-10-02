#include <iostream>
#include "sup.h"
#include "BSiterator.h"

void TreeFun3() {
    std::cout << "!!! Задача: Итератор для дерева !!!" << std::endl;
    std::cout << "Реализовать интерфейс итератора для бинарного дерева, "
        << "который будет возвращать значения элементов в узлах дерева "
        << "в порядке обхода: левый-корень-правый.";

    BTree Tree;
    HowToFill(Tree);

    std::cout << "\nИсходное дерево:\n";
    Tree.print();

    std::cout << "Обход с помощью итератора: ";
    TreeIterator it = Tree.get_iter();
    while (it.has_next()) {
        std::cout << it.next() << " ";
    }
}