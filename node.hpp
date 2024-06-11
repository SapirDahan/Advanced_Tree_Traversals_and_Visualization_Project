#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <type_traits>

class BaseNode {
public:
    virtual ~BaseNode() = default;
    virtual std::string get_value() const = 0;
    std::vector<BaseNode*> children;

    void add_child(BaseNode* child) {
        if (child) {
            children.push_back(child);
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
    }

    std::string get_value() const override {
        if constexpr (std::is_same_v<T, std::string>) {
            return value;
        } else if constexpr (std::is_arithmetic_v<T>) {
            return std::to_string(value);
        } else {
            return "Unsupported type";
        }
    }
};

#endif // NODE_HPP
