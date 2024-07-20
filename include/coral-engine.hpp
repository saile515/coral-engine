#pragma once

#include "node.hpp"
#include "resource-parser.hpp"
#include "typeless-vector.hpp"
#include "window.hpp"
#include <rapidxml.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace coral
{

struct NodeTypeInfo
{
    Node *(*constructor)();
    size_t size;
};

class CoralEngine
{
  public:
    ResourceParser resource;

  private:
    std::vector<Window> m_windows;
    std::unordered_map<std::string, TypelessVector> m_nodes;
    std::unordered_map<std::string, NodeTypeInfo> m_node_types;

  public:
    CoralEngine();

    void create_window();

    std::optional<Node *> create_node(std::string type);

    template <class NodeType>
    void register_node(std::string name);
};

template <class NodeType>
void CoralEngine::register_node(std::string name)
{
    static_assert(std::is_base_of<Node, NodeType>::value,
                  "NodeType must inherit from coral::Node.");
    m_node_types[name] = NodeTypeInfo{
        .constructor = reinterpret_cast<Node *(*)()>(&NodeType::create),
        .size = sizeof(NodeType)};
}

} // namespace coral
