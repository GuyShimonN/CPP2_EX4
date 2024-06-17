//
// Created by guy on 6/17/24.
//

#ifndef CPP_EX4_TREE_ITERATORS_H
#define CPP_EX4_TREE_ITERATORS_H

#include <stack>
#include <queue>
#include "tree.hpp"

template <typename T, int k>
class PreOrderIterator {
private:
    std::stack<typename Tree<T, k>::Node*> nodeStack;
public:
    PreOrderIterator(typename Tree<T, k>::Node* root) {
        if (root) nodeStack.push(root);
    }
    typename Tree<T, k>::Node& operator*() const { return *nodeStack.top(); }
    typename Tree<T, k>::Node* operator->() const { return nodeStack.top(); }
    PreOrderIterator& operator++() {
        if (!nodeStack.empty()) {
            typename Tree<T, k>::Node* current = nodeStack.top();
            nodeStack.pop();
            for (int i = current->children.size() - 1; i >= 0; --i) {
                nodeStack.push(current->children[i]);
            }
        }
        return *this;
    }
    bool operator==(const PreOrderIterator& other) const {
        return nodeStack == other.nodeStack;
    }
    bool operator!=(const PreOrderIterator& other) const {
        return !(*this == other);
    }
};

template <typename T, int k>
class PostOrderIterator {
private:
    std::stack<typename Tree<T, k>::Node*> nodeStack;
    typename Tree<T, k>::Node* lastVisited;
public:
    PostOrderIterator(typename Tree<T, k>::Node* root) {
        lastVisited = nullptr;
        if (root) nodeStack.push(root);
    }
    typename Tree<T, k>::Node& operator*() const { return *nodeStack.top(); }
    typename Tree<T, k>::Node* operator->() const { return nodeStack.top(); }
    PostOrderIterator& operator++() {
        if (!nodeStack.empty()) {
            typename Tree<T, k>::Node* current = nodeStack.top();
            if (current->children.empty() || current->children.back() == lastVisited) {
                nodeStack.pop();
                lastVisited = current;
            } else {
                for (int i = current->children.size() - 1; i >= 0; --i) {
                    nodeStack.push(current->children[i]);
                }
            }
        }
        return *this;
    }
    bool operator==(const PostOrderIterator& other) const {
        return nodeStack == other.nodeStack && lastVisited == other.lastVisited;
    }
    bool operator!=(const PostOrderIterator& other) const {
        return !(*this == other);
    }
};

template <typename T, int k>
class InOrderIterator {
private:
    std::stack<typename Tree<T, k>::Node*> nodeStack;
public:
    InOrderIterator(typename Tree<T, k>::Node* root) {
        pushLeftmostBranch(root);
    }
    typename Tree<T, k>::Node& operator*() const { return *nodeStack.top(); }
    typename Tree<T, k>::Node* operator->() const { return nodeStack.top(); }
    InOrderIterator& operator++() {
        if (!nodeStack.empty()) {
            typename Tree<T, k>::Node* current = nodeStack.top();
            nodeStack.pop();
            if (current->children.size() > 1) {
                pushLeftmostBranch(current->children[1]);
            }
        }
        return *this;
    }
    bool operator==(const InOrderIterator& other) const {
        return nodeStack == other.nodeStack;
    }
    bool operator!=(const InOrderIterator& other) const {
        return !(*this == other);
    }
private:
    void pushLeftmostBranch(typename Tree<T, k>::Node* node) {
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

template <typename T, int k>
class BFSIterator {
private:
    std::queue<typename Tree<T, k>::Node*> nodeQueue;
public:
    BFSIterator(typename Tree<T, k>::Node* root) {
        if (root) nodeQueue.push(root);
    }
    typename Tree<T, k>::Node& operator*() const { return *nodeQueue.front(); }
    typename Tree<T, k>::Node* operator->() const { return nodeQueue.front(); }
    BFSIterator& operator++() {
        if (!nodeQueue.empty()) {
            typename Tree<T, k>::Node* current = nodeQueue.front();
            nodeQueue.pop();
            for (auto child : current->children) {
                nodeQueue.push(child);
            }
        }
        return *this;
    }
    bool operator==(const BFSIterator& other) const {
        return nodeQueue == other.nodeQueue;
    }
    bool operator!=(const BFSIterator& other) const {
        return !(*this == other);
    }
};

template <typename T, int k>
class DFSIterator {
private:
    std::stack<typename Tree<T, k>::Node*> nodeStack;
public:
    DFSIterator(typename Tree<T, k>::Node* root) {
        if (root) nodeStack.push(root);
    }
    typename Tree<T, k>::Node& operator*() const { return *nodeStack.top(); }
    typename Tree<T, k>::Node* operator->() const { return nodeStack.top(); }
    DFSIterator& operator++() {
        if (!nodeStack.empty()) {
            typename Tree<T, k>::Node* current = nodeStack.top();
            nodeStack.pop();
            for (int i = current->children.size() - 1; i >= 0; --i) {
                nodeStack.push(current->children[i]);
            }
        }
        return *this;
    }
    bool operator==(const DFSIterator& other) const {
        return nodeStack == other.nodeStack;
    }
    bool operator!=(const DFSIterator& other) const {
        return !(*this == other);
    }
};

#endif //CPP_EX4_TREE_ITERATORS_H