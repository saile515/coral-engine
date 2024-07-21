#include "typeless-vector.hpp"

#include "log.hpp"
#include <cstring>

namespace coral
{

TypelessVector::TypelessVector(size_t size) : m_element_size(size)
{
    m_buffer = calloc(8, size);
    m_capacity = 8;
}

void TypelessVector::push_back(void *value)
{
    if (m_size >= m_capacity)
    {
        void *new_buffer = realloc(m_buffer, m_capacity * 2 * m_element_size);

        if (new_buffer == nullptr)
        {
            error("TypelessVector re-allocation failed.");
            return;
        }

        m_capacity *= 2;
    }

    void *address =
        static_cast<unsigned char *>(m_buffer) + m_element_size * m_size;

    std::memcpy(address, value, m_element_size);

    m_size++;
}

void *TypelessVector::back()
{
    return static_cast<unsigned char *>(m_buffer) +
           (m_size - 1) * m_element_size;
}

} // namespace coral
