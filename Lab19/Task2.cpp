#include <iostream>
#include "Haffman.h"
#include "sup.h"

void Task2() {
    std::string text;
    HowToFillHaffman(text);
    std::cout << "\nБыло использовано заданное значение: \"" << text << "\"\n";

    HaffmanCoder coder(text);
    coder.encode();
    coder.printTree();
    coder.printTable();
    coder.printStats();
    coder.printEncodedBits();

    std::string bits = coder.getEncodedBits();
    std::string decoded = coder.decodeFromTree(bits);

    std::cout << "\nДекодированная строка: \"" << decoded << "\"\n";
    std::cout << "Совпадает с оригиналом: " << (decoded == text ? "Да" : "Нет") << "\n";

    std::cin.get();
}