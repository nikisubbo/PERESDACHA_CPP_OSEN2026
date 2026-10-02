#include "Money.h"
#include <iomanip>
#include <sstream>

Money::Money() : rubles(0), kopeks(0) {}

Money::Money(unsigned int r, short int k) {
    set(r, k);
}

Money::Money(const Money& other) : rubles(other.rubles), kopeks(other.kopeks) {}

void Money::norm() {
    if (kopeks >= 100) {
        rubles += kopeks / 100;
        kopeks %= 100;
    }
    if (kopeks < 0) {
        kopeks = 0;
    }
}

void Money::set(unsigned int r, short int k) {
    rubles = r;
    kopeks = (k < 0) ? 0 : k;
    norm();
}

unsigned int Money::getRubles() const { return rubles; }
short int Money::getKopeks() const { return kopeks; }

bool Money::operator==(const Money& other) const {
    return rubles == other.rubles && kopeks == other.kopeks;
}

bool Money::operator!=(const Money& other) const {
    return !(*this == other);
}

bool Money::operator<(const Money& other) const {
    return ((unsigned long long)rubles * 100 + kopeks) < ((unsigned long long)other.rubles * 100 + other.kopeks);
}

bool Money::operator>(const Money& other) const { return other < *this; }
bool Money::operator<=(const Money& other) const { return !(other < *this); }
bool Money::operator>=(const Money& other) const { return !(*this < other); }

Money Money::operator-(unsigned int k) const {
    unsigned long long total = (unsigned long long)rubles * 100 + kopeks;
    if (total >= k) total -= k;
    else total = 0;
    return Money(static_cast<unsigned int>(total / 100), static_cast<short int>(total % 100));
}

Money& Money::operator-=(unsigned int k) {
    *this = *this - k;
    return *this;
}

Money Money::operator-(const Money& other) const {
    unsigned long long total1 = (unsigned long long)rubles * 100 + kopeks;
    unsigned long long total2 = (unsigned long long)other.rubles * 100 + other.kopeks;

    if (total1 >= total2) {
        unsigned long long diff = total1 - total2;
        return Money(static_cast<unsigned int>(diff / 100), static_cast<short int>(diff % 100));
    }
    return Money(0, 0);
}

Money& Money::operator+=(unsigned int k) {
    unsigned long long total = (unsigned long long)rubles * 100 + kopeks + k;
    rubles = static_cast<unsigned int>(total / 100);
    kopeks = static_cast<short int>(total % 100);
    return *this;
}

Money& Money::operator++() {
    *this += 1;
    return *this;
}

Money Money::operator++(int) {
    Money old = *this;
    ++(*this);
    return old;
}

Money& Money::operator--() {
    if (rubles == 0 && kopeks == 0) return *this;
    *this -= 1;
    return *this;
}

Money Money::operator--(int) {
    Money old = *this;
    --(*this);
    return old;
}

Money::operator unsigned int() const {
    return rubles;
}

Money::operator bool() const {
    return !(rubles == 0 && kopeks == 0);
}

std::ostream& operator<<(std::ostream& os, const Money& m) {
    os << m.rubles << " руб. "
        << std::setw(2) << std::setfill('0') << (int)m.kopeks << " коп.";
    return os;
}

std::istream& operator>>(std::istream& is, Money& m) {
    std::string s;
    while (true) {
        std::cout << "\n\tВведите сумму в формате руб.коп: ";
        is >> s;
        unsigned int rr;
        short int kk;
        char sep;
        std::stringstream ss(s);
        if (ss >> rr >> sep >> kk && sep == '.' && kk >= 0 && kk < 100) {
            m.set(rr, kk);
            break;
        }
        else {
            std::cout << "\n\tОшибка: используйте формат руб.коп (коп 0-99)\n";
        }
    }
    return is;
}

void Money::print() const {
    std::cout << *this;
}