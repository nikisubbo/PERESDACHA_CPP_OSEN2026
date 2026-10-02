#include <iostream>
#include <ctime>
#include <cstdlib>
#include "input.h"
int Input_Int() {
    int number;
    while (true) {
        if (std::cin >> number) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return number;
        }
        else {
            std::cout << "Error. Enter number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
