#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <random>
#include <limits>

#define NOMINMAX
#include <windows.h>

int get_input_method(const std::string& prompt = "Выберите способ ввода:\n1) С клавиатуры\n2) Случайно\n3) Из файла\nВыбор: ");

std::vector<int> read_vector_keyboard(int n);
std::vector<int> read_vector_random(int n, int min_val = 1, int max_val = 100);
std::vector<int> read_vector_from_file(int n, const std::string& default_filename = "data.txt");
std::vector<int> get_vector_with_methods(int n);

std::vector<std::string> read_words_keyboard(int n);
std::vector<std::string> read_words_random(int n);
std::vector<std::string> read_words_from_file(int n);
std::vector<std::string> get_words_with_methods(int n);

void print_vector(const std::string& name, const std::vector<int>& v);
int get_positive_number(const std::string& prompt);