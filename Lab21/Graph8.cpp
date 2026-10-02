#include "Graph8.h"
#include <iostream>
#include "sup.h"
#include <fstream>
#include <random>
#include <iomanip>
#include <queue>
#include <algorithm>
#include <limits>

Graph8::Graph8() : n(0) {}

Graph8::Graph8(const std::string& filename) : n(0) {
    loadFromFile(filename);
}

Graph8::Graph8(int size) : n(size) {
    adj.assign(n, std::vector<int>(n, 0));
}

Graph8::Graph8(const std::vector<std::vector<int>>& matrix) {
    adj = matrix;
    n = (int)adj.size();
    if (!validateMatrix()) {
        n = 0;
        adj.clear();
    }
}

bool Graph8::validateMatrix() const {
    if (n <= 0) return false;
    for (const auto& row : adj)
        if ((int)row.size() != n) {
            std::cout << "\nОшибка: матрица не квадратная\n";
            return false;
        }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (adj[i][j] != 0 && adj[i][j] != 1) {
                std::cout << "\nОшибка: допустимы только 0 или 1\n";
                return false;
            }
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (adj[i][j] != adj[j][i]) {
                std::cout << "\nОшибка: матрица не симметрична\n";
                return false;
            }
    return true;
}

void Graph8::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cout << "\nОшибка: не удалось создать файл\n";
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

void Graph8::loadFromFile(const std::string& filename) {
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

std::vector<int> Graph8::citiesWithExactStops(int start, int L) const {
    if (n == 0 || start < 0 || start >= n) return {};
    std::vector<int> dist(n, -1);
    std::queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int to = 0; to < n; ++to) {
            if (adj[v][to] == 1 && dist[to] == -1) {
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }
    std::vector<int> result;
    for (int i = 0; i < n; ++i)
        if (i != start && dist[i] == L + 1) result.push_back(i);
    std::sort(result.begin(), result.end());
    return result;
}

void Graph8::printResult(int start, int L) const {
    std::vector<int> cities = citiesWithExactStops(start - 1, L);
    if (cities.empty()) {
        std::cout << "\nРезультат: -1\n";
        return;
    }
    std::cout << "\nГорода ровно с " << L << " пересадками:\n";
    for (int c : cities) std::cout << c + 1 << " ";
    std::cout << "\n";
}

void Graph8::printMatrix() const {
    std::cout << "\nМатрица смежности (" << n << " вершин):\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "\t";
        for (int j = 0; j < n; ++j) std::cout << adj[i][j] << " ";
        std::cout << "\n";
    }
}

Graph8 Graph8::fromKeyboard() {
    int n;
    std::cout << "Введите количество городов (<= 15): ";
    n = Input_Int();
    if (n > 15) n = 15;
    std::vector<std::vector<int>> mat(n, std::vector<int>(n, 0));
    std::cout << "\nВведите матрицу смежности (только 0 или 1, верхний треугольник):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int val = Input_Int();
            if (val != 0 && val != 1) {
                std::cout << "Ошибка: допустимы только 0 или 1! Установлено 0.\n";
                val = 0;
            }
            mat[i][j] = val;
            mat[j][i] = val;
        }
    }
    Graph8 g(mat);
    g.saveToFile("FileName");
    return g;
}

Graph8 Graph8::fromRandom() {
    int n;
    std::cout << "Введите количество городов (<= 15): ";
    n = Input_Int();
    if (n > 15) n = 15;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    std::vector<std::vector<int>> mat(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (i == j) mat[i][j] = 0;
            else {
                int val = dis(gen);
                mat[i][j] = val;
                mat[j][i] = val;
            }
        }
    }
    Graph8 g(mat);
    g.saveToFile("Graph8.txt");
    return g;
}

Graph8 Graph8::fromFile() {
    std::string filename;
    std::cout << "Введите имя файла: ";
    std::cin >> filename;
    return Graph8(filename);
}