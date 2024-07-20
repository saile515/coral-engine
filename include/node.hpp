#pragma once

#include "reflection.hpp"

namespace coral
{

class Node
{
  public:
    std::vector<Node *> children;
    std::string name;

    REFLECT(Node)
};

} // namespace coral
