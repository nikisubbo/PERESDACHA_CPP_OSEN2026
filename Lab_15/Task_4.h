#pragma once
#include <iostream>
#include <string>

class Point4 {
private:
    double x;
    double y;
public:
    Point4(double x_val, double y_val);
    Point4(const Point4& other);
    ~Point4();
    Point4& operator=(const Point4& other);
    double get_x() const { return x; }
    double get_y() const { return y; }
    void set_x(double x_val) { x = x_val; }
    void set_y(double y_val) { y = y_val; }
    std::string to_string() const;
    void print() const;
};

class Line4 {
private:
    Point4 start;
    Point4 end;
public:
    Line4(const Point4& start_point, const Point4& end_point);
    Line4(double x1, double y1, double x2, double y2);
    Line4(const Line4& other);
    ~Line4();
    Line4& operator=(const Line4& other);
    Point4 get_start() const { return start; }
    Point4 get_end() const { return end; }
    void set_start(const Point4& p) { start = p; }
    void set_end(const Point4& p) { end = p; }
    std::string to_string() const;
    void print() const;
    int get_length() const;
};  