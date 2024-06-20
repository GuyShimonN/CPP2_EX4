#ifndef CPP_EX4_TREE_ITERATORS_H
#define CPP_EX4_TREE_ITERATORS_H

#include <stack>
#include <queue>
#include <stdexcept>
#include "node.hpp"

namespace ariel {

    template<typename T, int k>
    class Tree;

    template<typename T, int k>
    class PreOrderIterator {
    private:
        std::stack<Node<T> *> nodeStack;
    public:
        PreOrderIterator(Node<T> *root) {

            if (root) nodeStack.push(root);

        }

        Node<T> &operator*() const {
            if (nodeStack.empty()) {
                throw std::out_of_range("PreOrderIterator: Dereferencing an empty iterator");
            }
            return *nodeStack.top();
        }

        Node<T> *operator->() const {
            if (nodeStack.empty()) {
                throw std::out_of_range("PreOrderIterator: Dereferencing an empty iterator");
            }
            return nodeStack.top();
        }

        PreOrderIterator &operator++() {
            if (!nodeStack.empty()) {
                Node<T> *current = nodeStack.top();
                nodeStack.pop();
                for (int i = current->children.size() - 1; i >= 0; --i) {
                    nodeStack.push(current->children[i]);
                }
            }
            return *this;
        }
        PreOrderIterator &operator++(int) {
            PreOrderIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const PreOrderIterator &other) const {
            return nodeStack == other.nodeStack;
        }

        bool operator!=(const PreOrderIterator &other) const {
            return !(*this == other);
        }
    };

    template<typename T, int k>
    class PostOrderIterator {
    private:
        std::stack<Node<T> *> nodeStack;
        Node<T> *lastVisited;

        void pushLeftmostBranch(Node<T> *node) {
            while (node) {
                nodeStack.push(node);
                if (!node->children.empty()) {
                    node = node->children[0];
                } else {
                    node = nullptr;
                }
            }
        }

        bool isLastChild(Node<T> *parent, Node<T> *child) {
            return !parent->children.empty() && parent->children.back() == child;
        }

    public:
        PostOrderIterator(Node<T> *root) {
            lastVisited = nullptr;
            if (root) pushLeftmostBranch(root);
        }

        Node<T> &operator*() const {
            if (nodeStack.empty()) {
                throw std::out_of_range("PostOrderIterator: Dereferencing an empty iterator");
            }
            return *nodeStack.top();
        }

        Node<T> *operator->() const {
            if (nodeStack.empty()) {
                throw std::out_of_range("PostOrderIterator: Dereferencing an empty iterator");
            }
            return nodeStack.top();
        }
        PostOrderIterator &operator++() {
            if (nodeStack.empty()) {
                throw std::out_of_range("PostOrderIterator: Incrementing an empty iterator");
            }
            Node<T> *node = nodeStack.top();
            nodeStack.pop();
            if (node->children.size() > 0 && lastVisited != node->children.back()) {
                for (int i = node->children.size() - 1; i >= 0; --i) {
                    nodeStack.push(node->children[i]);
                }
            }
            lastVisited = node;
            return *this;
        }
        PostOrderIterator &operator++(int) {
            PostOrderIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const PostOrderIterator &other) const {
            return nodeStack == other.nodeStack && lastVisited == other.lastVisited;
        }

        bool operator!=(const PostOrderIterator &other) const {
            return !(*this == other);
        }
    };

    template<typename T, int k>
    class InOrderIterator {
    private:
        std::stack<Node<T> *> nodeStack;
        Node<T> *current;
    public:
        InOrderIterator(Node<T> *root) : current(root) {
            pushLeftmostBranch(root);
        }

        Node<T> &operator*() const {
            if (nodeStack.empty()) {
                throw std::out_of_range("InOrderIterator: Dereferencing an empty iterator");
            }
            return *nodeStack.top();
        }

        Node<T> *operator->() const {
            if (nodeStack.empty()) {
                throw std::out_of_range("InOrderIterator: Dereferencing an empty iterator");
            }
            return nodeStack.top();
        }

        InOrderIterator &operator++() {
            if (!nodeStack.empty()) {
                Node<T> *node = nodeStack.top();
                nodeStack.pop();
                if (!node->children.empty()) {
                    pushLeftmostBranch(node->children[0]);
                }
            }
            return *this;
        }
        InOrderIterator &operator++(int) {
            InOrderIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const InOrderIterator &other) const {
            return nodeStack == other.nodeStack && current == other.current;
        }

        bool operator!=(const InOrderIterator &other) const {
            return !(*this == other);
        }

    private:
        void pushLeftmostBranch(Node<T> *node) {
            while (node) {
                nodeStack.push(node);
                if (!node->children.empty()) {
                    node = node->children[0];
                } else {
                    node = nullptr;
                }
            }
        }
    };

    template<typename T, int k>
    class BFSIterator {
    private:
        std::queue<Node<T> *> nodeQueue;
    public:
        BFSIterator(Node<T> *root) {
            if (root) nodeQueue.push(root);
        }

        BFSIterator(typename std::vector<Node<T>*>::iterator begin, typename std::vector<Node<T>*>::iterator end) {
            while (begin != end) {
                nodeQueue.push(*begin);
                ++begin;
            }
        }

        Node<T> &operator*() const {
            if (nodeQueue.empty()) {
                throw std::out_of_range("BFSIterator: Dereferencing an empty iterator");
            }
            return *nodeQueue.front();
        }

        Node<T> *operator->() const {
            if (nodeQueue.empty()) {
                throw std::out_of_range("BFSIterator: Dereferencing an empty iterator");
            }
            return nodeQueue.front();
        }

        BFSIterator &operator++() {
            if (!nodeQueue.empty()) {
                Node<T> *current = nodeQueue.front();
                nodeQueue.pop();
                for (auto child: current->children) {
                    nodeQueue.push(child);
                }
            }
            return *this;
        }

        bool operator==(const BFSIterator &other) const {
            return nodeQueue == other.nodeQueue;
        }

        bool operator!=(const BFSIterator &other) const {
            return !(*this == other);
        }
    };

    template<typename T, int k>
    class DFSIterator {
    private:
        std::stack<Node<T> *> nodeStack;
    public:
        DFSIterator(Node<T> *root) {
            if (root) nodeStack.push(root);
        }

        Node<T> &operator*() const {
            if (nodeStack.empty()) {
                throw std::out_of_range("DFSIterator: Dereferencing an empty iterator");
            }
            return *nodeStack.top();
        }

        Node<T> *operator->() const {
            if (nodeStack.empty()) {
                throw std::out_of_range("DFSIterator: Dereferencing an empty iterator");
            }
            return nodeStack.top();
        }

        DFSIterator &operator++() {
            if (!nodeStack.empty()) {
                Node<T> *current = nodeStack.top();
                nodeStack.pop();
                for (int i = current->children.size() - 1; i >= 0; --i) {
                    nodeStack.push(current->children[i]);
                }
            }
            return *this;
        }

        bool operator==(const DFSIterator &other) const {
            return nodeStack == other.nodeStack;
        }

        bool operator!=(const DFSIterator &other) const {
            return !(*this == other);
        }
    };

}

#endif //CPP_EX4_TREE_ITERATORS_H
