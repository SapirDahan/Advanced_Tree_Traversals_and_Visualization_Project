#include "tree.hpp"
#include "gui.hpp"
#include <stdexcept>
#include <stack>

// Constructor implementations
Tree::Tree() : root(nullptr), maxDegree(2) {}

Tree::Tree(unsigned int degree) : root(nullptr), maxDegree(degree) {}

Tree::~Tree() {
    // Destructor implementation if needed
}

// Method implementations
void Tree::add_root(BaseNode* root_node) {
    root = root_node;
}

BaseNode* Tree::get_root() const {
    return root;
}

void Tree::add_sub_node(BaseNode* parent, BaseNode* child) {
    if (parent && child) {
        if (parent->children.size() < maxDegree) {
            parent->add_child(child);
        } else {
            throw std::runtime_error("Error: Cannot add child, maxDegree exceeded for parent node!");
        }
    } else {
        throw std::runtime_error("Error: Parent or child node is null!");
    }
}

// BFSIterator implementations
Tree::BFSIterator::BFSIterator(BaseNode* root) {
    if (root) {
        queue.push(root);
    }
}

BaseNode* Tree::BFSIterator::operator*() {
    return queue.front();
}

Tree::BFSIterator& Tree::BFSIterator::operator++() {
    BaseNode* node = queue.front();
    queue.pop();
    auto& children = node->children;
    for (auto child : children) {
        if (child != nullptr) {
            queue.push(child);
        } else {
            throw std::runtime_error("Error: Encountered null or invalid child node!");
        }
    }
    return *this;
}

bool Tree::BFSIterator::operator!=(const BFSIterator& other) const {
    return !queue.empty();
}

Tree::BFSIterator Tree::begin_bfs() const {
    return BFSIterator(root);
}

Tree::BFSIterator Tree::end_bfs() const {
    return BFSIterator(nullptr);
}

Tree::BFSIterator Tree::begin() const {
    return begin_bfs();
}

Tree::BFSIterator Tree::end() const {
    return end_bfs();
}

// DFSIterator implementations
Tree::DFSIterator::DFSIterator(BaseNode* root) {
    if (root) {
        next.push(root);
    }
}

BaseNode* Tree::DFSIterator::operator*() {
    return next.top();
}

Tree::DFSIterator& Tree::DFSIterator::operator++() {
    BaseNode* currentNode = next.top();
    next.pop();

    auto& children = currentNode->children;
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        if (*it != nullptr) {
            next.push(*it);
        } else {
            throw std::runtime_error("Error: Encountered null or invalid child node!");
        }
    }
    return *this;
}

bool Tree::DFSIterator::operator!=(const DFSIterator& other) const {
    return !next.empty();
}

Tree::DFSIterator Tree::begin_dfs() const {
    return DFSIterator(root);
}

Tree::DFSIterator Tree::end_dfs() const {
    return DFSIterator(nullptr);
}

// PreOrderIterator implementations
Tree::PreOrderIterator::PreOrderIterator(BaseNode* root, bool useDFS) : useDFS(useDFS) {
    if (root) {
        next.push(root);
    }
}

BaseNode* Tree::PreOrderIterator::operator*() {
    return next.top();
}

Tree::PreOrderIterator& Tree::PreOrderIterator::operator++() {
    BaseNode* currentNode = next.top();
    next.pop();

    auto& children = currentNode->children;
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        if (*it != nullptr) {
            next.push(*it);
        } else {
            throw std::runtime_error("Error: Encountered null or invalid child node!");
        }
    }
    return *this;
}

bool Tree::PreOrderIterator::operator!=(const PreOrderIterator& other) const {
    return !next.empty();
}

Tree::PreOrderIterator Tree::begin_pre_order() const {
    return PreOrderIterator(root, maxDegree > 2);
}

Tree::PreOrderIterator Tree::end_pre_order() const {
    return PreOrderIterator(nullptr, maxDegree > 2);
}

// PostOrderIterator implementations
Tree::PostOrderIterator::PostOrderIterator(BaseNode* root, bool useDFS) : useDFS(useDFS) {
    if (useDFS) {
        if (root) {
            dfsStack.push(root);
        }
    } else {
        if (root) {
            stack.push({root, false});
            expandTop();
        }
    }
}

void Tree::PostOrderIterator::expandTop() {
    while (!stack.empty()) {
        auto& [node, visited] = stack.top();
        if (visited) {
            stack.pop();
            dfsStack.push(node);
            break;
        } else {
            stack.pop();
            stack.push({node, true});
            auto& children = node->children;
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                if (*it != nullptr) {
                    stack.push({*it, false});
                } else {
                    throw std::runtime_error("Error: Encountered null or invalid child node!");
                }
            }
        }
    }
}

BaseNode* Tree::PostOrderIterator::operator*() {
    if (useDFS) {
        return dfsStack.top();
    } else {
        return dfsStack.top();
    }
}

