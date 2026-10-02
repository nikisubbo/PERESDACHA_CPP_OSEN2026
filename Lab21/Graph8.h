#pragma once
#pragma once
#include <vector>
#include <string>
#include <queue>
class Graph8 {
private:
    int n;
    std::vector<std::vector<int>> adj;
    bool validateMatrix() const;
public:
    Graph8();
    explicit Graph8(const std::string& filename);
    Graph8(int size);
    Graph8(const std::vector<std::vector<int>>& matrix);
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    std::vector<int> citiesWithExactStops(int start, int L) const;
    void printResult(int start, int L) const;
    void printMatrix() const;
    int getVertexCount() const { return n; }
    static Graph8 fromKeyboard();
    static Graph8 fromRandom();
    static Graph8 fromFile();
};