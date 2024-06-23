#ifndef CPP_EX4_TREE_H
#define CPP_EX4_TREE_H

#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <type_traits>
#include "node.hpp"
#include "tree_iterators.hpp"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include "complex.hpp"

namespace ariel {

    template<typename T, int k = 2>
    class Tree {
    private:
        Node<T> *root;

        void drawNode(QGraphicsScene *scene, Node<T> *node, double x, double y, double hSpacing, double vSpacing,
                      int level) const {
            // ... (implementation remains the same)
        }

        void clear(Node<T> *node) {
            if (node) {
                for (auto child : node->children) {
                    clear(child);
                }
                delete node;
            }
        }

        void print(std::ostream &os, Node<T> *node, int depth) const {
            if (node) {
                os << std::string(depth * 2, ' ') << node->value << std::endl;
                for (auto child : node->children) {
                    print(os, child, depth + 1);
                }
            }
        }

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

        PreOrderIterator<T, k> begin_pre_order() const { return PreOrderIterator<T, k>(root); }

        PreOrderIterator<T, k> end_pre_order() const { return PreOrderIterator<T, k>(nullptr); }

        PostOrderIterator<T, k> begin_post_order() const { return PostOrderIterator<T, k>(root); }

        PostOrderIterator<T, k> end_post_order() const { return PostOrderIterator<T, k>(nullptr); }

        InOrderIterator<T, k> begin_in_order() const { return InOrderIterator<T, k>(root); }

        InOrderIterator<T, k> end_in_order() const { return InOrderIterator<T, k>(nullptr); }

        BFSIterator<T, k> begin_bfs() const { return BFSIterator<T, k>(root); }

        BFSIterator<T, k> end_bfs() const { return BFSIterator<T, k>(nullptr); }

        DFSIterator<T, k> begin_dfs() const { return DFSIterator<T, k>(root); }

        DFSIterator<T, k> end_dfs() const { return DFSIterator<T, k>(nullptr); }

        template<typename Iterator>
        std::pair<Iterator, Iterator> myHeap(Iterator first, Iterator last) {
            std::vector<Node<T> *> vec;
            while (first != last) {
                vec.push_back(&(*first));
                ++first;
            }
            std::make_heap(vec.begin(), vec.end(), [](Node<T> *a, Node<T> *b) {
                return a->value > b->value;
            });
            return std::make_pair(Iterator(vec.begin(), vec.end()), Iterator(vec.end(), vec.end()));
        }

        friend std::ostream &operator<<(std::ostream &os, const Tree &tree) {
            tree.print(os, tree.root, 0);
            return os;
        }

        void drawTree(QGraphicsScene *scene, double xOffset = 0) const {
            if (!root) return;

            double hSpacing = 200;  // Horizontal spacing between nodes
            double vSpacing = 100;  // Vertical spacing between levels

            drawNode(scene, root, xOffset + scene->width() / 8, 50, hSpacing, vSpacing, 0);
        }
    };

} // namespace ariel

#endif // CPP_EX4_TREE_H