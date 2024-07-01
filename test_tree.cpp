#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "tree.hpp"
#include "complex.hpp"

// Test case for PreOrderIterator
TEST_CASE("PreOrderIterator works correctly") {
    ariel::Tree<int> tree;
    ariel::Node<int>* root = new ariel::Node<int>(1);
    tree.add_root(root);

    ariel::Node<int>* child1 = new ariel::Node<int>(2);
    ariel::Node<int>* child2 = new ariel::Node<int>(3);
    ariel::Node<int>* child3 = new ariel::Node<int>(4);
    ariel::Node<int>* child4 = new ariel::Node<int>(5);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);

    std::vector<int> expected_pre_order = {1, 2, 4, 5, 3};
    std::vector<int> actual_pre_order;

    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        actual_pre_order.push_back(it->value);
    }

    REQUIRE(expected_pre_order == actual_pre_order);
}

// Test case for PostOrderIterator
TEST_CASE("PostOrderIterator works correctly") {
    ariel::Tree<int> tree;
    ariel::Node<int>* root = new ariel::Node<int>(1);
    tree.add_root(root);

    ariel::Node<int>* child1 = new ariel::Node<int>(2);
    ariel::Node<int>* child2 = new ariel::Node<int>(3);
    ariel::Node<int>* child3 = new ariel::Node<int>(4);
    ariel::Node<int>* child4 = new ariel::Node<int>(5);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);

    std::vector<int> expected_post_order = {4, 5, 2, 3, 1};
    std::vector<int> actual_post_order;

    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        actual_post_order.push_back(it->value);
    }

    REQUIRE(expected_post_order == actual_post_order);
}

// Test case for InOrderIterator
TEST_CASE("InOrderIterator works correctly") {
    ariel::Tree<int> tree;
    ariel::Node<int>* root = new ariel::Node<int>(1);
    tree.add_root(root);

    ariel::Node<int>* child1 = new ariel::Node<int>(2);
    ariel::Node<int>* child2 = new ariel::Node<int>(3);
    ariel::Node<int>* child3 = new ariel::Node<int>(4);
    ariel::Node<int>* child4 = new ariel::Node<int>(5);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);

    std::vector<int> expected_in_order = {4, 2, 5, 1, 3};
    std::vector<int> actual_in_order;

    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        actual_in_order.push_back(it->value);
    }

    REQUIRE(expected_in_order == actual_in_order);
}

// Test case for BFSIterator
TEST_CASE("BFSIterator works correctly") {
    ariel::Tree<int> tree;
    ariel::Node<int>* root = new ariel::Node<int>(1);
    tree.add_root(root);

    ariel::Node<int>* child1 = new ariel::Node<int>(2);
    ariel::Node<int>* child2 = new ariel::Node<int>(3);
    ariel::Node<int>* child3 = new ariel::Node<int>(4);
    ariel::Node<int>* child4 = new ariel::Node<int>(5);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);

    std::vector<int> expected_bfs = {1, 2, 3, 4, 5};
    std::vector<int> actual_bfs;

    for (auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it) {
        actual_bfs.push_back(it->value);
    }

    REQUIRE(expected_bfs == actual_bfs);
}

// Test case for DFSIterator
TEST_CASE("DFSIterator works correctly") {
    ariel::Tree<int> tree;
    ariel::Node<int>* root = new ariel::Node<int>(1);
    tree.add_root(root);

    ariel::Node<int>* child1 = new ariel::Node<int>(2);
    ariel::Node<int>* child2 = new ariel::Node<int>(3);
    ariel::Node<int>* child3 = new ariel::Node<int>(4);
    ariel::Node<int>* child4 = new ariel::Node<int>(5);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);

    std::vector<int> expected_dfs = {1, 2, 4, 5, 3};
    std::vector<int> actual_dfs;

    for (auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it) {
        actual_dfs.push_back(it->value);
    }

    REQUIRE(expected_dfs == actual_dfs);
}

