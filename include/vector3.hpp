#pragma once

namespace coral
{

template <typename T = double>
class Vector3
{
  private:
    T m_x;
    T m_y;
    T m_z;

  public:
    void set(T x, T y, T z);

    void add_x(T x);
};

template <typename T>
void Vector3<T>::set(T x, T y, T z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

} // namespace coral
