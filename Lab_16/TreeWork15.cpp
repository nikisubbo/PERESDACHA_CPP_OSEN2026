#include "TreeWork15.h"
#include "sup.h"
#include <iostream>
#include <fstream>

NodeW15::NodeW15(int k) : key(k), left(nullptr), right(nullptr) {}

int NodeW15::get_key() const { return key; }
NodeW15* NodeW15::get_left() const { return left; }
NodeW15* NodeW15::get_right() const { return right; }
void NodeW15::set_left(NodeW15* node) { left = node; }
void NodeW15::set_right(NodeW15* node) { right = node; }

TreeWork15::TreeWork15() : root(nullptr) {}
TreeWork15::~TreeWork15() { cleanup(); }

void TreeWork15::add(NodeW15* node, int val) {
    if (val == node->get_key()) return;
    if (val < node->get_key()) {
        if (!node->get_left()) node->set_left(new NodeW15(val));
        else add(node->get_left(), val);
    }
    else {
        if (!node->get_right()) node->set_right(new NodeW15(val));
        else add(node->get_right(), val);
    }
}

void TreeWork15::build(const std::vector<int>& data) {
    cleanup();
    if (data.empty()) return;
    root = new NodeW15(data[0]);
    for (size_t i = 1; i < data.size(); ++i) add(root, data[i]);
}

void TreeWork15::print() const { print_node(root, 0); }

void TreeWork15::print_node(NodeW15* node, int level) const {
    if (!node) return;
    print_node(node->get_right(), level + 1);
    for (int i = 0; i < level; ++i) std::cout << "    ";
    std::cout << node->get_key() << "\n";
    print_node(node->get_left(), level + 1);
}

void TreeWork15::cleanup() { clear_node(root); root = nullptr; }

void TreeWork15::clear_node(NodeW15* node) {
    if (!node) return;
    clear_node(node->get_left());
    clear_node(node->get_right());
    delete node;
}

NodeW15* TreeWork15::find(int k, int& count) const {
    count = 0;
    NodeW15* cur = root;
    while (cur) {
        count++;
        if (k == cur->get_key()) return cur;
        if (k < cur->get_key()) cur = cur->get_left();
        else cur = cur->get_right();
    }
    return nullptr;
}

void HowToFillW15(TreeWork15& tree) {
    int choice = 0;
    do {
        std::cout << "\nКак вы хотите заполнить дерево поиска?\n";
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
            std::cout << "Введите " << n << " целых чисел (без повторов):\n";
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

void TreeWork15Task() {
    std::cout << "\n!!! Задача: TreeWork15 !!!\n";
    std::cout << "Найти в дереве поиска вершину со значением K\n\n";

    TreeWork15 tree;
    HowToFillW15(tree);

    std::cout << "\nДерево до преобразования:\n";
    tree.print();

    std::cout << "\nВведите значение K для поиска: ";
    int k = Input_Int();

    int count = 0;
    NodeW15* result = tree.find(k, count);

    if (result) {
        std::cout << "\nВершина со значением " << k << " найдена.\n";
        std::cout << "Указатель P2: " << result << "\n";
    }
    else {
        std::cout << "\nВершина со значением " << k << " не найдена.\n";
        std::cout << "Указатель P2: NULL\n";
    }
    std::cout << "Количество проанализированных вершин N = " << count << "\n";

    std::cin.get();
}

void TestTreeWork15::run() {
    std::cout << "\n=== Проверка  TreeWork15 ===\n";
    {
        TreeWork15 t;
        t.build({ 10, 5, 15, 3, 7, 12, 20 });
        int count = 0;
        NodeW15* r = t.find(7, count);
        std::cout << "Тест 1 (поиск 7): найдена = " << (r != nullptr ? "да" : "нет")
            << ", N = " << count << (count == 3 ? " OK\n" : " FAIL\n");
    }

    {
        TreeWork15 t;
        t.build({ 10, 5, 15 });
        int count = 0;
        NodeW15* r = t.find(99, count);
        std::cout << "Тест 2 (поиск 99): найдена = " << (r != nullptr ? "да" : "нет")
            << ", N = " << count << (r == nullptr ? " OK\n" : " FAIL\n");
    }

    {
        TreeWork15 t;
        t.build({ 10, 5, 15 });
        int count = 0;
        NodeW15* r = t.find(10, count);
        std::cout << "Тест 3 (поиск корня 10): N = " << count << (count == 1 ? " OK\n" : " FAIL\n");
    }
}