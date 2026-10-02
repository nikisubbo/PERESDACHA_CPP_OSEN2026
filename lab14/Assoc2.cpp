#include "Assoc2.h"
#include "stl_utils.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

void Assoc2() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::cout << "=== Задание Assoc2 ===\n";

    int n0;
    std::cout << "Введите размер вектора V0 (>= 1): ";
    std::cin >> n0;
    while (n0 < 1) {
        std::cout << "Ошибка: размер должен быть >= 1. Введите снова: ";
        std::cin >> n0;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\n--- Вектор V0 ---\n";
    std::vector<int> V0 = get_vector_with_methods(n0);

    std::cout << "\nВектор V0: ";
    for (int x : V0) std::cout << x << " ";
    std::cout << "\n";

    std::set<int> set_V0(V0.begin(), V0.end());
    std::cout << "Множество на основе V0 (уникальные элементы): ";
    for (int x : set_V0) std::cout << x << " ";
    std::cout << "\n";

    int N = get_positive_number("Введите количество векторов Vi для проверки: ");

    int count = 0;
    std::vector<std::vector<int>> all_vectors;

    for (int i = 1; i <= N; ++i) {
        int ni;
        std::cout << "\n--- Вектор V" << i << " ---\n";
        std::cout << "Введите размер вектора V" << i << " (>= 1): ";
        std::cin >> ni;
        while (ni < 1) {
            std::cout << "Ошибка: размер должен быть >= 1. Введите снова: ";
            std::cin >> ni;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::vector<int> Vi = get_vector_with_methods(ni);
        all_vectors.push_back(Vi);

        std::set<int> set_Vi(Vi.begin(), Vi.end());

        if (std::includes(set_Vi.begin(), set_Vi.end(), set_V0.begin(), set_V0.end())) {
            std::cout << "✓ Вектор V" << i << " содержит все элементы V0\n";
            count++;
        }
        else {
            std::cout << "✗ Вектор V" << i << " НЕ содержит все элементы V0\n";
        }
    }

    std::cout << "\n=== Результат ===\n";
    std::cout << "Количество векторов Vi, содержащих все элементы V0: " << count << " из " << N << "\n";

    std::cout << "\nВсе введённые векторы:\n";
    for (int i = 0; i < N; ++i) {
        print_vector("V" + std::to_string(i + 1), all_vectors[i]);
    }
}