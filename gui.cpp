/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#include "gui.hpp"

/**
 * @brief Renders the entire tree in a window.
 * @param tree The tree to render.
 */
void GUI::renderTree(const Tree& tree) const {

    // Create a window for visualization
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");

    // Load the font
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        throw std::runtime_error("Error loading font");
    }

    // Main loop for the window
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with white color
        window.clear(sf::Color::White);

        // Render the root node and its children recursively if the root is not null
        if (tree.get_root()) {
            renderNode(window, tree.get_root(), window.getSize().x / 2, 50, window.getSize().x, font, 0.001);
        }

        // Display the rendered frame on the window
        window.display();
    }
}

/**
 * @brief Recursively renders a node and its children.
 * @param window The window to draw on.
 * @param node The current node to render.
 * @param x The x-coordinate of the node.
 * @param y The y-coordinate of the node.
 * @param xOffset The horizontal offset for child nodes.
 * @param font The font used to draw text.
 * @param depth The current depth in the tree.
 */
void GUI::renderNode(sf::RenderWindow& window, BaseNode* node, float x, float y, float xOffset, sf::Font& font, double depth) const {
    if (!node) return;

    // Define the radius for the node's circle
    float radius = 35.0f;

    // Create and configure the circle shape representing the node
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(x - radius, y - radius);

    // Create and configure the text to display the node's value
    sf::Text text;
    text.setFont(font);
    text.setString(node->get_value());
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);

    // Center the text within the circle
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(x, y);

    // Calculate the position for the children nodes
    float childY = y + 2 * radius + 60;  // Adjust vertical distance between nodes
    float adjustedXOffset = xOffset / (depth + 0.9);  // Adjust horizontal spread based on depth
    if (depth == 1) adjustedXOffset = xOffset;  // Significant spread for the first level

    float startX = x - (adjustedXOffset / 2);

    // Iterate over each child node and render them recursively
    for (size_t i = 0; i < node->children.size(); i++) {
        BaseNode* child = node->children[i].get();
        float childX = startX + (i + 1) * (adjustedXOffset / (node->children.size() + 1));

        // Draw connecting lines between the current node and its children
        sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y)),
                sf::Vertex(sf::Vector2f(childX, childY - radius), sf::Color::Black)
        };

        window.draw(line, 2, sf::Lines);

        // Recursively render the child nodes
        renderNode(window, child, childX, childY, xOffset * 0.7, font, depth + 1);  // Further decrease horizontal spread
    }

    // Draw the current node's circle and text
    window.draw(shape);
    window.draw(text);
}