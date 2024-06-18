#include "gui.hpp"

void GUI::renderTree(const Tree& tree) const {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {  // Make sure "arial.ttf" is in the working directory
        throw std::runtime_error("Error loading font");
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        if (tree.get_root()) {
            renderNode(window, tree.get_root(), window.getSize().x / 2, 50, window.getSize().x, font, 0.001);  // Adjust the horizontal spread
        }
        window.display();
    }
}

void GUI::renderNode(sf::RenderWindow& window, BaseNode* node, float x, float y, float xOffset, sf::Font& font, double depth) const {
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
