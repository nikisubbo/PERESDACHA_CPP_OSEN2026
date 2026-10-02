#include "Graph4.h"
#include "sup.h"
#include <iostream>

void Graf4() {
    std::cout << "\nКак создать граф?\n";
    std::cout << "1) С клавиатуры\n2) Случайно\n3) Из файла\nВыбор: ";
    int choose = Input_Int();
    while (choose < 1 || choose > 3) {
        std::cout << "\nОшибка. Попробуйте ещё раз: ";
        choose = Input_Int();
    }
    Graph4 g;
    if (choose == 1) g = Graph4::fromKeyboard();
    else if (choose == 2) g = Graph4::fromRandom();
    else g = Graph4::fromFile();

    if (g.getVertexCount() == 0) {
        std::cout << "\n\tОшибка: не удалось загрузить граф!\n";
        std::cin.get();
        return;
    }
    std::cout << "\n\tГраф загружен! Вершин: " << g.getVertexCount() << "\n";
    g.printMatrix();
    std::cout << ("\n\tВведите начальную вершину (1-" + std::to_string(g.getVertexCount()) + "): ");
    int start = Input_Int();
    g.printBFS(start);
    std::cout << "  /\\_/\\\n" << " ( V.V )\n" << "  > ^ <\n";
}