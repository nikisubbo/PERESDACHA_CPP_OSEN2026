#pragma once
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <unordered_set>
class Node13 {
private:
    int key;
    Node13* left;
    Node13* right;
public:
    Node13(int k);
    int get_key() const;
    Node13* get_left() const;
    Node13* get_right() const;
    void set_left(Node13* node);
    void set_right(Node13* node);
};
class ByTree {
private:
    Node13* root;
    void print_node(Node13* node, int level) const;
    void clear_node(Node13* node);
    Node13* find_node(int val) const;
    int subtree_size(Node13* node) const;
    std::string serialize(Node13* node) const;
    std::unordered_map<Node13*, Node13*> build_parents() const;
public:
    ByTree();
    ~ByTree();
    void build(const std::vector<int>& data);
    void print() const;
    void cleanup();
    void remove_duplicates();
    void remove_duplicate_subtrees();
};
void HowToFill(ByTree& tree);