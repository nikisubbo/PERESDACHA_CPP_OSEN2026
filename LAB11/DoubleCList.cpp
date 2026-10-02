#include "DoubleClist.h"
#include "input.h"
#include <fstream>
#include <iostream>
#include <string>
#include "ListWork42.h"

CircularDoublyList::CircularDoublyList() : head(nullptr) {}

CircularDoublyList::~CircularDoublyList() {
    clear();
}

CircularDoublyList::CircularDoublyList(const CircularDoublyList& other) : head(nullptr) {
    copy_from(other);
}

CircularDoublyList& CircularDoublyList::operator=(const CircularDoublyList& other) {
    if (this != &other) {
        clear();
        copy_from(other);
    }
    return *this;
}

void CircularDoublyList::clear() {
    if (!head) return;
    Node* current = head;
    do {
        Node* temp = current;
        current = current->next;
        delete temp;
    } while (current != head);
    head = nullptr;
}

void CircularDoublyList::copy_from(const CircularDoublyList& other) {
    if (!other.head) {
        head = nullptr;
        return;
    }
    head = new Node(other.head->data);
    Node* current = head;
    Node* other_current = other.head->next;
    while (other_current != other.head) {
        current->next = new Node(other_current->data, nullptr, current);
        current = current->next;
        other_current = other_current->next;
    }
    current->next = head;
    head->prev = current;
}

void CircularDoublyList::add(int value) {
    Node* new_node = new Node(value);
    if (!head) {
        head = new_node;
        head->next = head;
        head->prev = head;
    }
    else {
        Node* tail = head->prev;
        tail->next = new_node;
        new_node->prev = tail;
        new_node->next = head;
        head->prev = new_node;
    }
}

bool CircularDoublyList::is_empty() const { return head == nullptr; }

void CircularDoublyList::print() const {
    if (!head) {
        std::cout << "Пуст";
        return;
    }
    Node* current = head;
    do {
        std::cout << current->data;
        current = current->next;
        if (current != head) std::cout << " <-> ";
    } while (current != head);
}

Node* CircularDoublyList::find(int value) const {
    if (!head) return nullptr;
    Node* current = head;
    do {
        if (current->data == value) return current;
        current = current->next;
    } while (current != head);
    return nullptr;
}

Node* CircularDoublyList::listwork42() {
    if (!head) {
        std::cout << "Список пуст.\n";
        return nullptr;
    }
    bool changed = true;
    while (changed && head) {
        changed = false;
        Node* current = head;
        Node* start = head;
        do {
            Node* next_node = current->next;
            if (current->next == current->prev) {
                if (current->next == current) {
                    delete current;
                    head = nullptr;
                    changed = true;
                    break;
                }
                current->prev->next = current->next;
                current->next->prev = current->prev;
                if (current == head) {
                    head = next_node;
                }
                delete current;
                changed = true;
            }
            current = next_node;
        } while (head && current != start);
    }
    if (!head) {
        std::cout << "\nВсе элементы удалены.\n";
        return nullptr;
    }
    return head->prev;
}

bool CircularDoublyList::remove(Node* target) {
    if (!target || !head) return false;
    if (head->next == head) {
        delete head;
        head = nullptr;
        return true;
    }
    target->prev->next = target->next;
    target->next->prev = target->prev;
    if (target == head) {
        head = target->next;
    }
    delete target;
    return true;
}

void CircularDoublyList::DobuleClistFromFile() {
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

void CircularDoublyList::fill_Dclist() {
    int n;
    int choice;
    std::cout << "Как вы хотите заполнить кольцевой двусвязный список?\n"
        << "1) Случайно\n2) С клавиатуры\n3) Из файла\nВыбор: ";
    choice = Input_Int();

    if (choice == 1) {
        std::cout << "Сколько чисел вы хотите добавить?\nВведите количество: ";
        n = Input_Int();
        for (int i = 0; i < n; i++) {
            add(rand());
        }
        std::cout << "Список заполнен " << n << " случайными числами.\n";
    }
    else if (choice == 2) {
        std::cout << "Сколько чисел вы хотите добавить?\nВведите количество: ";
        n = Input_Int();
        for (int i = 0; i < n; i++) {
            std::cout << "Введите элемент " << i + 1 << ": ";
            add(Input_Int());
        }
        std::cout << "Список заполнен " << n << " элементами.\n";
    }
    else if (choice == 3) {
        DobuleClistFromFile();
    }
    else {
        std::cout << "Неверный выбор. Пожалуйста, введите 1, 2 или 3.\n";
    }
}

void Dclist_menu() {
    CircularDoublyList s;
    int value_add;
    int value_find;
    int choice = -1;
    while (choice != 6) {
        std::cout << "\nВаш кольцевой двусвязный список: ";
        if (s.is_empty()) {
            std::cout << "Пуст";
        }
        else {
            s.print();
        }
        std::cout << "\n0) Заполнить список\n1) Добавить значение\n2) Удалить значение\n3) Поиск\n4) Проверить начало\n5) ListWork42\n6) Выход\nВыбор: ";
        choice = Input_Int();
        if (choice == 6) {
            std::cout << "Завершение работы...\n";
            break;
        }
        if (choice < 0 || choice > 6) {
            std::cout << "Ошибка. Введите число от 0 до 6.\n";
            continue;
        }
        switch (choice) {
        case 0:
            s.fill_Dclist();
            break;
        case 1:
            std::cout << "Введите значение: ";
            value_add = Input_Int();
            s.add(value_add);
            break;
        case 2:
            if (!s.is_empty()) {
                std::cout << "Введите значение для удаления: ";
                int value_pop = Input_Int();
                Node* target = s.find(value_pop);
                if (target) {
                    s.remove(target);
                    std::cout << "Удалено: " << value_pop << "\n";
                }
                else {
                    std::cout << "Значение " << value_pop << " не найдено.\n";
                }
            }
            else {
                std::cout << "Пуст\n";
            }
            break;
        case 3:
            if (!s.is_empty()) {
                std::cout << "Введите значение: ";
                value_find = Input_Int();
                Node* found = s.find(value_find);
                if (found) {
                    std::cout << "Найдено по адресу: " << found
                        << ", значение: " << found->data << "\n";
                }
                else {
                    std::cout << "Значение не найдено.\n";
                }
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
            ListWork42(s);
            break;
        }
    }
}