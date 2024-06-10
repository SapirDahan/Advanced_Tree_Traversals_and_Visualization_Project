#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <stack>
#include <queue>
#include <iostream>

class Tree {
private:
    void* root;

public:
    Tree() : root(nullptr) {}

    template <typename T>
    void add_root(Node<T>* root_node) {
        root = static_cast<void*>(root_node);
        std::cout << "Added root node with value: " << root_node->get_value() << std::endl;
    }

    template <typename T>
    Node<T>* get_root() const {
        return static_cast<Node<T>*>(root);
    }

    template <typename T, typename U>
    void add_sub_node(Node<T>* parent, Node<U>* child) {
        if (parent && child) {
            parent->add_child(static_cast<void*>(child));
            std::cout << "Added child node with value: " << child->get_value() << " to parent node with value: " << parent->get_value() << std::endl;
        } else {
            std::cerr << "Error: Parent or child node is null!" << std::endl;
        }
    }

    // Pre-order iterator
    template <typename T>
    class PreOrderIterator {
    private:
        std::stack<Node<T>*> next;

    public:
        explicit PreOrderIterator(Node<T>* root) {
            if (root) {
                next.push(root);
                std::cout << "Initialized PreOrderIterator with root node: " << root->get_value() << std::endl;
            }
        }

        Node<T>* operator*() {
            return next.top();
        }

        PreOrderIterator& operator++() {
            Node<T>* currentNode = next.top();
            next.pop();
            std::cout << "Popped node with value: " << currentNode->get_value() << std::endl;

            auto& children = currentNode->children;
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                Node<T>* childNode = static_cast<Node<T>*>(*it);
                if (childNode) {
                    std::cout << "Pushing child node with value: " << childNode->get_value() << std::endl;
                    next.push(childNode);
                } else {
                    std::cerr << "Error: Encountered null child node!" << std::endl;
                }
            }
            return *this;
        }

        bool operator!=(const PreOrderIterator& other) const {
            return !next.empty();
        }
    };

    template <typename T>
    PreOrderIterator<T> begin_pre_order() {
        return PreOrderIterator<T>(get_root<T>());
    }

    template <typename T>
    PreOrderIterator<T> end_pre_order() {
        return PreOrderIterator<T>(nullptr);
    }

    // Post-order iterator
    template <typename T>
    class PostOrderIterator {
    private:
        struct NodeInfo {
            Node<T>* node;
            bool isExpanded;
            bool operator==(const NodeInfo& rhs) const {
                return node == rhs.node && isExpanded == rhs.isExpanded;
            }
        };

        std::stack<NodeInfo> next;

        void expandTop() {
            while (!next.top().isExpanded) {
                next.top().isExpanded = true;
                auto& children = next.top().node->children;
                for (auto it = children.rbegin(); it != children.rend(); ++it) {
                    Node<T>* childNode = static_cast<Node<T>*>(*it);
                    if (childNode) {
                        next.push({childNode, false});
                    } else {
                        std::cerr << "Error: Encountered null child node!" << std::endl;
                    }
                }
            }
        }

    public:
        explicit PostOrderIterator(Node<T>* root) {
            if (root) {
                next.push({root, false});
                expandTop();
                std::cout << "Initialized PostOrderIterator with root node: " << root->get_value() << std::endl;
            }
        }

        Node<T>* operator*() {
            return next.top().node;
        }

        PostOrderIterator& operator++() {
            next.pop();
            if (!next.empty()) expandTop();
            return *this;
        }

        bool operator!=(const PostOrderIterator& other) const {
            return !next.empty();
        }
    };

    template <typename T>
    PostOrderIterator<T> begin_post_order() {
        return PostOrderIterator<T>(get_root<T>());
    }

    template <typename T>
    PostOrderIterator<T> end_post_order() {
        return PostOrderIterator<T>(nullptr);
    }

    // BFS iterator
    template <typename T>
    class BFSIterator {
    private:
        std::queue<Node<T>*> queue;

    public:
        explicit BFSIterator(Node<T>* root) {
            if (root) {
                queue.push(root);
                std::cout << "Initialized BFSIterator with root node: " << root->get_value() << std::endl;
            }
        }

        Node<T>* operator*() {
            return queue.front();
        }

        BFSIterator& operator++() {
            Node<T>* node = queue.front();
            queue.pop();
            auto& children = node->children;
            for (auto child : children) {
                Node<T>* childNode = static_cast<Node<T>*>(child);
                if (childNode) {
                    std::cout << "Queueing child node with value: " << childNode->get_value() << std::endl;
                    queue.push(childNode);
                } else {
                    std::cerr << "Error: Encountered null child node!" << std::endl;
                }
            }
            return *this;
        }

        bool operator!=(const BFSIterator& other) const {
            return !queue.empty();
        }
    };

    template <typename T>
    BFSIterator<T> begin_bfs() {
        return BFSIterator<T>(get_root<T>());
    }

    template <typename T>
    BFSIterator<T> end_bfs() {
        return BFSIterator<T>(nullptr);
    }

    // Tree iterator (BFS by default)
    template <typename T>
    BFSIterator<T> begin() {
        return begin_bfs<T>();
    }

    template <typename T>
    BFSIterator<T> end() {
        return end_bfs<T>();
    }
};

#endif // TREE_HPP
