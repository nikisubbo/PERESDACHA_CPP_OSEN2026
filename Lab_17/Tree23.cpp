#include "Tree23.h"
#include "sup.h"
#include <iostream>
#include <fstream>
#include <string>

void skipSpaces(const std::string& expr, int& pos) {
    while (pos < (int)expr.size() && expr[pos] == ' ') pos++;
}

Node2* ExprTree2::base(const std::string& str, int& pos) {
    skipSpaces(str, pos);
    if (pos >= (int)str.size()) return nullptr;
    if (str[pos] == '(') {
        pos++;
        Node2* node = addMin(str, pos);
        skipSpaces(str, pos);
        if (pos < (int)str.size() && str[pos] == ')') pos++;
        return node;
    }
    if (std::isdigit(str[pos])) {
        int val = 0;
        while (pos < (int)str.size() && std::isdigit(str[pos])) {
            val = val * 10 + (str[pos] - '0');
            pos++;
        }
        return new Node2(0, val);
    }
    if (str[pos] == 'x') {
        pos++;
        return new Node2(1, 0);
    }
    return nullptr;
}

Node2* ExprTree2::power(const std::string& expr, int& pos) {
    Node2* node = base(expr, pos);
    while (true) {
        skipSpaces(expr, pos);
        if (pos >= (int)expr.size() || expr[pos] != '^') break;
        pos++;
        Node2* right = base(expr, pos);
        Node2* parent = new Node2(2, -6);
        parent->set_l(node);
        parent->set_r(right);
        node = parent;
    }
    return node;
}

Node2* ExprTree2::mulDiv(const std::string& expr, int& pos) {
    Node2* node = power(expr, pos);
    while (true) {
        skipSpaces(expr, pos);
        if (pos >= (int)expr.size()) break;
        char op = expr[pos];
        if (op != '*' && op != '/' && op != '%') break;
        pos++;
        Node2* right = power(expr, pos);
        int code = (op == '*') ? -3 : (op == '/') ? -4 : -5;
        Node2* parent = new Node2(2, code);
        parent->set_l(node);
        parent->set_r(right);
        node = parent;
    }
    return node;
}

Node2* ExprTree2::addMin(const std::string& expr, int& pos) {
    Node2* node = mulDiv(expr, pos);
    while (true) {
        skipSpaces(expr, pos);
        if (pos >= (int)expr.size()) break;
        char op = expr[pos];
        if (op != '+' && op != '-') break;
        pos++;
        Node2* right = mulDiv(expr, pos);
        int code = (op == '+') ? -1 : -2;
        Node2* parent = new Node2(2, code);
        parent->set_l(node);
        parent->set_r(right);
        node = parent;
    }
    return node;
}

int ExprTree2::priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

int ExprTree2::operat(int a, int b, int op) {
    switch (op) {
    case -1: return a + b;
    case -2: return a - b;
    case -3: return a * b;
    case -4:
        if (b == 0) {
            std::cerr << "\nДеление на ноль.\n";
            return 0;
        }
        return a / b;
    case -5:
        if (b == 0) {
            std::cerr << "\nОстаток от деления на ноль.\n";
            return 0;
        }
        return a % b;
    case -6: {
        if (b < 0) {
            std::cerr << "\nОтрицательная степень.\n";
            return 0;
        }
        int res = 1;
        for (int i = 0; i < b; ++i) res *= a;
        return res;
    }
    default: return 0;
    }
}

int ExprTree2::calcut(Node2* node, int x) {
    if (!node) return 0;
    if (node->get_type() == 0) return node->get_val();
    if (node->get_type() == 1) return x;
    int l = calcut(node->get_l(), x);
    int r = calcut(node->get_r(), x);
    return operat(l, r, node->get_val());
}

void ExprTree2::swapAddX(Node2* node) {
    if (!node) return;
    if (node->get_type() == 2 && node->get_val() == -1 &&
        node->get_r() && node->get_r()->get_type() == 1) {
        Node2* tmp = node->get_l();
        node->set_l(node->get_r());
        node->set_r(tmp);
    }
    swapAddX(node->get_l());
    swapAddX(node->get_r());
}

void ExprTree2::toPrefix(Node2* node, std::string& res) {
    if (!node) return;
    if (node->get_type() == 0) res += std::to_string(node->get_val()) + " ";
    else if (node->get_type() == 1) res += "x ";
    else {
        char op = '?';
        switch (node->get_val()) {
        case -1: op = '+'; break; case -2: op = '-'; break;
        case -3: op = '*'; break; case -4: op = '/'; break;
        case -5: op = '%'; break; case -6: op = '^'; break;
        }
        res += op; res += " ";
        toPrefix(node->get_l(), res);
        toPrefix(node->get_r(), res);
    }
}

void ExprTree2::toPostfix(Node2* node, std::string& res) {
    if (!node) return;
    toPostfix(node->get_l(), res);
    toPostfix(node->get_r(), res);
    if (node->get_type() == 0) res += std::to_string(node->get_val()) + " ";
    else if (node->get_type() == 1) res += "x ";
    else {
        char op = '?';
        switch (node->get_val()) {
        case -1: op = '+'; break; case -2: op = '-'; break;
        case -3: op = '*'; break; case -4: op = '/'; break;
        case -5: op = '%'; break; case -6: op = '^'; break;
        }
        res += op; res += " ";
    }
}

