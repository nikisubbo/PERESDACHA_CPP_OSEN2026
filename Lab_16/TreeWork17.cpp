#include "TreeWork17.h"
#include "sup.h"
#include <iostream>
#include <fstream>

NodeW17::NodeW17(int k) : key(k), left(nullptr), right(nullptr) {}

int NodeW17::get_key() const { return key; }
NodeW17* NodeW17::get_left() const { return left; }
NodeW17* NodeW17::get_right() const { return right; }
void NodeW17::set_left(NodeW17* node) { left = node; }
void NodeW17::set_right(NodeW17* node) { right = node; }

TreeWork17::TreeWork17() : root(nullptr) {}
TreeWork17::~TreeWork17() { cleanup(); }

void TreeWork17::add(NodeW17* node, int val) {
    if (val == node->get_key()) return;
    if (val < node->get_key()) {
        if (!node->get_left()) node->set_left(new NodeW17(val));
        else add(node->get_left(), val);
    }
    else {
        if (!node->get_right()) node->set_right(new NodeW17(val));
        else add(node->get_right(), val);
    }
}

void TreeWork17::build(const std::vector<int>& data) {
    cleanup();
    if (data.empty()) return;
    root = new NodeW17(data[0]);
    for (size_t i = 1; i < data.size(); ++i) add(root, data[i]);
}

void TreeWork17::print() const { print_node(root, 0); }

void TreeWork17::print_node(NodeW17* node, int level) const {
    if (!node) return;
    print_node(node->get_right(), level + 1);
    for (int i = 0; i < level; ++i) std::cout << "    ";
    std::cout << node->get_key() << "\n";
    print_node(node->get_left(), level + 1);
}

void TreeWork17::cleanup() { clear_node(root); root = nullptr; }

void TreeWork17::clear_node(NodeW17* node) {
    if (!node) return;
    clear_node(node->get_left());
    clear_node(node->get_right());
    delete node;
}

// Второе минимальное значение за O(log n)
// Идём влево до конца (минимум). Если у минимума есть правый потомок —
// идём вправо и потом максимально влево. Иначе поднимаемся на уровень выше.
int TreeWork17::second_min() const {
    if (!root) return 0;

    NodeW17* cur = root;
    NodeW17* parent = nullptr;

    // Идём к минимуму
    while (cur->get_left()) {
        parent = cur;
        cur = cur->get_left();
    }

    // Если у минимума есть правый потомок — второе минимальное там
    if (cur->get_right()) {
        NodeW17* r = cur->get_right();
        while (r->get_left()) r = r->get_left();
        return r->get_key();
    }

    // Иначе второе минимальное — родитель минимума
    if (parent) return parent->get_key();

    // Если минимальный элемент — корень и у него нет левого потомка,
    // второе минимальное — минимум в правом поддереве
    NodeW17* r = root->get_right();
    if (!r) return root->get_key();
    while (r->get_left()) r = r->get_left();
    return r->get_key();
}

void HowToFillW17(TreeWork17& tree) {
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

void TreeWork17Task() {
    std::cout << "\n!!! Задача: TreeWork17 !!!\n";
    std::cout << "Вывести второе минимальное значение в дереве поиска за O(log n)\n\n";

    TreeWork17 tree;
    HowToFillW17(tree);

    std::cout << "\nДерево до преобразования:\n";
    tree.print();

    int sm = tree.second_min();
    std::cout << "\nВторое минимальное значение: " << sm << "\n";

    std::cin.get();
}

void TestTreeWork17::run() {
    std::cout << "\n=== Проверка TreeWork17 ===\n";

    {
        TreeWork17 t;
        t.build({ 10, 5, 15, 3, 7, 12, 20 });
        int sm = t.second_min();
        std::cout << "Тест 1 (10,5,15,3,7,12,20): 2-й мин = " << sm
            << (sm == 5 ? " OK\n" : " FAIL\n");
    }

    {
        TreeWork17 t;
        t.build({ 5, 3, 8, 1, 4 });
        int sm = t.second_min();
        std::cout << "Тест 2 (5,3,8,1,4): 2-й мин = " << sm
            << (sm == 3 ? " OK\n" : " FAIL\n");
    }

    {
        TreeWork17 t;
        t.build({ 2, 5, 8, 3 });
        int sm = t.second_min();
        std::cout << "Тест 3 (2,5,8,3): 2-й мин = " << sm
            << (sm == 3 ? " OK\n" : " FAIL\n");
    }
    {
        TreeWork17 t;
        t.build({ 10, 20 });
        int sm = t.second_min();
        std::cout << "Тест 4 (10,20): 2-й мин = " << sm
            << (sm == 20 ? " OK\n" : " FAIL\n");
    }
}