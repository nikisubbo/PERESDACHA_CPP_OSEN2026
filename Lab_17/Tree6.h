#pragma once
#include <string>
#include <vector>

class Node5 {
private:
    int type;  
    int val;
    Node5* l;
    Node5* r;
public:
    Node5(int t, int v);
    int get_type() const;
    int get_val() const;
    Node5* get_l() const;
    Node5* get_r() const;
    void set_l(Node5* node);
    void set_r(Node5* node);
};

class CalcTree5 {
private:
    Node5* root;
    Node5* parsePrefix(const std::vector<int>& tokens, int& pos);
    int calcut(Node5* node);
    Node5* removeAddSub(Node5* node);
    void deleteTree(Node5* node);
    void printTree(Node5* node, int level);
public:
    CalcTree5(const std::string& filename);
    CalcTree5(const std::vector<int>& tokens);  
    ~CalcTree5();
    void transform();
    void print();
    Node5* getRoot() const;
};

void CalcTree5Task();