// node.hpp
#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

template<typename T>
class Node {
public:
    T value;
    std::vector<Node<T>*> children;

    Node(T val) : value(val) {}

    T get_value() const {
        return value;
    }

    void add_child(Node<T>* child) {
        children.push_back(child);
    }
};

#endif // NODE_HPP
