#include "Graph1.h"
#include "sup.h"
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <limits>

Graph::Graph() : n(0) {}
Graph::~Graph() {}

Graph::Graph(const std::string& filename) : n(0) {
    loadFromFile(filename);
}

Graph::Graph(int size) : n(size) {
    adj.assign(n, std::vector<int>(n, 0));
}

Graph::Graph(const std::vector<std::vector<int>>& matrix) {
    adj = matrix;
    n = (int)adj.size();
    if (!validateMatrix()) {
        n = 0;
        adj.clear();
        throw std::invalid_argument("неверная матрица");
    }
    calcDegrees();
}

bool Graph::validateMatrix() const {
    for (const auto& row : adj)
        if ((int)row.size() != n) {
            std::cout << "\nОшибка: матрица не квадратная!\n";
            return false;
        }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (adj[i][j] != 0 && adj[i][j] != 1) {
                std::cout << "\nОшибка: допустимы только 0 и 1! Найдено: " << adj[i][j] << "\n";
                return false;
            }
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (adj[i][j] != adj[j][i]) {
                std::cout << "\nОшибка: матрица не симметрична!\n";
                return false;
            }
    return true;
}

void Graph::calcDegrees() {
    degrees.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        int deg = 0;
        for (int j = 0; j < n; ++j) deg += adj[i][j];
        if (adj[i][i] == 1) deg++;
        degrees[i] = deg;
    }
}

void Graph::saveToFile(const std::string& filename) const {
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

void Graph::loadFromFile(const std::string& filename) {
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
        return;
    }
    calcDegrees();
}

Graph Graph::fromKeyboard() {
    std::cout << "Введите количество вершин: ";
    int n = Input_Int();
    std::vector<std::vector<int>> mat(n, std::vector<int>(n, 0));
    std::cout << "\nВведите матрицу смежности (только 0 и 1, верхний треугольник):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            while (true) {
                int val = Input_Int();
                if (val == 0 || val == 1) {
                    mat[i][j] = val;
                    mat[j][i] = val;
                    break;
                }
                std::cout << "Ошибка: допустимы только 0 или 1!\n";
            }
        }
    }
    Graph g(mat);
    g.saveToFile("FileName");
    return g;
}

Graph Graph::fromRandom() {
    std::cout << "Введите количество вершин: ";
    int n = Input_Int();
    std::vector<std::vector<int>> mat(n, std::vector<int>(n, 0));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int val = dis(gen);
            mat[i][j] = val;
            mat[j][i] = val;
        }
    }
    Graph g(mat);
    g.saveToFile("Graph1.txt");
    return g;
}

Graph Graph::fromFile() {
    std::string filename;
    std::cout << "Введите имя файла: ";
    std::cin >> filename;
    return Graph(filename);
}

void Graph::printDegrees() const {
    std::cout << "\nСтепени вершин:\n";
    for (int i = 0; i < n; ++i)
        std::cout << "Вершина " << i + 1 << ": " << degrees[i] << "\n";
}

void Graph::printMatrix() const {
    std::cout << "\nМатрица смежности (" << n << " вершин):\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "\t";
        for (int j = 0; j < n; ++j) std::cout << adj[i][j] << " ";
        std::cout << "\n";
    }
}