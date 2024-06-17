#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>

class Tree {
private:
    BaseNode* root;
    unsigned int maxDegree = 2;

    void renderNode(sf::RenderWindow& window, BaseNode* node, float x, float y, float xOffset, sf::Font& font, double depth) const {
        if (!node) return;

        float radius = 30.0f;  // Circle radius
        sf::CircleShape shape(radius);
        shape.setFillColor(sf::Color::Black);
        shape.setPosition(x - radius, y - radius);

        sf::Text text;
        text.setFont(font);
        text.setString(node->get_value());
        text.setCharacterSize(20);  // Adjust text size
        text.setFillColor(sf::Color::White);

        // Center the text
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(x, y);

        float childY = y + 2 * radius + 40;  // Adjust vertical distance between nodes
        float adjustedXOffset = xOffset / (depth + 1);  // Adjust horizontal spread based on depth
        if (depth == 1) adjustedXOffset = xOffset;  // Significant spread for the first level

        float startX = x - (adjustedXOffset / 2);

        for (size_t i = 0; i < node->children.size(); ++i) {
            BaseNode* child = node->children[i];
            float childX = startX + (i + 1) * (adjustedXOffset / (node->children.size() + 1));

            // Draw connecting lines
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x, y)),
                    sf::Vertex(sf::Vector2f(childX, childY - radius), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);

            renderNode(window, child, childX, childY, xOffset * 0.7, font, depth + 0.5);  // Further decrease horizontal spread
        }

        window.draw(shape);
        window.draw(text);
    }

