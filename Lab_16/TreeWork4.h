#pragma once
#include <vector>
#include <string>

class NodeW4 {
private:
    int key;
    NodeW4* left;
    NodeW4* right;
public:
    NodeW4(int k);
    int get_key() const;
    NodeW4* get_left() const;
    NodeW4* get_right() const;
    void set_left(NodeW4* node);
    void set_right(NodeW4* node);
};

class TreeWork4 {
private:
    NodeW4* root;
    void print_node(NodeW4* node, int level) const;
    void clear_node(NodeW4* node);
    void collect_leaves(NodeW4* node, std::vector<int>& leaves) const;
public:
    TreeWork4();
    ~TreeWork4();
    void build(const std::vector<int>& data);
    void print() const;
    std::vector<int> get_leaves() const;
    void cleanup();
};

void HowToFillW4(TreeWork4& tree);
void TreeWork4Task();

class TestTreeWork4 {
public:
    static void run();
};