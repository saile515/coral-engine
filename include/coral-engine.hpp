#pragma once

#include "node.hpp"
#include "resource.hpp"
#include "window.hpp"
#include <functional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace coral {

class CoralEngine {
  private:
    std::vector<Window> m_windows;
    std::unordered_map<std::string, std::function<Node()>> m_nodes;

  public:
    void create_window();

    template <class NodeType>
    void register_node(std::string name, std::function<NodeType()> constructor);

    template <class ResourceType>
    void load(std::string path);
};

template <class NodeType>
void CoralEngine::register_node(std::string name,
                                std::function<NodeType()> constructor) {
    static_assert(std::is_base_of<Node, NodeType>::value,
                  "NodeType must inherit from coral::Node.");
    m_nodes[name] = constructor;
}

template <class ResourceType>
void CoralEngine::load(std::string path) {
    static_assert(std::is_base_of<Resource, ResourceType>::value,
                  "ResourceType must inherit from coral::Resource.");
}

} // namespace coral
