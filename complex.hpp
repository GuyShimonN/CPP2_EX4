#ifndef CPP_EX4_COMPLEX_H
#define CPP_EX4_COMPLEX_H

#include <iostream>
#include <string>

namespace ariel {
    class Complex {
    public:
        int real;
        int imag;

        Complex(int r, int i) : real(r), imag(i) {}

        bool operator>(const Complex &other) const {
            return real > other.real || (real == other.real && imag > other.imag);
        }

        std::string toString() const {
            return std::to_string(real) + "+" + std::to_string(imag) + "i";
        }

        friend std::ostream &operator<<(std::ostream &os, const Complex &c) {
            os << c.real << "+" << c.imag << "i";
            return os;
        }
    };
}

#endif //CPP_EX4_COMPLEX_H
