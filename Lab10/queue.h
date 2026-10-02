#pragma once
#include <iostream>
struct TNode {
	int data;
	TNode* next;
	TNode(int val = 0, TNode* nxt = nullptr) : data(val), next(nxt) {}
};
class Queue {
private:
	TNode* head; //начало
	TNode* tail; //конец
public:
	Queue();//конструктор
	~Queue();//деструктор
	Queue(const Queue&) = delete;
	Queue& operator=(const Queue&) = delete;
	void add(int value);//добавить в конец
	bool delq(int& value);//удалить из начала
	TNode* find(int value) const;//поиск по значению
	bool is_empty() const;//проверить пустой или нет
	void print() const;//вывод
	TNode* get_top() const { return head; }//начало
	TNode* get_bottom() const { return tail; }//конец
	void detach() { head = nullptr; tail = nullptr; }//отсоединяем
	void fill_queue();
	void QueueFromFile();
};
void queue_menu();
