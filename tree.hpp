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
            if (!node) return;

            QGraphicsEllipseItem* ellipse = scene->addEllipse(x - 20, y - 20, 40, 40);
            QString nodeText;
            if constexpr (std::is_same_v<T, Complex>) {
                nodeText = QString::fromStdString(node->value.to_string());
            } else if constexpr (std::is_same_v<T, std::string>) {
                nodeText = QString::fromStdString(node->value);
            } else {
                nodeText = QString::number(node->value);
            }
            QGraphicsTextItem* text = scene->addText(nodeText);
            text->setPos(x - 10, y - 10);

            double childrenWidth = hSpacing * (k - 1);
            double startX = x - childrenWidth / 2;
            for (int i = 0; i < node->children.size(); ++i) {
                double childX = startX + i * hSpacing;
                double childY = y + vSpacing;

                scene->addLine(x, y + 20, childX, childY - 20);

                drawNode(scene, node->children[i], childX, childY, hSpacing / 2, vSpacing, level + 1);
            }
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

        Node<T>* get_root() const { return root; }

        void add_sub_node(Node<T> *parent, Node<T> *child) {
            if (parent->children.size() < k) {
                parent->children.push_back(child);
            } else {
                throw std::runtime_error("Cannot add child to full node");
            }
        }

        auto begin_pre_order() const {
            if constexpr (k <= 2) {
                return PreOrderIterator<T, k>(root);
            } else {
                return DFSIterator<T, k>(root);
            }
        }

        auto end_pre_order() const {
            if constexpr (k <= 2) {
                return PreOrderIterator<T, k>(nullptr);
            } else {
                return DFSIterator<T, k>(nullptr);
            }
        }

        auto begin_post_order() const {
            if constexpr (k <= 2) {
                return PostOrderIterator<T, k>(root);
            } else {
                return DFSIterator<T, k>(root);
            }
        }

        auto end_post_order() const {
            if constexpr (k <= 2) {
                return PostOrderIterator<T, k>(nullptr);
            } else {
                return DFSIterator<T, k>(nullptr);
            }
        }

        auto begin_in_order() const {
            if constexpr (k <= 2) {
                return InOrderIterator<T, k>(root);
            } else {
                return DFSIterator<T, k>(root);
            }
        }

        auto end_in_order() const {
            if constexpr (k <= 2) {
                return InOrderIterator<T, k>(nullptr);
            } else {
                return DFSIterator<T, k>(nullptr);
            }
        }

        BFSIterator<T, k> begin_bfs() const { return BFSIterator<T, k>(root); }

        BFSIterator<T, k> end_bfs() const { return BFSIterator<T, k>(nullptr); }

        DFSIterator<T, k> begin_dfs() const { return DFSIterator<T, k>(root); }

        DFSIterator<T, k> end_dfs() const { return DFSIterator<T, k>(nullptr); }


        std::vector<T> myHeap() const {
            std::cout << "Entering myHeap()" << std::endl;
            std::vector<T> values;
            std::cout << "Collecting values from DFS traversal:" << std::endl;
            for (auto it = begin_dfs(); it != end_dfs(); ++it) {
                std::cout << "  Adding value: " << it->value << std::endl;
                values.push_back(it->value);
            }

            std::cout << "Sorting values:" << std::endl;
            std::sort(values.begin(), values.end());
            for (const auto& val : values) {
                std::cout << "  " << val << std::endl;
            }

            std::cout << "Removing duplicates:" << std::endl;
            auto last = std::unique(values.begin(), values.end());
            values.erase(last, values.end());
            for (const auto& val : values) {
                std::cout << "  " << val << std::endl;
            }

            std::cout << "Returning values" << std::endl;
            return values;
        }


        friend std::ostream &operator<<(std::ostream &os, const Tree &tree) {
            tree.print(os, tree.root, 0);
            return os;
        }

        void drawTree(QGraphicsScene* scene, double xOffset = 0, double yOffset = 0) const {
            if (!root) return;

            double hSpacing = 200;  // Horizontal spacing between nodes
            double vSpacing = 100;  // Vertical spacing between levels

            drawNode(scene, root, xOffset + scene->width() / 4, yOffset, hSpacing, vSpacing, 0);
        }
    };

} // namespace ariel

#endif // CPP_EX4_TREE_H