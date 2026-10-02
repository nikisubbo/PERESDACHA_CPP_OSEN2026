#define NOMINMAX
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <windows.h>
#include <ctime>
#include "Task_1.h"
#include "Task_2.h"
#include "utils.h"
#include "Task_3.h"
#include "Task_4.h"

void menu_task1();
void menu_task2();
void menu_task3();
void menu_task4();
void menu_task5();

void press_enter_to_continue() {
    std::cout << "\nНажмите Enter для возврата в меню...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    srand(static_cast<unsigned int>(time(nullptr)));

    int choice;
    do {
        std::cout << "\nМеню";
        std::cout << "\n1. Задача 1";
        std::cout << "\n2. Задача 2";
        std::cout << "\n3. Задача 3";
        std::cout << "\n4. Задача 4";
        std::cout << "\n5. Задача 5";
        std::cout << "\n0. Выход\n";

        choice = get_int("\nВыбор действия: ");

        switch (choice) {
        case 1: menu_task1(); break;
        case 2: menu_task2(); break;
        case 3: menu_task3(); break;
        case 4: menu_task4(); break;
        case 5: menu_task5(); break;
        case 0: std::cout << "\nЗавершение работы"; break;
        }

        if (choice != 0) {
            press_enter_to_continue();
        }
    } while (choice != 0);
    return 0;
}

void menu_task1() {
    int sub_choice;
    do {
        std::cout << "\nЗадача 1: Точка";
        std::cout << "\n1. Создать точки";
        std::cout << "\n2. Продемонстрировать операции с точкой";
        std::cout << "\n3. Выйти в главное меню\n";
        sub_choice = get_int("\nВыбор: ");

        switch (sub_choice) {
        case 1: {
            std::cout << "\nСоздание 3 точек";
            std::cout << "\nВведите координаты для 3 точек (нужно 6 значений X и Y):\n";

            std::vector<double> coords;
            fill_doubles(coords, 6, "Координата");

            Point p1(coords[0], coords[1]);
            Point p2(coords[2], coords[3]);
            Point p3(coords[4], coords[5]);

            std::cout << "\nСозданные точки:\n";
            p1.print();
            p2.print();
            p3.print();
            press_enter_to_continue();
            break;
        }
        case 2: {
            std::cout << "\nДемонстрация операций с точкой:";
            std::cout << "\n1. Создание точки (конструктор по умолчанию)";
            Point p1;
            std::cout << "\nРезультат: ";
            p1.print();

            std::vector<double> coords;
            fill_doubles(coords, 2, "Координата");
            std::cout << "\nСоздана точка (" << coords[0] << ", " << coords[1] << ")";
            Point p2(coords[0], coords[1]);
            std::cout << "\nРезультат: ";
            p2.print();

            std::cout << "\n2. Создание копии точки (конструктор копирования)";
            Point p3 = p2;
            std::cout << "\nРезультат: ";
            p3.print();

            std::cout << "\n3. Создание точки и присваивание из другой";
            Point p4;
            std::cout << "\nДо присваивания: ";
            p4.print();
            p4 = p3;
            std::cout << "\nПосле присваивания: ";
            p4.print();

            press_enter_to_continue();
            break;
        }
        case 3: break;
        }
    } while (sub_choice != 3);
}

