#include "tree.hpp"
#include "complex.hpp"
#include <iostream>

int main() {
    // Demonstrate Integer Tree
    Tree<int> intTree;
    Node<int>* root = new Node<int>(1);
    intTree.add_root(root);

    Node<int>* child1 = new Node<int>(2);
    Node<int>* child2 = new Node<int>(3);
    Node<int>* child3 = new Node<int>(4);
    Node<int>* child4 = new Node<int>(5);
    intTree.add_sub_node(root, child1);
    intTree.add_sub_node(root, child2);
    intTree.add_sub_node(child1, child3);
    intTree.add_sub_node(child1, child4);

    std::cout << "Integer Tree:" << std::endl;
    std::cout << intTree;

    std::cout << "Pre-order traversal: ";
    for (auto it = intTree.begin_pre_order(); it != intTree.end_pre_order(); ++it) {
        std::cout << it->value << " ";
    }
    std::cout << std::endl;

    std::cout << "Post-order traversal: ";
    for (auto it = intTree.begin_post_order(); it != intTree.end_post_order(); ++it) {
        std::cout << it->value << " ";
    }
    std::cout << std::endl;

    std::cout << "In-order traversal: ";
    for (auto it = intTree.begin_in_order(); it != intTree.end_in_order(); ++it) {
        std::cout << it->value << " ";
    }
    std::cout << std::endl;

    std::cout << "BFS traversal: ";
    for (auto it = intTree.begin_bfs(); it != intTree.end_bfs(); ++it) {
        std::cout << it->value << " ";
    }
    std::cout << std::endl;

    std::cout << "DFS traversal: ";
    for (auto it = intTree.begin_dfs(); it != intTree.end_dfs(); ++it) {
        std::cout << it->value << " ";
    }
    std::cout << std::endl;

    // Demonstrate Complex Tree
    Tree<Complex> complexTree;
    Node<Complex>* complexRoot = new Node<Complex>(Complex(1, 2));
    complexTree.add_root(complexRoot);

    Node<Complex>* complexChild1 = new Node<Complex>(Complex(3, 4));
    Node<Complex>* complexChild2 = new Node<Complex>(Complex(5, 6));
    complexTree.add_sub_node(complexRoot, complexChild1);
    complexTree.add_sub_node(complexRoot, complexChild2);

    std::cout << "\nComplex Tree:" << std::endl;
    std::cout << complexTree;

    // Demonstrate heap conversion
    std::cout << "Heap (first 3 elements): ";
    auto heapIterators = intTree.myHeap(intTree.begin_bfs(), intTree.end_bfs());
    for (int i = 0; i < 3 && heapIterators.first != heapIterators.second; ++i, ++heapIterators.first) {
        std::cout << (*heapIterators.first)->value << " ";
    }
    std::cout << std::endl;

    // Demonstrate error handling
    try {
        intTree.add_sub_node(child1, new Node<int>(6));
        intTree.add_sub_node(child1, new Node<int>(7));
        intTree.add_sub_node(child1, new Node<int>(8)); // This should throw
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
}