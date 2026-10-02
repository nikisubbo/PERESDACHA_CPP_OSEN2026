#include "Task_3.h"
#include <iostream>
#include <string>

Student::Student() : name("Неизвестно"), grades({}) {}
Student::Student(const std::string& student_name, const std::vector<int>& student_grades)
    : name(student_name), grades(student_grades) {
}
Student::Student(const Student& other) : name(other.name), grades(other.grades) {}
Student::~Student() {}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        name = other.name;
        grades = other.grades;
    }
    return *this;
}

std::string Student::to_string() const {
    std::string result = "Имя: " + name + " [";
    for (size_t i = 0; i < grades.size(); ++i) {
        if (i > 0) result += ", ";
        result += std::to_string(grades[i]);
    }
    result += "]";
    return result;
}

void Student::print() const {
    std::cout << "\t" << to_string() << "\n";
}