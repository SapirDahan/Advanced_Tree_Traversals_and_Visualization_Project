
<!-- * Author: Sapir Dahan -->
<!-- ID: 325732972 -->
<!-- * Mail: sapirdahan2003@gmail.com -->

# Tree Traversal and Manipulation Project

## Author: Sapir Dahan
- **ID**: 325732972
- **Email**: sapirdahan2003@gmail.com

## Project Overview

This project implements a tree data structure supporting various types of traversals and manipulations, including:
- In-order
- Pre-order
- Post-order
- BFS (Breadth-First Search)
- DFS (Depth-First Search)
- Range-based for loop traversal (which behaves as BFS)

Additionally, the project supports creating a min-heap from a binary tree and working with complex number nodes. The project also includes a graphical user interface (GUI) for visualizing the tree using the SFML library, providing a visual representation of the tree.

## Features

### Tree Traversals
The project supports several types of tree traversals. If the maximum degree of the tree is greater than 2, the pre-order, post-order, and in-order traversals will switch to a DFS approach.

#### In-Order Traversal
In-order traversal visits the nodes in the following order:
1. Left child
2. Root
3. Right child

#### Pre-Order Traversal
Pre-order traversal visits the nodes in the following order:
1. Root
2. Left child
3. Right child

#### Post-Order Traversal
Post-order traversal visits the nodes in the following order:
1. Left child
2. Right child
3. Root

#### BFS (Breadth-First Search)
BFS traversal visits nodes level by level from top to bottom and left to right within each level.

#### DFS (Depth-First Search)
DFS traversal explores as far as possible along each branch before backtracking.

#### Range-Based For Loop
This traversal behaves as a BFS traversal and allows easy iteration over the tree nodes using a range-based for loop.

### Complex Number Nodes
The project supports nodes containing complex numbers. Complex numbers are implemented with both real and imaginary parts, and their string representations and ASCII values are supported.

### Min-Heap Creation
A specialized function `myHeap` transforms a binary tree (maxDegree = 2) into a min-heap. If the tree is not a binary tree, an error is thrown.

### Graphical User Interface (GUI)
The project includes a GUI for visualizing the tree using the SFML library. The GUI allows users to see the tree structure with nodes and edges, providing an interactive and visual representation of the tree.

## Usage

### Tree Traversal Demonstration
The `demonstrate_tree` function showcases the different traversals of the tree.

### Creating Trees
Functions are provided to create various sample trees:
- `create_sample_tree`
- `create_another_sample_tree`
- `create_complex_tree`
- `create_string_tree`

Each function returns a `Tree` object initialized with different types and structures of nodes.

### Main Function
The main function demonstrates the creation of trees and their traversals:

```cpp
int main() {
    // Redirect stderr to /dev/null
    freopen("/dev/null", "w", stderr);

    std::cout << "Demo 1:" << std::endl;
    Tree tree1 = create_sample_tree();
    demonstrate_tree(tree1);

    std::cout << "

Demo 2:" << std::endl;
    Tree tree2 = create_another_sample_tree();
    demonstrate_tree(tree2);

    std::cout << "

Demo 3:" << std::endl;
    Tree tree3 = create_complex_tree();
    demonstrate_tree(tree3);

    std::cout << "

Demo 4 (String Tree - Original):" << std::endl;
    Tree stringTree = create_string_tree();
    demonstrate_tree(stringTree);

    try {
        std::cout << "

Demo 4 (String Tree - Min-Heap):" << std::endl;
        Tree heapTree = stringTree.myHeap();
        demonstrate_tree(heapTree);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
```

## Example Trees

### Demo 1: Sample Tree
![Demo 1 Tree](Images/1.png)

### Demo 2: Another Sample Tree
![Demo 2 Tree](Images/2.png)

### Demo 3: Complex Tree
![Demo 3 Tree](Images/3.png)

### Demo 4: String Tree - Original
![Demo 4 Original Tree](Images/4.png)

### Demo 4: String Tree - Min-Heap
![Demo 4 Min-Heap Tree](Images/5.png)

### Running the Code

To build and run the code:
```sh
make tree
./tree
```

## Testing

The project includes a set of test cases to verify the functionality of the tree. These tests are implemented in `TestCounter.cpp` and `Tests.cpp`.

### Running Tests:
```sh
make test
./test
```
The `make test` command compiles the test executable.
The `./test` command runs the compiled test executable.

## Memory Management

The project uses Valgrind to check for memory leaks.

### Running Valgrind:
```sh
make valgrind
```
The `make valgrind` command runs Valgrind on both the demo and test executables to check for memory leaks.

## Static Code Analysis

Static code analysis is performed using cppcheck.

### Running Cppcheck:
```sh
make cppcheck
```
The `make cppcheck` command runs cppcheck on all source files for static code analysis.

## Cleaning Up

To clean up the build artifacts:
```sh
make clean
```
The `make clean` command removes all compiled object files and executables.
