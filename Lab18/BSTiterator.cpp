#include "BSiterator.h"
#include <fstream>
#include "sup.h"
#include <iostream>

Node3::Node3(int k) : key(k), left(nullptr), right(nullptr) {}

int Node3::get_key() const { return key; }
Node3* Node3::get_left() const { return left; }
Node3* Node3::get_right() const { return right; }

void Node3::set_left(Node3* node) { left = node; }
void Node3::set_right(Node3* node) { right = node; }

TreeIterator::TreeIterator(Node3* root) : curr(root) {}

bool TreeIterator::has_next() {
    return !st.empty() || curr != nullptr;
}

int TreeIterator::next() {
    while (curr != nullptr) {
        st.push(curr);
        curr = curr->get_left();
    }
    Node3* node = st.top();
    st.pop();
    curr = node->get_right();
    return node->get_key();
}

BTree::BTree() : root(nullptr) {}
BTree::~BTree() { cleanup(); }

void BTree::build(const std::vector<int>& data) {
    if (data.empty()) return;
    std::queue<Node3*> q;
    root = new Node3(data[0]);
    q.push(root);
    int i = 1;
    while (!q.empty() && i < data.size()) {
        Node3* cur = q.front(); q.pop();
        if (i < data.size()) {
            cur->set_left(new Node3(data[i++]));
            q.push(cur->get_left());
        }
        if (i < data.size()) {
            cur->set_right(new Node3(data[i++]));
            q.push(cur->get_right());
        }
    }
}

void BTree::print() const { print_node(root, 0); }

void BTree::print_node(Node3* node, int level) const {
    if (!node) return;
    print_node(node->get_right(), level + 1);
    for (int i = 0; i < level; ++i) std::cout << "    ";
    std::cout << node->get_key() << "\n";
    print_node(node->get_left(), level + 1);
}

void BTree::cleanup() { clear_node(root); root = nullptr; }

void BTree::clear_node(Node3* node) {
    if (!node) return;
    clear_node(node->get_left());
    clear_node(node->get_right());
    delete node;
}

TreeIterator BTree::get_iter() const { return TreeIterator(root); }

void HowToFill(BTree& tree) {
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
            tree.build(data);
            break;
        }
        case 2: {
            std::cout << "Введите количество элементов: ";
            int n = Input_Int();
            for (int i = 0; i < n; i++) {
                data.push_back(std::rand() % 100);
            }
            tree.build(data);
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
                tree.build(data);
            }
            break;
        }
        }
    } while (choice != 4);
}