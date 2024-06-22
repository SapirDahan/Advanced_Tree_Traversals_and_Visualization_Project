/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#include "node.hpp"

/**
 * @brief Destructor for the BaseNode class.
 * Deletes all child nodes to ensure proper cleanup.
 */
BaseNode::~BaseNode() {
    for (BaseNode* child : children) {
        delete child; // Delete each child node
    }
    children.clear(); // Clear the vector to avoid dangling pointers
}