// Test case for an empty tree
TEST_CASE("Empty tree iterators work correctly") {
    ariel::Tree<int> tree;

    REQUIRE(tree.begin_pre_order() == tree.end_pre_order());
    REQUIRE(tree.begin_post_order() == tree.end_post_order());
    REQUIRE(tree.begin_in_order() == tree.end_in_order());
    REQUIRE(tree.begin_bfs() == tree.end_bfs());
    REQUIRE(tree.begin_dfs() == tree.end_dfs());
}

// Test case for a single node tree
TEST_CASE("Single node tree iterators work correctly") {
    ariel::Tree<int> tree;
    ariel::Node<int>* root = new ariel::Node<int>(1);
    tree.add_root(root);

    std::vector<int> expected_single_node = {1};
    std::vector<int> actual_pre_order;
    std::vector<int> actual_post_order;
    std::vector<int> actual_in_order;
    std::vector<int> actual_bfs;
    std::vector<int> actual_dfs;

    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        actual_pre_order.push_back(it->value);
    }

    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        actual_post_order.push_back(it->value);
    }

    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        actual_in_order.push_back(it->value);
    }

    for (auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it) {
        actual_bfs.push_back(it->value);
    }

    for (auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it) {
        actual_dfs.push_back(it->value);
    }

    REQUIRE(expected_single_node == actual_pre_order);
    REQUIRE(expected_single_node == actual_post_order);
    REQUIRE(expected_single_node == actual_in_order);
    REQUIRE(expected_single_node == actual_bfs);
    REQUIRE(expected_single_node == actual_dfs);
}

TEST_CASE("Complex number tree iterators work correctly") {
    ariel::Tree<ariel::Complex> tree;
    ariel::Node<ariel::Complex>* root = new ariel::Node<ariel::Complex>(ariel::Complex(1, 2));
    tree.add_root(root);

    ariel::Node<ariel::Complex>* child1 = new ariel::Node<ariel::Complex>(ariel::Complex(3, 4));
    ariel::Node<ariel::Complex>* child2 = new ariel::Node<ariel::Complex>(ariel::Complex(5, 6));
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);

    std::vector<std::string> expected_pre_order = {"1.000000 + 2.000000i", "3.000000 + 4.000000i", "5.000000 + 6.000000i"};
    std::vector<std::string> actual_pre_order;

    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        actual_pre_order.push_back(it->value.to_string());
    }

    REQUIRE(expected_pre_order == actual_pre_order);
}

// Test case for tree with duplicate values
TEST_CASE("Tree with duplicate values iterators work correctly") {
    ariel::Tree<int> tree;
    ariel::Node<int>* root = new ariel::Node<int>(1);
    tree.add_root(root);

    ariel::Node<int>* child1 = new ariel::Node<int>(2);
    ariel::Node<int>* child2 = new ariel::Node<int>(2);
    ariel::Node<int>* child3 = new ariel::Node<int>(1);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);

    std::vector<int> expected_pre_order = {1, 2, 1, 2};
    std::vector<int> actual_pre_order;

    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        actual_pre_order.push_back(it->value);
    }

    REQUIRE(expected_pre_order == actual_pre_order);
}

// Test case for adding sub node to a full node
TEST_CASE("Adding sub node to a full node throws error") {
    ariel::Tree<int> tree;
    ariel::Node<int>* root = new ariel::Node<int>(1);
    tree.add_root(root);

    ariel::Node<int>* child1 = new ariel::Node<int>(2);
    ariel::Node<int>* child2 = new ariel::Node<int>(3);
    ariel::Node<int>* child3 = new ariel::Node<int>(4);
    ariel::Node<int>* child4 = new ariel::Node<int>(5);
    ariel::Node<int>* child5 = new ariel::Node<int>(6);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);

//    REQUIRE_NOTHROW(tree.add_sub_node(root, child5));
    REQUIRE_THROWS(tree.add_sub_node(child1, new ariel::Node<int>(7)));
}

