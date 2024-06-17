#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

template <typename T>
class Node {
public:
    T value;
    std::vector<Node<T>*> children;

    Node(T val) : value(val) {}
    ~Node() {
        for (auto child : children) {
            delete child;
        }
    }

    T get_value() const {
        return value;
    }
};

#endif // NODE_HPP
