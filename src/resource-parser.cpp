#include "resource-parser.hpp"

#include "coral-engine.hpp"
#include "log.hpp"

namespace coral
{

ResourceParser::ResourceParser(CoralEngine &engine) : m_engine(engine) {};

template <typename T>
static std::optional<T> get_or_error(Variant node, std::string type)
{
    if (!std::holds_alternative<T>(node))
    {
        error("Property is not of type \"{}\".", type);
        return {};
    }

    return std::get<T>(node);
}

template <typename T>
static void parse_primitive(rapidxml::xml_node<> *node_tree, Variant node,
                            std::string type)
{

    std::optional<T *> property = get_or_error<T *>(node, type);

    if (!property.has_value())
    {
        return;
    }

    property.value()->assign(node_tree->value());
}

void ResourceParser::load_xml_node(rapidxml::xml_node<> *node_tree,
                                   Variant node)
{
    std::string type = node_tree->name();

    if (type == "List")
    {
        std::string list_type = node_tree->first_attribute("type")->value();

        if (list_type == "Node")
        {
            std::optional<std::vector<Node *> *> items =
                get_or_error<std::vector<Node *> *>(
                    node, std::format("{}<{}>", type, list_type));

            if (!items.has_value())
            {
                return;
            }

            for (rapidxml::xml_node<> *child = node_tree->first_node(); child;
                 child = child->next_sibling())
            {
                std::string child_type = child->name();
                std::optional<Node *> child_node =
                    m_engine.create_node(child_type);

                if (!child_node.has_value())
                {
                    return;
                }

                load_xml_node(child, &child_node.value());

                items.value()->push_back(child_node.value());
            }
        }
        return;
    }

    if (type == "String")
    {
        parse_primitive<std::string>(node_tree, node, type);
        return;
    }

    std::optional<Node **> scene_node = get_or_error<Node **>(node, type);

    if (!scene_node.has_value())
    {
        return;
    }

    for (rapidxml::xml_node<> *child = node_tree->first_node(); child;
         child = child->next_sibling())
    {
        rapidxml::xml_attribute<> *name_attribute =
            child->first_attribute("name");

        if (name_attribute == nullptr)
        {
            error("Children of resource must have a name attribute.");
            continue;
        }

        std::string name = name_attribute->value();

        std::optional<Variant> property = (**scene_node.value())[name];

        if (!property.has_value())
        {
            error("Property \"{}\" does not exist in {}.", name, type);
            continue;
        }

        load_xml_node(child, property.value());
    }
}

std::optional<std::string>
ResourceParser::get_attribute(rapidxml::xml_node<> *node,
                              std::string attribute_name)
{
    rapidxml::xml_attribute<> *attribute =
        node->first_attribute("attribute_name");

    if (attribute == nullptr)
    {
        return {};
    }

    return attribute->value();
}

} // namespace coral