// Test case for tree with different data types (strings)
TEST_CASE("Tree with strings iterators work correctly") {
    ariel::Tree<std::string> tree;
    ariel::Node<std::string>* root = new ariel::Node<std::string>("root");
    tree.add_root(root);

    ariel::Node<std::string>* child1 = new ariel::Node<std::string>("child1");
    ariel::Node<std::string>* child2 = new ariel::Node<std::string>("child2");
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);

    std::vector<std::string> expected_pre_order = {"root", "child1", "child2"};
    std::vector<std::string> actual_pre_order;

    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        actual_pre_order.push_back(it->value);
    }

    REQUIRE(expected_pre_order == actual_pre_order);
}




// Test case for tree with only left children
TEST_CASE("Tree with only left children iterators work correctly") {
    ariel::Tree<int> tree;
    ariel::Node<int>* root = new ariel::Node<int>(1);
    tree.add_root(root);

    ariel::Node<int>* child1 = new ariel::Node<int>(2);
    ariel::Node<int>* child2 = new ariel::Node<int>(3);
    ariel::Node<int>* child3 = new ariel::Node<int>(4);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(child1, child2);
    tree.add_sub_node(child2, child3);

    std::vector<int> expected_pre_order = {1, 2, 3, 4};
    std::vector<int> actual_pre_order;

    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        actual_pre_order.push_back(it->value);
    }

    REQUIRE(expected_pre_order == actual_pre_order);
}

// Test case for tree with only right children
TEST_CASE("Tree with only right children iterators work correctly") {
    ariel::Tree<int> tree;
    ariel::Node<int>* root = new ariel::Node<int>(1);
    tree.add_root(root);

    ariel::Node<int>* child1 = new ariel::Node<int>(2);
    ariel::Node<int>* child2 = new ariel::Node<int>(3);
    ariel::Node<int>* child3 = new ariel::Node<int>(4);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(child1, child2);
    tree.add_sub_node(child2, child3);

    std::vector<int> expected_pre_order = {1, 2, 3, 4};
    std::vector<int> actual_pre_order;

    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        actual_pre_order.push_back(it->value);
    }

    REQUIRE(expected_pre_order == actual_pre_order);
}

// Test case for mixed data types (ints and doubles)
TEST_CASE("Tree with mixed data types iterators work correctly") {
    ariel::Tree<double> tree;
    ariel::Node<double>* root = new ariel::Node<double>(1.1);
    tree.add_root(root);

    ariel::Node<double>* child1 = new ariel::Node<double>(2.2);
    ariel::Node<double>* child2 = new ariel::Node<double>(3.3);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);

    std::vector<double> expected_pre_order = {1.1, 2.2, 3.3};
    std::vector<double> actual_pre_order;

    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        actual_pre_order.push_back(it->value);
    }

    REQUIRE(expected_pre_order == actual_pre_order);
}

// Test case for a deep tree
TEST_CASE("Deep tree iterators work correctly") {
    ariel::Tree<int> tree;
    ariel::Node<int>* root = new ariel::Node<int>(1);
    tree.add_root(root);

    ariel::Node<int>* current = root;
    for (int i = 2; i <= 10; ++i) {
        ariel::Node<int>* child = new ariel::Node<int>(i);
        tree.add_sub_node(current, child);
        current = child;
    }

    std::vector<int> expected_pre_order = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> actual_pre_order;

    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        actual_pre_order.push_back(it->value);
    }

    REQUIRE(expected_pre_order == actual_pre_order);
}

// Test case for modifying the tree structure
TEST_CASE("Modifying the tree structure works correctly") {
    ariel::Tree<int> tree;
    ariel::Node<int>* root = new ariel::Node<int>(1);
    tree.add_root(root);

    ariel::Node<int>* child1 = new ariel::Node<int>(2);
    ariel::Node<int>* child2 = new ariel::Node<int>(3);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);

    ariel::Node<int>* new_child = new ariel::Node<int>(4);
    tree.add_sub_node(child1, new_child);

    std::vector<int> expected_pre_order = {1, 2, 4, 3};
    std::vector<int> actual_pre_order;

    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        actual_pre_order.push_back(it->value);
    }

    REQUIRE(expected_pre_order == actual_pre_order);
}

