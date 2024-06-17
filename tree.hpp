//
// Created by guy on 6/17/24.
//

#ifndef CPP_EX4_TREE_H
#define CPP_EX4_TREE_H

#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include "node.hpp"

template <typename T, int k = 2>
class Tree;

#include "tree_iterators.hpp"

template <typename T, int k = 2>
class Tree {
private:
    Node<T>* root;

public:
    Tree() : root(nullptr) {}
    ~Tree() { clear(root); }

    void add_root(Node<T>* node) { root = node; }
    void add_sub_node(Node<T>* parent, Node<T>* child) {
        if (parent->children.size() < k) {
            parent->children.push_back(child);
        } else {
            throw std::runtime_error("Cannot add child to full node");
        }
    }

    // Iterators
    using PreOrderIterator = ::PreOrderIterator<T, k>;
    using PostOrderIterator = ::PostOrderIterator<T, k>;
    using InOrderIterator = ::InOrderIterator<T, k>;
    using BFSIterator = ::BFSIterator<T, k>;
    using DFSIterator = ::DFSIterator<T, k>;

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

    // Heap conversion
    template <typename Iterator>
    std::pair<Iterator, Iterator> myHeap(Iterator first, Iterator last) {
        std::vector<Node<T>*> vec;
        while (first != last) {
            vec.push_back(&(*first));
            ++first;
        }
        std::make_heap(vec.begin(), vec.end(), [](Node<T>* a, Node<T>* b) {
            return a->value > b->value;
        });
        return std::make_pair(vec.begin(), vec.end());
    }

    friend std::ostream& operator<<(std::ostream& os, const Tree& tree) {
        tree.print(os, tree.root, 0);
        return os;
    }

private:
    void clear(Node<T>* node) {
        if (node) {
            for (auto child : node->children) {
                clear(child);
            }
            delete node;
        }
    }

    void print(std::ostream& os, Node<T>* node, int depth) const {
        if (node) {
            os << std::string(depth * 2, ' ') << node->value << std::endl;
            for (auto child : node->children) {
                print(os, child, depth + 1);
            }
        }
    }
};

#endif //CPP_EX4_TREE_H