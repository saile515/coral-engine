#include "coral-engine.hpp"

namespace coral
{

CoralEngine::CoralEngine() : resource(*this) {};

void CoralEngine::create_window() { m_windows.push_back(Window()); }

std::optional<Node *> CoralEngine::create_node(std::string type)
{
    if (!m_node_types.contains(type))
    {
        error(
            "Cannot create node of type \"{}\". Did you forget to register it?",
            type);
        return nullptr;
    }

    Node *node = m_node_types[type].constructor();

    if (!m_nodes.contains(type))
    {
        m_nodes.insert(
            std::make_pair(type, TypelessVector(m_node_types[type].size)));
    }

    m_nodes.at(type).push_back(node);

    free(node);

    Node *new_node = static_cast<Node *>(m_nodes.at(type).back());

    new_node->update_properties();

    return new_node;
}

} // namespace coral
