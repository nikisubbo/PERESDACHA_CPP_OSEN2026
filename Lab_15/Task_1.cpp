#include "Task_1.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

Point::Point() : x(0.0), y(0.0) {}
Point::Point(double x_val, double y_val) : x(x_val), y(y_val) {}
Point::Point(const Point& other) : x(other.x), y(other.y) {}
Point::~Point() {}

Point& Point::operator=(const Point& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

std::string Point::to_string() const {
    std::ostringstream oss;
    if (x == static_cast<int>(x) && y == static_cast<int>(y)) {
        oss << "{" << static_cast<int>(x) << "; " << static_cast<int>(y) << "}";
    }
    else {
        oss << std::fixed << std::setprecision(3) << "{" << x << "; " << y << "}";
    }
    return oss.str();
}

void Point::print() const {
    if (x == static_cast<int>(x) && y == static_cast<int>(y)) {
        std::cout << "\t{" << static_cast<int>(x) << "; " << static_cast<int>(y) << "}\n";
    }
    else {
        std::cout << std::fixed << std::setprecision(3) << "\t{" << x << "; " << y << "}\n";
    }
}