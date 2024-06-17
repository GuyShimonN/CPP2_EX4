//
// Created by guy on 6/17/24.
//

#ifndef CPP_EX4_COMPLEX_H
#define CPP_EX4_COMPLEX_H

#include <iostream>

class Complex {
public:
    double real, imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real << ", " << c.imag << ")";
        return os;
    }
};

#endif //CPP_EX4_COMPLEX_H