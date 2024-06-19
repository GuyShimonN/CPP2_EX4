#ifndef CPP_EX4_TREE_H
#define CPP_EX4_TREE_H

#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include "node.hpp"
#include "tree_iterators.hpp"

namespace ariel {

    template<typename T, int k = 2>
    class Tree {
    private:
        Node<T> *root;

    public:
        Tree() : root(nullptr) {}
        explicit Tree(Node<T> *root) : root(root) {}

        ~Tree() { clear(root); }

        void add_root(Node<T> *node) { root = node; }

        void add_sub_node(Node<T> *parent, Node<T> *child) {
            if (parent->children.size() < k) {
                parent->children.push_back(child);
            } else {
                throw std::runtime_error("Cannot add child to full node");
            }
        }

        // Iterators
        PreOrderIterator<T, k> begin_pre_order() { return PreOrderIterator<T, k>(root); }

        PreOrderIterator<T, k> end_pre_order() { return PreOrderIterator<T, k>(nullptr); }

        PostOrderIterator<T, k> begin_post_order() { return PostOrderIterator<T, k>(root); }

        PostOrderIterator<T, k> end_post_order() { return PostOrderIterator<T, k>(nullptr); }

        InOrderIterator<T, k> begin_in_order() { return InOrderIterator<T, k>(root); }

        InOrderIterator<T, k> end_in_order() { return InOrderIterator<T, k>(nullptr); }

        BFSIterator<T, k> begin_bfs() { return BFSIterator<T, k>(root); }

        BFSIterator<T, k> end_bfs() { return BFSIterator<T, k>(nullptr); }

        DFSIterator<T, k> begin_dfs() { return DFSIterator<T, k>(root); }

        DFSIterator<T, k> end_dfs() { return DFSIterator<T, k>(nullptr); }

        // Heap conversion
        template<typename Iterator>
        std::pair<Iterator, Iterator> myHeap(Iterator first, Iterator last) {
            std::vector<Node<T>*> vec;
            while (first != last) {
                vec.push_back(&(*first));
                ++first;
            }
            std::make_heap(vec.begin(), vec.end(), [](Node<T>* a, Node<T>* b) {
                return a->value > b->value;
            });
            return std::make_pair(Iterator(vec.begin(), vec.end()), Iterator(vec.end(), vec.end()));
        }

        friend std::ostream &operator<<(std::ostream &os, const Tree &tree) {
            tree.print(os, tree.root, 0);
            return os;
        }

    private:
        void clear(Node<T> *node) {
            if (node) {
                for (auto child: node->children) {
                    clear(child);
                }
                delete node;
            }
        }

        void print(std::ostream &os, Node<T> *node, int depth) const {
            if (node) {
                os << std::string(depth * 2, ' ') << node->value << std::endl;
                for (auto child: node->children) {
                    print(os, child, depth + 1);
                }
            }
        }
    };

}

#endif //CPP_EX4_TREE_H