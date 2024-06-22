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

class BaseNode {
public:
    virtual ~BaseNode() = default;

    virtual std::string get_value() const = 0;
    virtual unsigned int get_ascii_value() const = 0;
    std::vector<BaseNode*> children;

    void add_child(BaseNode* child) {
        if (child) {
            children.push_back(child);
        } else {
            throw std::runtime_error("Error: Tried to add a null child!");
        }
    }
};

template <typename T>
class Node : public BaseNode {
public:
    T value;

    Node(T val) : value(val) {}

    std::string get_value() const override {
        if constexpr (std::is_same_v<T, std::string>) {
            return value;
        } else if constexpr (std::is_integral_v<T>) {
            return std::to_string(value);
        } else if constexpr (std::is_floating_point_v<T>) {
            std::ostringstream out;
            out << std::fixed << std::setprecision(2) << value;
            std::string str = out.str();
            str.erase(str.find_last_not_of('0') + 1, std::string::npos);
            str.erase(str.find_last_not_of('.') + 1, std::string::npos);
            return str;
        } else if constexpr (std::is_same_v<T, Complex<typename T::real_type, typename T::imag_type>>) {
            return value.to_string();
        } else {
            throw std::runtime_error("Unsupported type");
        }
    }

    unsigned int get_ascii_value() const override {
        std::string str_value = get_value();
        unsigned int ascii_sum = 0;
        for (char c : str_value) {
            ascii_sum += static_cast<unsigned int>(c);
        }
        return ascii_sum;
    }
};

