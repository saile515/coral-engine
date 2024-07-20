#pragma once

#include "file.hpp"
#include "log.hpp"
#include "resource.hpp"
#include <rapidxml.h>
#include <string>
#include <type_traits>

namespace coral
{

class CoralEngine;

class ResourceParser
{
  private:
    CoralEngine &m_engine;

  public:
    ResourceParser(CoralEngine &engine);

    template <class ResourceType>
    std::optional<ResourceType> load(std::string path);

  private:
    void load_xml_node(rapidxml::xml_node<> *node_tree, Variant node);

    std::optional<std::string> get_attribute(rapidxml::xml_node<> *node,
                                             std::string attribute);
};

template <class ResourceType>
std::optional<ResourceType> ResourceParser::load(std::string path)
{
    static_assert(std::is_base_of<Resource, ResourceType>::value,
                  "ResourceType must inherit from coral::Resource.");
    std::string resource_source =
        read_file(std::string("resources/").append(path));

    rapidxml::xml_document document_tree;
    document_tree.parse<0>(resource_source.data());

    rapidxml::xml_node<> *resource_tree = document_tree.first_node();

    ResourceType resource;

    for (rapidxml::xml_node<> *child = resource_tree->first_node(); child;
         child = child->next_sibling())
    {
        rapidxml::xml_attribute<> *name_attribute =
            child->first_attribute("name");

        if (name_attribute == nullptr)
        {
            error("Children of resource must have a name attribute.");
            return {};
        }

        std::string name = name_attribute->value();

        std::optional<Variant> property = resource[name];

        if (!property.has_value())
        {
            error("Property \"{}\" does not exist in ResourceType.", name);
            return {};
        }

        load_xml_node(child, property.value());
    }

    return resource;
}

} // namespace coral
