#pragma once
#include <vector>
#include <string>

class NodeW17 {
private:
    int key;
    NodeW17* left;
    NodeW17* right;
public:
    NodeW17(int k);
    int get_key() const;
    NodeW17* get_left() const;
    NodeW17* get_right() const;
    void set_left(NodeW17* node);
    void set_right(NodeW17* node);
};

class TreeWork17 {
private:
    NodeW17* root;
    void print_node(NodeW17* node, int level) const;
    void clear_node(NodeW17* node);
    void add(NodeW17* node, int val);
public:
    TreeWork17();
    ~TreeWork17();
    void build(const std::vector<int>& data);
    void print() const;
    int second_min() const;  // O(log n)
    void cleanup();
};

void HowToFillW17(TreeWork17& tree);
void TreeWork17Task();

class TestTreeWork17 {
public:
    static void run();
};