#include "iter15.h"
#include "stl_utils.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <limits>
#include <random>

void iter15() {
    std::string name;
    std::cout << "Введите имя выходного файла: ";
    std::cin >> name;
    int count;
    std::cout << "Сколько чисел вы хотите ввести? ";
    std::cin >> count;
    std::vector<int> numbers;
    int method;
    std::cout << "Выберите способ ввода:\n1) С клавиатуры\n2) Случайно\n3) Из файла\nВыбор: ";
    std::cin >> method;
    while (method < 1 || method > 3) {
        std::cout << "Неверный выбор. Введите 1, 2 или 3: ";
        std::cin >> method;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (method == 1) {
        std::cout << "Введите " << count << " целых чисел:\n";
        for (int i = 0; i < count; ++i) {
            int num;
            std::cin >> num;
            numbers.push_back(num);
        }
    }
    else if (method == 2) {
        std::cout << "Генерация " << count << " случайных чисел:\n";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        for (int i = 0; i < count; ++i) {
            int num = dis(gen);
            numbers.push_back(num);
            std::cout << num << " ";
        }
        std::cout << "\n";
    }
    else if (method == 3) {
        std::string filename;
        std::cout << "Введите имя исходного файла: ";
        std::cin >> filename;
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Ошибка. Исходный файл не открыт: " << filename << "\n";
            return;
        }
        int num;
        int read_count = 0;
        while (read_count < count && infile >> num) {
            numbers.push_back(num);
            read_count++;
        }
        infile.close();
        if (read_count < count) {
            std::cout << "Внимание: Файл содержал только " << read_count << " элементов.\n";
        }
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (numbers.empty()) {
        std::cout << "Множество чисел пусто. Запись не выполнена.\n";
        return;
    }
    std::ofstream file(name);
    if (!file.is_open()) {
        std::cerr << "Ошибка. Файл не открыт: " << name << "\n";
        return;
    }
    std::cout << "\nЗапись выполняется с заменой 0 на 10 и добавлением двух пробелов...\n";
    std::replace_copy(
        numbers.begin(),
        numbers.end(),
        std::ostream_iterator<int>(file, "  "),
        0,
        10
    );
    file.close();
    std::cout << "Успешно записано в " << name << "\n";
    std::cout << "\nСодержимое файла:\n";
    std::ifstream check_file(name);
    std::string line;
    if (check_file.is_open()) {
        std::getline(check_file, line);
        std::cout << line << "\n";
        check_file.close();
    }
}