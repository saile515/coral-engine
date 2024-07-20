#pragma once

#include <cstdlib>

namespace coral
{

class TypelessVector
{

  private:
    void *m_buffer;
    size_t m_size = 0;
    size_t m_capacity;
    size_t m_element_size;

  public:
    TypelessVector(size_t size);

    void push_back(void *value);

    void *back();
};

} // namespace coral
