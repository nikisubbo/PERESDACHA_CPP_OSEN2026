#pragma once
#include <vector>
#include <string>
class Graph {
private:
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> degrees;
    void calcDegrees();
    bool validateMatrix() const;
public:
    Graph();
    explicit Graph(const std::string& filename);
    Graph(int size);
    Graph(const std::vector<std::vector<int>>& matrix);
    ~Graph();
    static Graph fromKeyboard();
    static Graph fromRandom();
    static Graph fromFile();
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void printDegrees() const;
    void printMatrix() const;
    int getVertexCount() const { return n; }
};