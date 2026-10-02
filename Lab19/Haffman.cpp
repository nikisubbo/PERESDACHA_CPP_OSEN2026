#include "Haffman.h"
#include <windows.h>
#include "sup.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>


std::vector<std::string> splitUTF8(const std::string& text) {
    std::vector<std::string> result;
    int i = 0;
    while (i < (int)text.length()) {
        int len = 1;
        unsigned char c = text[i];
        if ((c & 0xE0) == 0xC0) len = 2;       
        else if ((c & 0xF0) == 0xE0) len = 3;  
        else if ((c & 0xF8) == 0xF0) len = 4; 
        result.push_back(text.substr(i, len));
        i += len;
    }
    return result;
}

HaffmanNode::HaffmanNode(const std::string& sym, int freq)
    : sym(sym), freq(freq), left(nullptr), right(nullptr) {
}

std::string HaffmanNode::get_sym() const { return sym; }
int HaffmanNode::get_freq() const { return freq; }
HaffmanNode* HaffmanNode::get_left() const { return left; }
HaffmanNode* HaffmanNode::get_right() const { return right; }

void HaffmanNode::set_left(HaffmanNode* node) { left = node; }
void HaffmanNode::set_right(HaffmanNode* node) { right = node; }

bool NodeComparator::operator()(HaffmanNode* a, HaffmanNode* b) const {
    return a->get_freq() > b->get_freq();
}

HaffmanCoder::HaffmanCoder(const std::string& txt) : text(txt), root(nullptr), totalBits(0) {
    std::vector<std::string> symbols = splitUTF8(txt);
    for (const auto& s : symbols) {
        freqs[s]++;
    }
}

HaffmanCoder::~HaffmanCoder() {
    deleteTree(root);
}

void HaffmanCoder::deleteTree(HaffmanNode* node) {
    if (!node) return;
    deleteTree(node->get_left());
    deleteTree(node->get_right());
    delete node;
}

void HaffmanCoder::buildTree() {
    std::priority_queue<HaffmanNode*, std::vector<HaffmanNode*>, NodeComparator> pq;
    for (auto& pair : freqs) {
        pq.push(new HaffmanNode(pair.first, pair.second));
    }
    while (pq.size() > 1) {
        HaffmanNode* l = pq.top(); pq.pop();
        HaffmanNode* r = pq.top(); pq.pop();
        HaffmanNode* p = new HaffmanNode("", l->get_freq() + r->get_freq());
        p->set_left(l);
        p->set_right(r);
        pq.push(p);
    }
    if (!pq.empty()) root = pq.top();
}

void HaffmanCoder::generateCodes(HaffmanNode* node, std::string code) {
    if (!node) return;
    if (!node->get_left() && !node->get_right()) {
        codes[node->get_sym()] = code.empty() ? "0" : code;
        return;
    }
    generateCodes(node->get_left(), code + "0");
    generateCodes(node->get_right(), code + "1");
}

void HaffmanCoder::encode() {
    buildTree();
    generateCodes(root, "");
    totalBits = 0;
    encodedBits.clear();

    std::vector<std::string> symbols = splitUTF8(text);
    for (const auto& s : symbols) {
        std::string code = codes[s];
        totalBits += (int)code.length();
        encodedBits += code;
    }
}

void HaffmanCoder::printTreeRecursive(HaffmanNode* node, int level) const {
    if (!node) return;
    printTreeRecursive(node->get_right(), level + 1);
    for (int i = 0; i < level; ++i) std::cout << "    ";
    std::cout << node->get_freq() << ":< ";
    if (!node->get_sym().empty()) std::cout << "'" << node->get_sym() << "'";
    std::cout << "\n";
    printTreeRecursive(node->get_left(), level + 1);
}

void HaffmanCoder::printTree() const {
    std::cout << "\n\tДерево: \n";
    if (root) printTreeRecursive(root, 0);
}

