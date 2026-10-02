#include "hemming.h"
#include <windows.h>
#include "sup.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

HemmingCode::HemmingCode(const std::string& bits) {
    for (char c : bits) data.push_back(c - '0');
    m = (int)data.size();
    r = 0;
    while ((1 << r) < m + r + 1) r++;
    n = m + r;
    code.assign(n, 0);
    errPos = 0;
}

void HemmingCode::printEmpty() const {
    std::cout << "\n\t";
    for (int i = 1; i <= n; ++i) std::cout << std::setw(2) << i << " | ";
    std::cout << "\n\t";
    int idx = 0;
    for (int i = 1; i <= n; ++i) {
        if ((i & (i - 1)) == 0) std::cout << " _ | ";
        else std::cout << " " << data[idx++] << " | ";
    }
    std::cout << "\n";
}

void HemmingCode::calcControlBits() {
    int idx = 0;
    for (int i = 1; i <= n; ++i) {
        if ((i & (i - 1)) == 0) continue;
        code[i - 1] = data[idx++];
    }
    for (int p = 1; p <= n; p *= 2) {
        int sum = 0;
        for (int i = p; i <= n; ++i) {
            if ((i & p) && i != p) sum ^= code[i - 1];
        }
        code[p - 1] = sum;
    }
}

int HemmingCode::syndrome() const {
    int syn = 0;
    for (int p = 1; p <= n; p *= 2) {
        int sum = 0;
        for (int i = p; i <= n; ++i) {
            if (i & p) sum ^= code[i - 1];
        }
        if (sum) syn += p;
    }
    return syn;
}

void HemmingCode::run() {
    calcControlBits();
    errPos = syndrome();
}

void HemmingCode::insertError(int pos) {
    if (pos >= 1 && pos <= n) {
        code[pos - 1] ^= 1;
        errPos = syndrome();
    }
}

void HemmingCode::printFull() const {
    std::cout << "\nИсходное сообщение (" << m << " бит): ";
    for (int b : data) std::cout << b;
    std::cout << "\nКонтрольных битов: " << r;
    std::cout << "\nОбщая длина кода: " << n << "\n";

    std::cout << "\nКонтрольные биты: ";
    for (int p = 1; p <= n; p *= 2) {
        std::cout << "\tC" << p << " = ";
        bool first = true;
        for (int i = p + 1; i <= n; ++i) {
            if (i & p) {
                if (!first) std::cout << " + ";
                std::cout << code[i - 1];
                first = false;
            }
        }
        std::cout << " = " << code[p - 1] << "\n";
    }
    std::cout << "\n\t";
    for (int i = 1; i <= n; ++i) std::cout << std::setw(2) << i << " | ";
    std::cout << "\n\t";
    for (int i = 0; i < n; ++i) std::cout << " " << code[i] << " | ";
    std::cout << "\n";
}

void HemmingCode::printSyndrome() const {
    std::cout << "\nКонтрольных битов: " << r;
    std::cout << "\nОбщая длина кода: " << n << "\n";
    std::cout << "\n\t";
    for (int i = 1; i <= n; ++i) std::cout << std::setw(2) << i << " | ";
    std::cout << "\n\t";
    for (int i = 0; i < n; ++i) std::cout << " " << code[i] << " | ";
    std::cout << "\n";
    std::cout << "\nВычисление синдромов: ";
    for (int p = 1; p <= n; p *= 2) {
        std::cout << "\ts" << p << " = ";
        int sum = 0;
        bool first = true;
        for (int i = p; i <= n; ++i) {
            if ((i & p) != 0) {
                if (!first) std::cout << " + ";
                std::cout << code[i - 1];
                sum ^= code[i - 1];
                first = false;
            }
        }
        std::cout << " = " << sum << "\n";

        std::cout << "\t\tv" << p << " = {";
        first = true;
        for (int i = p; i <= n; ++i) {
            if ((i & p) != 0) {
                if (!first) std::cout << ", ";
                std::cout << i;
                first = false;
            }
        }
        std::cout << "}\n";
    }
    if (errPos) {
        std::cout << "\nСиндром = " << errPos << ", ошибка в бите " << errPos << "\n";
        std::cout << "\nИсправленное слово: ";
        for (int i = 0; i < n; ++i) {
            int val = code[i];
            if (i == errPos - 1) val ^= 1;
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
    else {
        std::cout << "\nСиндром = 0. Ошибок нет.\n";
    }
}

void HowToFillHemming(std::string& msg) {
    int choice = 0;
    do {
        std::cout << "\nКак вы хотите получить двоичное сообщение?\n";
        std::cout << "1) С клавиатуры\n";
        std::cout << "2) Случайно\n";
        std::cout << "3) Из файла\n";
        std::cout << "4) Назад\n";
        std::cout << "Выбор: ";

        choice = Input_Int();
        if (choice < 1 || choice > 4) {
            std::cout << "Ошибка. Введите корректное число (1-4).\n";
            continue;
        }
        switch (choice) {
        case 1: {
            std::cout << "Введите двоичное сообщение (только 0 и 1): ";
            std::cin >> msg;
            while (msg.empty() || msg.find_first_not_of("01") != std::string::npos) {
                std::cout << "Ошибка. Допустимы только '0' и '1'. Попробуйте снова: ";
                std::cin >> msg;
            }
            break;
        }
        case 2: {
            std::cout << "Введите длину сообщения: ";
            int len = Input_Int();
            msg.clear();
            for (int i = 0; i < len; ++i) {
                msg += std::to_string(std::rand() % 2);
            }
            std::cout << "Случайное сообщение: " << msg << "\n";
            break;
        }
        case 3: {
            std::string filename;
            std::cout << "Введите имя файла (например, data.txt): ";
            std::cin >> filename;
            std::ifstream infile(filename);
            if (!infile.is_open()) {
                std::cerr << "Ошибка. Не удалось открыть файл.\n";
                break;
            }
            infile >> msg;
            infile.close();
            if (msg.empty()) {
                std::cerr << "Ошибка. Файл пуст.\n";
                break;
            }
            if (msg.find_first_not_of("01") != std::string::npos) {
                std::cerr << "Ошибка. Файл должен содержать только 0 и 1.\n";
                msg.clear();
                break;
            }
            std::cout << "Сообщение из файла: " << msg << "\n";
            break;
        }
        }
    } while (choice != 4);
}