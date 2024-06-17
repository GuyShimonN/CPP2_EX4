#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"

using namespace std;

int main()
{
    Node<double> root_node = Node<double>(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);

    Node<double> n1 = Node<double>(1.2);
    Node<double> n2 = Node<double>(1.3);
    Node<double> n3 = Node<double>(1.4);
    Node<double> n4 = Node<double>(1.5);
    Node<double> n5 = Node<double>(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // Pre-Order Traversal
    auto pre_order = tree.begin_pre_order();
    while (pre_order.has_next()) {
        cout << pre_order.next()->get_value() << endl;
    }

    // Post-Order Traversal
    auto post_order = tree.begin_post_order();
    while (post_order.has_next()) {
        cout << post_order.next()->get_value() << endl;
    }

    // In-Order Traversal
    auto in_order = tree.begin_in_order();
    while (in_order.has_next()) {
        cout << in_order.next()->get_value() << endl;
    }

    // BFS Traversal
    auto bfs = tree.begin_bfs();
    while (bfs.has_next()) {
        cout << bfs.next()->get_value() << endl;
    }

    // DFS Traversal
    auto dfs = tree.begin_dfs();
    while (dfs.has_next()) {
        cout << dfs.next()->get_value() << endl;
    }

    // Output the tree structure (placeholder for GUI)
    cout << tree;

    // Create a 3-ary tree (tree with max 3 children per node)
    Tree<double,3> three_ary_tree;
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    // The 3-ary tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */

    return 0;
}
