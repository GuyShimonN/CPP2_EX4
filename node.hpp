#ifndef CPP_EX4_NODE_H
#define CPP_EX4_NODE_H

#include <vector>

namespace ariel {
    template<typename T>
    class Node {
    public:
        T value;
        std::vector<Node<T> *> children;

        Node(T val) : value(val) {}

        ~Node() {}

        T get_value() const {
            return value;
        }
    };
}

#endif //CPP_EX4_NODE_H