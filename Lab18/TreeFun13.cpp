#include <iostream>
#include "sup.h"
#include "BTree.h"

void TreeFun13() {
    std::cout << "!!! Задача: Удаление повторяющихся поддеревьев !!!" << std::endl;
    std::cout << "Найти и удалить все повторяющиеся поддеревья, начиная с самых больших\n\n" << std::endl;

    ByTree Tree;
    HowToFill(Tree);

    std::cout << "\n Исходное дерево:\n";
    Tree.print();

    Tree.remove_duplicate_subtrees();

    std::cout << "\n Дерево после удаления повторяющихся поддеревьев:\n";
    Tree.print();
}