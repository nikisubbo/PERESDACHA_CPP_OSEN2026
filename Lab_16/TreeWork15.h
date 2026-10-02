#pragma once
#include <vector>
#include <string>

class NodeW15 {
private:
    int key;
    NodeW15* left;
    NodeW15* right;
public:
    NodeW15(int k);
    int get_key() const;
    NodeW15* get_left() const;
    NodeW15* get_right() const;
    void set_left(NodeW15* node);
    void set_right(NodeW15* node);
};

class TreeWork15 {
private:
    NodeW15* root;
    void print_node(NodeW15* node, int level) const;
    void clear_node(NodeW15* node);
    void add(NodeW15* node, int val);
public:
    TreeWork15();
    ~TreeWork15();
    void build(const std::vector<int>& data);
    void print() const;
    NodeW15* find(int k, int& count) const;
    void cleanup();
};

void HowToFillW15(TreeWork15& tree);
void TreeWork15Task();

class TestTreeWork15 {
public:
    static void run();
};