TEST_CASE("tree whit more then 2 children"){

    ariel::Tree<int, 3> tree;
    ariel::Node<int>* root = new ariel::Node<int>(1);
    tree.add_root(root);

    ariel::Node<int>* child1 = new ariel::Node<int>(2);
    ariel::Node<int>* child2 = new ariel::Node<int>(3);
    ariel::Node<int>* child3 = new ariel::Node<int>(4);
    ariel::Node<int>* child4 = new ariel::Node<int>(5);
    ariel::Node<int>* child5 = new ariel::Node<int>(6);
    ariel::Node<int>* child6 = new ariel::Node<int>(7);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(root, child3);
    tree.add_sub_node(child1, child4);
    tree.add_sub_node(child1, child5);
    tree.add_sub_node(child1, child6);

    std::vector<int> expected_pre_order = {1, 2, 5, 6, 7,3, 4};
    std::vector<int> actual_pre_order;

    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        actual_pre_order.push_back(it->value);
    }

    REQUIRE(expected_pre_order == actual_pre_order);
    std::vector<int> actual_BFS;
    for(auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it){
       actual_BFS.push_back(it->value);
    }
    std::vector<int> expected_BFS = {1, 2, 3, 4, 5, 6, 7};

    REQUIRE(expected_BFS == actual_BFS);

    std::vector<int> actual_DFS;
    for(auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it){
       actual_DFS.push_back(it->value);
    }
    std::vector<int> expected_DFS = {1, 2, 5, 6, 7, 3 , 4};

    REQUIRE(expected_DFS == actual_DFS);

    std::vector<int> actual_post_order;
    for(auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it){
       actual_post_order.push_back(it->value);
    }
    std::vector<int> expected_post_order = {1, 2, 5, 6, 7, 3, 4};

    REQUIRE(expected_post_order == actual_post_order);

    std::vector<int> actual_in_order;
    for(auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it){
       actual_in_order.push_back(it->value);
    }
    std::vector<int> expected_in_order = {1, 2, 5, 6, 7, 3, 4};

    REQUIRE(expected_in_order == actual_in_order);
}

TEST_CASE("Heap functionality") {
    SECTION("Binary tree to min heap") {
        ariel::Tree<int> tree;
        ariel::Node<int>* root = new ariel::Node<int>(5);
        tree.add_root(root);
        tree.add_sub_node(root, new ariel::Node<int>(3));
        tree.add_sub_node(root, new ariel::Node<int>(7));
        tree.add_sub_node(root->children[0], new ariel::Node<int>(2));
        tree.add_sub_node(root->children[0], new ariel::Node<int>(4));
        tree.add_sub_node(root->children[1], new ariel::Node<int>(6));
        tree.add_sub_node(root->children[1], new ariel::Node<int>(8));

        std::cout << "Calling myHeap()" << std::endl;
        std::vector<int> heap = tree.myHeap();

        std::vector<int> expected = {2, 3, 4, 5, 6, 7, 8};

        std::cout << "Expected: ";
        for (const auto& val : expected) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        std::cout << "Actual: ";
        for (const auto& val : heap) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        REQUIRE(expected == heap);
    }

    SECTION("Tree with duplicate values to heap") {
        ariel::Tree<int> tree;
        ariel::Node<int>* root = new ariel::Node<int>(3);
        tree.add_root(root);
        tree.add_sub_node(root, new ariel::Node<int>(3));
        tree.add_sub_node(root, new ariel::Node<int>(2));
        tree.add_sub_node(root->children[0], new ariel::Node<int>(1));
        tree.add_sub_node(root->children[0], new ariel::Node<int>(3));

        std::cout << "Calling myHeap() for duplicate values test" << std::endl;
        std::vector<int> heap = tree.myHeap();

        std::vector<int> expected = {1, 2, 3};

        std::cout << "Expected: ";
        for (const auto& val : expected) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        std::cout << "Actual: ";
        for (const auto& val : heap) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        REQUIRE(expected == heap);
    }
}

