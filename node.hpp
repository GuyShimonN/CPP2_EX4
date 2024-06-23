#ifndef CPP_EX4_NODE_H
#define CPP_EX4_NODE_H

#include <vector>

namespace ariel {

    template<typename T>
    class Node {
    public:
        T value;
        std::vector<Node*> children;

        explicit Node(const T& val) : value(val) {}
    };

}

#endif //CPP_EX4_NODE_H