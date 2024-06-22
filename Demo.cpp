/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#include <iostream>
#include <string>
#include <memory>
#include "node.hpp"
#include "tree.hpp"
#include "Complex.hpp"

using namespace std;

/**
 * @brief Function to demonstrate tree traversal and printing
 * @param tree The tree to traverse and print
 */
void demonstrate_tree(const Tree& tree) {
    try {
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

        // Range-based for loop (BFS traversal)
        std::cout << "\n\nRange-based for loop (BFS traversal):" << std::endl;
        for (auto node_ptr : tree) {
            std::cout << node_ptr->get_value() << " ";
        }

        std::cout << "\n" << std::endl;

        // Render the tree using the GUI
        std::cout << tree;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception occurred!" << std::endl;
    }
}

/**
 * @brief Function to create and return a sample tree
 * @return Tree A sample tree
 */
Tree create_sample_tree() {
    auto root_node = std::make_unique<Node<string>>("root");
    Tree tree(3);
    tree.add_root(root_node.get());

    auto n1 = std::make_unique<Node<int>>(1);
    auto n2 = std::make_unique<Node<string>>("n2");
    auto n3 = std::make_unique<Node<double>>(12.35);
    auto n4 = std::make_unique<Node<double>>(0.25);
    auto n5 = std::make_unique<Node<string>>("n5");
    auto n6 = std::make_unique<Node<string>>("n6");
    auto n7 = std::make_unique<Node<string>>("n7");
    auto n8 = std::make_unique<Node<Complex<int, double>>>(Complex<int, double>(7, -4.5));

    tree.add_sub_node(root_node.get(), n1.get());
    tree.add_sub_node(root_node.get(), n2.get());
    tree.add_sub_node(root_node.get(), n3.get());
    tree.add_sub_node(n1.get(), n4.get());
    tree.add_sub_node(n1.get(), n5.get());
    tree.add_sub_node(n2.get(), n6.get());
    tree.add_sub_node(n2.get(), n7.get());
    tree.add_sub_node(n5.get(), n8.get());

    // Release ownership of nodes to the tree
    root_node.release();
    n1.release();
    n2.release();
    n3.release();
    n4.release();
    n5.release();
    n6.release();
    n7.release();
    n8.release();

    return tree;
}

/**
 * @brief Function to create and return another sample tree
 * @return Tree Another sample tree
 */
Tree create_another_sample_tree() {
    auto root_node = std::make_unique<Node<string>>("root2");
    Tree tree(2);
    tree.add_root(root_node.get());

    auto n1 = std::make_unique<Node<int>>(10);
    auto n2 = std::make_unique<Node<string>>("n2");
    auto n3 = std::make_unique<Node<double>>(20.45);
    auto n4 = std::make_unique<Node<double>>(0.5);
    auto n5 = std::make_unique<Node<string>>("n5");
    auto n6 = std::make_unique<Node<string>>("n6");
    auto n7 = std::make_unique<Node<Complex<double, int>>>(Complex<double, int>(4.5, 7));
    auto n8 = std::make_unique<Node<Complex<int, double>>>(Complex<int, double>(3, -1.2));

    tree.add_sub_node(root_node.get(), n1.get());
    tree.add_sub_node(root_node.get(), n2.get());
    tree.add_sub_node(n1.get(), n3.get());
    tree.add_sub_node(n1.get(), n4.get());
    tree.add_sub_node(n2.get(), n5.get());
    tree.add_sub_node(n2.get(), n6.get());
    tree.add_sub_node(n5.get(), n7.get());
    tree.add_sub_node(n6.get(), n8.get());

    // Release ownership of nodes to the tree
    root_node.release();
    n1.release();
    n2.release();
    n3.release();
    n4.release();
    n5.release();
    n6.release();
    n7.release();
    n8.release();

    return tree;
}

/**
 * @brief Function to create and return a more complex tree
 * @return Tree A complex tree
 */
