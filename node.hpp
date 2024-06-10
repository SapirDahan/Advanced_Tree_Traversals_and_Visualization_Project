#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <type_traits>

template <typename T>
class Node {
public:
    T value;
    std::vector<void*> children;

    Node(T val) : value(val) {}

    void add_child(void* child) {
        if (child && static_cast<Node<T>*>(child)->get_value() != "") {
            children.push_back(child);
            std::cout << "Added child node with value!!!: " << static_cast<Node<T>*>(child)->get_value() << std::endl;
        } else {
            std::cerr << "Error: Tried to add a null child!" << std::endl;
        }
    }

    std::string get_value() const {
        if constexpr (std::is_same_v<T, std::string>) {
            std::cout<<"the value is 1: " << value <<std::endl;
            return value;
        } else {
            std::cout<<"the value is 2: " << std::to_string(value) <<std::endl;

            return std::to_string(value);
        }
    }

    T get_raw_value() const {
        return value;
    }
};

#endif // NODE_HPP
