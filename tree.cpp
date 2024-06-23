/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#include "tree.hpp"
#include "gui.hpp"
#include <stdexcept>
#include <stack>

// Default constructor initializes a tree with a maximum degree of 2
Tree::Tree() : root(nullptr), maxDegree(2) {}

// Constructor that allows setting a custom maximum degree for the tree
Tree::Tree(unsigned int degree) : root(nullptr), maxDegree(degree) {}

// Destructor
Tree::~Tree() {
}

// Method to set the root node of the tree
void Tree::add_root(std::shared_ptr<BaseNode> root_node) {
    root = root_node;
}

// Method to get the root node of the tree
BaseNode* Tree::get_root() const {
    return root.get();
}

// Method to add a child node to a parent node
void Tree::add_sub_node(BaseNode* parent, std::shared_ptr<BaseNode> child) {
    if (parent && child) {
        // Ensure the parent node does not exceed the maximum degree
        if (parent->children.size() < maxDegree) {
            parent->add_child(child);
        }
        else {
            // Throw an error if adding the child would exceed maxDegree
            throw std::runtime_error("Error: Cannot add child, maxDegree exceeded for parent node!");
        }
    }
    else {
        // Throw an error if the parent or child node is null
        throw std::runtime_error("Error: Parent or child node is null!");
    }
}

// BFSIterator implementations

// Constructor initializes the iterator with the root node
Tree::BFSIterator::BFSIterator(BaseNode* root) {
    if (root) {
        queue.push(root);  // Add root to the queue if it is not null
    }
}

// Dereference operator returns the current node at the front of the queue
BaseNode* Tree::BFSIterator::operator*() {
    return queue.front();
}

// Increment operator moves the iterator to the next node in BFS order
Tree::BFSIterator& Tree::BFSIterator::operator++() {
    BaseNode* node = queue.front();  // Get the current node
    queue.pop();  // Remove the current node from the queue
    auto& children = node->children;
    for (auto& child : children) {
        if (child != nullptr) {
            queue.push(child.get());  // Add each non-null child to the queue
        }
        else {
            // Throw an error if a null or invalid child is encountered
            throw std::runtime_error("Error: Encountered null or invalid child node!");
        }
    }
    return *this;
}

// Comparison operator checks if the iterator is not at the end
bool Tree::BFSIterator::operator!=(const BFSIterator& other) const {
    return !queue.empty();  // The iterators are not equal if the queue is not empty
}

// Returns an iterator to the beginning of the BFS traversal
Tree::BFSIterator Tree::begin_bfs() const {
    return BFSIterator(root.get());  // Return a BFSIterator starting from the root
}

// Returns an iterator to the end of the BFS traversal
Tree::BFSIterator Tree::end_bfs() const {
    return BFSIterator(nullptr);  // Return a BFSIterator representing the end
}

// Returns an iterator to the beginning of the BFS traversal (default)
Tree::BFSIterator Tree::begin() const {
    return begin_bfs();
}

// Returns an iterator to the end of the BFS traversal (default)
Tree::BFSIterator Tree::end() const {
    return end_bfs();
}


// DFSIterator implementations

// Constructor initializes the iterator with the root node
Tree::DFSIterator::DFSIterator(BaseNode* root) {
    if (root) {
        next.push(root);  // Add root to the stack if it is not null
    }
}

// Dereference operator returns the current node at the top of the stack
BaseNode* Tree::DFSIterator::operator*() {
    return next.top();
}

// Increment operator moves the iterator to the next node in DFS order
Tree::DFSIterator& Tree::DFSIterator::operator++() {
    BaseNode* currentNode = next.top();  // Get the current node
    next.pop();  // Remove the current node from the stack

    auto& children = currentNode->children;
    // Add children to the stack in reverse order to maintain DFS order
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        if (*it != nullptr) {
            next.push(it->get());
        }
        else {
            // Throw an error if a null or invalid child is encountered
            throw std::runtime_error("Error: Encountered null or invalid child node!");
        }
    }
    return *this;
}

// Comparison operator checks if the iterator is not at the end
bool Tree::DFSIterator::operator!=(const DFSIterator& other) const {
    return !next.empty();  // The iterators are not equal if the stack is not empty
}

// Returns an iterator to the beginning of the DFS traversal
Tree::DFSIterator Tree::begin_dfs() const {
    return DFSIterator(root.get());  // Return a DFSIterator starting from the root
}

// Returns an iterator to the end of the DFS traversal
Tree::DFSIterator Tree::end_dfs() const {
    return DFSIterator(nullptr);  // Return a DFSIterator representing the end
}


// PreOrderIterator implementations

// Constructor initializes the iterator with the root node and DFS flag
Tree::PreOrderIterator::PreOrderIterator(BaseNode* root, bool useDFS) : useDFS(useDFS) {
    if (root) {
        next.push(root);  // Add root to the stack if it is not null
    }
}

