#include "Tree6.h"
#include "sup.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

Node5::Node5(int t, int v) : type(t), val(v), l(nullptr), r(nullptr) {}

int Node5::get_type() const { return type; }
int Node5::get_val() const { return val; }
Node5* Node5::get_l() const { return l; }
Node5* Node5::get_r() const { return r; }

void Node5::set_l(Node5* node) { l = node; }
void Node5::set_r(Node5* node) { r = node; }

Node5* CalcTree5::parsePrefix(const std::vector<int>& tokens, int& pos) {
    if (pos >= (int)tokens.size()) return nullptr;
    int val = tokens[pos++];
    if (val >= 0) {
        return new Node5(0, val);
    }
    Node5* node = new Node5(2, val);
    node->set_l(parsePrefix(tokens, pos));
    node->set_r(parsePrefix(tokens, pos));
    return node;
}

int CalcTree5::calcut(Node5* node) {
    if (!node) return 0;
    if (node->get_type() == 0) return node->get_val();
    int l = calcut(node->get_l());
    int r = calcut(node->get_r());
    int op = node->get_val();
    if (op == -1) return l + r;
    if (op == -2) return l - r;
    if (op == -3) return l * r;
    if (op == -4) return (r != 0) ? l / r : 0;
    return 0;
}

Node5* CalcTree5::removeAddSub(Node5* node) {
    if (!node) return nullptr;
    if (node->get_type() == 0) return node;
    Node5* l = removeAddSub(node->get_l());
    Node5* r = removeAddSub(node->get_r());
    node->set_l(l);
    node->set_r(r);
    if (node->get_val() == -1 || node->get_val() == -2) {
        int res = calcut(node);
        deleteTree(node);
        return new Node5(0, res);
    }
    return node;
}

void CalcTree5::deleteTree(Node5* node) {
    if (!node) return;
    deleteTree(node->get_l());
    deleteTree(node->get_r());
    delete node;
}

void CalcTree5::printTree(Node5* node, int level) {
    if (!node) return;
    printTree(node->get_r(), level + 1);
    for (int i = 0; i < level; ++i) std::cout << "    ";
    if (node->get_type() == 0) {
        std::cout << node->get_val() << "\n";
    }
    else {
        char op = '?';
        switch (node->get_val()) {
        case -1: op = '+'; break;
        case -2: op = '-'; break;
        case -3: op = '*'; break;
        case -4: op = '/'; break;
        }
        std::cout << op << "\n";
    }
    printTree(node->get_l(), level + 1);
}

CalcTree5::CalcTree5(const std::string& filename) : root(nullptr) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "\nОшибка: файл не найден!\n";
        return;
    }
    std::vector<int> tokens;
    std::string token;
    while (in >> token) {
        if (token == "+") tokens.push_back(-1);
        else if (token == "-") tokens.push_back(-2);
        else if (token == "*") tokens.push_back(-3);
        else if (token == "/") tokens.push_back(-4);
        else {
            try {
                tokens.push_back(std::stoi(token));
            }
            catch (...) {
                std::cerr << "\nНеверный токен: " << token << "\n";
            }
        }
    }
    in.close();
    int pos = 0;
    root = parsePrefix(tokens, pos);
}
CalcTree5::CalcTree5(const std::vector<int>& tokens) : root(nullptr) {
    int pos = 0;
    root = parsePrefix(tokens, pos);
}

CalcTree5::~CalcTree5() { deleteTree(root); }

void CalcTree5::transform() {
    root = removeAddSub(root);
}

void CalcTree5::print() {
    printTree(root, 0);
}

Node5* CalcTree5::getRoot() const { return root; }

std::vector<int> parseExpressionString(const std::string& expr) {
    std::vector<int> tokens;
    std::istringstream iss(expr);
    std::string token;
    while (iss >> token) {
        if (token == "+") tokens.push_back(-1);
        else if (token == "-") tokens.push_back(-2);
        else if (token == "*") tokens.push_back(-3);
        else if (token == "/") tokens.push_back(-4);
        else {
            try {
                tokens.push_back(std::stoi(token));
            }
            catch (...) {
                std::cerr << "\nНеверный токен: " << token << "\n";
            }
        }
    }
    return tokens;
}

void CalcTree5Task() {
    std::cout << "\nЗадача 6 – Префиксное выражение\n";
    std::cout << "\nКак вы хотите получить выражение?\n";
    std::cout << "1) С клавиатуры\n";
    std::cout << "2) Случайно\n";
    std::cout << "3) Из файла\n";
    std::cout << "Выбор: ";
    int choice = Input_Int();
    while (choice < 1 || choice > 3) {
        std::cout << "Ошибка. Введите корректное число (1-3): ";
        choice = Input_Int();
    }

    std::vector<int> tokens;

    switch (choice) {
    case 1: {
        std::cout << "\nВведите префиксное выражение (через пробел, например: + 2 * 3 4): ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string expr;
        std::getline(std::cin, expr);
        while (expr.empty()) {
            std::cout << "Ошибка. Выражение не может быть пустым. Попробуйте снова: ";
            std::getline(std::cin, expr);
        }
        tokens = parseExpressionString(expr);
        break;
    }
    case 2: {
        std::string ops[] = { "+", "-", "*", "/" };
        int opCodes[] = { -1, -2, -3, -4 };
        int opIdx = std::rand() % 4;
        int num1 = std::rand() % 20 + 1;
        int num2 = std::rand() % 20 + 1;

        tokens.push_back(opCodes[opIdx]);
        tokens.push_back(num1);
        tokens.push_back(num2);

        std::cout << "\nСлучайное выражение: " << ops[opIdx] << " " << num1 << " " << num2 << "\n";
        break;
    }
    case 3: {
        std::string filename;
        std::cout << "\nВведите имя файла с выражением: ";
        std::cin >> filename;
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Ошибка. Не удалось открыть файл.\n";
            return;
        }
        std::string token;
        while (infile >> token) {
            if (token == "+") tokens.push_back(-1);
            else if (token == "-") tokens.push_back(-2);
            else if (token == "*") tokens.push_back(-3);
            else if (token == "/") tokens.push_back(-4);
            else {
                try {
                    tokens.push_back(std::stoi(token));
                }
                catch (...) {
                    std::cerr << "\nНеверный токен: " << token << "\n";
                }
            }
        }
        infile.close();
        if (tokens.empty()) {
            std::cerr << "Ошибка. Файл пуст.\n";
            return;
        }
        std::cout << "Выражение загружено из файла.\n";
        break;
    }
    }

    if (tokens.empty()) {
        std::cerr << "Ошибка. Не удалось получить выражение.\n";
        return;
    }

    CalcTree5 tree(tokens);
    std::cout << "\nИсходное дерево:\n";
    tree.print();

    tree.transform();
    std::cout << "\nПреобразованное дерево (без + и -):\n";
    tree.print();

    std::cout << "\nУказатель на корень: " << tree.getRoot() << "\n";
}