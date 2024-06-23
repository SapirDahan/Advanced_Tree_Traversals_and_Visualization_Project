/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#pragma once

#include "node.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

/**
 * @brief Class representing a generic tree structure.
 */
class Tree {
private:
    std::shared_ptr<BaseNode> root;  // Pointer to the root node of the tree.
    unsigned int maxDegree;          // Maximum number of children each node can have.

public:
    /**
     * @brief Default constructor initializes the tree with a maximum degree of 2.
     */
    Tree();

    /**
     * @brief Constructor to initialize the tree with a custom maximum degree.
     * @param degree Maximum number of children each node can have.
     */
    Tree(unsigned int degree);

    /**
     * @brief Destructor to clean up the tree.
     */
    ~Tree();

    /**
     * @brief Sets the root node of the tree.
     * @param root_node Pointer to the root node.
     */
    void add_root(std::shared_ptr<BaseNode> root_node);

    /**
     * @brief Gets the root node of the tree.
     * @return Pointer to the root node.
     */
    BaseNode* get_root() const;

    /**
     * @brief Adds a child node to a parent node.
     * @param parent Pointer to the parent node.
     * @param child Pointer to the child node.
     * @throw std::runtime_error if the parent has reached the maximum number of children or if parent/child is null.
     */
    void add_sub_node(BaseNode* parent, std::shared_ptr<BaseNode> child);

    /**
     * @brief BFS (Breadth-First Search) iterator class for traversing the tree.
     */
    class BFSIterator {
    private:
        std::queue<BaseNode*> queue;  // Queue to manage the BFS traversal.

    public:
        /**
         * @brief Constructor initializes the iterator with the root node.
         * @param root Pointer to the root node.
         */
        explicit BFSIterator(BaseNode* root);

        /**
         * @brief Dereference operator to access the current node.
         * @return Pointer to the current node.
         */
        BaseNode* operator*();

        /**
         * @brief Increment operator to move to the next node in BFS order.
         * @return Reference to the updated iterator.
         */
        BFSIterator& operator++();

        /**
         * @brief Comparison operator to check if the iterator is not at the end.
         * @param other Another BFS iterator to compare with.
         * @return True if the iterators are not at the same position, false otherwise.
         */
        bool operator!=(const BFSIterator& other) const;
    };

    /**
     * @brief Gets the beginning iterator for BFS traversal.
     * @return BFS iterator pointing to the beginning of the traversal.
     */
    BFSIterator begin_bfs() const;

    /**
     * @brief Gets the end iterator for BFS traversal.
     * @return BFS iterator pointing to the end of the traversal.
     */
    BFSIterator end_bfs() const;

    /**
     * @brief Gets the default beginning iterator (BFS).
     * @return BFS iterator pointing to the beginning of the traversal.
     */
    BFSIterator begin() const;

    /**
     * @brief Gets the default end iterator (BFS).
     * @return BFS iterator pointing to the end of the traversal.
     */
    BFSIterator end() const;

    /**
     * @brief DFS (Depth-First Search) iterator class for traversing the tree.
     */
    class DFSIterator {
    private:
        std::stack<BaseNode*> next;  // Stack to manage the DFS traversal.

    public:
        /**
         * @brief Constructor initializes the iterator with the root node.
         * @param root Pointer to the root node.
         */
        explicit DFSIterator(BaseNode* root);

        /**
         * @brief Dereference operator to access the current node.
         * @return Pointer to the current node.
         */
        BaseNode* operator*();

        /**
         * @brief Increment operator to move to the next node in DFS order.
         * @return Reference to the updated iterator.
         */
        DFSIterator& operator++();

        /**
         * @brief Comparison operator to check if the iterator is not at the end.
         * @param other Another DFS iterator to compare with.
         * @return True if the iterators are not at the same position, false otherwise.
         */
        bool operator!=(const DFSIterator& other) const;
    };

    /**
     * @brief Gets the beginning iterator for DFS traversal.
     * @return DFS iterator pointing to the beginning of the traversal.
     */
    DFSIterator begin_dfs() const;

    /**
     * @brief Gets the end iterator for DFS traversal.
     * @return DFS iterator pointing to the end of the traversal.
     */
    DFSIterator end_dfs() const;

    /**
     * @brief Pre-order iterator class for traversing the tree in pre-order.
     */
    class PreOrderIterator {
    private:
        std::stack<BaseNode*> next;  // Stack to manage the pre-order traversal.
        bool useDFS;  // Flag to determine whether to use DFS.

    public:
        /**
         * @brief Constructor initializes the iterator with the root node and DFS flag.
         * @param root Pointer to the root node.
         * @param useDFS Flag to determine whether to use DFS.
         */
        explicit PreOrderIterator(BaseNode* root, bool useDFS);