// Dereference operator returns the current node at the top of the stack
BaseNode* Tree::PreOrderIterator::operator*() {
    return next.top();
}

// Increment operator moves the iterator to the next node in pre-order traversal
Tree::PreOrderIterator& Tree::PreOrderIterator::operator++() {
    BaseNode* currentNode = next.top();  // Get the current node
    next.pop();  // Remove the current node from the stack

    auto& children = currentNode->children;
    // Add children to the stack in reverse order to maintain pre-order traversal
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        if (*it != nullptr) {
            next.push(it->get());
        }
        else {
            // Throw an error if a null or invalid child is encountered
            throw std::runtime_error("Error: Encountered null or invalid child node!");
        }
    }
    return *this;
}

// Comparison operator checks if the iterator is not at the end
bool Tree::PreOrderIterator::operator!=(const PreOrderIterator& other) const {
    return !next.empty();  // The iterators are not equal if the stack is not empty
}

// Returns an iterator to the beginning of the pre-order traversal
Tree::PreOrderIterator Tree::begin_pre_order() const {
    return PreOrderIterator(root.get(), maxDegree > 2);  // Use DFS if maxDegree > 2
}

// Returns an iterator to the end of the pre-order traversal
Tree::PreOrderIterator Tree::end_pre_order() const {
    return PreOrderIterator(nullptr, maxDegree > 2);  // Use DFS if maxDegree > 2
}

// PostOrderIterator implementations

// Constructor initializes the iterator with the root node and DFS flag
Tree::PostOrderIterator::PostOrderIterator(BaseNode* root, bool useDFS) : useDFS(useDFS) {
    if (useDFS) {
        if (root) {
            dfsStack.push(root);  // Add root to the DFS stack if it is not null
        }
    }

    else {
        if (root) {
            stack.push({root, false});  // Add root to the stack if it is not null
            expandTop();  // Expand the stack to process the first node
        }
    }
}

// Helper method to process the stack for standard post-order traversal
void Tree::PostOrderIterator::expandTop() {
    while (!stack.empty()) {
        auto& [node, visited] = stack.top();
        if (visited) {
            stack.pop();
            dfsStack.push(node);  // Push the node to the DFS stack
            break;
        }
        else {
            stack.pop();
            stack.push({node, true});  // Mark the node as visited
            auto& children = node->children;

            // Add children to the stack in reverse order
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                if (*it != nullptr) {
                    stack.push({it->get(), false});
                }
                else {
                    // Throw an error if a null or invalid child is encountered
                    throw std::runtime_error("Error: Encountered null or invalid child node!");
                }
            }
        }
    }
}

// Dereference operator returns the current node at the top of the DFS stack
BaseNode* Tree::PostOrderIterator::operator*() {
    return dfsStack.top();  // Return the node at the top of the DFS stack
}

// Increment operator moves the iterator to the next node in post-order traversal
Tree::PostOrderIterator& Tree::PostOrderIterator::operator++() {
    if (useDFS) {
        BaseNode* currentNode = dfsStack.top();
        dfsStack.pop();  // Remove the current node from the DFS stack
        auto& children = currentNode->children;
        // Add children to the DFS stack in reverse order
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            if (*it != nullptr) {
                dfsStack.push(it->get());
            } else {
                // Throw an error if a null or invalid child is encountered
                throw std::runtime_error("Error: Encountered null or invalid child node!");
            }
        }
    }

    else {
        dfsStack.pop();  // Remove the current node from the stack
        expandTop();  // Process the next node in the stack
    }
    return *this;
}

// Comparison operator checks if the iterator is not at the end
bool Tree::PostOrderIterator::operator!=(const PostOrderIterator& other) const {
    return !dfsStack.empty();  // The iterators are not equal if the DFS stack is not empty
}

// Returns an iterator to the beginning of the post-order traversal
Tree::PostOrderIterator Tree::begin_post_order() const {
    return PostOrderIterator(root.get(), maxDegree > 2);  // Use DFS if maxDegree > 2
}

// Returns an iterator to the end of the post-order traversal
Tree::PostOrderIterator Tree::end_post_order() const {
    return PostOrderIterator(nullptr, maxDegree > 2);  // Use DFS if maxDegree > 2
}


// InOrderIterator implementations

// Constructor initializes the iterator with the root node and DFS flag
Tree::InOrderIterator::InOrderIterator(BaseNode* root, bool useDFS) : useDFS(useDFS) {
    if (root) {
        if (useDFS) {
            next.push(root);  // Add root to the stack if it is not null
        }

        else {
            pushLeft(root);  // Push all left children of the root to the stack
        }
    }
}

