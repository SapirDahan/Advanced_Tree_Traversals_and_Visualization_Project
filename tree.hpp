#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

class Tree {
private:
    BaseNode* root;
    unsigned int maxDegree;

public:
    Tree();
    Tree(unsigned int degree);
    ~Tree();

    void add_root(BaseNode* root_node);
    BaseNode* get_root() const;
    void add_sub_node(BaseNode* parent, BaseNode* child);

    // BFS iterator
    class BFSIterator {
    private:
        std::queue<BaseNode*> queue;
    public:
        explicit BFSIterator(BaseNode* root);
        BaseNode* operator*();
        BFSIterator& operator++();
        bool operator!=(const BFSIterator& other) const;
    };

    BFSIterator begin_bfs() const;
    BFSIterator end_bfs() const;
    BFSIterator begin() const;
    BFSIterator end() const;

    // DFS iterator
    class DFSIterator {
    private:
        std::stack<BaseNode*> next;
    public:
        explicit DFSIterator(BaseNode* root);
        BaseNode* operator*();
        DFSIterator& operator++();
        bool operator!=(const DFSIterator& other) const;
    };

    DFSIterator begin_dfs() const;
    DFSIterator end_dfs() const;

    // Pre-order iterator
    class PreOrderIterator {
    private:
        std::stack<BaseNode*> next;
        bool useDFS;
    public:
        explicit PreOrderIterator(BaseNode* root, bool useDFS);
        BaseNode* operator*();
        PreOrderIterator& operator++();
        bool operator!=(const PreOrderIterator& other) const;
    };

    PreOrderIterator begin_pre_order() const;
    PreOrderIterator end_pre_order() const;

    // Post-order iterator
    class PostOrderIterator {
    private:
        std::stack<std::pair<BaseNode*, bool>> stack;
        std::stack<BaseNode*> dfsStack;
        bool useDFS;
        void expandTop();
    public:
        explicit PostOrderIterator(BaseNode* root, bool useDFS);
        BaseNode* operator*();
        PostOrderIterator& operator++();
        bool operator!=(const PostOrderIterator& other) const;
    };

    PostOrderIterator begin_post_order() const;
    PostOrderIterator end_post_order() const;

    // In-order iterator
    class InOrderIterator {
    private:
        std::stack<BaseNode*> next;
        std::stack<bool> visited;
        bool useDFS;
        void pushLeft(BaseNode* node);
    public:
        explicit InOrderIterator(BaseNode* root, bool useDFS);
        BaseNode* operator*();
        InOrderIterator& operator++();
        bool operator!=(const InOrderIterator& other) const;
    };

    InOrderIterator begin_in_order() const;
    InOrderIterator end_in_order() const;

    // Heap iterator
    class HeapIterator {
    private:
        std::vector<BaseNode*> heap;
        size_t index;
        void heapify();
    public:
        explicit HeapIterator(const std::vector<BaseNode*>& nodes);
        BaseNode* operator*();
        HeapIterator& operator++();
        bool operator!=(const HeapIterator& other) const;
    };

    HeapIterator begin_heap() const;
    HeapIterator end_heap() const;

    friend std::ostream& operator<<(std::ostream& os, const Tree& tree);

    Tree myHeap() const;

};

#endif // TREE_HPP
