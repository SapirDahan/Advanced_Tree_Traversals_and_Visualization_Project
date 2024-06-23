/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#include "Complex.hpp"

// Constructor implementations

/**
 * @brief Default constructor initializes real and imaginary parts to zero.
 */
template <typename RealType, typename ImagType>
Complex<RealType, ImagType>::Complex() : real(0), imag(0) {}

/**
 * @brief Parameterized constructor initializes real and imaginary parts to given values.
 * @param r The real part of the complex number.
 * @param i The imaginary part of the complex number.
 */
template <typename RealType, typename ImagType>
Complex<RealType, ImagType>::Complex(RealType r, ImagType i) : real(r), imag(i) {}

/**
 * @brief Converts the complex number to a string representation.
 * @return A string in the format "real+imaginaryi" or "real-imaginaryi".
 */
template <typename RealType, typename ImagType>
std::string Complex<RealType, ImagType>::to_string() const {
    std::ostringstream out;
    out << real;  // Add the real part to the string
    if (imag >= 0) out << "+";  // Add "+" if the imaginary part is non-negative
    out << imag << "i";  // Add the imaginary part and the "i"
    return out.str();
}

/**
 * @brief Calculates the ASCII sum of the string representation of the complex number.
 * @return The ASCII sum of the string representation.
 */
template <typename RealType, typename ImagType>
unsigned int Complex<RealType, ImagType>::get_ascii_value() const {

    // Make that complex into a string
    std::string str_value = to_string();

    unsigned int ascii_sum = 0;

    // Go over all the chars
    for (char c : str_value) {
        ascii_sum += static_cast<unsigned int>(c);  // Sum up ASCII values of all characters in the string
    }

    return ascii_sum;
}

// Explicit template instantiation definitions
template class Complex<int, int>;
template class Complex<int, double>;
template class Complex<double, double>;
template class Complex<double, int>;