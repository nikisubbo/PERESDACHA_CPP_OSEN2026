#include "Graph4.h"
#include "sup.h"
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <queue>
#include <algorithm>
#include <limits>

Graph4::Graph4() : n(0) {}

Graph4::Graph4(const std::string& filename) : n(0) {
    loadFromFile(filename);
}

Graph4::Graph4(int size) : n(size) {
    adj.assign(n, std::vector<int>(n, 0));
}

Graph4::Graph4(const std::vector<std::vector<int>>& matrix) {
    adj = matrix;
    n = (int)adj.size();
    if (!validateMatrix()) {
        n = 0;
        adj.clear();
    }
}

bool Graph4::validateMatrix() const {
    if (n <= 0) {
        std::cout << "\nОшибка: n <= 0\n";
        return false;
    }
    for (const auto& row : adj)
        if ((int)row.size() != n) {
            std::cout << "\nОшибка: матрица не квадратная\n";
            return false;
        }
    return true;
}

void Graph4::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cout << "\nОшибка: не удалось создать файл " << filename << "\n";
        return;
    }
    out << n << "\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) out << adj[i][j] << " ";
        out << "\n";
    }
    out.close();
    std::cout << "\nМатрица сохранена в " << filename << "\n";
}

void Graph4::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cout << "\nОшибка: файл \"" << filename << "\" не найден!\n";
        n = 0;
        return;
    }
    if (!(in >> n) || n <= 0) {
        std::cout << "\nОшибка: неверное количество вершин\n";
        n = 0;
        return;
    }
    adj.assign(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (!(in >> adj[i][j])) {
                std::cout << "\nОшибка: не удалось прочитать матрицу\n";
                n = 0;
                return;
            }
    in.close();
    if (!validateMatrix()) {
        n = 0;
        adj.clear();
    }
}

std::vector<int> Graph4::bfs(int start) const {
    if (n == 0 || start < 0 || start >= n) return {};
    std::vector<bool> visited(n, false);
    std::vector<int> order;
    std::queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        order.push_back(v);
        std::vector<int> neighbors;
        for (int to = 0; to < n; ++to)
            if (adj[v][to] != 0 && !visited[to])
                neighbors.push_back(to);
        std::sort(neighbors.begin(), neighbors.end());
        for (int to : neighbors) {
            visited[to] = true;
            q.push(to);
        }
    }
    return order;
}

void Graph4::printBFS(int start) const {
    if (n == 0) {
        std::cout << "\nГраф не загружен\n";
        return;
    }
    if (start < 1 || start > n) {
        std::cout << "\nОшибка: вершина должна быть от 1 до " << n << "\n";
        return;
    }
    int startZero = start - 1;
    std::vector<int> order = bfs(startZero);
    std::cout << "\nBFS от вершины " << start << ":\n\t";
    for (int v : order) std::cout << v + 1 << " ";
    std::cout << "\n";
}

void Graph4::printMatrix() const {
    std::cout << "\nМатрица смежности (" << n << " вершин):\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "\t";
        for (int j = 0; j < n; ++j) std::cout << adj[i][j] << " ";
        std::cout << "\n";
    }
}

Graph4 Graph4::fromKeyboard() {
    std::cout << "Введите количество вершин: ";
    int n = Input_Int();
    std::vector<std::vector<int>> mat(n, std::vector<int>(n));
    std::cout << "\nВведите матрицу смежности (веса, 0 если нет ребра):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mat[i][j] = Input_Int();
        }
    }
    Graph4 g(mat);
    g.saveToFile("FileName");
    return g;
}

Graph4 Graph4::fromRandom() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    std::uniform_int_distribution<> wdis(1, 10);
    int n;
    std::cout << "\nВведите количество вершин: ";
    std::cin >> n;
    std::vector<std::vector<int>> mat(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j && dis(gen) == 1)
                mat[i][j] = wdis(gen);
    Graph4 g(mat);
    g.saveToFile("Graph4.txt");
    return g;
}

Graph4 Graph4::fromFile() {
    std::string filename;
    std::cout << "\nВведите имя файла: ";
    std::cin >> filename;
    return Graph4(filename);
}