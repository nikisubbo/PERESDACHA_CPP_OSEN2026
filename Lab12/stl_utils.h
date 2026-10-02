#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>

int get_even_number(const std::string& prompt);

template <typename Container>
void print_forward(const std::string& name, const Container& c) {
    std::cout << name << " в прямом порядке: ";
    for (auto it = c.begin(); it != c.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

template <typename Container>
void print_backward(const std::string& name, const Container& c) {
    std::cout << name << " в обратном порядке: ";
    for (auto it = c.rbegin(); it != c.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

int get_min_number(const std::string& prompt, int min_val);
int get_odd_number(const std::string& prompt, int min_val);