// Helper method to push all left children onto the stack for in-order traversal
void Tree::InOrderIterator::pushLeft(BaseNode* node) {
    while (node) {
        next.push(node);  // Push the current node onto the stack
        visited.push(false);  // Mark the current node as not visited
        if (!node->children.empty()) {
            node = node->children[0].get();  // Move to the leftmost child
        }

        else {
            break;  // Stop if the current node has no children
        }
    }
}

// Dereference operator returns the current node at the top of the stack
BaseNode* Tree::InOrderIterator::operator*() {
    return next.top();  // Return the node at the top of the stack
}

// Increment operator moves the iterator to the next node in in-order traversal
Tree::InOrderIterator& Tree::InOrderIterator::operator++() {
    BaseNode* currentNode = next.top();
    next.pop();
    visited.pop();

    if (useDFS) {
        auto& children = currentNode->children;
        // Add children to the stack in reverse order to maintain DFS order
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            if (*it != nullptr) {
                next.push(it->get());
            }
            else {
                // Throw an error if a null or invalid child is encountered
                throw std::runtime_error("Error: Encountered null or invalid child node!");
            }
        }
    }
    else {
        if (!currentNode->children.empty()) {
            std::vector<std::shared_ptr<BaseNode>>& children = currentNode->children;
            // Push all left children of the next child onto the stack
            for (size_t i = 1; i < children.size(); ++i) {
                pushLeft(children[i].get());
            }
        }
    }
    return *this;
}

// Comparison operator checks if the iterator is not at the end
bool Tree::InOrderIterator::operator!=(const InOrderIterator& other) const {
    return !next.empty();  // The iterators are not equal if the stack is not empty
}

// Returns an iterator to the beginning of the in-order traversal
Tree::InOrderIterator Tree::begin_in_order() const {
    return InOrderIterator(root.get(), maxDegree > 2);  // Use DFS if maxDegree > 2
}

// Returns an iterator to the end of the in-order traversal
Tree::InOrderIterator Tree::end_in_order() const {
    return InOrderIterator(nullptr, maxDegree > 2);  // Use DFS if maxDegree > 2
}

/**
 * @brief Stream insertion operator to print the tree.
 *
 * This function needs to be a friend function because it requires access to the
 * private and protected members of the Tree class in order to properly traverse
 * and print the tree's structure. As a friend, it is granted access to these
 * members, enabling it to perform its task effectively.
 *
 * @param os Output stream.
 * @param tree The tree to print.
 * @return Reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const Tree& tree) {
    GUI gui;
    gui.renderTree(tree);  // Use GUI to render the tree
    return os;
}

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

    // Use shared_ptr to store the new nodes
    std::vector<std::shared_ptr<BaseNode>> newNodes;
    for (BaseNode* node : nodes) {
        if (auto strNode = dynamic_cast<Node<std::string>*>(node)) {
            newNodes.push_back(std::make_shared<Node<std::string>>(strNode->value));
        }
        else if (auto intNode = dynamic_cast<Node<int>*>(node)) {
            newNodes.push_back(std::make_shared<Node<int>>(intNode->value));
        }
        else if (auto doubleNode = dynamic_cast<Node<double>*>(node)) {
            newNodes.push_back(std::make_shared<Node<double>>(doubleNode->value));
        }
        else if (auto complexNode1 = dynamic_cast<Node<Complex<int, double>>*>(node)) {
            newNodes.push_back(std::make_shared<Node<Complex<int, double>>>(complexNode1->value));
        }
        else if (auto complexNode2 = dynamic_cast<Node<Complex<double, int>>*>(node)) {
            newNodes.push_back(std::make_shared<Node<Complex<double, int>>>(complexNode2->value));
        }
        else if (auto complexNode3 = dynamic_cast<Node<Complex<double, double>>*>(node)) {
            newNodes.push_back(std::make_shared<Node<Complex<double, double>>>(complexNode3->value));
        }
        else if (auto complexNode4 = dynamic_cast<Node<Complex<int, int>>*>(node)) {
            newNodes.push_back(std::make_shared<Node<Complex<int, int>>>(complexNode4->value));
        }

    }

    // Add root node
    heapTree.add_root(newNodes[0]);

    // Use a queue to build the tree level by level
    std::queue<BaseNode*> queue;
    queue.push(newNodes[0].get());

    size_t index = 1;
    while (index < newNodes.size()) {
        BaseNode* current = queue.front();
        queue.pop();

        // Add left child
        if (index < newNodes.size()) {
            heapTree.add_sub_node(current, newNodes[index]);
            queue.push(newNodes[index].get());
            index++;
        }

        // Add right child
        if (index < newNodes.size()) {
            heapTree.add_sub_node(current, newNodes[index]);
            queue.push(newNodes[index].get());
            index++;
        }
    }

    // Return the heap
    return heapTree;
}
