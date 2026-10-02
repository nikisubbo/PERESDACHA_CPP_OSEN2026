#pragma once
#include <iostream>
#include <vector>
#include <string>

class Student {
private:
    std::string name;
    std::vector<int> grades;
public:
    Student();
    Student(const std::string& student_name, const std::vector<int>& student_grades);
    Student(const Student& other);
    ~Student();
    Student& operator=(const Student& other);
    std::string get_name() const { return name; }
    std::vector<int> get_grades() const { return grades; }
    void set_name(const std::string& new_name) { name = new_name; }
    void set_grades(const std::vector<int>& new_grades) { grades = new_grades; }
    std::string to_string() const;
    void print() const;
};