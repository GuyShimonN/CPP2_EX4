//
// Created by guy on 6/17/24.
//

#ifndef CPP_EX4_NODE_H
#define CPP_EX4_NODE_H

#include <vector>

template <typename T>
class Node {
public:
    T value;
    std::vector<Node<T>*> children;

    Node(T val) : value(val) {}
};

#endif //CPP_EX4_NODE_H