void menu_task2() {
    int sub_choice;
    do {
        std::cout << "\nЗадача 2: Линия";
        std::cout << "\n1. Создать линии";
        std::cout << "\n2. Продемонстрировать операции с линией";
        std::cout << "\n3. Выйти в главное меню\n";
        sub_choice = get_int("\nВыбор: ");

        switch (sub_choice) {
        case 1: {
            std::cout << "\nСоздание 3 линий";
            std::cout << "\nВведите координаты для 3 линий (нужно 12 значений):\n";

            std::vector<double> coords;
            fill_doubles(coords, 12, "Координата");

            Line line1(Point(coords[0], coords[1]), Point(coords[2], coords[3]));
            Line line2(Point(coords[4], coords[5]), Point(coords[6], coords[7]));
            Line line3(line1.get_start(), line2.get_end());

            std::cout << "\nСозданные линии:\n";
            std::cout << "Линия 1: "; line1.print();
            std::cout << "Линия 2: "; line2.print();
            std::cout << "Линия 3: "; line3.print();

            press_enter_to_continue();
            break;
        }
        case 2: {
            std::cout << "\nДемонстрация операций с линией:";
            std::cout << "\n1. Создание линии 1 (конструктор по умолчанию)";
            Line l1;
            std::cout << "\nРезультат: ";
            l1.print();

            std::vector<double> coords;
            fill_doubles(coords, 4, "Координата");
            Point p1(coords[0], coords[1]), p2(coords[2], coords[3]);
            Line l2(p1, p2);
            std::cout << "\nСоздана линия 2 из (" << coords[0] << ";" << coords[1]
                << ") в (" << coords[2] << ";" << coords[3] << ")";
            std::cout << "\nРезультат: ";
            l2.print();

            std::cout << "\n2. Создание линии 3 (копия линии 2)";
            Line l3 = l2;
            std::cout << "\nРезультат: ";
            l3.print();

            std::cout << "\n3. Создание линии 4 (по умолчанию), присваивание из линии 3";
            Line l4;
            std::cout << "\nДо присваивания: ";
            l4.print();
            l4 = l3;
            std::cout << "\nПосле присваивания: ";
            l4.print();

            press_enter_to_continue();
            break;
        }
        case 3: break;
        }
    } while (sub_choice != 3);
}

void menu_task3() {
    int sub_choice;
    do {
        std::cout << "\nЗадача 3: Студент";
        std::cout << "\n1. Создать студента";
        std::cout << "\n2. Продемонстрировать операции со студентом";
        std::cout << "\n3. Выйти в главное меню\n";
        sub_choice = get_int("\nВыбор: ");

        switch (sub_choice) {
        case 1: {
            std::cout << "\nСоздание студента 3:\n";
            Student vasya("Вася", { 3, 4, 5 });
            std::cout << "\n1. Создание студента Вася:\n";
            vasya.print();

            Student petya("Петя", vasya.get_grades());
            std::cout << "\n2. Создание студента Петя (копирование оценок от Васи):\n";
            petya.print();

            std::vector<int> petya_grades = petya.get_grades();
            if (!petya_grades.empty()) {
                petya_grades[0] = 5;
                petya.set_grades(petya_grades);
            }
            std::cout << "\n3. Изменим первую оценку Пети на 5:\n";
            vasya.print();
            petya.print();

            std::cout << "\nПроверка глубокого копирования (изменения не влияют друг на друга):\n";
            Student andrey("Андрей", vasya.get_grades());
            std::cout << "\n4. Создание студента Андрей (копирование оценок от Васи):\n";
            andrey.print();

            press_enter_to_continue();
            break;
        }
        case 2: {
            std::cout << "\nДемонстрация операций со студентом:";
            std::cout << "\n1. Создание студента 1 (конструктор по умолчанию)";
            Student s1;
            std::cout << "\nРезультат: ";
            s1.print();

            std::cout << "\n2. Задайте имя студента: ";
            std::string name;
            std::getline(std::cin, name);

            int n = get_min2();
            std::vector<int> grades;
            fill_grades(grades, n);

            Student s2(name, grades);
            std::cout << "\nСоздан студент 2:\n";
            s2.print();

            std::cout << "\n3. Создание студента 3 (копия студента 2)";
            Student s3 = s2;
            std::cout << "\nРезультат: ";
            s3.print();

            std::cout << "\n4. Создание студента 4, присваивание из студента 3";
            Student s4;
            std::cout << "\nДо присваивания: ";
            s4.print();
            s4 = s3;
            std::cout << "\nПосле присваивания: ";
            s4.print();

            press_enter_to_continue();
            break;
        }
        case 3: break;
        }
    } while (sub_choice != 3);
}

