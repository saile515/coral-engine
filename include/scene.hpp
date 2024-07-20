#pragma once

#include "node.hpp"
#include "resource.hpp"
#include <vector>

namespace coral
{

struct Scene : Resource
{
    std::vector<Node *> children;

    REFLECT(Scene)
};

} // namespace coral
