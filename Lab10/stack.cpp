#include "stack.h"
#include "input.h"
#include <fstream>
#include <iostream>
#include "Dynamic4.h"

Stack::Stack() {
    top = nullptr;
} 

Stack::Stack(const Stack& other) {
    top = nullptr;
    copy(other);
} 

Stack::~Stack() {
    clear();
} 

Stack& Stack::operator=(const Stack& other) { 
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

void Stack::add(int value) { 
    Node* new_node = new Node;
    new_node->data = value;
    new_node->next = top;
    top = new_node;
}

bool Stack::pop(int& value) { 
    if (top == nullptr) return false;
    value = top->data;
    Node* temp = top;
    top = top->next;
    delete temp;
    return true;
}

bool Stack::peek(int& value) const { 
    if (top == nullptr) return false;
    value = top->data;
    return true;
}

Node* Stack::find(int value) const { 
    Node* current = top;
    while (current) {
        if (current->data == value) return current;
        current = current->next;
    }
    return nullptr;
}

bool Stack::is_empty() const { return top == nullptr; } 

Node* Stack::get_top() const { return top; } 

void Stack::print() const { 
    if (top == nullptr) {
        std::cout << "Пустой стек";
        return;
    }
    Node* current = top;
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next != nullptr) {
            std::cout << " -> ";
        }
        current = current->next;
    }
}

void Stack::clear() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

void Stack::StackFromFile() {
    std::string filename;
    std::cout << "Введите имя файла: ";
    std::cin >> filename;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка: Не удалось открыть файл '" << filename << "'.\n";
        return;
    }
    int value;
    int count = 0;
    while (file >> value) {
        add(value);
        count++;
    }
    file.close();
    std::cout << "Успешно загружено " << count << " элементов из файла.\n";
}

void Stack::copy(const Stack& other) {
    if (other.top == nullptr) {
        top = nullptr;
        return;
    }
    Node* temp = nullptr;
    Node* current = other.top;
    while (current != nullptr) {
        Node* new_node = new Node;
        new_node->data = current->data;
        new_node->next = temp;
        temp = new_node;
        current = current->next;
    }
    top = nullptr;
    current = temp;
    while (current != nullptr) {
        Node* next_node = current->next;
        current->next = top;
        top = current;
        current = next_node;
    }
}

void stack_menu() {
    Stack s;
    int value_add;
    int value_pop;
    int value_find;
    int choice = -1;

    while (choice != 6) {
        std::cout << "\nВаш стек: ";
        if (s.is_empty()) {
            std::cout << "Пуст" << std::endl;
        }
        else {
            s.print();
        }

        std::cout << "\n0) Заполнить стек\n1) Добавить значение\n2) Удалить значение\n3) Поиск\n4) Проверить вершину\n5) Запустить Dynamic4\n6) Выход\nВыбор: ";
        choice = Input_Int();

        if (choice < 0 || choice > 6) {
            std::cout << "Ошибка. Введите число от 0 до 6: "; 
            choice = Input_Int();
            continue;
        }

        switch (choice) {
        case 0:
            s.fill_stack();
            break;
        case 1:
            std::cout << "Введите значение: ";
            value_add = Input_Int();
            s.add(value_add);
            break;
        case 2:
            if (!s.is_empty()) {
                s.pop(value_pop);
                std::cout << "Удалено: " << value_pop << "\n";
            }
            else {
                std::cout << "Стек пуст\n";
            }
            break;
        case 3:
            if (!s.is_empty()) {
                std::cout << "Введите значение для поиска: ";
                value_find = Input_Int();
                std::cout << "Адрес найденного элемента: " << s.find(value_find) << "\n";
            }
            else {
                std::cout << "Стек пуст\n";
            }
            break;
        case 4:
            if (!s.is_empty()) {
                std::cout << "Адрес вершины: " << s.get_top() << ", значение: " << s.get_top()->data << "\n"; 
            }
            else {
                std::cout << "Стек пуст\n";
            }
            break;
        case 5:
            Dynamic4(s);
            break; 
        }
    }
}

void Stack::fill_stack() {
    int n;
    int choice;
    std::cout << "Как вы хотите заполнить стек?\n1) Случайно\n2) С клавиатуры\n3) Из файла\nВыбор: ";
    choice = Input_Int();

    if (choice == 1) {
        std::cout << "Сколько чисел вы хотите добавить?\nВведите количество: ";
        n = Input_Int();
        for (int i = 0; i < n; i++) {
            int number = rand();
            add(number);
        }
        std::cout << "Стек заполнен " << n << " случайными числами.\n";
    }
    else if (choice == 2) {
        std::cout << "Сколько чисел вы хотите добавить?\nВведите количество: ";
        n = Input_Int();
        for (int i = 0; i < n; i++) {
            std::cout << "Введите элемент " << i + 1 << ": ";
            int number = Input_Int();
            add(number);
        }
        std::cout << "Стек заполнен " << n << " элементами.\n";
    }
    else if (choice == 3) {
        StackFromFile();
    }
    else {
        std::cout << "Неверный выбор. Пожалуйста, введите 1, 2 или 3.\n";
    }
}