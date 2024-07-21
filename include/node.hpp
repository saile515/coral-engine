#pragma once

#include "reflection.hpp"

namespace coral
{

class Node
{
  public:
    std::vector<Node *> children;
    std::string name;

    template <typename T>
    static Node *create();

    REFLECT(Node)
};

template <typename T>
Node *Node::create()
{
    return new T();
}

} // namespace coral
