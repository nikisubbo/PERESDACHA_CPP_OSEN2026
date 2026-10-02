#include "list.h"
#include "input.h"
#include <iostream>
#include <fstream>
#include "ListWork13.h"
#include "ListWork22.h"
#include "ListWork60.h"

LinkedList::LinkedList() : head(nullptr) {} 

LinkedList::~LinkedList() {
    clear();
}

LinkedList::LinkedList(const LinkedList& other) {
    copy(other);
}

LinkedList& LinkedList::operator=(const LinkedList& other) {
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

void LinkedList::add(int value) { 
    if (!head) {
        head = new ListNode(value);
        return;
    }
    ListNode* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = new ListNode(value);
}

void LinkedList::copy(const LinkedList& other) {
    if (other.head == nullptr) {
        head = nullptr;
        return;
    }
    head = new ListNode;
    head->data = other.head->data;
    head->next = nullptr;
    ListNode* tail = head;
    ListNode* current = other.head->next;
    while (current != nullptr) {
        ListNode* new_node = new ListNode;
        new_node->data = current->data;
        new_node->next = nullptr;
        tail->next = new_node;
        tail = new_node;
        current = current->next;
    }
}

void LinkedList::insert_sorted(int value) {
    ListNode* new_node = new ListNode(value);
    if (head == nullptr || head->data >= value) {
        new_node->next = head;
        head = new_node;
    }
    else {
        ListNode* current = head;
        while (current->next != nullptr && current->next->data < value) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

bool LinkedList::remove(int value) { 
    if (!head) return false;
    if (head->data == value) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
        return true;
    }
    ListNode* current = head;
    while (current->next) {
        if (current->next->data == value) {
            ListNode* temp = current->next;
            current->next = temp->next;
            delete temp;
            return true;
        }
        current = current->next;
    }
    return false;
}

ListNode* LinkedList::find(int value) const { 
    ListNode* current = head;
    while (current) {
        if (current->data == value) return current;
        current = current->next;
    }
    return nullptr;
}

bool LinkedList::is_empty() const { return head == nullptr; }

void LinkedList::print() const {
    if (!head) {
        std::cout << "пустой";
        return;
    }
    ListNode* current = head;
    std::cout << current->data;
    current = current->next;
    while (current) {
        std::cout << " -> " << current->data;
        current = current->next;
    }
}

void LinkedList::clear() {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

ListNode* LinkedList::every_second(int M) {
    if (!head || !head->next) {
        ListNode* tail = head;
        while (tail && tail->next) tail = tail->next;
        return tail;
    }
    ListNode* current = head;
    int i = 1; 
    while (current) {
        if (i % 2 == 0) { 
            ListNode* new_node = new ListNode(M, current->next);
            current->next = new_node;
            current = new_node->next;
            i++;
        }
        else {
            current = current->next;
            i++;
        }
    }
    ListNode* tail = head;
    while (tail && tail->next) {
        tail = tail->next;
    }
    return tail;
}

void LinkedList::ListFromFile() {
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
    std::cout << "Успешно загружено " << count << " элементов из файла в связный список.\n";
}

void list_menu() {
    LinkedList l;
    int value_add;
    int value_pop;
    int value_find;
    int choice = -1;

    while (choice != 9) {
        std::cout << "\nВаш список: ";
        if (l.is_empty()) {
            std::cout << "Пуст" << std::endl;
        }
        else {
            l.print();
        }

        std::cout << "\n0) Заполнить список\n1) Добавить значение\n2) Удалить значение\n3) Поиск\n4) Проверить начало\n5) Проверить конец\n6) ListWork13\n7) ListWork22\n8) ListWork60\n9) Выход\nВыбор: ";
        choice = Input_Int();

        if (choice < 0 || choice > 9) {
            std::cout << "Ошибка. Введите число от 0 до 9: "; 
            choice = Input_Int();
            continue;
        }

        switch (choice) {
        case 0:
            l.fill_list();
            break;
        case 1:
            std::cout << "Введите значение: ";
            value_add = Input_Int();
            l.add(value_add);
            break;
        case 2:
            if (!l.is_empty()) {
                std::cout << "Введите значение для удаления: ";
                value_pop = Input_Int();
                l.remove(value_pop);
                std::cout << "Удалено: " << value_pop << "\n";
            }
            else {
                std::cout << "Список пуст\n";
            }
            break;
        case 3:
            if (!l.is_empty()) {
                std::cout << "Введите значение для поиска: ";
                value_find = Input_Int();
                std::cout << "Адрес найденного элемента: " << l.find(value_find) << "\n"; 
            }
            else {
                std::cout << "Список пуст\n";
            }
            break;
        case 4:
            if (!l.is_empty()) {
                std::cout << 4; 
            }
            else {
                std::cout << "Список пуст\n";
            }
            break;
        case 5:
            if (!l.is_empty()) {
                std::cout << 4; 
            }
            else {
                std::cout << "Список пуст\n";
            }
            break;
        case 6:
            ListWork13(l);
            break;
        case 7:
            ListWork22(l);
            break;
        case 8:
            ListWork60(l); 
            break;
        }
    }
}

void LinkedList::fill_list() {
    int n;
    int choice;
    std::cout << "Как вы хотите заполнить список?\n1) Случайно\n2) С клавиатуры\n3) Из файла\nВыбор: "; 
    choice = Input_Int();

    if (choice == 1) {
        std::cout << "Сколько чисел вы хотите добавить?\nВведите количество: ";
        n = Input_Int();
        for (int i = 0; i < n; i++) {
            int number = rand();
            add(number);
        }
        std::cout << "Список заполнен " << n << " случайными числами.\n"; 
    }
    else if (choice == 2) {
        std::cout << "Сколько чисел вы хотите добавить?\nВведите количество: ";
        n = Input_Int();
        for (int i = 0; i < n; i++) {
            std::cout << "Введите элемент " << i + 1 << ": ";
            int number = Input_Int();
            add(number);
        }
        std::cout << "Список заполнен " << n << " элементами.\n"; 
    }
    else if (choice == 3) {
        ListFromFile();
    }
    else {
        std::cout << "Неверный выбор. Пожалуйста, введите 1, 2 или 3.\n";
    }
}