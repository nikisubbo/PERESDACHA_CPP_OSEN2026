#pragma once
#include "Task_1.h"
#include <string>

class Line {
private:
    Point start;
    Point end;
public:
    Line();
    Line(const Point& start_point, const Point& end_point);
    Line(const Line& other);
    ~Line();
    Line& operator=(const Line& other);
    Point get_start() const { return start; }
    Point get_end() const { return end; }
    void set_start(const Point& p) { start = p; }
    void set_end(const Point& p) { end = p; }
    std::string to_string() const;
    void print() const;
};