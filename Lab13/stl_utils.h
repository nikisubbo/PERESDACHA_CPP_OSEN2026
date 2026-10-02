#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
std::vector<int> get_vector_from_input(const std::string& prompt);
void print_vector(const std::string& name, const std::vector<int>& v);
std::list<int> get_even_list_from_input(const std::string& prompt);
template <typename T>
void print_list(const std::string& name, const std::list<T>& lst) {
    std::cout << name << ": ";
    if (lst.empty()) {
        std::cout << "Empty";
    }
    else {
        for (const auto& x : lst) {
            std::cout << x << " ";
        }
    }
    std::cout << "\n";
}
std::vector<int> get_vector_min_size(const std::string& prompt, int min_size);