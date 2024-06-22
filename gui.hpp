/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#pragma once

#include "tree.hpp"
#include <SFML/Graphics.hpp>

class GUI {
public:
    void renderTree(const Tree& tree) const;

private:
    void renderNode(sf::RenderWindow& window, BaseNode* node, float x, float y, float xOffset, sf::Font& font, double depth) const;
};

