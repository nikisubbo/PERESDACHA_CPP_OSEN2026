#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

std::vector<std::string> splitUTF8(const std::string& text);

class HaffmanNode {
private:
    std::string sym;
    int freq;
    HaffmanNode* left;
    HaffmanNode* right;
public:
    HaffmanNode(const std::string& sym, int freq);
    std::string get_sym() const;
    int get_freq() const;
    HaffmanNode* get_left() const;
    HaffmanNode* get_right() const;
    void set_left(HaffmanNode* node);
    void set_right(HaffmanNode* node);
};

struct NodeComparator {
    bool operator()(HaffmanNode* a, HaffmanNode* b) const;
};

class HaffmanCoder {
private:
    std::string text;
    HaffmanNode* root;
    int totalBits;
    std::string encodedBits;
    std::map<std::string, int> freqs;
    std::map<std::string, std::string> codes;

    void deleteTree(HaffmanNode* node);
    void printTreeRecursive(HaffmanNode* node, int level) const;

public:
    HaffmanCoder(const std::string& txt);
    ~HaffmanCoder();

    void buildTree();
    void generateCodes(HaffmanNode* node, std::string code);
    void encode();

    void printTree() const;
    void printTable() const;
    void printStats() const;
    void printEncodedBits() const;

    std::string decodeFromTree(const std::string& bits) const;
    static std::string decode(const std::string& bits, HaffmanNode* treeRoot);

    std::string getEncodedBits() const { return encodedBits; }
};
void HowToFillHaffman(std::string& msg);