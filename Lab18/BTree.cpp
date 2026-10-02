#include "BTree.h"
#include <fstream>
#include "sup.h"
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <unordered_set>

Node13::Node13(int k) : key(k), left(nullptr), right(nullptr) {}

int Node13::get_key() const { return key; }
Node13* Node13::get_left() const { return left; }
Node13* Node13::get_right() const { return right; }

void Node13::set_left(Node13* node) { left = node; }
void Node13::set_right(Node13* node) { right = node; }

ByTree::ByTree() : root(nullptr) {}
ByTree::~ByTree() { cleanup(); }

void ByTree::build(const std::vector<int>& data) {
    if (data.empty()) return;
    clear_node(root);
    root = new Node13(data[0]);
    std::queue<Node13*> q;
    q.push(root);
    int i = 1;
    while (!q.empty() && i < data.size()) {
        Node13* cur = q.front(); q.pop();
        if (i < data.size()) {
            cur->set_left(new Node13(data[i++]));
            q.push(cur->get_left());
        }
        if (i < data.size()) {
            cur->set_right(new Node13(data[i++]));
            q.push(cur->get_right());
        }
    }
}

void ByTree::print() const { print_node(root, 0); }

void ByTree::print_node(Node13* node, int level) const {
    if (!node) return;
    print_node(node->get_right(), level + 1);
    for (int i = 0; i < level; ++i) std::cout << "    ";
    std::cout << node->get_key() << "\n";
    print_node(node->get_left(), level + 1);
}

void ByTree::cleanup() { clear_node(root); root = nullptr; }

void ByTree::clear_node(Node13* node) {
    if (!node) return;
    clear_node(node->get_left());
    clear_node(node->get_right());
    delete node;
}

int ByTree::subtree_size(Node13* node) const {
    if (!node) return 0;
    return 1 + subtree_size(node->get_left()) + subtree_size(node->get_right());
}

std::string ByTree::serialize(Node13* node) const {
    if (!node) return "#";
    return "(" + std::to_string(node->get_key()) + " " +
        serialize(node->get_left()) + " " +
        serialize(node->get_right()) + ")";
}

std::unordered_map<Node13*, Node13*> ByTree::build_parents() const {
    std::unordered_map<Node13*, Node13*> parents;
    if (!root) return parents;
    std::queue<Node13*> q;
    q.push(root);
    parents[root] = nullptr;
    while (!q.empty()) {
        Node13* cur = q.front(); q.pop();
        if (cur->get_left()) { parents[cur->get_left()] = cur; q.push(cur->get_left()); }
        if (cur->get_right()) { parents[cur->get_right()] = cur; q.push(cur->get_right()); }
    }
    return parents;
}

void ByTree::remove_duplicate_subtrees() {
    if (!root) return;

    std::unordered_map<std::string, std::vector<Node13*>> subtrees;
    std::queue<Node13*> q;
    q.push(root);

    while (!q.empty()) {
        Node13* cur = q.front(); q.pop();
        subtrees[serialize(cur)].push_back(cur);
        if (cur->get_left()) q.push(cur->get_left());
        if (cur->get_right()) q.push(cur->get_right());
    }

    struct DupGroup { int size; std::vector<Node13*> roots; };
    std::vector<DupGroup> duplicates;

    for (auto& pair : subtrees) {
        if (pair.second.size() > 1) {
            DupGroup g;
            g.size = subtree_size(pair.second[0]);
            g.roots = pair.second;
            duplicates.push_back(g);
        }
    }

    std::sort(duplicates.begin(), duplicates.end(),
        [](const DupGroup& a, const DupGroup& b) { return a.size > b.size; });

    std::unordered_set<Node13*> deleted;
    auto parents = build_parents();

    for (const auto& group : duplicates) {
        bool first_kept = false;
        for (Node13* node : group.roots) {
            if (deleted.count(node)) continue;

            if (!first_kept) { first_kept = true; continue; }

            auto it = parents.find(node);
            if (it != parents.end() && it->second != nullptr) {
                Node13* parent = it->second;
                if (parent->get_left() == node) parent->set_left(nullptr);
                else if (parent->get_right() == node) parent->set_right(nullptr);
            }

            std::queue<Node13*> to_delete;
            to_delete.push(node);
            while (!to_delete.empty()) {
                Node13* cur = to_delete.front(); to_delete.pop();
                if (!cur) continue;
                deleted.insert(cur);
                if (cur->get_left()) to_delete.push(cur->get_left());
                if (cur->get_right()) to_delete.push(cur->get_right());
                delete cur;
            }
        }
    }
}

void HowToFill(ByTree& tree) {
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
            for (int i = 0; i < n; i++) data.push_back(Input_Int());
            tree.build(data);
            break;
        }
        case 2: {
            std::cout << "Введите количество элементов: ";
            int n = Input_Int();
            for (int i = 0; i < n; i++) data.push_back(std::rand() % 100);
            tree.build(data);
            break;
        }
        case 3: {
            std::string filename;
            std::cout << "Введите имя файла (например, data.txt): ";
            std::cin >> filename;
            std::ifstream infile(filename);
            if (!infile.is_open()) { std::cerr << "Ошибка. Не удалось открыть файл.\n"; break; }
            int number3;
            while (infile >> number3) data.push_back(number3);
            infile.close();
            if (data.empty()) std::cerr << "Файл пуст.\n";
            else tree.build(data);
            break;
        }
        }
    } while (choice != 4);
}