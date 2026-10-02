#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "HomeDyn3.h"
#include "input.h"

void HomeDyn3() {
    std::cout << "Задание: HomeDyn3 (Максимальная сумма пути в матрице)\n";
    int choice = 0;

    do {
        std::cout << "\nКак вы хотите ввести данные?\n";
        std::cout << "1) С клавиатуры\n";
        std::cout << "2) Случайно\n";
        std::cout << "3) Из файла\n";
        std::cout << "4) Назад\n";
        std::cout << "Выбор: ";
        choice = Input_Int();

        if (choice < 1 || choice > 4) {
            std::cout << "Ошибка. Введите число от 1 до 4.\n";
            continue;
        }

        int size = 0;
        std::vector<std::vector<int>> field;

        if (choice == 1) { 
            std::cout << "Введите размер квадратной матрицы (N): ";
            size = Input_Int();
            field.assign(size, std::vector<int>(size));
            std::cout << "Введите " << size * size << " элементов матрицы:\n";
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    field[i][j] = Input_Int();
                }
            }
        }
        else if (choice == 2) { 
            size = std::rand() % 4 + 3; 
            field.assign(size, std::vector<int>(size));
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    field[i][j] = std::rand() % 9 + 1; 
                }
            }
            std::cout << "\n[Случайные данные] Размер матрицы: " << size << "x" << size << "\n";
        }
        else if (choice == 3) { 
            std::string file_name;
            std::cout << "Введите название файла (без .txt): ";
            std::cin >> file_name;
            file_name += ".txt";

            std::ifstream file(file_name);
            while (!file.is_open()) {
                std::cout << "Файл не найден. Введите название заново: ";
                std::cin >> file_name;
                file_name += ".txt";
                file.open(file_name);
            }

            file >> size;
            field.assign(size, std::vector<int>(size));
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    file >> field[i][j];
                }
            }
            file.close();
        }
        else {
            break; 
        }


        std::cout << "\nПоле:\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << field[i][j] << ' ';
            }
            std::cout << '\n';
        }
        std::vector<std::vector<int>> d_field(size, std::vector<int>(size));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == 0 && j == 0) {
                    d_field[i][j] = field[i][j];
                }
                else if (i == 0) {
                    d_field[i][j] = d_field[i][j - 1] + field[i][j];
                }
                else if (j == 0) {
                    d_field[i][j] = d_field[i - 1][j] + field[i][j];
                }
                else {
                    d_field[i][j] = std::max(d_field[i - 1][j], d_field[i][j - 1]) + field[i][j];
                }
            }
        }


        std::string moves = "";
        int current_index_r = size - 1;
        int current_index_c = size - 1;
        int summa = d_field[current_index_r][current_index_c];

        while (current_index_r > 0 || current_index_c > 0) {
            if (current_index_r == 0) {
                moves += "L ";
                current_index_c--;
            }
            else if (current_index_c == 0) {
                moves += "U ";
                current_index_r--;
            }
            else {
                if (d_field[current_index_r - 1][current_index_c] > d_field[current_index_r][current_index_c - 1]) {
                    moves += "U ";
                    current_index_r--;
                }
                else {
                    moves += "L ";
                    current_index_c--;
                }
            }
        }


        std::string file_name_output;
        std::cout << "\nВведите название файла для вывода (без .txt): ";
        std::cin >> file_name_output;
        file_name_output += ".txt";

        std::ofstream file_output(file_name_output);
        file_output << summa << "\n" << moves;
        file_output.close();
        std::cout << "Результат успешно записан в " << file_name_output << "\n";

    } while (choice != 4);
}