        /**
         * @brief Dereference operator to access the current node.
         * @return Pointer to the current node.
         */
        BaseNode* operator*();

        /**
         * @brief Increment operator to move to the next node in pre-order traversal.
         * @return Reference to the updated iterator.
         */
        PreOrderIterator& operator++();

        /**
         * @brief Comparison operator to check if the iterator is not at the end.
         * @param other Another PreOrder iterator to compare with.
         * @return True if the iterators are not at the same position, false otherwise.
         */
        bool operator!=(const PreOrderIterator& other) const;
    };

    /**
     * @brief Gets the beginning iterator for pre-order traversal.
     * @return PreOrder iterator pointing to the beginning of the traversal.
     */
    PreOrderIterator begin_pre_order() const;

    /**
     * @brief Gets the end iterator for pre-order traversal.
     * @return PreOrder iterator pointing to the end of the traversal.
     */
    PreOrderIterator end_pre_order() const;

    /**
     * @brief Post-order iterator class for traversing the tree in post-order.
     */
    class PostOrderIterator {
    private:
        std::stack<std::pair<BaseNode*, bool>> stack;  // Stack to manage the post-order traversal.
        std::stack<BaseNode*> dfsStack;  // Stack to manage DFS traversal.
        bool useDFS;  // Flag to determine whether to use DFS.

        /**
         * @brief Helper method to expand the stack for post-order traversal.
         */
        void expandTop();

    public:
        /**
         * @brief Constructor initializes the iterator with the root node and DFS flag.
         * @param root Pointer to the root node.
         * @param useDFS Flag to determine whether to use DFS.
         */
        explicit PostOrderIterator(BaseNode* root, bool useDFS);

        /**
         * @brief Dereference operator to access the current node.
         * @return Pointer to the current node.
         */
        BaseNode* operator*();

        /**
         * @brief Increment operator to move to the next node in post-order traversal.
         * @return Reference to the updated iterator.
         */
        PostOrderIterator& operator++();

        /**
         * @brief Comparison operator to check if the iterator is not at the end.
         * @param other Another PostOrder iterator to compare with.
         * @return True if the iterators are not at the same position, false otherwise.
         */
        bool operator!=(const PostOrderIterator& other) const;
    };

    /**
     * @brief Gets the beginning iterator for post-order traversal.
     * @return PostOrder iterator pointing to the beginning of the traversal.
     */
    PostOrderIterator begin_post_order() const;

    /**
     * @brief Gets the end iterator for post-order traversal.
     * @return PostOrder iterator pointing to the end of the traversal.
     */
    PostOrderIterator end_post_order() const;

    /**
     * @brief In-order iterator class for traversing the tree in in-order.
     */
    class InOrderIterator {
    private:
        std::stack<BaseNode*> next;  // Stack to manage the in-order traversal.
        std::stack<bool> visited;  // Stack to manage the visited state of nodes.
        bool useDFS;  // Flag to determine whether to use DFS.

        /**
         * @brief Helper method to push left children onto the stack for in-order traversal.
         * @param node Pointer to the node to push.
         */
        void pushLeft(BaseNode* node);

    public:
        /**
         * @brief Constructor initializes the iterator with the root node and DFS flag.
         * @param root Pointer to the root node.
         * @param useDFS Flag to determine whether to use DFS.
         */
        explicit InOrderIterator(BaseNode* root, bool useDFS);

        /**
         * @brief Dereference operator to access the current node.
         * @return Pointer to the current node.
         */
        BaseNode* operator*();

        /**
         * @brief Increment operator to move to the next node in in-order traversal.
         * @return Reference to the updated iterator.
         */
        InOrderIterator& operator++();

        /**
         * @brief Comparison operator to check if the iterator is not at the end.
         * @param other Another InOrder iterator to compare with.
         * @return True if the iterators are not at the same position, false otherwise.
         */
        bool operator!=(const InOrderIterator& other) const;
    };

    /**
     * @brief Gets the beginning iterator for in-order traversal.
     * @return InOrder iterator pointing to the beginning of the traversal.
     */
    InOrderIterator begin_in_order() const;

    /**
     * @brief Gets the end iterator for in-order traversal.
     * @return InOrder iterator pointing to the end of the traversal.
     */
    InOrderIterator end_in_order() const;


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
    friend std::ostream& operator<<(std::ostream& os, const Tree& tree);


    /**
     * @brief Method to convert the tree into a min-heap.
     * @return A new tree that is a min-heap.
     */
    Tree myHeap() const;
};
