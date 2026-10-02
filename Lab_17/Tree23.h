#pragma once
#include <string>
class Node2 {
private:
    int type;
    int val;
    Node2* l;
    Node2* r;
public:
    Node2(int t, int v) : type(t), val(v), l(nullptr), r(nullptr) {}
    int get_type() const { return type; }
    int get_val() const { return val; }
    Node2* get_l() const { return l; }
    Node2* get_r() const { return r; }
    void set_l(Node2* node) { l = node; }
    void set_r(Node2* node) { r = node; }
    void set_val(int v) { val = v; }
};
class ExprTree2 {
private:
    Node2* root;
    Node2* base(const std::string& expr, int& pos);
    Node2* power(const std::string& expr, int& pos);
    Node2* mulDiv(const std::string& expr, int& pos);
    Node2* addMin(const std::string& expr, int& pos);
    int priority(char op);
    int operat(int a, int b, int op);
    int calcut(Node2* node, int x);
    void swapAddX(Node2* node);
    void toPrefix(Node2* node, std::string& res);
    void toPostfix(Node2* node, std::string& res);
    void toInfix(Node2* node, std::string& res);
    void deleteTree(Node2* node);
    void printTree(Node2* node, int level);
public:
    ExprTree2(const std::string& expr);
    ~ExprTree2();
    int compute(int x);
    void transform();
    void print();
    std::string getPrefix();
    std::string getPostfix();
    std::string getInfix();
};
void Tree23();