void ExprTree2::toInfix(Node2* node, std::string& res) {
    if (!node) return;
    if (node->get_type() == 0) res += std::to_string(node->get_val());
    else if (node->get_type() == 1) res += "x";
    else {
        res += "(";
        toInfix(node->get_l(), res);
        char op = '?';
        switch (node->get_val()) {
        case -1: op = '+'; break; case -2: op = '-'; break;
        case -3: op = '*'; break; case -4: op = '/'; break;
        case -5: op = '%'; break; case -6: op = '^'; break;
        }
        res += " "; res += op; res += " ";
        toInfix(node->get_r(), res);
        res += ")";
    }
}

void ExprTree2::deleteTree(Node2* node) {
    if (!node) return;
    deleteTree(node->get_l());
    deleteTree(node->get_r());
    delete node;
}

void ExprTree2::printTree(Node2* node, int level) {
    if (!node) return;
    printTree(node->get_r(), level + 1);
    for (int i = 0; i < level; ++i) std::cout << "    ";
    if (node->get_type() == 0) std::cout << node->get_val() << "\n";
    else if (node->get_type() == 1) std::cout << "x\n";
    else {
        char op = '?';
        switch (node->get_val()) {
        case -1: op = '+'; break; case -2: op = '-'; break;
        case -3: op = '*'; break; case -4: op = '/'; break;
        case -5: op = '%'; break; case -6: op = '^'; break;
        }
        std::cout << op << "\n";
    }
    printTree(node->get_l(), level + 1);
}

ExprTree2::ExprTree2(const std::string& expr) {
    int pos = 0;
    root = addMin(expr, pos);
}

ExprTree2::~ExprTree2() { deleteTree(root); }

int ExprTree2::compute(int x) { return calcut(root, x); }

void ExprTree2::transform() { swapAddX(root); }

void ExprTree2::print() { printTree(root, 0); }

std::string ExprTree2::getPrefix() {
    std::string res;
    toPrefix(root, res);
    return res;
}

std::string ExprTree2::getPostfix() {
    std::string res;
    toPostfix(root, res);
    return res;
}

std::string ExprTree2::getInfix() {
    std::string res;
    toInfix(root, res);
    return res;
}

void Tree23() {
    std::string fn1, fn2;
    std::cout << "\nЗадача 23 – Инфиксная запись\n";

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

    std::string expr;

    switch (choice) {
    case 1: {
        std::cout << "\nВведите выражение в инфиксной форме: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, expr);
        while (expr.empty()) {
            std::cout << "Ошибка. Выражение не может быть пустым. Попробуйте снова: ";
            std::getline(std::cin, expr);
        }
        break;
    }
    case 2: {
        std::string ops = "+-*/";
        int a = std::rand() % 20 + 1;
        int b = std::rand() % 20 + 1;
        int c = std::rand() % 20 + 1;
        char op1 = ops[std::rand() % ops.length()];
        char op2 = ops[std::rand() % ops.length()];
        expr = std::to_string(a) + " " + op1 + " " + std::to_string(b) + " " + op2 + " " + std::to_string(c);
        std::cout << "\nСлучайное выражение: " << expr << "\n";
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
        std::getline(infile, expr);
        infile.close();
        if (expr.empty()) {
            std::cerr << "Ошибка. Файл пуст.\n";
            return;
        }
        std::cout << "Выражение из файла: " << expr << "\n";
        break;
    }
    }

    std::cout << "\nВведите имя файла 1 для записи выражения: ";
    std::cin >> fn1;
    std::ofstream out1(fn1);
    if (!out1) {
        std::cerr << "\nОшибка: не удалось создать файл " << fn1 << "\n";
        return;
    }
    out1 << expr;
    out1.close();
    std::cout << "\nВыражение записано в " << fn1 << "\n";

    std::cout << "\nВведите имя файла 2 для вывода результатов: ";
    std::cin >> fn2;

    int x;
    do {
        std::cout << "\nВведите значение x (не 0): ";
        x = Input_Int();
        if (x == 0) {
            std::cout << "\nОшибка: x не может быть 0!\n";
        }
    } while (x == 0);

    ExprTree2 tree(expr);
    std::cout << "\nДерево до преобразования:\n";
    tree.print();

    int res = tree.compute(x);

    std::ofstream out2(fn2, std::ios::trunc);
    if (!out2) {
        std::cerr << "\nОшибка: не удалось создать файл " << fn2 << "\n";
        return;
    }
    out2 << "\nВыражение: " << expr << "\n";
    out2 << "\nx = " << x << ", результат: " << res << "\n";
    std::cout << "\nВыражение: " << expr << "\n";
    std::cout << "\nx = " << x << ", результат: " << res << "\n";

    tree.transform();
    std::cout << "\nДерево после замены A+x на x+A:\n";
    tree.print();
    out2 << "\nДерево после замены A+x на x+A:\n";

    out2 << "Префиксная: " << tree.getPrefix() << "\n";
    out2 << "Постфиксная: " << tree.getPostfix() << "\n";
    out2 << "Инфиксная: " << tree.getInfix() << "\n";
    std::cout << "Префиксная: " << tree.getPrefix() << "\n";
    std::cout << "Постфиксная: " << tree.getPostfix() << "\n";
    std::cout << "Инфиксная: " << tree.getInfix() << "\n";

    out2.close();
    std::cout << "\nРезультат записан в " << fn2 << "\n";
}