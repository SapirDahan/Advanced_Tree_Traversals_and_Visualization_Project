#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include <sstream>
#include <iomanip>

class BaseNode {
public:
//    virtual ~BaseNode() {
//
//    }

    virtual std::string get_value() const = 0;
    std::vector<BaseNode*> children;

    void add_child(BaseNode* child) {
        if (child) {
            children.push_back(child);
            std::cout << "Added child node with value: " << child->get_value() << std::endl;
        } else {
            std::cerr << "Error: Tried to add a null child!" << std::endl;
        }
    }
};

template <typename T>
class Node : public BaseNode {
public:
    T value;

    Node(T val) : value(val) {
        std::cout << "Node created with value: " << get_value() << std::endl;
    }

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
        } else {
            return "Unsupported type";
        }
    }
};

#endif // NODE_HPP
