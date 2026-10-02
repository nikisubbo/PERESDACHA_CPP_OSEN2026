#include "utils.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <cstdlib>

int get_int(const std::string& prompt) {
    int value;
    while (true) {
        if (!prompt.empty()) std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        else {
            std::cout << "\nОшибка! Введено не число. Попробуйте снова: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

double get_double(const std::string& prompt) {
    double value;
    while (true) {
        if (!prompt.empty()) std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        else {
            std::cout << "\nОшибка! Введено не число. Попробуйте снова: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int get_min2() {
    int val;
    while (true) {
        std::cout << "\tВведите число >= 2: ";
        if (std::cin >> val && val >= 2) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cout << "\tОшибка! Число должно быть >= 2.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int get_grade(const std::string& prompt) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val && val >= 2 && val <= 5) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cout << "\tОшибка! Оценка должна быть от 2 до 5.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int choose_input_mode() {
    std::cout << "\nОткуда взять данные:";
    std::cout << "\n1. С клавиатуры";
    std::cout << "\n2. Случайно";
    std::cout << "\n3. Из файла\n";
    int mode = get_int("Ваш выбор: ");
    while (mode < 1 || mode > 3) {
        std::cout << "Неверный выбор. Введите 1, 2 или 3: ";
        mode = get_int("");
    }
    return mode;
}

void fill_doubles(std::vector<double>& vec, int count, const std::string& value_name) {
    vec.clear();
    int mode = choose_input_mode();

    if (mode == 1) {
        for (int i = 0; i < count; ++i) {
            vec.push_back(get_double(value_name + " " + std::to_string(i + 1) + ": "));
        }
    }
    else if (mode == 2) {
        for (int i = 0; i < count; ++i) {
            double val = (rand() % 10001 - 5000) / 100.0;  
            vec.push_back(val);
        }
        std::cout << "\nСгенерированы случайные значения.\n";
    }
    else if (mode == 3) {
        std::ifstream file("input.txt");
        if (file.is_open()) {
            double val;
            while (file >> val && static_cast<int>(vec.size()) < count) {
                vec.push_back(val);
            }
            file.close();

            if (static_cast<int>(vec.size()) < count) {
                std::cout << "\nВ файле недостаточно данных. Оставшиеся введите с клавиатуры:\n";
                while (static_cast<int>(vec.size()) < count) {
                    vec.push_back(get_double(value_name + " " + std::to_string(vec.size() + 1) + ": "));
                }
            }
            else {
                std::cout << "\nДанные успешно загружены из файла input.txt.\n";
            }
        }
        else {
            std::cout << "\nФайл input.txt не найден. Ввод с клавиатуры:\n";
            for (int i = 0; i < count; ++i) {
                vec.push_back(get_double(value_name + " " + std::to_string(i + 1) + ": "));
            }
        }
    }
}

void fill_grades(std::vector<int>& grades, int n) {
    grades.clear();
    std::cout << "\nОткуда взять оценки:";
    std::cout << "\n1. С клавиатуры";
    std::cout << "\n2. Случайно (от 2 до 5)";
    std::cout << "\n3. Из файла (grades.txt)\n";

    int method = get_int("Ваш выбор: ");

    if (method == 1) {
        for (int i = 0; i < n; ++i) {
            grades.push_back(get_grade("Оценка " + std::to_string(i + 1) + ": "));
        }
    }
    else if (method == 2) {
        for (int i = 0; i < n; ++i) {
            grades.push_back((rand() % 4) + 2);
        }
        std::cout << "\nСгенерированы случайные оценки.\n";
    }
    else if (method == 3) {
        std::ifstream file("grades.txt");
        if (file.is_open()) {
            int grade;
            while (file >> grade && static_cast<int>(grades.size()) < n) {
                if (grade >= 2 && grade <= 5) {
                    grades.push_back(grade);
                }
            }
            file.close();

            if (static_cast<int>(grades.size()) < n) {
                std::cout << "\nВ файле недостаточно корректных оценок. Оставшиеся введите с клавиатуры:\n";
                while (static_cast<int>(grades.size()) < n) {
                    grades.push_back(get_grade("Оценка " + std::to_string(grades.size() + 1) + ": "));
                }
            }
            else {
                std::cout << "\nОценки успешно загружены из файла grades.txt.\n";
            }
        }
        else {
            std::cout << "\nФайл grades.txt не найден. Ввод с клавиатуры:\n";
            for (int i = 0; i < n; ++i) {
                grades.push_back(get_grade("Оценка " + std::to_string(i + 1) + ": "));
            }
        }
    }
    else {
        std::cout << "\nНеверный выбор. Ввод с клавиатуры по умолчанию.\n";
        for (int i = 0; i < n; ++i) {
            grades.push_back(get_grade("Оценка " + std::to_string(i + 1) + ": "));
        }
    }
}