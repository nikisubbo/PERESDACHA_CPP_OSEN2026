#include "CircularList.h"
#include <fstream>
#include <iostream>
#include <locale>  
#include <windows.h>  
#include "ListWork67.h"
#include "input.h"

CircularList::CircularList() : head(nullptr) {}
CircularList::~CircularList() { clear(); }
CircularList::CircularList(const CircularList& other) : head(nullptr) {
    copy_from(other);
}
CircularList& CircularList::operator=(const CircularList& other) {
    if (this != &other) {
        clear();
        copy_from(other);
    }
    return *this;
}
void CircularList::clear() {
    if (!head) return;
    CNode* current = head;
    do {
        CNode* temp = current;
        current = current->next;
        delete temp;
    } while (current != head);
    head = nullptr;
}
void CircularList::copy_from(const CircularList& other) {
    if (!other.head) {
        head = nullptr;
        return;
    }
    head = new CNode(other.head->data);
    CNode* current = head;
    CNode* other_current = other.head->next;
    while (other_current != other.head) {
        current->next = new CNode(other_current->data);
        current = current->next;
        other_current = other_current->next;
    }
    current->next = head;
}
void CircularList::add(int value) {
    CNode* new_node = new CNode(value);
    if (!head) {
        head = new_node;
        head->next = head;
    }
    else {
        CNode* tail = head;
        while (tail->next != head) tail = tail->next;
        tail->next = new_node;
        new_node->next = head;
    }
}
bool CircularList::is_empty() const { return head == nullptr; }
void CircularList::print() const {
    if (!head) {
        std::cout << "Пуст";
        return;
    }
    CNode* current = head;
    do {
        std::cout << current->data;
        current = current->next;
        if (current != head) std::cout << " -> ";
    } while (current != head);
}
CNode* CircularList::find(int value) const {
    if (!head) return nullptr;
    CNode* current = head;
    do {
        if (current->data == value) return current;
        current = current->next;
    } while (current != head);
    return nullptr;
}
int CircularList::size() const {
    if (!head) return 0;
    int count = 0;
    CNode* current = head;
    do {
        count++;
        current = current->next;
    } while (current != head);
    return count;
}
bool CircularList::remove(int value) {
    if (!head) return false;
    if (head->next == head) {
        if (head->data == value) {
            delete head;
            head = nullptr;
            return true;
        }
        return false;
    }
    CNode* current = head;
    CNode* prev = nullptr;
    do {
        if (current->data == value) {
            if (current == head) {
                CNode* tail = head;
                while (tail->next != head) tail = tail->next;
                tail->next = head->next;
                head = head->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    } while (current != head);
    return false;
}
void CircularList::ClistFromFile() {
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
void CircularList::fill_clist() {
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
        ClistFromFile();
    }
    else {
        std::cout << "Неверный выбор. Пожалуйста, введите 1, 2 или 3.\n";
    }
}
void clist_menu() {
    CircularList s;
    int value_add;
    int value_pop;
    int value_find;
    int choice = -1;
    while (choice != 7) {
        std::cout << "\nВаш кольцевой список: ";
        if (s.is_empty()) {
            std::cout << "Пуст" << std::endl;
        }
        else {
            s.print();
        }
        std::cout << "\n0) Заполнить список\n1) Добавить значение\n2) Удалить значение\n3) Поиск\n4) Проверить начало\n5) Запустить ListWork67\n6) Задача 3\n7) Выход\nВыбор: ";
        choice = Input_Int();
        if (choice < 0 || choice > 7) {
            std::cout << "Ошибка. Введите число от 0 до 7: ";
            choice = Input_Int();
            continue;
        }
        switch (choice) {
        case 0:
            s.fill_clist();
            break;
        case 1:
            std::cout << "Введите значение: ";
            value_add = Input_Int();
            s.add(value_add);
            break;
        case 2:
            if (!s.is_empty()) {
                std::cout << "Введите значение для удаления: ";
                value_pop = Input_Int();
                s.remove(value_pop);
                std::cout << "Удалено: " << value_pop << "\n";
            }
            else {
                std::cout << "Пуст\n";
            }
            break;
        case 3:
            if (!s.is_empty()) {
                std::cout << "Введите значение: ";
                value_find = Input_Int();
                std::cout << "Адрес найденного элемента: " << s.find(value_find) << "\n";
            }
            else {
                std::cout << "Пуст\n";
            }
            break;
        case 4:
            if (!s.is_empty()) {
                std::cout << "Адрес начала: " << s.get_head() << ", значение: " << s.get_head()->data << "\n";
            }
            else {
                std::cout << "Пуст\n";
            }
            break;
        case 5: {
            std::string filename = "ListWork67.txt";
            s.ListWork67(filename);
            break;
        }
        case 6:
            s.Task3();
            break;
        }
    }
}