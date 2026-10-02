#pragma once
#include <windows.h>
#include <vector>
#include <string>
class HemmingCode {
private:
    std::vector<int> data;
    std::vector<int> code;
    int r, m, n, errPos;
    void calcControlBits();
    int syndrome() const;
public:
    explicit HemmingCode(const std::string& bits);
    void insertError(int pos);
    void run();
    void printEmpty() const;
    void printFull() const;
    int get_n() const { return n; }
    void printSyndrome() const;
};
void HowToFillHemming(std::string& msg);