#include <iostream>
#include <ctime>
#include <fstream>
#include "BSTDlist.h"
#include "sup.h"

Node::Node(int k) : key(k), left(nullptr), right(nullptr) {}

int Node::get_key() const { return key; }
Node* Node::get_left() const { return left; }
Node* Node::get_right() const { return right; }

void Node::set_left(Node* node) { left = node; }
void Node::set_right(Node* node) { right = node; }

BinaryTree::BinaryTree() : root(nullptr) {}
BinaryTree::~BinaryTree() { clear(root); }

void BinaryTree::CompletionTree(const std::vector<int>& data) {
    for (int val : data) {
        if (!root) root = new Node(val);
        else add(root, val);
    }
}

void BinaryTree::add(Node* node, int val) {
    if (val == node->get_key()) return;
    if (val < node->get_key()) {
        if (!node->get_left()) node->set_left(new Node(val));
        else add(node->get_left(), val);
    }
    else {
        if (!node->get_right()) node->set_right(new Node(val));
        else add(node->get_right(), val);
    }
}

void BinaryTree::show() const { print(root, 0); }

void BinaryTree::print(Node* node, int level) const {
    if (!node) return;
    print(node->get_right(), level + 1);
    for (int i = 0; i < level; ++i)
        std::cout << "    ";
    std::cout << node->get_key() << "\n";
    print(node->get_left(), level + 1);
}

Node* BinaryTree::convert_to_list() {
    Node* head = nullptr;
    Node* prev = nullptr;
    convert(root, head, prev);
    root = nullptr;
    return head;
}

void BinaryTree::convert(Node* node, Node*& head, Node*& prev) {
    if (!node) return;
    convert(node->get_left(), head, prev);
    if (!head) head = node;
    if (prev) {
        node->set_left(prev);
        prev->set_right(node);
    }
    prev = node;
    convert(node->get_right(), head, prev);
}

void BinaryTree::show_list(Node* head) const {
    Node* curr = head;
    while (curr) {
        std::cout << curr->get_key() << " <=> ";
        curr = curr->get_right();
    }
    std::cout << "null\n";
}

void BinaryTree::cleanup() {
    clear(root);
    root = nullptr;
}

void BinaryTree::clear(Node* node) {
    if (!node) return;
    clear(node->get_left());
    clear(node->get_right());
    delete node;
}

void HowToFill(BinaryTree& tree) {
    int choice = 0;
    do {
        std::cout << "\nКак вы хотите заполнить дерево?\n";
        std::cout << "1) С клавиатуры\n";
        std::cout << "2) Случайно\n";
        std::cout << "3) Из файла\n";
        std::cout << "4) Назад\n";
        std::cout << "Выбор: ";

        choice = Input_Int();
        if (choice < 1 || choice > 4) {
            std::cout << "Ошибка. Введите корректное число (1-4).\n";
            continue;
        }
        std::vector<int> data;
        switch (choice) {
        case 1: {
            std::cout << "Введите количество элементов: ";
            int n = Input_Int();
            std::cout << "Введите " << n << " целых чисел:\n";
            for (int i = 0; i < n; i++) {
                data.push_back(Input_Int());
            }
            tree.CompletionTree(data);
            break;
        }
        case 2: {
            std::cout << "Введите количество элементов: ";
            int n = Input_Int();
            for (int i = 0; i < n; i++) {
                data.push_back(std::rand() % 100);
            }
            tree.CompletionTree(data);
            break;
        }
        case 3: {
            std::string filename;
            std::cout << "Введите имя файла (например, data.txt): ";
            std::cin >> filename;
            std::ifstream infile(filename);
            if (!infile.is_open()) {
                std::cerr << "Ошибка. Не удалось открыть файл.\n";
                break;
            }
            int number3;
            while (infile >> number3) {
                data.push_back(number3);
            }
            infile.close();
            if (data.empty()) {
                std::cerr << "Файл пуст или не содержит целых чисел.\n";
            }
            else {
                tree.CompletionTree(data);
            }
            break;
        }
        }
    } while (choice != 4);
}