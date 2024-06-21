#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "Complex.hpp"

using namespace std;

// Function to demonstrate tree traversal and printing
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

        std::cout << "\n\nRange-based for loop (BFS traversal):" << std::endl;
        for (auto node_ptr : tree) {
            std::cout << node_ptr->get_value() << " ";
        }

        std::cout << "\n" << std::endl;

        std::cout << tree;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception occurred!" << std::endl;
    }
}

// Function to create and return a sample tree
Tree create_sample_tree() {
    auto root_node = new Node<string>("root");
    Tree tree(3);
    tree.add_root(root_node);

    auto n1 = new Node<int>(1);
    auto n2 = new Node<string>("n2");
    auto n3 = new Node<double>(12.35);
    auto n4 = new Node<double>(0.25);
    auto n5 = new Node<string>("n5");
    auto n6 = new Node<string>("n6");
    auto n7 = new Node<string>("n7");
    auto n8 = new Node<Complex<int, double>>(Complex<int, double>(7, -4.5));

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(root_node, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n2, n6);
    tree.add_sub_node(n2, n7);
    tree.add_sub_node(n5, n8);

    return tree;
}

// Function to create and return another sample tree
Tree create_another_sample_tree() {
    auto root_node = new Node<string>("root2");
    Tree tree;
    tree.add_root(root_node);

    auto n1 = new Node<int>(10);
    auto n2 = new Node<string>("n2");
    auto n3 = new Node<double>(20.45);
    auto n4 = new Node<double>(0.5);
    auto n5 = new Node<string>("n5");
    auto n6 = new Node<string>("n6");
    auto n7 = new Node<Complex<double, int>>(Complex<double, int>(4.5, 7));
    auto n8 = new Node<Complex<int, double>>(Complex<int, double>(3, -1.2));

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n2, n6);
    tree.add_sub_node(n5, n7);
    tree.add_sub_node(n6, n8);

    return tree;
}

// Function to create a more complex tree
Tree create_complex_tree() {
    auto root_node = new Node<string>("complex");
    Tree tree(4);
    tree.add_root(root_node);

    auto n1 = new Node<Complex<int, double>>(Complex<int, double>(1, 2.5));
    auto n2 = new Node<Complex<double, int>>(Complex<double, int>(3.14, 7));
    auto n3 = new Node<Complex<int, double>>(Complex<int, double>(5, -1.5));
    auto n4 = new Node<Complex<double, int>>(Complex<double, int>(2.71, 3));
    auto n5 = new Node<int>(42);
    auto n6 = new Node<double>(6.28);
    auto n7 = new Node<string>("n7");
    auto n8 = new Node<string>("n8");
    auto n9 = new Node<string>("n9");
    auto n10 = new Node<Complex<int, double>>(Complex<int, double>(-3, 1.1));
    auto n11 = new Node<Complex<int, double>>(Complex<int, double>(10, 2.2)); // Additional node for n8

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(root_node, n3);
    tree.add_sub_node(root_node, n4);
    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n1, n6);
    tree.add_sub_node(n2, n7);
    tree.add_sub_node(n2, n8);
    tree.add_sub_node(n3, n9);
    tree.add_sub_node(n4, n10);
    tree.add_sub_node(n8, n11);

    return tree;
}

// Function to create and return a tree with only strings
Tree create_string_tree() {
    auto root_node = new Node<string>("node5");
    Tree tree(2);
    tree.add_root(root_node);

    auto n1 = new Node<string>("node3");
    auto n2 = new Node<string>("node8");
    auto n3 = new Node<string>("node1");
    auto n4 = new Node<string>("node4");
    auto n5 = new Node<string>("node7");
    auto n6 = new Node<string>("node6");
    auto n7 = new Node<string>("node2");

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n5, n6);
    tree.add_sub_node(n3, n7);

    return tree;
}




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


    std::cout << "\n\nDemo 4 (String Tree - Min-Heap):" << std::endl;
    Tree stringTree = create_string_tree();

    std::cout << "\n\nThe tree before:" << std::endl;
    demonstrate_tree(stringTree);

    std::cout << "\n\nThe min heap:" << std::endl;
    try {
        Tree heapTree = stringTree.myHeap();
        demonstrate_tree(heapTree);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