Tree create_complex_tree() {
    auto root_node = std::make_unique<Node<string>>("complex");
    Tree tree(4);
    tree.add_root(root_node.get());

    auto n1 = std::make_unique<Node<Complex<int, double>>>(Complex<int, double>(1, 2.5));
    auto n2 = std::make_unique<Node<Complex<double, int>>>(Complex<double, int>(3.14, 7));
    auto n3 = std::make_unique<Node<Complex<int, double>>>(Complex<int, double>(5, -1.5));
    auto n4 = std::make_unique<Node<Complex<double, int>>>(Complex<double, int>(2.71, 3));
    auto n5 = std::make_unique<Node<int>>(42);
    auto n6 = std::make_unique<Node<double>>(6.28);
    auto n7 = std::make_unique<Node<string>>("n7");
    auto n8 = std::make_unique<Node<string>>("n8");
    auto n9 = std::make_unique<Node<string>>("n9");
    auto n10 = std::make_unique<Node<Complex<int, double>>>(Complex<int, double>(-3, 1.1));
    auto n11 = std::make_unique<Node<Complex<int, double>>>(Complex<int, double>(10, 2.2));

    tree.add_sub_node(root_node.get(), n1.get());
    tree.add_sub_node(root_node.get(), n2.get());
    tree.add_sub_node(root_node.get(), n3.get());
    tree.add_sub_node(root_node.get(), n4.get());
    tree.add_sub_node(n1.get(), n5.get());
    tree.add_sub_node(n1.get(), n6.get());
    tree.add_sub_node(n2.get(), n7.get());
    tree.add_sub_node(n2.get(), n8.get());
    tree.add_sub_node(n3.get(), n9.get());
    tree.add_sub_node(n4.get(), n10.get());
    tree.add_sub_node(n8.get(), n11.get());

    // Release ownership of nodes to the tree
    root_node.release();
    n1.release();
    n2.release();
    n3.release();
    n4.release();
    n5.release();
    n6.release();
    n7.release();
    n8.release();
    n9.release();
    n10.release();
    n11.release();

    return tree;
}

/**
 * @brief Function to create and return a tree with only strings
 * @return Tree A tree with only string nodes
 */
Tree create_string_tree() {
    auto root_node = std::make_unique<Node<string>>("node5");
    Tree tree(2);
    tree.add_root(root_node.get());

    auto n1 = std::make_unique<Node<string>>("node3");
    auto n2 = std::make_unique<Node<string>>("node8");
    auto n3 = std::make_unique<Node<string>>("node1");
    auto n4 = std::make_unique<Node<string>>("node4");
    auto n5 = std::make_unique<Node<string>>("node7");
    auto n6 = std::make_unique<Node<string>>("node6");
    auto n7 = std::make_unique<Node<string>>("node2");

    tree.add_sub_node(root_node.get(), n1.get());
    tree.add_sub_node(root_node.get(), n2.get());
    tree.add_sub_node(n1.get(), n3.get());
    tree.add_sub_node(n1.get(), n4.get());
    tree.add_sub_node(n2.get(), n5.get());
    tree.add_sub_node(n5.get(), n6.get());
    tree.add_sub_node(n3.get(), n7.get());

    // Release ownership of nodes to the tree
    root_node.release();
    n1.release();
    n2.release();
    n3.release();
    n4.release();
    n5.release();
    n6.release();
    n7.release();

    return tree;
}

/**
 * @brief Main function to demonstrate tree traversals and heap creation.
 *
 * The main function creates different types of trees, demonstrates their traversals,
 * and creates a min-heap from a string tree.
 *
 * @return int Exit status of the program.
 */
int main() {
    // Redirect stderr to /dev/null
    freopen("/dev/null", "w", stderr);

    std::cout << "Demo 1:" << std::endl;
    Tree tree1 = create_sample_tree();
    demonstrate_tree(tree1);

    std::cout << "\n\nDemo 2:" << std::endl;
    Tree tree2 = create_another_sample_tree();
    demonstrate_tree(tree2);

    std::cout << "\n\nDemo 3:" << std::endl;
    Tree tree3 = create_complex_tree();
    demonstrate_tree(tree3);

    std::cout << "\n\nDemo 4 (String Tree - Original):" << std::endl;
    Tree stringTree = create_string_tree();
    demonstrate_tree(stringTree);

    std::cout << "\n\nDemo 4 (String Tree - Min-Heap):" << std::endl;
    try {
        Tree heapTree = stringTree.myHeap();
        demonstrate_tree(heapTree);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
