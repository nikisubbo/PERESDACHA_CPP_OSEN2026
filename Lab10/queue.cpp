#include "queue.h"
#include <iostream>
#include <fstream>
#include "input.h"
#include "Dynamic26.h"

Queue::Queue() : head(nullptr), tail(nullptr) {} 

Queue::~Queue() { 
    while (head) {
        TNode* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

void Queue::add(int value) { 
    TNode* new_node = new TNode(value, nullptr);
    if (!tail) {
        head = tail = new_node;
    }
    else {
        tail->next = new_node;
        tail = new_node;
    }
}

bool Queue::delq(int& value) { 
    if (!head) return false;
    value = head->data;
    TNode* temp = head;
    head = head->next;
    if (!head) tail = nullptr;
    delete temp;
    return true;
}

TNode* Queue::find(int value) const { 
    TNode* current = head;
    while (current) {
        if (current->data == value) return current;
        current = current->next;
    }
    return nullptr;
}

bool Queue::is_empty() const { return head == nullptr; } 

void Queue::print() const { 
    if (!head) {
        std::cout << "пустая";
        return;
    }
    TNode* cur = head;
    std::cout << cur->data;
    cur = cur->next;
    while (cur) {
        std::cout << " -> " << cur->data;
        cur = cur->next;
    }
}

void Queue::QueueFromFile() {
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
        this->add(value);
        count++;
    }
    file.close();
    std::cout << "Успешно загружено " << count << " элементов из файла в очередь.\n";
}

void Queue::fill_queue() {
    int n;
    int choice;
    std::cout << "Как вы хотите заполнить очередь?\n1) Случайно\n2) С клавиатуры\n3) Из файла\nВыбор: ";
    choice = Input_Int();
    if (choice == 1) {
        std::cout << "Сколько чисел вы хотите добавить?\nВведите количество: ";
        n = Input_Int();
        for (int i = 0; i < n; i++) {
            int number = rand();
            add(number);
        }
        std::cout << "Очередь заполнена " << n << " случайными числами.\n";
    }
    else if (choice == 2) {
        std::cout << "Сколько чисел вы хотите добавить?\nВведите количество: ";
        n = Input_Int();
        for (int i = 0; i < n; i++) {
            std::cout << "Введите элемент " << i + 1 << ": ";
            int number = Input_Int();
            add(number);
        }
        std::cout << "Очередь заполнена " << n << " элементами.\n";
    }
    else if (choice == 3) {
        QueueFromFile();
    }
    else {
        std::cout << "Неверный выбор. Пожалуйста, введите 1, 2 или 3.\n";
    }
}

void queue_menu() {
    Queue q;
    int value_add;
    int value_pop;
    int value_find;
    int choice = -1;

    while (choice != 7) {
        std::cout << "\nВаша очередь: ";
        if (q.is_empty()) {
            std::cout << "Пустая" << std::endl;
        }
        else {
            q.print();
        }

        std::cout << "\n0) Заполнить очередь\n1) Добавить значение в конец\n2) Удалить значение из начала\n3) Поиск\n4) Проверить начало\n5) Проверить конец\n6) Запустить Dynamic26\n7) Выход\nВыбор: ";
        choice = Input_Int();

        if (choice < 0 || choice > 7) {
            std::cout << "Ошибка. Введите число от 0 до 7: ";
            choice = Input_Int();
            continue;
        }

        switch (choice) {
        case 0:
            q.fill_queue();
            break;
        case 1:
            std::cout << "Введите значение: ";
            value_add = Input_Int();
            q.add(value_add);
            break;
        case 2:
            if (!q.is_empty()) {
                q.delq(value_pop);
                std::cout << "Удалено: " << value_pop << "\n";
            }
            else {
                std::cout << "Очередь пуста\n";
            }
            break;
        case 3:
            if (!q.is_empty()) {
                std::cout << "Введите значение для поиска: ";
                value_find = Input_Int();
                std::cout << "Адрес найденного элемента в очереди: " << q.find(value_find) << "\n";
            }
            else {
                std::cout << "Очередь пуста\n";
            }
            break;
        case 4:
            if (!q.is_empty()) {
                std::cout << "Адрес начала: " << q.get_top() << ", значение: " << q.get_top()->data << "\n";
            }
            else {
                std::cout << "Очередь пуста\n";
            }
            break;
        case 5:
            if (!q.is_empty()) {
                std::cout << "Адрес конца: " << q.get_bottom() << ", значение: " << q.get_bottom()->data << "\n";
            }
            else {
                std::cout << "Очередь пуста\n";
            }
            break;
        case 6:
            Dynamic26(q);
            break;
        }
    }
}