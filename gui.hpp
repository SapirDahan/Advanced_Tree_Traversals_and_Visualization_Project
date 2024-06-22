/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#pragma once

#include "tree.hpp"
#include <SFML/Graphics.hpp>

/**
 * @class GUI
 * @brief A class responsible for rendering a tree structure using SFML.
 */
class GUI {
public:
    /**
     * @brief Renders the entire tree.
     * @param tree The tree to render.
     */
    void renderTree(const Tree& tree) const;

private:
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
    void renderNode(sf::RenderWindow& window, BaseNode* node, float x, float y, float xOffset, sf::Font& font, double depth) const;
};