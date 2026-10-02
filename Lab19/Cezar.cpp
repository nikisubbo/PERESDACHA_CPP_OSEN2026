#include "Cezar.h"
#include "sup.h"
#include <iostream>
#include <fstream>

char CaesarCipher::shiftChar(char c, int k, bool encrypt) const {
    if (c >= 'А' && c <= 'Я') {
        int base = 'А';
        int alphabetSize = 32;
        if (encrypt)
            return (char)(base + (c - base + k % alphabetSize + alphabetSize) % alphabetSize);
        else
            return (char)(base + (c - base - k % alphabetSize + alphabetSize) % alphabetSize);
    }
    if (c >= 'а' && c <= 'я') {
        int base = 'а';
        int alphabetSize = 32;
        if (encrypt)
            return (char)(base + (c - base + k % alphabetSize + alphabetSize) % alphabetSize);
        else
            return (char)(base + (c - base - k % alphabetSize + alphabetSize) % alphabetSize);
    }
    if (c >= 'A' && c <= 'Z') {
        int base = 'A';
        int alphabetSize = 26;
        if (encrypt)
            return (char)(base + (c - base + k % alphabetSize + alphabetSize) % alphabetSize);
        else
            return (char)(base + (c - base - k % alphabetSize + alphabetSize) % alphabetSize);
    }
    if (c >= 'a' && c <= 'z') {
        int base = 'a';
        int alphabetSize = 26;
        if (encrypt)
            return (char)(base + (c - base + k % alphabetSize + alphabetSize) % alphabetSize);
        else
            return (char)(base + (c - base - k % alphabetSize + alphabetSize) % alphabetSize);
    }
    return c;
}

CaesarCipher::CaesarCipher(const std::string& txt, int k) : text(txt), key(k) {}

void CaesarCipher::encrypt() {
    encrypted.clear();
    for (char c : text) {
        encrypted += shiftChar(c, key, true);
    }
}

void CaesarCipher::decrypt() {
    decrypted.clear();
    for (char c : encrypted) {
        decrypted += shiftChar(c, key, false);
    }
}

void CaesarCipher::printResult() const {
    std::cout << "\nИсходный текст:    \"" << text << "\"\n";
    std::cout << "Ключ сдвига:       " << key << "\n";
    std::cout << "Зашифрованный:     \"" << encrypted << "\"\n";
    std::cout << "Расшифрованный:    \"" << decrypted << "\"\n";
    std::cout << "Совпадает с оригиналом: " << (decrypted == text ? "Да" : "Нет") << "\n";
}

void HowToFillCaesar(std::string& msg) {
    int choice = 0;
    do {
        std::cout << "\nКак вы хотите получить текст?\n";
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
            std::cout << "Введите текст: ";
            std::getline(std::cin, msg);
            while (msg.empty()) {
                std::cout << "Ошибка. Текст не может быть пустым. Попробуйте снова: ";
                std::getline(std::cin, msg);
            }
            break;
        }
        case 2: {
            std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            std::cout << "Введите длину сообщения: ";
            int len = Input_Int();
            msg.clear();
            for (int i = 0; i < len; ++i) {
                msg += chars[std::rand() % chars.length()];
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
            std::getline(infile, msg);
            infile.close();
            if (msg.empty()) {
                std::cerr << "Ошибка. Файл пуст.\n";
                break;
            }
            std::cout << "Сообщение из файла: " << msg << "\n";
            break;
        }
        }
    } while (choice != 4);
}