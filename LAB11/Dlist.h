#pragma once
#include <iostream>
class DNode {
public:
    int data;
    DNode* next;
    DNode* prev;
    DNode(int val = 0, DNode* n = nullptr, DNode* p = nullptr)
        : data(val), next(n), prev(p) {
    }
};
class DoublyList {
private:
    DNode* head;
    DNode* tail;
    void clear();
    void copy_from(const DoublyList& other);
public:
    DoublyList();
    DoublyList(const DoublyList& other);
    ~DoublyList();
    DoublyList& operator=(const DoublyList& other);
    void add_front(int value);
    void add_back(int value);
    bool remove(int value);
    DNode* find(int value) const;
    bool is_empty() const;
    void print() const;
    DNode* get_head() const { return head; }
    DNode* get_tail() const { return tail; }
    void disconnect();
    void DobuleFromFile();
    void fill_Dlist();
    int remove_back();
};
void Dlist_menu();
DNode* create_barrier_and_link(DNode* head, DNode* tail);
