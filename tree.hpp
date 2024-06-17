#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include "tree_iterators.hpp"
#include <queue>
#include <stack>
#include <iterator>
#include <algorithm>
#include <functional>

template <typename T, int K = 2>
class Tree {
public:
    using PreOrderIterator = ::PreOrderIterator<T, K>;
    using PostOrderIterator = ::PostOrderIterator<T, K>;
    using InOrderIterator = ::InOrderIterator<T, K>;
    using BFSIterator = ::BFSIterator<T, K>;
    using DFSIterator = ::DFSIterator<T, K>;

    Tree() : root(nullptr) {}
    ~Tree() { clear(); }

    void add_root(Node<T>& node) {
        root = &node;
    }

    void add_sub_node(Node<T>& parent, Node<T>& child) {
        if (parent.children.size() < K) {
            parent.children.push_back(&child);
        }
    }

    PreOrderIterator begin_pre_order() { return PreOrderIterator(root); }
    PreOrderIterator end_pre_order() { return PreOrderIterator(nullptr); }

    PostOrderIterator begin_post_order() { return PostOrderIterator(root); }
    PostOrderIterator end_post_order() { return PostOrderIterator(nullptr); }

    InOrderIterator begin_in_order() { return InOrderIterator(root); }
    InOrderIterator end_in_order() { return InOrderIterator(nullptr); }

    BFSIterator begin_bfs() { return BFSIterator(root); }
    BFSIterator end_bfs() { return BFSIterator(nullptr); }

    DFSIterator begin_dfs() { return DFSIterator(root); }
    DFSIterator end_dfs() { return DFSIterator(nullptr); }

    void myHeap() {
        std::vector<Node<T>*> nodes;
        collect_nodes(root, nodes);

        std::make_heap(nodes.begin(), nodes.end(), [](Node<T>* a, Node<T>* b) {
            return a->get_value() > b->get_value();
        });

        root = nodes.front();
        rebuild_heap(nodes);
    }

    void clear() {
        delete root;
        root = nullptr;
    }

    friend std::ostream& operator<<(std::ostream& os, const Tree& tree) {
        // Placeholder for GUI output
        os << "Tree with root: " << (tree.root ? tree.root->get_value() : T()) << std::endl;
        return os;
    }

private:
    Node<T>* root;

    void collect_nodes(Node<T>* node, std::vector<Node<T>*>& nodes) {
        if (!node) return;
        nodes.push_back(node);
        for (Node<T>* child : node->children) {
            collect_nodes(child, nodes);
        }
    }

    void rebuild_heap(const std::vector<Node<T>*>& nodes) {
        std::queue<Node<T>*> queue;
        queue.push(nodes.front());

        size_t index = 1;
        while (!queue.empty() && index < nodes.size()) {
            Node<T>* current = queue.front();
            queue.pop();

            current->children.clear();
            for (int i = 0; i < K && index < nodes.size(); ++i) {
                current->children.push_back(nodes[index++]);
                queue.push(current->children.back());
            }
        }
    }
};

#endif // TREE_HPP
