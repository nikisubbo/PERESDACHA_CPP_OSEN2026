#pragma once
#pragma once
#include <iostream>
#include <string>
class CNode {
public:
	int data;
	CNode* next;
	CNode(int val = 0, CNode* nxt = nullptr) : data(val), next(nxt) {}
};
class CircularList {
private:
	CNode* head;
	void clear();
	void copy_from(const CircularList& other);
public:
	CircularList();//конструктор
	CircularList(const CircularList& other);
	~CircularList();//деструктор
	CircularList& operator=(const CircularList& other);
	int size() const;
	void add(int value);
	bool remove(int value);
	CNode* find(int value) const;
	bool is_empty() const;
	void print() const;
	CNode* get_head() const { return head; }
	void listwork66(const std::string& filename);
	void ClistFromFile();
	void fill_clist();
	void ListWork67(const std::string& filename);
	void Task3();
};
void clist_menu();