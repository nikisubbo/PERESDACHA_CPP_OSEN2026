#include <iostream>
#include "Cezar.h"
#include "sup.h"

void Task3() {
    std::cout << "Задача 3. Шифр Цезаря.\n";
    std::string message;
    HowToFillCaesar(message);

    std::cout << "\nВведите ключ сдвига (целое число): ";
    int key = Input_Int();

    CaesarCipher cipher(message, key);
    cipher.encrypt();
    cipher.decrypt();
    cipher.printResult();

    std::cin.get();
}