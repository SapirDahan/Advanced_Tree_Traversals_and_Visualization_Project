#include "doctest.h"
#include "Complex.hpp"
#include "node.hpp"
#include "tree.hpp"


// Test default constructor
TEST_CASE("Complex Default Constructor") {
Complex<int, int> c;
REQUIRE(c.to_string() == "0+0i");
}

// Test parameterized constructor
TEST_CASE("Complex Parameterized Constructor") {
Complex<int, double> c(3, 4.5);
REQUIRE(c.to_string() == "3+4.5i");
}

// Test parameterized constructor with negative imaginary part
TEST_CASE("Complex Parameterized Constructor with Negative Imaginary Part") {
Complex<double, int> c(3.2, -4);
REQUIRE(c.to_string() == "3.2-4i");
}

// Test to_string method
TEST_CASE("Complex to_string Method") {
Complex<double, double> c(1.1, 2.2);
REQUIRE(c.to_string() == "1.1+2.2i");
}

// Test get_ascii_value method
TEST_CASE("Complex get_ascii_value Method") {
Complex<int, int> c(1, -2);
unsigned int expected_value = static_cast<unsigned int>('1') +
                              static_cast<unsigned int>('-') +
                              static_cast<unsigned int>('2') +
                              static_cast<unsigned int>('i');
REQUIRE(c.get_ascii_value() == expected_value);
}

// Test copy constructor
TEST_CASE("Complex Copy Constructor") {
Complex<int, int> c1(3, 4);
Complex<int, int> c2(c1);
REQUIRE(c2.to_string() == "3+4i");
}

// Test assignment operator
TEST_CASE("Complex Assignment Operator") {
Complex<int, int> c1(3, 4);
Complex<int, int> c2;
c2 = c1;
REQUIRE(c2.to_string() == "3+4i");
}

Tree create_sample_tree() {
    auto root_node = new Node<std::string>("root");
    Tree tree(3);
    tree.add_root(root_node);

    auto n1 = new Node<int>(1);
    auto n2 = new Node<std::string>("n2");
    auto n3 = new Node<double>(12.35);
    auto n4 = new Node<double>(0.25);
    auto n5 = new Node<std::string>("n5");
    auto n6 = new Node<std::string>("n6");
    auto n7 = new Node<std::string>("n7");
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

Tree create_another_sample_tree() {
    auto root_node = new Node<std::string>("root2");
    Tree tree(2);
    tree.add_root(root_node);

    auto n1 = new Node<int>(10);
    auto n2 = new Node<std::string>("n2");
    auto n3 = new Node<double>(20.45);
    auto n4 = new Node<double>(0.5);
    auto n5 = new Node<std::string>("n5");
    auto n6 = new Node<std::string>("n6");
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

Tree create_complex_tree() {
    auto root_node = new Node<std::string>("complex_root");
    Tree tree(4);
    tree.add_root(root_node);

    auto n1 = new Node<Complex<int, double>>(Complex<int, double>(1, 2.5));
    auto n2 = new Node<Complex<double, int>>(Complex<double, int>(3.14, 7));
    auto n3 = new Node<Complex<int, double>>(Complex<int, double>(5, -1.5));
    auto n4 = new Node<Complex<double, int>>(Complex<double, int>(2.71, 3));
    auto n5 = new Node<int>(42);
    auto n6 = new Node<double>(6.28);
    auto n7 = new Node<std::string>("n7");
    auto n8 = new Node<std::string>("n8");
    auto n9 = new Node<std::string>("n9");
    auto n10 = new Node<Complex<int, double>>(Complex<int, double>(-3, 1.1));

    auto n11 = new Node<Complex<int, double>>(Complex<int, double>(10, 2.2));
    auto n12 = new Node<Complex<int, double>>(Complex<int, double>(-7, 3.3));

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
    tree.add_sub_node(n8, n12);

    return tree;
}

// Test functions
void test_pre_order(Tree& tree, const std::vector<std::string>& expected) {
    std::vector<std::string> result;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        BaseNode* node_ptr = *it;
        result.push_back(node_ptr->get_value());
    }
    CHECK(result == expected);
}

void test_post_order(Tree& tree, const std::vector<std::string>& expected) {
    std::vector<std::string> result;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        BaseNode* node_ptr = *it;
        result.push_back(node_ptr->get_value());
    }
    CHECK(result == expected);
}

void test_in_order(Tree& tree, const std::vector<std::string>& expected) {
    std::vector<std::string> result;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        BaseNode* node_ptr = *it;
        result.push_back(node_ptr->get_value());
    }
    CHECK(result == expected);
}

// Tests
TEST_CASE("Tree traversal tests") {
    // Sample tree tests
    {
        Tree tree = create_sample_tree();
        test_pre_order(tree, {"root", "1", "0.25", "n5", "7-4.5i", "n2", "n6", "n7", "12.35"});
        test_post_order(tree, {"0.25", "7-4.5i", "n5", "1", "n6", "n7", "n2", "12.35", "root"});
        test_in_order(tree, {"0.25", "1", "7-4.5i", "n5", "root", "n6", "n2", "n7", "12.35"});
    }

    // Another sample tree tests
    {
        Tree tree = create_another_sample_tree();
        test_pre_order(tree, {"root2", "10", "20.45", "0.5", "n2", "n5", "4.57i", "n6", "3-1.2i"});
        test_post_order(tree, {"20.45", "0.5", "10", "4.57i", "n5", "3-1.2i", "n6", "n2", "root2"});
        test_in_order(tree, {"20.45", "10", "0.5", "root2", "4.57i", "n5", "n2", "3-1.2i", "n6"});
    }

    // Complex tree tests
    {
        Tree tree = create_complex_tree();
        test_pre_order(tree, {"complex_root", "12.5i", "42", "6.28", "3.147i", "n7", "n8", "102.2i", "-73.3i", "5-1.5i", "n9", "2.713i", "-31.1i"});
        test_post_order(tree, {"42", "6.28", "12.5i", "n7", "102.2i", "-73.3i", "n8", "3.147i", "n9", "5-1.5i", "-31.1i", "2.713i", "complex_root"});
        test_in_order(tree, {"42", "6.28", "12.5i", "n7", "102.2i", "-73.3i", "n8", "3.147i", "n9", "5-1.5i", "-31.1i", "2.713i", "complex_root"});
    }
}