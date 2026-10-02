#pragma once
#include <string>
struct ListNode {//узел списк
	int data;
	ListNode* next;
	ListNode(int val = 0, ListNode* nxt = nullptr) : data(val), next(nxt) {}
};
class LinkedList {
private:
	ListNode* head;//указатель на головушку
	void copy(const LinkedList& other);
public:
	LinkedList();//конструктор
	~LinkedList();//деструктор
	LinkedList(const LinkedList&);
	LinkedList& operator=(const LinkedList&);
	void add(int value);//добавление в конец
	bool remove(int value);//удалить первый найденный 
	ListNode* find(int value) const;//поиск по значению
	bool is_empty() const;//проерка на пустоту 
	void print() const;//вывод
	void clear();//очистить список
	ListNode* get_head() const { return head; }
	void fill_list();
	void insert_sorted(int value); //вставка с сохранением упорядоченности
	ListNode* every_second(int M);//вставка м после каждого второго
	void ListFromFile();
};
void list_menu();