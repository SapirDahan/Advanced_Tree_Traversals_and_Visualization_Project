#include "Complex.hpp"

// Constructor implementations
template <typename RealType, typename ImagType>
Complex<RealType, ImagType>::Complex() : real(0), imag(0) {}

template <typename RealType, typename ImagType>
Complex<RealType, ImagType>::Complex(RealType r, ImagType i) : real(r), imag(i) {}

// Convert to string
template <typename RealType, typename ImagType>
std::string Complex<RealType, ImagType>::to_string() const {
    std::ostringstream out;
    out << real;
    if (imag >= 0) out << "+";
    out << imag << "i";
    return out.str();
}

// Calculate ASCII sum of the string representation
template <typename RealType, typename ImagType>
unsigned int Complex<RealType, ImagType>::get_ascii_value() const {
    std::string str_value = to_string();
    unsigned int ascii_sum = 0;
    for (char c : str_value) {
        ascii_sum += static_cast<unsigned int>(c);
    }
    return ascii_sum;
}

// Explicit template instantiation for common types
template class Complex<int, int>;
template class Complex<int, double>;
template class Complex<double, double>;
template class Complex<double, int>;

