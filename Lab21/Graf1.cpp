#include "Graph1.h"
#include "sup.h"
#include <iostream>

void Graf1() {
    std::cout << "\nКак создать граф?\n";
    std::cout << "1) С клавиатуры\n2) Случайно\n3) Из файла\nВыбор: ";
    int choose = Input_Int();
    while (choose < 1 || choose > 3) {
        std::cout << "\nОшибка. Попробуйте ещё раз: ";
        choose = Input_Int();
    }
    Graph g;
    if (choose == 1) g = Graph::fromKeyboard();
    else if (choose == 2) g = Graph::fromRandom();
    else g = Graph::fromFile();

    if (g.getVertexCount() == 0) {
        std::cout << "\nОшибка: не удалось загрузить граф!\n";
        std::cin.get();
        return;
    }
    g.printMatrix();
    g.printDegrees();
    std::cout << "  /\\_/\\\n" << " ( V.V )\n" << "  > ^ <\n";
}