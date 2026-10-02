#pragma once
#pragma once
#include <iostream>
#include <string>
class Node {
public:
    int data;
    Node* next;
    Node* prev;
    Node(int val = 0, Node* n = nullptr, Node* p = nullptr)
        : data(val), next(n), prev(p) {
    }
};
class CircularDoublyList {
private:
    Node* head;
    void clear();
    void copy_from(const CircularDoublyList& other);
public:
    CircularDoublyList();//конструктор
    CircularDoublyList(const CircularDoublyList& other);
    ~CircularDoublyList();//деструкруктор
    CircularDoublyList& operator=(const CircularDoublyList& other);
    void add(int value);
    bool remove(Node* target);
    Node* find(int value) const;
    bool is_empty() const;
    void print() const;
    Node* get_head() const { return head; }
    Node* get_tail() const { return head ? head->prev : nullptr; }
    void DobuleClistFromFile();
    void fill_Dclist();
    Node* listwork42();
};
void Dclist_menu();
