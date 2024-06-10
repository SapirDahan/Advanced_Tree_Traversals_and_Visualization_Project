// complex.hpp
#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <cmath>

class Complex {
private:
    double real;
    double imag;

public:
    // Constructors
    Complex() : real(0), imag(0) {}
    Complex(double r, double i) : real(r), imag(i) {}


    // Stream insertion
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real;
        if (c.imag >= 0) os << "+";
        os << c.imag << "i";
        return os;
    }
};

#endif // COMPLEX_HPP