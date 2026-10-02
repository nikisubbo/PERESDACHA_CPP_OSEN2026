#include "Task_2.h"
#include <iostream>
#include <string>

Line::Line() : start(Point(0, 0)), end(Point(0, 0)) {}
Line::Line(const Point& start_point, const Point& end_point)
    : start(start_point), end(end_point) {
}
Line::Line(const Line& other) : start(other.start), end(other.end) {}
Line::~Line() {}

Line& Line::operator=(const Line& other) {
    if (this != &other) {
        start = other.start;
        end = other.end;
    }
    return *this;
}

std::string Line::to_string() const {
    return "от " + start.to_string() + " до " + end.to_string();
}

void Line::print() const {
    std::cout << "\t" << to_string() << "\n";
}