Tree::PostOrderIterator& Tree::PostOrderIterator::operator++() {
    if (useDFS) {
        BaseNode* currentNode = dfsStack.top();
        dfsStack.pop();
        auto& children = currentNode->children;
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            if (*it != nullptr) {
                dfsStack.push(*it);
            } else {
                throw std::runtime_error("Error: Encountered null or invalid child node!");
            }
        }
    } else {
        dfsStack.pop();
        expandTop();
    }
    return *this;
}

bool Tree::PostOrderIterator::operator!=(const PostOrderIterator& other) const {
    if (useDFS) {
        return !dfsStack.empty();
    } else {
        return !dfsStack.empty();
    }
}

Tree::PostOrderIterator Tree::begin_post_order() const {
    return PostOrderIterator(root, maxDegree > 2);
}

Tree::PostOrderIterator Tree::end_post_order() const {
    return PostOrderIterator(nullptr, maxDegree > 2);
}

// InOrderIterator implementations
Tree::InOrderIterator::InOrderIterator(BaseNode* root, bool useDFS) : useDFS(useDFS) {
    if (root) {
        if (useDFS) {
            next.push(root);
        } else {
            pushLeft(root);
        }
    }
}

void Tree::InOrderIterator::pushLeft(BaseNode* node) {
    while (node) {
        next.push(node);
        visited.push(false);
        if (!node->children.empty()) {
            node = node->children[0];
        } else {
            break;
        }
    }
}

BaseNode* Tree::InOrderIterator::operator*() {
    return next.top();
}

Tree::InOrderIterator& Tree::InOrderIterator::operator++() {
    BaseNode* currentNode = next.top();
    next.pop();
    visited.pop();

    if (useDFS) {
        auto& children = currentNode->children;
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            if (*it != nullptr) {
                next.push(*it);
            } else {
                throw std::runtime_error("Error: Encountered null or invalid child node!");
            }
        }
    } else {
        if (!currentNode->children.empty()) {
            std::vector<BaseNode*>& children = currentNode->children;
            for (size_t i = 1; i < children.size(); ++i) {
                pushLeft(children[i]);
            }
        }
    }
    return *this;
}

bool Tree::InOrderIterator::operator!=(const InOrderIterator& other) const {
    return !next.empty();
}

Tree::InOrderIterator Tree::begin_in_order() const {
    return InOrderIterator(root, maxDegree > 2);
}

Tree::InOrderIterator Tree::end_in_order() const {
    return InOrderIterator(nullptr, maxDegree > 2);
}

// Stream insertion
std::ostream& operator<<(std::ostream& os, const Tree& tree) {
    GUI gui;
    gui.renderTree(tree);
    return os;
}

// Function to create a min-heap tree from the given tree
// Function to create a min-heap tree from the given tree
Tree Tree::myHeap() const {
    if (maxDegree != 2) {
        throw std::runtime_error("Error: Tree is not a binary tree (maxDegree != 2)");
    }

    // Collect all nodes in BFS order
    std::vector<BaseNode*> nodes;
    for (auto it = begin_bfs(); it != end_bfs(); ++it) {
        nodes.push_back(*it);
    }

    // Sort nodes based on ASCII value to form a min-heap
    std::sort(nodes.begin(), nodes.end(), [](BaseNode* a, BaseNode* b) {
        return a->get_ascii_value() < b->get_ascii_value();
    });

    // Create a new tree with maxDegree 2
    Tree heapTree(2);
    if (nodes.empty()) return heapTree;

    // Use a vector to store the new nodes
    std::vector<BaseNode*> newNodes;
    for (BaseNode* node : nodes) {
        if (dynamic_cast<Node<std::string>*>(node)) {
            newNodes.push_back(new Node<std::string>(dynamic_cast<Node<std::string>*>(node)->value));
        } else if (dynamic_cast<Node<int>*>(node)) {
            newNodes.push_back(new Node<int>(dynamic_cast<Node<int>*>(node)->value));
        } else if (dynamic_cast<Node<double>*>(node)) {
            newNodes.push_back(new Node<double>(dynamic_cast<Node<double>*>(node)->value));
        } else if (dynamic_cast<Node<Complex<int, double>>*>(node)) {
            newNodes.push_back(new Node<Complex<int, double>>(dynamic_cast<Node<Complex<int, double>>*>(node)->value));
        } else if (dynamic_cast<Node<Complex<double, int>>*>(node)) {
            newNodes.push_back(new Node<Complex<double, int>>(dynamic_cast<Node<Complex<double, int>>*>(node)->value));
        }
    }

    // Add root node
    heapTree.add_root(newNodes[0]);

    // Use a queue to build the tree level by level
    std::queue<BaseNode*> queue;
    queue.push(newNodes[0]);

    size_t index = 1;
    while (index < newNodes.size()) {
        BaseNode* current = queue.front();
        queue.pop();

        // Add left child
        if (index < newNodes.size()) {
            heapTree.add_sub_node(current, newNodes[index]);
            queue.push(newNodes[index]);
            index++;
        }

        // Add right child
        if (index < newNodes.size()) {
            heapTree.add_sub_node(current, newNodes[index]);
            queue.push(newNodes[index]);
            index++;
        }
    }

    return heapTree;
}
