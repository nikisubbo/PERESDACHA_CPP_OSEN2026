#pragma once
#include <string>
#include <vector>

int get_int(const std::string& prompt = "");
double get_double(const std::string& prompt = "");
int get_min2();
int get_grade(const std::string& prompt = "");

void fill_grades(std::vector<int>& grades, int n);

int choose_input_mode();  
void fill_doubles(std::vector<double>& vec, int count, const std::string& value_name = "значение");