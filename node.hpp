/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "Complex.hpp"

/**
 * @class BaseNode
 * @brief A base class representing a generic node in a tree.
 */
class BaseNode {
public:
    virtual ~BaseNode();

    /**
     * @brief Get the value of the node as a string.
     * @return The value of the node as a string.
     */
    virtual std::string get_value() const = 0;

    /**
     * @brief Get the ASCII sum of the node's value.
     * @return The ASCII sum of the node's value.
     */
    virtual unsigned int get_ascii_value() const = 0;

    // Vector to store child nodes
    std::vector<BaseNode*> children;

    /**
     * @brief Add a child node to the current node.
     * @param child The child node to add.
     * @throws std::runtime_error if the child node is null.
     */
    void add_child(BaseNode* child) {
        if (child) {
            children.push_back(child);  // Add the child to the children vector
        } else {
            throw std::runtime_error("Error: Tried to add a null child!");  // Throw an error if the child is null
        }
    }
};

/**
 * @class Node
 * @brief A template class representing a node with a specific value type.
 * @tparam T The type of the value stored in the node.
 */
template <typename T>
class Node : public BaseNode {
public:
    T value; ///< The value stored in the node.

    /**
     * @brief Constructor to initialize the node with a value.
     * @param val The value to initialize the node with.
     */
    Node(T val) : value(val) {}

    /**
     * @brief Destructor for the Node class.
     */
    ~Node() override = default;

    /**
     * @brief Get the value of the node as a string.
     * @return The value of the node as a string.
     * @throws std::runtime_error if the type is unsupported.
     */
    std::string get_value() const override {
        if constexpr (std::is_same_v<T, std::string>) {
            return value;  // Return the string value
        } else if constexpr (std::is_integral_v<T>) {
            return std::to_string(value);  // Convert and return the integral value as a string
        } else if constexpr (std::is_floating_point_v<T>) {
            // Convert the floating-point value to a string with fixed precision
            std::ostringstream out;
            out << std::fixed << std::setprecision(2) << value;
            std::string str = out.str();
            // Remove trailing zeros and the decimal point if necessary
            str.erase(str.find_last_not_of('0') + 1, std::string::npos);
            str.erase(str.find_last_not_of('.') + 1, std::string::npos);
            return str;
        } else if constexpr (std::is_same_v<T, Complex<typename T::real_type, typename T::imag_type>>) {
            return value.to_string();  // Return the complex number as a string
        } else {
            throw std::runtime_error("Unsupported type");  // Throw an error if the type is unsupported
        }
    }

    /**
     * @brief Get the ASCII sum of the node's value.
     * @return The ASCII sum of the node's value.
     */
    unsigned int get_ascii_value() const override {
        std::string str_value = get_value();  // Get the value of the node as a string
        unsigned int ascii_sum = 0;
        // Calculate the sum of ASCII values of all characters in the string
        for (char c : str_value) {
            ascii_sum += static_cast<unsigned int>(c);
        }
        return ascii_sum;  // Return the ASCII sum
    }
};
