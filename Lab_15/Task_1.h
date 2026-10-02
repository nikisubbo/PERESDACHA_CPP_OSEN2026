#pragma once
#include <iostream>
#include <string>

class Point {
private:
    double x;
    double y;
public:
    Point();
    Point(double x_val, double y_val);
    Point(const Point& other);
    ~Point();
    Point& operator=(const Point& other);
    double get_x() const { return x; }
    double get_y() const { return y; }
    void set_x(double x_val) { x = x_val; }
    void set_y(double y_val) { y = y_val; }
    const Point& get_ref() const { return *this; }
    std::string to_string() const;
    void print() const;
};