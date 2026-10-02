#pragma once
struct Node {
	int data;
	Node* next;
};

class Stack {
private:
	Node* top;
	void copy(const Stack& other);//копирование

public:
	Stack();//конструктор по умолчанию
	Stack(const Stack& other);//конструктор копирования
	~Stack();//деструктор
	Stack& operator=(const Stack& other);
	void add(int value);//добавить
	bool pop(int& value);//удалить
	bool peek(int& value) const;//посмотреть вершину
	Node* find(int value) const;//поиск по значению 
	bool is_empty() const;//проверить пустой или нет
	Node* get_top() const;//указатель на вершину
	void print() const;//вывод
	void clear();//очистить
	void fill_stack();
	void StackFromFile();
};
void stack_menu();