public:
    Tree() : root(nullptr) {}

    Tree(unsigned int degree) : root(nullptr), maxDegree(degree) {}

    ~Tree() {

    }

    void add_root(BaseNode* root_node) {
        root = root_node;
        std::cout << "Added root node with value: " << root_node->get_value() << std::endl;
    }

    BaseNode* get_root() const {
        return root;
    }

    void add_sub_node(BaseNode* parent, BaseNode* child) {
        if (parent && child) {
            if (parent->children.size() < maxDegree) {
                parent->add_child(child);
            } else {
                std::cerr << "Error: Cannot add child, maxDegree exceeded for parent node!" << std::endl;
            }
        } else {
            std::cerr << "Error: Parent or child node is null!" << std::endl;
        }
    }

    void render() const {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");

        sf::Font font;
        if (!font.loadFromFile("Arial.ttf")) {  // Make sure "arial.ttf" is in the working directory
            std::cerr << "Error loading font" << std::endl;
            return;
        }

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);
            if (root) {
                renderNode(window, root, window.getSize().x / 2, 50, window.getSize().x, font, 0.001);  // Adjust the horizontal spread
            }
            window.display();
        }
    }

    // Overload the << operator
    friend std::ostream& operator<<(std::ostream& os, const Tree& tree) {
        tree.render();
        return os;
    }

    // BFS iterator
    class BFSIterator {
    private:
        std::queue<BaseNode*> queue;

    public:
        explicit BFSIterator(BaseNode* root) {
            if (root) {
                queue.push(root);
            }
        }

        BaseNode* operator*() {
            return queue.front();
        }

        BFSIterator& operator++() {
            BaseNode* node = queue.front();
            queue.pop();
            auto& children = node->children;
            for (auto child : children) {
                if (child != nullptr) {
                    queue.push(child);
                } else {
                    std::cerr << "Error: Encountered null or invalid child node!" << std::endl;
                }
            }
            return *this;
        }

        bool operator!=(const BFSIterator& other) const {
            return !queue.empty();
        }
    };

    BFSIterator begin_bfs() const {
        return BFSIterator(root);
    }

    BFSIterator end_bfs() const {
        return BFSIterator(nullptr);
    }

    BFSIterator begin() const {
        return begin_bfs();
    }

    BFSIterator end() const {
        return end_bfs();
    }

    // DFS iterator
    class DFSIterator {
    private:
        std::stack<BaseNode*> next;

    public:
        explicit DFSIterator(BaseNode* root) {
            if (root) {
                next.push(root);
            }
        }

        BaseNode* operator*() {
            return next.top();
        }

        DFSIterator& operator++() {
            BaseNode* currentNode = next.top();
            next.pop();

            auto& children = currentNode->children;
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                if (*it != nullptr) {
                    next.push(*it);
                } else {
                    std::cerr << "Error: Encountered null or invalid child node!" << std::endl;
                }
            }
            return *this;
        }

        bool operator!=(const DFSIterator& other) const {
            return !next.empty();
        }
    };

    DFSIterator begin_dfs() const {
        return DFSIterator(root);
    }

    DFSIterator end_dfs() const {
        return DFSIterator(nullptr);
    }

    // Pre-order iterator
    class PreOrderIterator {
    private:
        std::stack<BaseNode*> next;
        bool useDFS;

    public:
        explicit PreOrderIterator(BaseNode* root, bool useDFS) : useDFS(useDFS) {
            if (root) {
                next.push(root);
            }
        }

        BaseNode* operator*() {
            return next.top();
        }

        PreOrderIterator& operator++() {
            BaseNode* currentNode = next.top();
            next.pop();

            auto& children = currentNode->children;
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                if (*it != nullptr) {
                    next.push(*it);
                } else {
                    std::cerr << "Error: Encountered null or invalid child node!" << std::endl;
                }
            }
            return *this;
        }

        bool operator!=(const PreOrderIterator& other) const {
            return !next.empty();
        }
    };

    PreOrderIterator begin_pre_order() const {
        return PreOrderIterator(root, maxDegree > 2);
    }

    PreOrderIterator end_pre_order() const {
        return PreOrderIterator(nullptr, maxDegree > 2);
    }

    // Post-order iterator
    class PostOrderIterator {
    private:
        std::stack<BaseNode*> next;
        bool useDFS;

        void expandTop() {
            while (!next.empty() && !next.top()->children.empty()) {
                BaseNode* node = next.top();
                next.pop();
                auto& children = node->children;
                for (auto it = children.rbegin(); it != children.rend(); ++it) {
                    if (*it != nullptr) {
                        next.push(*it);
                    } else {
                        std::cerr << "Error: Encountered null or invalid child node!" << std::endl;
                    }
                }
                next.push(node);
            }
        }

    public:
        explicit PostOrderIterator(BaseNode* root, bool useDFS) : useDFS(useDFS) {
            if (root) {
                next.push(root);
                if (!useDFS) {
                    expandTop();
                }
            }
        }

        BaseNode* operator*() {
            return next.top();
        }

        PostOrderIterator& operator++() {
            BaseNode* node = next.top();
            next.pop();
            if (useDFS) {
                auto& children = node->children;
                for (auto it = children.rbegin(); it != children.rend(); ++it) {
                    if (*it != nullptr) {
                        next.push(*it);
                    } else {
                        std::cerr << "Error: Encountered null or invalid child node!" << std::endl;
                    }
                }
            } else {
                expandTop();
            }
            return *this;
        }

        bool operator!=(const PostOrderIterator& other) const {
            return !next.empty();
        }
    };

    PostOrderIterator begin_post_order() const {
        return PostOrderIterator(root, maxDegree > 2);
    }

    PostOrderIterator end_post_order() const {
        return PostOrderIterator(nullptr, maxDegree > 2);
    }

    // In-order iterator
    class InOrderIterator {
    private:
        std::stack<BaseNode*> next;
        std::stack<bool> visited;
        bool useDFS;

        void pushLeft(BaseNode* node) {
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

    public:
        explicit InOrderIterator(BaseNode* root, bool useDFS) : useDFS(useDFS) {
            if (root) {
                pushLeft(root);
            }
        }

        BaseNode* operator*() {
            return next.top();
        }

        InOrderIterator& operator++() {
            BaseNode* currentNode = next.top();
            next.pop();
            visited.pop();

            if (useDFS) {
                auto& children = currentNode->children;
                for (auto it = children.rbegin(); it != children.rend(); ++it) {
                    if (*it != nullptr) {
                        next.push(*it);
                    } else {
                        std::cerr << "Error: Encountered null or invalid child node!" << std::endl;
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

        bool operator!=(const InOrderIterator& other) const {
            return !next.empty();
        }
    };

    InOrderIterator begin_in_order() const {
        return InOrderIterator(root, maxDegree > 2);
    }

    InOrderIterator end_in_order() const {
        return InOrderIterator(nullptr, maxDegree > 2);
    }

    // Heap iterator
    class HeapIterator {
    private:
        std::vector<BaseNode*> heap;
        size_t index;

        void heapify() {
            auto comparator = [](BaseNode* a, BaseNode* b) {
                return a->get_ascii_value() < b->get_ascii_value();
            };
            std::make_heap(heap.begin(), heap.end(), comparator);
            std::sort_heap(heap.begin(), heap.end(), comparator);
        }

    public:
        explicit HeapIterator(const std::vector<BaseNode*>& nodes) : heap(nodes), index(0) {
            heapify();
        }

        BaseNode* operator*() {
            return heap[index];
        }

        HeapIterator& operator++() {
            ++index;
            return *this;
        }

        bool operator!=(const HeapIterator& other) const {
            return index != other.index;
        }
    };

    HeapIterator begin_heap() const {
        std::vector<BaseNode*> nodes;
        for (auto it = begin_in_order(); it != end_in_order(); ++it) {
            nodes.push_back(*it);
        }
        return HeapIterator(nodes);
    }

    HeapIterator end_heap() const {
        return HeapIterator({});
    }
};

#endif // TREE_HPP
