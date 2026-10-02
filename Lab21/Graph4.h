#pragma once
#include <vector>
#include <string>
#include <queue>
class Graph4 {
private:
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> bfs(int start) const;
    bool validateMatrix() const;
public:
    Graph4();
    explicit Graph4(const std::string& filename);
    Graph4(int size);
    Graph4(const std::vector<std::vector<int>>& matrix);
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void printBFS(int start) const;
    void printMatrix() const;
    int getVertexCount() const { return n; }
    static Graph4 fromKeyboard();
    static Graph4 fromRandom();
    static Graph4 fromFile();
};