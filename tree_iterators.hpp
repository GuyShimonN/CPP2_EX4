#ifndef TREE_ITERATORS_HPP
#define TREE_ITERATORS_HPP

#include "node.hpp"
#include <queue>
#include <stack>

template <typename T, int K>
class Tree;

template <typename T, int K>
class PreOrderIterator {
private:
    std::stack<Node<T>*> stack;
public:
    PreOrderIterator(Node<T>* root) {
        if (root) stack.push(root);
    }
    bool has_next() const {
        return !stack.empty();
    }
    Node<T>* next() {
        Node<T>* node = stack.top();
        stack.pop();
        for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
            stack.push(*it);
        }
        return node;
    }
};

template <typename T, int K>
class PostOrderIterator {
private:
    std::stack<Node<T>*> stack;
    Node<T>* last_visited;
public:
    PostOrderIterator(Node<T>* root) {
        if (root) stack.push(root);
        last_visited = nullptr;
    }
    bool has_next() const {
        return !stack.empty();
    }
    Node<T>* next() {
        while (!stack.empty()) {
            Node<T>* current = stack.top();
            if (!current->children.empty() && last_visited != current->children.back()) {
                for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                    stack.push(*it);
                }
            } else {
                last_visited = current;
                stack.pop();
                return current;
            }
        }
        return nullptr;
    }
};

template <typename T, int K>
class InOrderIterator {
private:
    std::stack<Node<T>*> stack;
    Node<T>* current;
public:
    InOrderIterator(Node<T>* root) : current(root) {
        while (current && !current->children.empty()) {
            stack.push(current);
            current = current->children.front();
        }
    }
    bool has_next() const {
        return current || !stack.empty();
    }
    Node<T>* next() {
        while (current) {
            stack.push(current);
            if (!current->children.empty()) {
                current = current->children.front();
            } else {
                current = nullptr;
            }
        }
        current = stack.top();
        stack.pop();
        Node<T>* node = current;
        if (!current->children.empty()) {
            current = current->children.back();
        } else {
            current = nullptr;
        }
        return node;
    }
};

template <typename T, int K>
class BFSIterator {
private:
    std::queue<Node<T>*> queue;
public:
    BFSIterator(Node<T>* root) {
        if (root) queue.push(root);
    }
    bool has_next() const {
        return !queue.empty();
    }
    Node<T>* next() {
        Node<T>* node = queue.front();
        queue.pop();
        for (Node<T>* child : node->children) {
            queue.push(child);
        }
        return node;
    }
};

template <typename T, int K>
class DFSIterator {
private:
    std::stack<Node<T>*> stack;
public:
    DFSIterator(Node<T>* root) {
        if (root) stack.push(root);
    }
    bool has_next() const {
        return !stack.empty();
    }
    Node<T>* next() {
        Node<T>* node = stack.top();
        stack.pop();
        for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
            stack.push(*it);
        }
        return node;
    }
};

#endif // TREE_ITERATORS_HPP
