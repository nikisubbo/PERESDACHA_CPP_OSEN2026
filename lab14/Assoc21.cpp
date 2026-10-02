#include "Assoc21.h"
#include "stl_utils.h"
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

void Assoc21() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::cout << "=== Задание Assoc21 ===\n";

    int n;
    std::cout << "Введите количество элементов вектора V (> 0): ";
    std::cin >> n;
    while (n <= 0) {
        std::cout << "Ошибка: количество должно быть > 0. Введите снова: ";
        std::cin >> n;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\n--- Ввод элементов ---\n";
    std::vector<int> V = get_vector_with_methods(n);

    std::cout << "\nВведённые числа: ";
    for (int x : V) std::cout << x << " ";
    std::cout << "\n";

    std::multimap<int, int> M;
    for (int val : V) {
        int last_digit = std::abs(val) % 10;
        M.insert(std::make_pair(last_digit, val));
    }

    std::cout << "\nРезультат (последняя цифра : число):\n";
    std::cout << "Ключ\tЗначение\n";
    for (const auto& pair : M) {
        std::cout << pair.first << "\t" << pair.second << "\n";
    }
}