#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <stack>
#include <queue>
#include <iostream>
#include <SFML/Graphics.hpp>

class Tree {
private:
    BaseNode* root;

    void renderNode(sf::RenderWindow& window, BaseNode* node, float x, float y, float xOffset, sf::Font& font) const {
        if (!node) return;

        sf::CircleShape shape(20);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(x, y);

        sf::Text text;
        text.setFont(font);
        text.setString(node->get_value());
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::White);
        text.setPosition(x + 10, y + 10);

        window.draw(shape);
        window.draw(text);

        float childY = y + 60;
        float childXOffset = xOffset / 2;
        for (BaseNode* child : node->children) {
            float childX = x - xOffset / 2 + (&child - &node->children[0]) * xOffset;
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x + 20, y + 20)),
                    sf::Vertex(sf::Vector2f(childX + 20, childY + 20))
            };
            window.draw(line, 2, sf::Lines);
            renderNode(window, child, childX, childY, childXOffset, font);
        }
    }

public:
    Tree() : root(nullptr) {}

    void render() const {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");

        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font" << std::endl;
            return;
        }

        while (window.isOpen()) {
            sf::Event event;
            while (event.type == sf::Event::Closed)
                window.close();

            window.clear();
            if (root) {
                renderNode(window, root, window.getSize().x / 2, 50, window.getSize().x / 4, font);
            }
            window.display();
        }
    }

    // Overload the << operator
    friend std::ostream& operator<<(std::ostream& os, const Tree& tree) {
        tree.render();
        return os;
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
            parent->add_child(child);
        } else {
            std::cerr << "Error: Parent or child node is null!" << std::endl;
        }
    }

    // Pre-order iterator
    class PreOrderIterator {
    private:
        std::stack<BaseNode*> next;

    public:
        explicit PreOrderIterator(BaseNode* root) {
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

    PreOrderIterator begin_pre_order() {
        return PreOrderIterator(root);
    }

    PreOrderIterator end_pre_order() {
        return PreOrderIterator(nullptr);
    }

    // Post-order iterator
    class PostOrderIterator {
    private:
        struct NodeInfo {
            BaseNode* node;
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
                    if (*it != nullptr) {
                        next.push({*it, false});
                    } else {
                        std::cerr << "Error: Encountered null or invalid child node!" << std::endl;
                    }
                }
            }
        }

    public:
        explicit PostOrderIterator(BaseNode* root) {
            if (root) {
                next.push({root, false});
                expandTop();
            }
        }

        BaseNode* operator*() {
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

    PostOrderIterator begin_post_order() {
        return PostOrderIterator(root);
    }

    PostOrderIterator end_post_order() {
        return PostOrderIterator(nullptr);
    }

    // In-order iterator
    class InOrderIterator {
    private:
        std::stack<BaseNode*> next;
        std::stack<bool> visited;

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
        explicit InOrderIterator(BaseNode* root) {
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

            if (!currentNode->children.empty()) {
                std::vector<BaseNode*>& children = currentNode->children;
                for (size_t i = 1; i < children.size(); ++i) {
                    pushLeft(children[i]);
                }
            }

            return *this;
        }

        bool operator!=(const InOrderIterator& other) const {
            return !next.empty();
        }
    };

    InOrderIterator begin_in_order() {
        return InOrderIterator(root);
    }

    InOrderIterator end_in_order() {
        return InOrderIterator(nullptr);
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

    BFSIterator begin_bfs() {
        return BFSIterator(root);
    }

    BFSIterator end_bfs() {
        return BFSIterator(nullptr);
    }

    BFSIterator begin() {
        return begin_bfs();
    }

    BFSIterator end() {
        return end_bfs();
    }

    // DFS iterator (similar to pre-order)
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

    DFSIterator begin_dfs() {
        return DFSIterator(root);
    }

    DFSIterator end_dfs() {
        return DFSIterator(nullptr);
    }
};

#endif // TREE_HPP
