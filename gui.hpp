#ifndef GUI_HPP
#define GUI_HPP

#include "tree.hpp"
#include <SFML/Graphics.hpp>

class GUI {
public:
    void renderTree(const Tree& tree) const;

private:
    void renderNode(sf::RenderWindow& window, BaseNode* node, float x, float y, float xOffset, sf::Font& font, double depth) const;
};

#endif // GUI_HPP
