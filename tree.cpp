#include "tree.hpp"
#include "gui.hpp"
#include <stdexcept>

// Constructor implementations
Tree::Tree() : root(nullptr) {}

Tree::Tree(unsigned int degree) : root(nullptr), maxDegree(degree) {}

Tree::~Tree() {
    // Destructor implementation if needed
}

// Method implementations
void Tree::add_root(BaseNode* root_node) {
    root = root_node;
    std::cout << "Added root node with value: " << root_node->get_value() << std::endl;
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
    if (root) {
        next.push(root);
        if (!useDFS) {
            expandTop();
        }
    }
}

void Tree::PostOrderIterator::expandTop() {
    while (!next.empty() && !next.top()->children.empty()) {
        BaseNode* node = next.top();
        next.pop();
        auto& children = node->children;
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            if (*it != nullptr) {
                next.push(*it);
            } else {
                throw std::runtime_error("Error: Encountered null or invalid child node!");
            }
        }
        next.push(node);
    }
}

BaseNode* Tree::PostOrderIterator::operator*() {
    return next.top();
}

Tree::PostOrderIterator& Tree::PostOrderIterator::operator++() {
    BaseNode* node = next.top();
    next.pop();
    if (useDFS) {
        auto& children = node->children;
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            if (*it != nullptr) {
                next.push(*it);
            } else {
                throw std::runtime_error("Error: Encountered null or invalid child node!");
            }
        }
    } else {
        expandTop();
    }
    return *this;
}

bool Tree::PostOrderIterator::operator!=(const PostOrderIterator& other) const {
    return !next.empty();
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
        pushLeft(root);
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

// HeapIterator implementations
Tree::HeapIterator::HeapIterator(const std::vector<BaseNode*>& nodes) : heap(nodes), index(0) {
    heapify();
}

void Tree::HeapIterator::heapify() {
    auto comparator = [](BaseNode* a, BaseNode* b) {
        return a->get_ascii_value() < b->get_ascii_value();
    };
    std::make_heap(heap.begin(), heap.end(), comparator);
    std::sort_heap(heap.begin(), heap.end(), comparator);
}

BaseNode* Tree::HeapIterator::operator*() {
    return heap[index];
}

Tree::HeapIterator& Tree::HeapIterator::operator++() {
    ++index;
    return *this;
}

bool Tree::HeapIterator::operator!=(const HeapIterator& other) const {
    return index != other.index;
}

Tree::HeapIterator Tree::begin_heap() const {
    std::vector<BaseNode*> nodes;
    for (auto it = begin_in_order(); it != end_in_order(); ++it) {
        nodes.push_back(*it);
    }
    return HeapIterator(nodes);
}

Tree::HeapIterator Tree::end_heap() const {
    return HeapIterator({});
}

// Stream insertion
std::ostream& operator<<(std::ostream& os, const Tree& tree) {
    GUI gui;
    gui.renderTree(tree);
    return os;
}
