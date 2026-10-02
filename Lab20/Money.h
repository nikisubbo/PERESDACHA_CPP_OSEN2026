#ifndef MONEY_H
#define MONEY_H
#include <iostream>
class Money {
private:
    unsigned int rubles;
    short int kopeks;
    void norm();
public:
    Money();
    Money(unsigned int r, short int k);
    Money(const Money& other);
    void set(unsigned int r, short int k);
    unsigned int getRubles() const;
    short int getKopeks() const;
    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;
    bool operator<(const Money& other) const;
    bool operator>(const Money& other) const;
    bool operator<=(const Money& other) const;
    bool operator>=(const Money& other) const;
    Money operator-(unsigned int k) const;
    Money& operator-=(unsigned int k);
    Money operator-(const Money& other) const;
    Money& operator+=(unsigned int k);
    Money& operator++();
    Money operator++(int);
    Money& operator--();
    Money operator--(int);
    explicit operator unsigned int() const;
    explicit operator bool() const;
    friend std::ostream& operator<<(std::ostream& os, const Money& m);
    friend std::istream& operator>>(std::istream& is, Money& m);
    void print() const;
};
#endif