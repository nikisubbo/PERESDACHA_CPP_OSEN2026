#pragma once
#include <windows.h>
#include <string>

class CaesarCipher {
private:
    std::string text;
    int key;
    std::string encrypted;
    std::string decrypted;

    char shiftChar(char c, int k, bool encrypt) const;

public:
    explicit CaesarCipher(const std::string& txt, int k);
    void encrypt();
    void decrypt();
    void printResult() const;
    std::string getEncrypted() const { return encrypted; }
    std::string getDecrypted() const { return decrypted; }
};

void HowToFillCaesar(std::string& msg);