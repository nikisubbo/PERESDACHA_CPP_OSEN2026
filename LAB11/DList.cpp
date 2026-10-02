#include "Dlist.h"
#include "input.h"
#include "ListWork63.h"
#include "ListWork46.h"
#include <fstream>
#include <iostream>

DoublyList::DoublyList() : head(nullptr), tail(nullptr) {}
DoublyList::~DoublyList() { clear(); }
DoublyList::DoublyList(const DoublyList& other) : head(nullptr), tail(nullptr) {
    copy_from(other);
}
DoublyList& DoublyList::operator=(const DoublyList& other) {
    if (this != &other) {
        clear();
        copy_from(other);
    }
    return *this;
}
void DoublyList::clear() {
    while (head) {
        DNode* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}
void DoublyList::copy_from(const DoublyList& other) {
    DNode* current = other.head;
    while (current) {
        add_back(current->data);
        current = current->next;
    }
}
void DoublyList::add_back(int value) {
    DNode* new_node = new DNode(value);
    if (!head) {
        head = tail = new_node;
    }
    else {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
}
void DoublyList::print() const {
    if (!head) {
        std::cout << "Пуст";
        return;
    }
    DNode* current = head;
    while (current) {
        std::cout << current->data;
        current = current->next;
        if (current) std::cout << " <-> ";
    }
}
bool DoublyList::is_empty() const {
    return head == nullptr;
}
void DoublyList::disconnect() {
    head = nullptr;
    tail = nullptr;
}
void DoublyList::add_front(int value) {
    DNode* new_node = new DNode(value);
    if (!head) {
        head = tail = new_node;
    }
    else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
}
bool DoublyList::remove(int value) {
    DNode* current = head;
    while (current) {
        if (current->data == value) {
            if (current == head && current == tail) {
                head = tail = nullptr;
            }
            else if (current == head) {
                head = head->next;
                head->prev = nullptr;
            }
            else if (current == tail) {
                tail = tail->prev;
                tail->next = nullptr;
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            return true;
        }
        current = current->next;
    }
    return false;
}

DNode* DoublyList::find(int value) const {
    DNode* current = head;
    while (current) {
        if (current->data == value) return current;
        current = current->next;
    }
    return nullptr;
}

DNode* create_barrier_and_link(DNode* head, DNode* tail) {
    DNode* barrier = new DNode(0);
    if (head == nullptr) {
        barrier->next = barrier;
        barrier->prev = barrier;
    }
    else {
        barrier->next = head;
        barrier->prev = tail;
        head->prev = barrier;
        tail->next = barrier;
    }

    return barrier;
}
int DoublyList::remove_back() {
    if (!tail) {
        throw std::runtime_error("Список пуст");
    }
    int value = tail->data;
    DNode* to_delete = tail;
    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    }
    else {
        tail = tail->prev;
        tail->next = nullptr;
    }

    delete to_delete;
    return value;
}
void DoublyList::DobuleFromFile() {
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
        add_front(value);
        count++;
    }
    file.close();
    std::cout << "Успешно загружено " << count << " элементов из файла.\n";
}
void DoublyList::fill_Dlist() {
    int n;
    int choice;
    std::cout << "Как вы хотите заполнить двусвязный список?\n"
        << "1) Случайно\n2) С клавиатуры\n3) Из файла\nВыбор: ";
    choice = Input_Int();

    if (choice == 1) {
        std::cout << "Сколько чисел вы хотите добавить?\nВведите количество: ";
        n = Input_Int();
        for (int i = 0; i < n; i++) {
            add_back(rand());
        }
        std::cout << "Список заполнен " << n << " случайными числами.\n";
    }
    else if (choice == 2) {
        std::cout << "Сколько чисел вы хотите добавить?\nВведите количество: ";
        n = Input_Int();
        for (int i = 0; i < n; i++) {
            std::cout << "Введите элемент " << i + 1 << ": ";
            add_back(Input_Int());
        }
        std::cout << "Список заполнен " << n << " элементами.\n";
    }
    else if (choice == 3) {
        DobuleFromFile();
    }
    else {
        std::cout << "Неверный выбор. Пожалуйста, введите 1, 2 или 3.\n";
    }
}
void Dlist_menu() {
    DoublyList s;
    int value_add;
    int value_find;
    int choice = -1;
    while (choice != 7) {
        std::cout << "\nВаш двусвязный список: ";
        if (s.is_empty()) {
            std::cout << "Пуст";
        }
        else {
            s.print();
        }
        std::cout << "\n0) Заполнить список\n1) Добавить значение\n2) Удалить значение\n3) Поиск\n4) Проверить начало\n5) ListWork63\n6) ListWork46\n7) Выход\nВыбор: ";
        choice = Input_Int();
        if (choice == 7) {
            std::cout << "Завершение работы...\n";
            break;
        }
        if (choice < 0 || choice > 7) {
            std::cout << "Ошибка. Введите число от 0 до 7.\n";
            continue;
        }
        switch (choice) {
        case 0:
            s.fill_Dlist();
            break;
        case 1:
            std::cout << "Введите значение: ";
            value_add = Input_Int();
            s.add_back(value_add);
            break;
        case 2:
            if (!s.is_empty()) {
                std::cout << "Введите значение для удаления: ";
                int value_pop = Input_Int();
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
                std::cout << "Адрес начала: " << s.get_head()
                    << ", значение: " << s.get_head()->data << "\n";
            }
            else {
                std::cout << "Пуст\n";
            }
            break;
        case 5:
            ListWork63(s);
            break;
        case 6:
            ListWork46(s);
            break;
        }
    }
}