#include "stl_utils.h"

int get_input_method(const std::string& prompt) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    int method;
    std::cout << prompt;
    std::cin >> method;
    while (method < 1 || method > 3) {
        std::cout << "Неверный выбор. Введите 1, 2 или 3: ";
        std::cin >> method;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return method;
}

std::vector<int> read_vector_keyboard(int n) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    std::cout << "Введите " << n << " целых чисел:\n";
    std::vector<int> vec;
    for (int i = 0; i < n; ++i) {
        int val;
        std::cin >> val;
        vec.push_back(val);
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return vec;
}

std::vector<int> read_vector_random(int n, int min_val, int max_val) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    std::cout << "Генерация " << n << " случайных чисел:\n";
    std::vector<int> vec;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min_val, max_val);
    for (int i = 0; i < n; ++i) {
        int val = dis(gen);
        vec.push_back(val);
        std::cout << val << " ";
    }
    std::cout << "\n";
    return vec;
}

std::vector<int> read_vector_from_file(int n, const std::string& default_filename) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    std::string filename;
    std::cout << "Введите имя файла (или нажмите Enter для '" << default_filename << "'): ";
    std::getline(std::cin, filename);
    if (filename.empty()) filename = default_filename;
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Ошибка. Файл не открыт: " << filename << "\n";
        return {};
    }
    std::vector<int> vec;
    int val;
    int count = 0;
    while (count < n && infile >> val) {
        vec.push_back(val);
        count++;
    }
    infile.close();
    if (count < n) {
        std::cout << "Внимание: Файл содержал только " << count << " элементов.\n";
    }
    return vec;
}

std::vector<int> get_vector_with_methods(int n) {
    int method = get_input_method();
    if (method == 1) return read_vector_keyboard(n);
    if (method == 2) return read_vector_random(n);
    return read_vector_from_file(n);
}

std::vector<std::string> read_words_keyboard(int n) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    std::cout << "Введите " << n << " английских слов заглавными буквами:\n";
    std::vector<std::string> words(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> words[i];
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return words;
}

std::vector<std::string> read_words_random(int n) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    std::cout << "Генерация " << n << " случайных слов:\n";
    std::vector<std::string> words;
    std::vector<std::string> sample_words = { "APPLE", "BANANA", "CHERRY", "DATE", "ELDERBERRY",
                                              "FIG", "GRAPE", "HONEYDEW", "KIWI", "LEMON",
                                              "MANGO", "NECTARINE", "ORANGE", "PAPAYA", "QUINCE" };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sample_words.size() - 1);
    for (int i = 0; i < n; ++i) {
        std::string word = sample_words[dis(gen)];
        words.push_back(word);
        std::cout << word << " ";
    }
    std::cout << "\n";
    return words;
}

std::vector<std::string> read_words_from_file(int n) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    std::string filename;
    std::cout << "Введите имя файла: ";
    std::cin >> filename;
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Ошибка. Файл не открыт: " << filename << "\n";
        return {};
    }
    std::vector<std::string> words;
    std::string word;
    int count = 0;
    while (count < n && infile >> word) {
        words.push_back(word);
        count++;
    }
    infile.close();
    if (count < n) {
        std::cout << "Внимание: Файл содержал только " << count << " слов.\n";
    }
    return words;
}

std::vector<std::string> get_words_with_methods(int n) {
    int method = get_input_method();
    if (method == 1) return read_words_keyboard(n);
    if (method == 2) return read_words_random(n);
    return read_words_from_file(n);
}

void print_vector(const std::string& name, const std::vector<int>& v) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    std::cout << name << ": ";
    if (v.empty()) {
        std::cout << "Пуст";
    }
    else {
        for (int x : v) {
            std::cout << x << " ";
        }
    }
    std::cout << "\n";
}

int get_positive_number(const std::string& prompt) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    int n;
    while (true) {
        std::cout << prompt;
        if (std::cin >> n) {
            if (n > 0) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return n;
            }
            std::cout << "Ошибка: число должно быть строго больше 0!\n";
        }
        else {
            std::cout << "Ошибка: введите корректное целое число!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}