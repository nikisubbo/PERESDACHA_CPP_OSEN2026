#include "TreeWork4.h"
#include "sup.h"
#include <iostream>
#include <fstream>
#include <queue>

NodeW4::NodeW4(int k) : key(k), left(nullptr), right(nullptr) {}

int NodeW4::get_key() const { return key; }
NodeW4* NodeW4::get_left() const { return left; }
NodeW4* NodeW4::get_right() const { return right; }
void NodeW4::set_left(NodeW4* node) { left = node; }
void NodeW4::set_right(NodeW4* node) { right = node; }

TreeWork4::TreeWork4() : root(nullptr) {}
TreeWork4::~TreeWork4() { cleanup(); }

void TreeWork4::build(const std::vector<int>& data) {
    if (data.empty()) return;
    cleanup();
    root = new NodeW4(data[0]);
    std::queue<NodeW4*> q;
    q.push(root);
    int i = 1;
    while (!q.empty() && i < (int)data.size()) {
        NodeW4* cur = q.front(); q.pop();
        if (i < (int)data.size()) {
            cur->set_left(new NodeW4(data[i++]));
            q.push(cur->get_left());
        }
        if (i < (int)data.size()) {
            cur->set_right(new NodeW4(data[i++]));
            q.push(cur->get_right());
        }
    }
}

void TreeWork4::print() const { print_node(root, 0); }

void TreeWork4::print_node(NodeW4* node, int level) const {
    if (!node) return;
    print_node(node->get_right(), level + 1);
    for (int i = 0; i < level; ++i) std::cout << "    ";
    std::cout << node->get_key() << "\n";
    print_node(node->get_left(), level + 1);
}

void TreeWork4::cleanup() { clear_node(root); root = nullptr; }

void TreeWork4::clear_node(NodeW4* node) {
    if (!node) return;
    clear_node(node->get_left());
    clear_node(node->get_right());
    delete node;
}

void TreeWork4::collect_leaves(NodeW4* node, std::vector<int>& leaves) const {
    if (!node) return;
    if (!node->get_left() && !node->get_right()) {
        leaves.push_back(node->get_key());
        return;
    }
    collect_leaves(node->get_left(), leaves);
    collect_leaves(node->get_right(), leaves);
}

std::vector<int> TreeWork4::get_leaves() const {
    std::vector<int> leaves;
    collect_leaves(root, leaves);
    return leaves;
}

void HowToFillW4(TreeWork4& tree) {
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

void TreeWork4Task() {
    std::cout << "\n!!! Задача: TreeWork4 !!!\n";
    std::cout << "Вывести содержимое листьев дерева слева направо\n\n";

    TreeWork4 tree;
    HowToFillW4(tree);

    std::cout << "\nДерево до преобразования:\n";
    tree.print();

    std::vector<int> leaves = tree.get_leaves();
    std::cout << "\nЛистья дерева (слева направо): ";
    for (int v : leaves) std::cout << v << " ";
    std::cout << "\n";

    std::cin.get();
}

void TestTreeWork4::run() {
    std::cout << "\n=== Проверка  TreeWork4 ===\n";
    {
        TreeWork4 t;
        t.build({ 1, 2, 3, 4, 5 });
        auto leaves = t.get_leaves();
        std::cout << "Тест 1 (1,2,3,4,5): листья = ";
        for (int v : leaves) std::cout << v << " ";
        std::cout << (leaves == std::vector<int>{4, 5, 3} ? " OK\n" : " FAIL\n");
    }

    {
        TreeWork4 t;
        t.build({ 42 });
        auto leaves = t.get_leaves();
        std::cout << "Тест 2 (42): листья = ";
        for (int v : leaves) std::cout << v << " ";
        std::cout << (leaves == std::vector<int>{42} ? " OK\n" : " FAIL\n");
    }

    {
        TreeWork4 t;
        t.build({ 10, 20, 30, 40, 50, 60, 70 });
        auto leaves = t.get_leaves();
        std::cout << "Тест 3 (полное): листья = ";
        for (int v : leaves) std::cout << v << " ";
        std::cout << (leaves == std::vector<int>{40, 50, 60, 70} ? " OK\n" : " FAIL\n");
    }
}