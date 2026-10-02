#pragma once
#include <vector>
#include <stack>
#include <queue>
class Node3 {
private:
    int key;
    Node3* left;
    Node3* right;
public:
    Node3(int k);
    int get_key() const;
    Node3* get_left() const;
    Node3* get_right() const;
    void set_left(Node3* node);
    void set_right(Node3* node);
};
class TreeIterator {
private:
    std::stack<Node3*> st;
    Node3* curr;
public:
    TreeIterator(Node3* root);
    bool has_next();
    int next();
};
class BTree {
private:
    Node3* root;
    void print_node(Node3* node, int level) const;
    void clear_node(Node3* node);
public:
    BTree();
    ~BTree();
    void build(const std::vector<int>& data);
    void print() const;
    void cleanup();
    TreeIterator get_iter() const;
};
void HowToFill(BTree& tree);