void menu_task4() {
    int sub_choice;
    do {
        std::cout << "\nЗадача 4: Точка и линия (обновл.)";
        std::cout << "\n1. Создать точки и линии";
        std::cout << "\n2. Продемонстрировать операции";
        std::cout << "\n3. Выйти в главное меню\n";
        sub_choice = get_int("\nВыбор: ");

        switch (sub_choice) {
        case 1: {
            std::cout << "\nСоздание 3 точек и 3 линий:\n";

            std::cout << "\nКоординаты для 3 точек (6 значений):\n";
            std::vector<double> pt_coords;
            fill_doubles(pt_coords, 6, "Координата");

            Point4 p1(pt_coords[0], pt_coords[1]);
            Point4 p2(pt_coords[2], pt_coords[3]);
            Point4 p3(pt_coords[4], pt_coords[5]);
            p1.print();
            p2.print();
            p3.print();

            std::cout << "\nКоординаты для 3 линий (12 значений):\n";
            std::vector<double> ln_coords;
            fill_doubles(ln_coords, 12, "Координата");

            Line4 line1(Point4(ln_coords[0], ln_coords[1]), Point4(ln_coords[2], ln_coords[3]));
            Line4 line2(Point4(ln_coords[4], ln_coords[5]), Point4(ln_coords[6], ln_coords[7]));
            Line4 line3(line1.get_start(), line2.get_end());

            std::cout << "Линия 1: "; line1.print();
            std::cout << "Линия 2: "; line2.print();
            std::cout << "Линия 3: "; line3.print();

            press_enter_to_continue();
            break;
        }
        case 2: {
            std::cout << "\nДемонстрация операций с точкой и линией:";

            std::vector<double> pt_coords;
            fill_doubles(pt_coords, 2, "Координата");
            Point4 pt(pt_coords[0], pt_coords[1]);
            std::cout << "\nСозданная точка: "; pt.print();

            std::cout << "\n1. Задайте координаты линии (4 значения):\n";
            std::vector<double> ln_coords1;
            fill_doubles(ln_coords1, 4, "Координата");
            Line4 l1(Point4(ln_coords1[0], ln_coords1[1]), Point4(ln_coords1[2], ln_coords1[3]));
            std::cout << "Линия: "; l1.print();

            std::cout << "\n2. Задайте ещё 4 координаты для линии:\n";
            std::vector<double> ln_coords2;
            fill_doubles(ln_coords2, 4, "Координата");
            Line4 l2(Point4(ln_coords2[0], ln_coords2[1]), Point4(ln_coords2[2], ln_coords2[3]));
            std::cout << "Линия: "; l2.print();

            press_enter_to_continue();
            break;
        }
        case 3: break;
        }
    } while (sub_choice != 3);
}

void menu_task5() {
    int sub_choice;
    do {
        std::cout << "\nЗадача 5: Длина линии";
        std::cout << "\n1. Создать линию и вычислить длину";
        std::cout << "\n2. Создать ещё одну линию и вычислить длину";
        std::cout << "\n3. Выйти в главное меню\n";
        sub_choice = get_int("\nВыбор: ");

        switch (sub_choice) {
        case 1: {
            std::cout << "\nСоздание линии 1:";
            std::cout << "\nВведите координаты линии (4 значения: X1 Y1 X2 Y2):\n";

            std::vector<double> coords1;
            fill_doubles(coords1, 4, "Координата");

            Line4 line1(Point4(coords1[0], coords1[1]), Point4(coords1[2], coords1[3]));
            std::cout << "\nСозданная линия:\n";
            line1.print();
            std::cout << "\nДлина: " << line1.get_length() << "\n";

            press_enter_to_continue();
            break;
        }
        case 2: {
            std::cout << "\nСоздание линии 2:";
            std::cout << "\nВведите координаты линии (4 значения: X1 Y1 X2 Y2):\n";

            std::vector<double> coords2;
            fill_doubles(coords2, 4, "Координата");

            Line4 line2(Point4(coords2[0], coords2[1]), Point4(coords2[2], coords2[3]));
            std::cout << "\nСозданная линия:\n";
            line2.print();
            std::cout << "\nДлина: " << line2.get_length() << "\n";

            press_enter_to_continue();
            break;
        }
        case 3: break;
        }
    } while (sub_choice != 3);
}