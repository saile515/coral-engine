#pragma once

#include "vector3.hpp"
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace coral
{

class Node;

#define REFLECT(Struct)                                                        \
  protected:                                                                   \
    std::unordered_map<std::string, coral::Variant> m_properties;              \
                                                                               \
  public:                                                                      \
    Struct();                                                                  \
    std::optional<coral::Variant> operator[](std::string name);                \
    void update_properties();

#define START_REFLECTION(Struct)                                               \
    std::optional<coral::Variant> Struct::operator[](std::string name)         \
    {                                                                          \
        if (!m_properties.contains(name))                                      \
        {                                                                      \
            return {};                                                         \
        }                                                                      \
                                                                               \
        return m_properties[name];                                             \
    }                                                                          \
                                                                               \
    Struct::Struct() { update_properties(); }                                  \
                                                                               \
    void Struct::update_properties()                                           \
    {

#define REFLECT_PROPERTY(property)                                             \
    m_properties[#property] = coral::Variant(&property);

#define END_REFLECTION() }

typedef std::variant<double *, int *, bool *, std::string *, Vector3<double> *,
                     Node **, std::vector<Node *> *>
    Variant;

} // namespace coral