void HaffmanCoder::printTable() const {
    std::cout << "\n\tСимвол | Частота | Код Хаффмана:\n";
    std::vector<std::pair<std::string, int>> sortedFreq(freqs.begin(), freqs.end());
    std::sort(sortedFreq.begin(), sortedFreq.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    for (const auto& pair : sortedFreq) {
        std::string sym = pair.first;
        int freq = pair.second;
        std::string code = codes.at(sym);
        std::cout << "\t  '" << sym << "'   |   " << freq << "   |   " << code << "\n";
    }
}

void HaffmanCoder::printStats() const {
    int unique = (int)freqs.size();
    std::vector<std::string> symbols = splitUTF8(text);
    int len = (int)symbols.size();
    int bitsPerSym = (unique > 1) ? (int)std::ceil(std::log2(unique)) : 1;
    int uniformBits = len * bitsPerSym;
    int huffmanBits = totalBits;
    int diff = uniformBits - huffmanBits;

    std::cout << "\nСравнение размеров:)\n";
    std::cout << "Уникальных символов: " << unique << "\n";
    std::cout << "Бит на символ (равномерно): " << bitsPerSym << "\n";
    std::cout << "Равномерный код: " << uniformBits << " бит\n";
    std::cout << "Код Хаффмана: " << huffmanBits << " бит\n";
    std::cout << "Разница: " << diff << " бит\n";
}

std::string HaffmanCoder::decodeFromTree(const std::string& bits) const {
    std::string result;
    HaffmanNode* curr = root;
    for (char bit : bits) {
        if (bit == '0') curr = curr->get_left();
        else curr = curr->get_right();
        if (!curr->get_left() && !curr->get_right()) {
            result += curr->get_sym();
            curr = root;
        }
    }
    return result;
}

std::string HaffmanCoder::decode(const std::string& bits, HaffmanNode* treeRoot) {
    std::string result;
    HaffmanNode* current = treeRoot;
    for (char bit : bits) {
        if (bit == '0') current = current->get_left();
        else current = current->get_right();
        if (!current->get_left() && !current->get_right()) {
            result += current->get_sym();
            current = treeRoot;
        }
    }
    return result;
}

void HaffmanCoder::printEncodedBits() const {
    std::cout << "\nЗакодированная битовая строка:\n";
    for (size_t i = 0; i < encodedBits.length(); ++i) {
        std::cout << encodedBits[i];
        if ((i + 1) % 8 == 0) std::cout << " ";
    }
    std::cout << "\n";
}

void HowToFillHaffman(std::string& msg) {
    int choice = 0;
    do {
        std::cout << "\nКак вы хотите получить текст?\n";
        std::cout << "1) С клавиатуры\n";
        std::cout << "2) Случайно\n";
        std::cout << "3) Из файла\n";
        std::cout << "4) Назад\n";
        std::cout << "Выбор: ";

        choice = Input_Int();
        if (choice < 1 || choice > 4) {
            std::cout << "Ошибка. Введите корректное число (1-4).\n";
            continue;
        }
        switch (choice) {
        case 1: {
            std::cout << "Введите текст: ";
            std::getline(std::cin, msg);
            while (msg.empty()) {
                std::cout << "Ошибка. Текст не может быть пустым. Попробуйте снова: ";
                std::getline(std::cin, msg);
            }
            break;
        }
        case 2: {
            std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            std::cout << "Введите длину сообщения: ";
            int len = Input_Int();
            msg.clear();
            for (int i = 0; i < len; ++i) {
                msg += chars[std::rand() % chars.length()];
            }
            std::cout << "Случайное сообщение: " << msg << "\n";
            break;
        }
        case 3: {
            std::string filename;
            std::cout << "Введите имя файла (например, data.txt): ";
            std::cin >> filename;
            std::ifstream infile(filename);
            if (!infile.is_open()) {
                std::cerr << "Ошибка. Не удалось открыть файл.\n";
                break;
            }
            std::getline(infile, msg);
            infile.close();
            if (msg.empty()) {
                std::cerr << "Ошибка. Файл пуст.\n";
                break;
            }
            std::cout << "Сообщение из файла: " << msg << "\n";
            break;
        }
        }
    } while (choice != 4);
}