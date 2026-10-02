#include <iostream>
#include "sup.h"
#include "BSTDlist.h"
#include "TreeFun1.h"

void TreeFun1() {
    std::cout << "!!! Задача: Дерево в список !!!" << std::endl;
    std::cout << "Преобразовать бинарное дерево поиска в двусвязный список без использования дополнительной памяти\n\n" << std::endl;

    BinaryTree Tree;
    HowToFill(Tree);

    std::cout << "\nИсходное дерево поиска:\n";
    Tree.show();

    Node* List = Tree.convert_to_list();
    std::cout << "\nПолученный двусвязный список: ";
    Tree.show_list(List);

    Node* current = List;
    while (current != nullptr) {
        Node* next = current->get_right();
        delete current;
        current = next;
    }
}