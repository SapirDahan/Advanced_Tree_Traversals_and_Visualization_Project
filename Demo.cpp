/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"

using namespace std;

int main()
{
    Node<string> root_node = Node(string("root"));
    Tree tree;
    tree.add_root(&root_node);
    Node<int> n1 = Node(1);
    Node<string> n2 = Node(string("n2"));
    Node<double> n3 = Node(12.35);
    Node<double> n4 = Node(1 / 4.0);
    Node<string> n5 = Node(string("n5"));
    Node<string> n6 = Node(string("n6"));
    Node<string> n7 = Node(string("n7"));

    tree.add_sub_node(&root_node, &n1);
    tree.add_sub_node(&root_node, &n2);
    tree.add_sub_node(&root_node, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n1, &n5);
    tree.add_sub_node(&n2, &n6);
    tree.add_sub_node(&n2, &n7);
    // The tree should look like:
    /**
     * root
     * |__1
     * |  |__0.25
     * |  |__n5
     * |__n2
     * |  |__n6
     * |  |__n7
     * |__12.35
     */

    // Pre-order traversal
    std::cout << "Pre-order traversal:" << std::endl;
    for (auto it = tree.begin_pre_order<string>(); it != tree.end_pre_order<string>(); ++it) {
        std::cout << "Visiting node with value: " << (*it)->get_value() << std::endl;
    }

    // Post-order traversal
    std::cout << "Post-order traversal:" << std::endl;
    for (auto it = tree.begin_post_order<string>(); it != tree.end_post_order<string>(); ++it) {
        std::cout << "Visiting node with value: " << (*it)->get_value() << std::endl;
    }

    // BFS traversal
    std::cout << "BFS traversal:" << std::endl;
    for (auto it = tree.begin_bfs<string>(); it != tree.end_bfs<string>(); ++it) {
        std::cout << "Visiting node with value: " << (*it)->get_value() << std::endl;
    }

    return 0;
}
