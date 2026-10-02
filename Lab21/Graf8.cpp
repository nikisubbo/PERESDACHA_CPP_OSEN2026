#include "Graph8.h"
#include "sup.h"
#include <iostream>

void Graf8() {
    std::cout << "\nКак создать граф?\n";
    std::cout << "1) С клавиатуры\n2) Случайно\n3) Из файла\nВыбор: ";
    int choose = Input_Int();
    while (choose < 1 || choose > 3) {
        std::cout << "\nОшибка. Попробуйте ещё раз: ";
        choose = Input_Int();
    }
    Graph8 g;
    if (choose == 1) g = Graph8::fromKeyboard();
    else if (choose == 2) g = Graph8::fromRandom();
    else g = Graph8::fromFile();

    if (g.getVertexCount() == 0) {
        std::cout << "\n\tОшибка: не удалось загрузить граф!\n";
        std::cin.get();
        return;
    }
    g.printMatrix();
    std::cout << ("\n\tВведите начальный город (1-" + std::to_string(g.getVertexCount()) + "): ");
    int K = Input_Int();
    std::cout << ("\n\tВведите количество пересадок: ");
    int L = Input_Int();
    g.printResult(K, L);
    std::cout << "  /\\_/\\\n" << " ( V.V )\n" << "  > ^ <\n";
}