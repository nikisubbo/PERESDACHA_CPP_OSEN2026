#include "Assoc17.h"
#include "stl_utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

void Assoc17() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::cout << "=== Задание Assoc17 ===\n";

    int n;
    std::cout << "Введите количество слов в векторе V: ";
    std::cin >> n;
    while (n < 1) {
        std::cout << "Ошибка: количество должно быть >= 1. Введите снова: ";
        std::cin >> n;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\n--- Ввод слов ---\n";
    std::vector<std::string> V = get_words_with_methods(n);

    std::cout << "\nВведённые слова: ";
    for (const auto& word : V) std::cout << word << " ";
    std::cout << "\n";

    std::map<char, int> M;
    for (const auto& word : V) {
        if (!word.empty()) {
            M[word[0]] += word.size();
        }
    }

    std::cout << "\nРезультат (буква : сумма длин слов):\n";
    for (const auto& pair : M) {
        std::cout << pair.first << " : " << pair.second << "\n";
    }
}