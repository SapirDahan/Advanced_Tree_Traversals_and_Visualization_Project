// tree.hpp
#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <queue>
#include <stack>
#include <iterator>

template<typename T>
class Tree {
private:
    Node<T>* root;

public:
    Tree() : root(nullptr) {}

    void add_root(Node<T>* root_node) {
        root = root_node;
    }

    void add_sub_node(Node<T>* parent, Node<T>* child) {
        if (parent) {
            parent->add_child(child);
        }
    }

    // Pre-order iterator
    class PreOrderIterator : public std::iterator<std::input_iterator_tag, Node<T>> {
        std::stack<Node<T>*> nodes;

    public:
        PreOrderIterator(Node<T>* root) {
            if (root) {
                nodes.push(root);
            }
        }

        bool operator!=(const PreOrderIterator &other) const {
            return !nodes.empty() || !other.nodes.empty();
        }

        Node<T>* operator*() const {
            return nodes.top();
        }

        PreOrderIterator &operator++() {
            auto current = nodes.top();
            nodes.pop();
            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                nodes.push(*it);
            }
            return *this;
        }
    };

    PreOrderIterator begin_pre_order() {
        return PreOrderIterator(root);
    }

    PreOrderIterator end_pre_order() {
        return PreOrderIterator(nullptr);
    }

    // Post-order iterator
    class PostOrderIterator : public std::iterator<std::input_iterator_tag, Node<T>> {
        std::stack<Node<T>*> nodes;
        std::stack<bool> visited;

    public:
        PostOrderIterator(Node<T>* root) {
            if (root) {
                nodes.push(root);
                visited.push(false);
            }
        }

        bool operator!=(const PostOrderIterator &other) const {
            return !nodes.empty() || !other.nodes.empty();
        }

        Node<T>* operator*() const {
            return nodes.top();
        }

        PostOrderIterator &operator++() {
            while (!nodes.empty()) {
                auto current = nodes.top();
                bool visit = visited.top();
                nodes.pop();
                visited.pop();

                if (visit) {
                    return *this;
                } else {
                    nodes.push(current);
                    visited.push(true);
                    for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                        nodes.push(*it);
                        visited.push(false);
                    }
                }
            }
            return *this;
        }
    };

    PostOrderIterator begin_post_order() {
        return PostOrderIterator(root);
    }

    PostOrderIterator end_post_order() {
        return PostOrderIterator(nullptr);
    }

    // In-order iterator (for binary tree, here it acts similar to pre-order)
    class InOrderIterator : public std::iterator<std::input_iterator_tag, Node<T>> {
        std::stack<Node<T>*> nodes;

    public:
        InOrderIterator(Node<T>* root) {
            if (root) {
                nodes.push(root);
            }
        }

        bool operator!=(const InOrderIterator &other) const {
            return !nodes.empty() || !other.nodes.empty();
        }

        Node<T>* operator*() const {
            return nodes.top();
        }

        InOrderIterator &operator++() {
            auto current = nodes.top();
            nodes.pop();
            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                nodes.push(*it);
            }
            return *this;
        }
    };

    InOrderIterator begin_in_order() {
        return InOrderIterator(root);
    }

    InOrderIterator end_in_order() {
        return InOrderIterator(nullptr);
    }

    // BFS iterator
    class BFSIterator : public std::iterator<std::input_iterator_tag, Node<T>> {
        std::queue<Node<T>*> nodes;

    public:
        BFSIterator(Node<T>* root) {
            if (root) {
                nodes.push(root);
            }
        }

        bool operator!=(const BFSIterator &other) const {
            return !nodes.empty() || !other.nodes.empty();
        }

        Node<T>* operator*() const {
            return nodes.front();
        }

        BFSIterator &operator++() {
            auto current = nodes.front();
            nodes.pop();
            for (const auto &child : current->children) {
                nodes.push(child);
            }
            return *this;
        }
    };

    BFSIterator begin_bfs_scan() {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() {
        return BFSIterator(nullptr);
    }

    // BFS default iterator
    BFSIterator begin() {
        return begin_bfs_scan();
    }

    BFSIterator end() {
        return end_bfs_scan();
    }
};

#endif // TREE_HPP
