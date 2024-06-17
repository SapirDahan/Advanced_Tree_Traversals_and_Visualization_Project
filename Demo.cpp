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
    Node<string> root_node("root");
    Tree tree(3);
    tree.add_root(&root_node);

    Node<int> n1(1);
    Node<string> n2("n2");
    Node<double> n3(12.35);
    Node<double> n4(0.25);
    Node<string> n5("n5");
    Node<string> n6("n6");
    Node<string> n7("n7");

    tree.add_sub_node(&root_node, &n1);
    tree.add_sub_node(&root_node, &n2);
    tree.add_sub_node(&root_node, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n1, &n5);
    tree.add_sub_node(&n2, &n6);
    tree.add_sub_node(&n2, &n7);

    // Pre-order traversal
    std::cout << "Pre-order traversal:" << std::endl;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        BaseNode* node_ptr = *it;
        std::cout << node_ptr->get_value() << " ";
    }

    // Post-order traversal
    std::cout << "\n\nPost-order traversal:" << std::endl;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        BaseNode* node_ptr = *it;
        std::cout << node_ptr->get_value() << " ";
    }

    // In-order traversal
    std::cout << "\n\nIn-order traversal:" << std::endl;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        BaseNode* node_ptr = *it;
        std::cout << node_ptr->get_value() << " ";
    }

    // BFS traversal
    std::cout << "\n\nBFS traversal:" << std::endl;
    for (auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it) {
        BaseNode* node_ptr = *it;
        std::cout << node_ptr->get_value() << " ";
    }

    // DFS traversal
    std::cout << "\n\nDFS traversal:" << std::endl;
    for (auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it) {
        BaseNode* node_ptr = *it;
        std::cout << node_ptr->get_value() << " ";
    }

    std::cout << "\n\nRange-based for loop (BFS traversal):" << std::endl;
    for (auto node_ptr : tree) {
        std::cout << node_ptr->get_value() << " ";
    }

    std::cout<<"\n\n" << std::endl;

    std::cout << tree;

    return 0;
}
