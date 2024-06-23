/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#pragma once

#include <iostream>
#include <sstream>

/**
 * @class Complex
 * @brief A template class to represent complex numbers with real and imaginary parts of different types.
 * @tparam RealType Type of the real part of the complex number.
 * @tparam ImagType Type of the imaginary part of the complex number.
 */
template <typename RealType, typename ImagType>
class Complex {
public:
    using real_type = RealType;
    using imag_type = ImagType;

private:
    RealType real;  // Real part of the complex number.
    ImagType imag;  // Imaginary part of the complex number.

public:
    /**
     * @brief Default constructor initializes real and imaginary parts to zero.
     */
    Complex();

    /**
     * @brief Parameterized constructor initializes real and imaginary parts to given values.
     * @param r The real part of the complex number.
     * @param i The imaginary part of the complex number.
     */
    Complex(RealType r, ImagType i);

    /**
     * @brief Converts the complex number to a string representation.
     * @return A string in the format "real+imaginaryi" or "real-imaginaryi".
     */
    std::string to_string() const;

    /**
     * @brief Calculates the ASCII sum of the string representation of the complex number.
     * @return The ASCII sum of the string representation.
     */
    unsigned int get_ascii_value() const;
};



