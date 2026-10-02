#pragma once
#include <vector>
class Node {
private:
    int key;
    Node* left;
    Node* right;
public:
    Node(int k);
    int get_key() const;
    Node* get_left() const;
    Node* get_right() const;
    void set_left(Node* node);
    void set_right(Node* node);
};
class BinaryTree {
private:
    Node* root;
    void add(Node* node, int val);
    void print(Node* node, int level) const;
    void convert(Node* node, Node*& head, Node*& prev);
    void clear(Node* node);
public:
    BinaryTree();
    ~BinaryTree();
    void CompletionTree(const std::vector<int>& data);
    void show() const;
    Node* convert_to_list();
    void show_list(Node* head) const;
    void cleanup();
};
void HowToFill(BinaryTree& tree);